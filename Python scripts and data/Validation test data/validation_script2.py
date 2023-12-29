def process_data(input_file, output_file):
    # Open the input file for reading
    with open(input_file, 'r') as file:
        # Read lines from the file
        lines = file.readlines()

    # Process each line of data
    processed_data = []
    for line in lines:
        # Remove the "data: " string
        line = line.replace("data: ", "")

        # Split the line into two numbers
        num1, num2 = map(int, line.split(','))

        # Multiply each number by 10^(-7) and format with 7 decimals
        processed_num1 = format(num1 * 1e-7, '.7f')
        processed_num2 = format(num2 * 1e-7, '.7f')

        # Create the processed line and add it to the list
        processed_line = f"{processed_num1},{processed_num2}\n"
        processed_data.append(processed_line)

    # Open the output file for writing
    with open(output_file, 'w') as file:
        # Write the processed data to the output file
        file.writelines(processed_data)

# Example Usage
input_file_path = 'validation_test.txt'
output_file_path = 'validation_test_output.csv'
process_data(input_file_path, output_file_path)
