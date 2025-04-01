import random
import time
import queue
import threading

# Compute checksum for packet
def compute_checksum(packet):
    return sum(packet) % 65536  # Keep within 16-bit range

# USART class to simulate transmission and reception with noise handling
class USART:
    def __init__(self, drop_rate=0.1, bit_flip_rate=0.05):
        self.tx_queue = queue.Queue()
        self.rx_queue = queue.Queue()
        self.drop_rate = drop_rate
        self.bit_flip_rate = bit_flip_rate
    
    # Write packet to the tx queue and simulate transmission
    def write(self, packet):
        time.sleep(0.1)  # Simulated transmission delay
        if random.random() < self.drop_rate:
            print("[USART] Packet dropped!")
            return
        packet = self.corrupt_packet(packet)
        self.rx_queue.put(packet)
    
    # Read packet from the rx queue, simulating a delay and packet loss
    def read(self, expected_length, timeout=2):
        start_time = time.time()
        while time.time() - start_time < timeout:
            time.sleep(0.1)  # Simulated processing delay
            if not self.rx_queue.empty():
                packet = self.rx_queue.get()
                return packet if len(packet) == expected_length else None
        return None  # Timeout

    # Corrupt packet by randomly flipping a bit in one byte
    def corrupt_packet(self, packet):
        corrupted = bytearray(packet)
        if random.random() < self.bit_flip_rate:
            byte_index = random.randint(0, len(corrupted) - 1)
            bit_index = random.randint(0, 7)
            corrupted[byte_index] ^= (1 << bit_index)
            print(f"[USART] Bit flipped in packet at index {byte_index}, bit {bit_index}")
        return bytes(corrupted)

# DMA transmit simulates direct memory access transmission
def dma_transmit(usart, packet):
    time.sleep(0.05)  # Simulated DMA delay
    usart.write(packet)  # Write the packet to the USART for transmission

# DMA receive simulates direct memory access reception
def dma_receive(usart, expected_length, timeout=2):
    packet = usart.read(expected_length, timeout)
    return packet

# Sender function to send data in chunks
def tcp_send(data, usart):
    index = 0
    seq_num = 0
    ack_num = 0
    max_retries = 3  # Max retries for each packet
    
    while index < len(data):
        chunk = data[index:index + 28]  # Chunk size of 28 bytes
        padding = 28 - len(chunk)
        packet = bytearray([seq_num, ack_num, 0, 0] + list(chunk) + [0] * padding)
        checksum = compute_checksum(packet)
        packet[2] = checksum >> 8  # High byte
        packet[3] = checksum & 0xFF  # Low byte
        
        print(f"[Sender] Sending SEQ={seq_num}, Checksum={checksum:04X}, Data={chunk}")
        dma_transmit(usart, packet)  # Send the packet
        
        retries = 0
        while retries < max_retries:
            ack_packet = dma_receive(usart, 32, timeout=2)  # Receive ACK
            if ack_packet and ack_packet[0] == seq_num:
                seq_num = (seq_num + 1) % 256
                index += 28
                break
            else:
                print("[Sender] Retransmitting due to missing/invalid ACK")
                retries += 1
                time.sleep(0.5)  # Delay before retransmission
        if retries == max_retries:
            print("[Sender] Max retries reached, moving to next packet.")
    
    # Send End of Transmission (EOT) packet
    eot_packet = bytearray([255, ack_num, 0, 0] + [0] * 28)  # Special SEQ=255 indicates EOT
    eot_checksum = compute_checksum(eot_packet)
    eot_packet[2] = eot_checksum >> 8
    eot_packet[3] = eot_checksum & 0xFF
    print("[Sender] Sending EOT packet SEQ=255")
    
    retries = 0
    while retries < max_retries:
        dma_transmit(usart, eot_packet)  # Send EOT packet
        ack_packet = dma_receive(usart, 32, timeout=2)  # Receive EOT ACK
        if ack_packet and ack_packet[0] == 255:
            print("[Sender] EOT ACK received.")
            break
        else:
            print("[Sender] Retransmitting EOT packet due to missing/invalid ACK")
            retries += 1
            time.sleep(0.5)  # Delay before retransmission
    
    if retries == max_retries:
        print("[Sender] Max retries reached for EOT, ending transmission.")

# Receiver function to receive data
def tcp_receive(usart):
    buffer = bytearray()
    expected_seq = 0
    
    while True:
        incoming_packet = dma_receive(usart, 32, timeout=2)  # Receive packet
        if not incoming_packet:
            continue
        
        seq_num = incoming_packet[0]
        
        # Check for EOT packet
        if seq_num == 255:  # End of Transmission (EOT) detected
            print("[Receiver] EOT packet received. Ending reception.")
            break
        
        received_checksum = (incoming_packet[2] << 8) | incoming_packet[3]
        data = incoming_packet[4:32]
        
        temp_packet = bytearray(incoming_packet)
        temp_packet[2] = 0
        temp_packet[3] = 0
        computed_checksum = compute_checksum(temp_packet)
        
        if received_checksum != computed_checksum:
            print("[Receiver] Checksum mismatch! Ignoring packet.")
            continue
        
        if seq_num == expected_seq:
            buffer.extend(data)
            expected_seq = (expected_seq + 1) % 256
        
        ack_packet = bytearray([seq_num, expected_seq, 0, 0] + [0] * 28)
        ack_checksum = compute_checksum(ack_packet)
        ack_packet[2] = ack_checksum >> 8
        ack_packet[3] = ack_checksum & 0xFF
        dma_transmit(usart, ack_packet)  # Send ACK
        
        if len(data) < 28:
            break  # End of transmission
    
    received_message = buffer.decode(errors='ignore')
    print("[Receiver] Full message received:", received_message)
    return received_message

# Main function to simulate the communication
usart = USART(drop_rate=0.1, bit_flip_rate=0.05)
message = b"Hello, this is a test message with noise handling!"

# Simulating a delay in starting the receiver (receiver initially off)
def delayed_receiver_start():
    print("[Receiver] Waiting to start receiver...")
    time.sleep(3)  # Simulate receiver being off for 3 seconds
    receive_thread = threading.Thread(target=tcp_receive, args=(usart,))
    receive_thread.start()
    return receive_thread

# Start the sender and receiver threads
send_thread = threading.Thread(target=tcp_send, args=(message, usart))
receive_thread = delayed_receiver_start()  # Delay the start of receiver

send_thread.start()
receive_thread.join()  # Wait for receiver to finish
send_thread.join()

print("[Main] Transmission and reception complete.")
