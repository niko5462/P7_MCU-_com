def calculate_fer(sent_data_file, received_data_file):
    # Load sent data
    with open(sent_data_file, 'r') as file:
        sent_data = [line.strip().split(',') for line in file]

    # Load received data
    with open(received_data_file, 'r') as file:
        received_data = [line.strip().split(',') for line in file]

    total_frames = len(sent_data)
    error_count = 0
    error_indices = []

    for i in range(total_frames):
        # Check if the received frame matches the sent frame
        if i < len(received_data):
            if sent_data[i] != received_data[i]:
                error_count += 1
                error_indices.append(i)
        else:
            # If there are more sent frames than received frames, consider them as errors
            error_count += 1
            error_indices.append(i+1)

    fer = error_count / total_frames
    return fer, error_indices

def main():
    sent_data_file = 'Position logging data.csv'  # Change this to the actual file name
    received_data_file = 'Link logging data.csv'  # Change this to the actual file name

    fer, error_indices = calculate_fer(sent_data_file, received_data_file)

    print(f"Total Frames: {len(open(sent_data_file).readlines())}")
    print(f"Frame Error Rate (FER): {fer * 100:.2f}%")

    if fer > 0:
        print(f"Error Indices: {error_indices}")

if __name__ == "__main__":
    main()
