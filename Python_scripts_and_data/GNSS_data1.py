import numpy as np
import os

file = (os.path.basename(__file__)).replace(".py", "")

def generate_random_coordinates(num_points, spread, x_mean, y_mean):
    # Generate random distances from the center following a normal distribution
    distances = np.random.normal(loc=0, scale=spread, size=num_points)

    # Generate random angles in radians
    angles = np.random.uniform(0, 2 * np.pi, size=num_points)

    # Convert polar coordinates to Cartesian coordinates
    x_coordinates = distances * np.cos(angles)
    x_coordinates += x_mean
    y_coordinates = distances * np.sin(angles)
    y_coordinates += y_mean

    # Scale the coordinate s to fit within the specified radius
    scaled_coordinates = np.column_stack((x_coordinates , y_coordinates ))
    return scaled_coordinates

# Set the param ters
num_points = 1000
spread = 0.0001
x_mean = 57
y_mean = 10

# Generate random coordinates with the specified mean
random_coordinates = generate_random_coordinates(num_points, spread, x_mean, y_mean)


# Save the coordinates to a CSV file in the same directory as the script
file_path = os.path.join(os.path.dirname(os.path.abspath(__file__)),file +'.csv')
np.savetxt(file_path, random_coordinates, delimiter=',', comments='')

print(f"Random coordinates saved to {file_path}")
