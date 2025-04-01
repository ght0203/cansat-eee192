import threading
import time
import queue

# Simulate Transmitter
def transmitter(data_queue):
    # Example data to send
    data_to_send = ["Hello", "How are you?", "This is a test", "Goodbye"]
    
    for message in data_to_send:
        print(f"Transmitting message: {message}")
        data_queue.put(message)  # Place data in the queue
        time.sleep(1)  # Simulate transmission delay

# Simulate Receiver
def receiver(data_queue):
    while True:
        # Wait for data in the queue
        data_received = data_queue.get()
        if data_received == "END":
            break  # Stop the receiver thread when "END" message is received
        print(f"Receiving message: {data_received}")
        time.sleep(1.5)  # Simulate receiving delay

# Create a queue for data transmission
data_queue = queue.Queue()

# Create transmitter and receiver threads
transmitter_thread = threading.Thread(target=transmitter, args=(data_queue,))
receiver_thread = threading.Thread(target=receiver, args=(data_queue,))

# Start the threads
transmitter_thread.start()
receiver_thread.start()

# Wait for the transmitter thread to finish
transmitter_thread.join()

# Send a termination message for the receiver thread to stop
data_queue.put("END")

# Wait for the receiver thread to finish
receiver_thread.join()

print("Simulation complete!")
