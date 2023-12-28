import numpy as np
import matplotlib.pyplot as plt
import os
import math

file = (os.path.basename(__file__)).replace(".py", "")
filepath = os.path.dirname(__file__) + '/'
fig = plt.figure()
ax1 = fig.add_subplot()

# DEFINE THE COLLOR
r = 'r'
p = 'purple'
c = 'cyan'

cep_radius = 0

# Specify the path to your data file
file_path = 'GNSS_data_test.csv'
# Read data from the file
data = np.genfromtxt(file_path, delimiter=',', skip_header=1)
y, x = data[:, 0], data[:, 1]


def calculate_and_plot_cep(x, y, color, percentage):
    # Calculate mean f x and y
    mean_x, mean_y = np.mean(x), np.mean(y)
    # Calculate distances from the mean for each point
    distances = np.sqrt((x - mean_x)**2 + (y - mean_y)**2)
    # Sort distances
    sorted_distances = np.sort(distances)
    # Find the distance that corresponds to the given probability
    cep_radius = sorted_distances[int(percentage/100 * len(sorted_distances))]
    # Calculating
    radius_meter = haversine([0.0, 0.0], [cep_radius, 0.0])
    # Make the circle instance
    circle = plt.Circle((np.mean(x), np.mean(y)), cep_radius, edgecolor=color, facecolor='none', label='CEP '+str(percentage)+'% \n r = '+str(radius_meter)+' m')
    # Plot CEP
    plt.gca().add_patch(circle)

def haversine(coord1: object, coord2: object):
    # Coordinates in decimal degrees (e.g. 2.89078, 12.79797)
    lon1, lat1 = coord1
    lon2, lat2 = coord2

    R = 6371000  # radius of Earth in meters
    phi_1 = math.radians(lat1)
    phi_2 = math.radians(lat2)

    delta_phi = math.radians(lat2 - lat1)
    delta_lambda = math.radians(lon2 - lon1)

    a = math.sin(delta_phi / 2.0) ** 2 + math.cos(phi_1) * math.cos(phi_2) * math.sin(delta_lambda / 2.0) ** 2

    c = 2 * math.atan2(math.sqrt(a), math.sqrt(1 - a))

    meters = R * c  # output distance in meters
    meters = round(meters, 2)
    return meters
    # meters = round(meters, 3)

def plot_data(x,y):
    # Plot the data points
    ax1.scatter(x, y, label='Data Points', s = 4)

def main():
    # Plot data and CEP circle
    plot_data(x,y)

    # Calculate Circular Error Probability (CEP) radius
    # Plot data and CEP circle
    calculate_and_plot_cep(x, y, r, 50)
    calculate_and_plot_cep(x, y, p, 70)
    calculate_and_plot_cep(x, y, c, 95)

if __name__ == "__main__":
    main()

    # Set all the axis and define the plots
    ax1.set_xlabel('lattitude')
    ax1.set_ylabel('longitude')
    ax1.set_title('Data Points and CEP Circle')
    ax1.legend()

    ax1.axis('equal')

    #ax1.set_xlim(min(x), max(x)+0.001)
    #ax1.set_ylim(min(y), max(y)+0.001)

    #ax1.set_xticks(np.linspace(min(x), max(x),5))
    #ax1.set_yticks(np.linspace(min(y), max(y),5))
    ax1.ticklabel_format(useOffset=False)
    ax1.ticklabel_format(useMathText=True)


    fig.tight_layout()
    fig.savefig(filepath + file + ".pdf", format="pdf")
