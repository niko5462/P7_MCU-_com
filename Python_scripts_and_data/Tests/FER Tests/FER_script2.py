def load_data(file_path):
    with open(file_path, 'r') as file:

        data = [line.replace('Data sent: ', '').strip().split(',') for line in file]
        # Filter out empty lines or lines with an unexpected number of el
        # data = [line for line in data if len(line) == 3
    return data

def calculate_fer(sent_data_file, received_data_file):
    # Load sent data
    sent_data = load_data(sent_data_file)

    # Load received data
    received_data = load_data(received_data_file)

    total_frames = max(len(sent_data), len(received_data))
    error_count = 0
    error_indices = []

    for i in range(total_frames):
        # Check if the received fme matches the sent fram
        sent_frame = sent_data[i] if i < len(sent_data) else None
        received_frame = received_data[i] if i < len(received_data) else None

        if sent_frame != received_frame:
            error_count += 1
            error_indices.append(i)

    fer = error_count / total_frames
    return fer, error_indices

def main():
    sent_data_file = 'Logging100k.csv'  # Chang tis to the actual file name
    received_data_file = 'Logging100k-receive.csv'  # Change this to the actual file name

    fer, error_indices = calculate_fer(sent_data_file, received_data_file)

    print(f"Total Frames: {max(len(load_data(sent_data_file)), len(load_data(received_data_file)))}")
    print(f"Frame Error Rate (FER): {fer * 100:.2f}%")

    if fer > 0:
        print(f"Error Indices: {error_indices}")

if __name__ == "__main__":
    main()
