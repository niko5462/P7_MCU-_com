def calculate_non_matching_lines(original_data, received_data):
    with open(original_data, 'r') as file_original, open(received_data, 'r') as file_received:

        lines_original = [line.replace('Data sent: ', '').strip().split(',') for line in file_original]
        lines_received = [line.strip().split(',') for line in file_received]

        non_matching_lines_count = 0

        # Check each line in the original f
        for line in lines_original:
            # Check if the line has a match in the received file
            if line not in lines_received:
                non_matching_lines_count += 1

        return lines_original, lines_received, non_matching_lines_count

def calculate_fer(sent_data, received_data, error_count):
    total_frames = max(len(sent_data), len(received_data))
    fer = (error_count / total_frames) * 100
    return fer,total_frames

if __name__ == "__main__":
    # Specify the paths to the original and received data files
    original_data_path = "Logging100k.csv"
    received_data_path = "Logging100k-receive.csv"

    # Calculate non-matching lin
    sent_data,received_data,nmlc = calculate_non_matching_lines(original_data_path, received_data_path)

    fer,total_frames = calculate_fer(sent_data, received_data, nmlc)

    print(f"Total Frames: {total_frames}")
    print(f"Number of packages that does not match in the received file: {nmlc}")
    print(f"Frame Error Rate (FER): {fer:.2f}%")