
def load_data(file_path):
    with open(file_path, 'r') as file:
        data = [line.replace('Data sent: ', '').strip().split(',') for line in file]
        # Filter out empty lines or lines with an unexpected number of el
        # data = [line for line in data if len(line) == 3
    return data

def check_line_match(original_data, received_data, total_frames):
    match = 0
    for i in range(total_frames):
        for j in range(total_frames):
            if original_data[i] == received_data[j]:
                match += 1
    return match


if __name__ == "__main__":
    # Specify the paths to the original and received data fi
    original_data_path = "Logging10k.csv"
    received_data_path = "Logging10k-receive.csv"

    # Load sent data
    sent_data = load_data(original_data_path)

    # Load received data
    received_data = load_data(received_data_path)

    print(check_line_match(sent_data, received_data, len(sent_data)))

    # Calculate FER
    fer_result = ((len(sent_data)-check_line_match(sent_data, received_data, len(sent_data)))/len(sent_data))*100

    if fer_result is not None:
        print(f"Frame Error Rate (FER): {fer_result:.2f}%")
