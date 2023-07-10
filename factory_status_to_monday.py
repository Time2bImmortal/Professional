import csv
import serial
import time
from datetime import datetime, timedelta
import os

# Define your temperature range
TEMPERATURE_RANGE = (27.0, 31.0)

# Initialize your min and max temperatures to None
min_temperature = None
max_temperature = None

def temperature_out_of_range(temperature, temperature_range):
    return not (temperature_range[0] <= temperature <= temperature_range[1])

def handle_temperature_out_of_range(temperature):
    # This function will be called when the temperature is out of the specified range
    # Append the data to out_of_range.csv
    with open('out_of_range.csv', 'a', newline='') as file:
        writer = csv.writer(file)
        writer.writerow([datetime.now().strftime("%Y-%m-%d %H:%M:%S"), temperature])

def write_csv(file_path, data):
    with open(file_path, 'w', newline='') as file:
        writer = csv.writer(file)
        writer.writerows(data)

def main():
    global min_temperature, max_temperature

    # Initialize the last recorded time to one hour ago
    last_recorded_time = datetime.now() - timedelta(minutes=30)

    file_path = 'recordings.csv'
    start_time = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

    # Create the CSV file if it doesn't exist and write the headers
    if not os.path.isfile(file_path):
        write_csv(file_path, [['Start', 'Time', 'Adults Room Temperature', 'Adults Room Humidity', 'Larvae Room Temperature', 'Max Temperature', 'Min Temperature'],
                              [start_time, '', '', '', '', '', '']])
    # Create out_of_range.csv if it doesn't exist
    if not os.path.isfile('out_of_range.csv'):
        with open('out_of_range.csv', 'w', newline='') as file:
            writer = csv.writer(file)
            writer.writerow(['Time', 'Temperature'])

    ser = serial.Serial('COM9', 9600)  # Open the serial port

    time.sleep(2)  # Wait for the Arduino to initialize

    while True:
        try:
            # Read the data from the serial port
            data = ser.readline().decode().strip()

            # Split the data into temperature and humidity values
            values = data.split(',')
            if len(values) != 3:
                print(f"Unexpected data format: {data}")
                continue

            try:
                adults_temperature = float(values[0])
                adults_humidity = float(values[1])
                larvae_temperature = float(values[2])
            except ValueError:
                print(f"Unable to convert data to float: {values}")
                continue

            # Update the min and max temperatures if necessary
            temperatures = [adults_temperature, larvae_temperature]
            min_temperature = min(temperatures) if min_temperature is None else min(min_temperature, min(temperatures))
            max_temperature = max(temperatures) if max_temperature is None else max(max_temperature, max(temperatures))

            # Get the current time
            now = datetime.now()

            # Print the current time and measurements
            print(f'[{now.strftime("%Y-%m-%d %H:%M:%S")}] Current measurements:')
            print(f'Adults Room Temperature: {adults_temperature:.2f}°C')
            print(f'Adults Room Humidity: {adults_humidity:.2f}%')
            print(f'Larvae Room Temperature: {larvae_temperature:.2f}°C')

            # Check if the temperature is out of range and call the appropriate function if it is
            if temperature_out_of_range(larvae_temperature, TEMPERATURE_RANGE):
                handle_temperature_out_of_range(larvae_temperature)

            # Load the existing data
            with open(file_path, 'r') as file:
                data = list(csv.reader(file))

            # Update min and max temperature in the first row
            data[1][5] = max_temperature
            data[1][6] = min_temperature

            # Write to CSV every 30 minutes
            if (now - last_recorded_time) >= timedelta(minutes=30):
                # Append the new row
                data.append(['', now.strftime("%Y-%m-%d %H:%M:%S"), adults_temperature, adults_humidity, larvae_temperature, '', ''])
                last_recorded_time = now

            # Write the data back to the CSV
            write_csv(file_path, data)

        except serial.SerialException as e:
            print(f"Error reading from serial port: {e}")
            time.sleep(10)  # Sleep before trying to read again

        time.sleep(5*60)  # Wait for 5 minutes before reading again

if __name__ == "__main__":
    main()
