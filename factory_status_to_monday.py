import csv
import serial
import time
from datetime import datetime, timedelta
import os
import yagmail
from twilio.rest import Client
import smtplib
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText

Range_Dict = {"Temperature_larvae":(28.0, 31.0), "Temperature_adults":(27.0, 30.0), "Humidity_adults": (60.0, 85.0)}
last_sms_sent_date = None
# Initialize your min and max temperatures to None
min_temperature_larvae, max_temperature_larvae = None, None
min_temperature_adults, max_temperature_adults = None, None
def send_email(issue):
    yag = yagmail.SMTP('themosquitoesassociation@gmail.com', 'uyqlsubglvmfjxgi')
    yag.send(
        to='yfantys@gmail.com',
        subject='Facility issue alert',
        contents=issue,
    )

def send_sms():
    global last_sms_sent_date

    today_date = datetime.now().date()

    # If the last SMS was not sent today, you can send another SMS
    if last_sms_sent_date is None or last_sms_sent_date != today_date:
        last_sms_sent_date = today_date  # Update the date when the last SMS was sent

        account_sid = 'AC4adabbfdb849ecc0dbb0eb855351f69f'
        auth_token = '13bcbed89c4545f5eea5571875296dea'
        client = Client(account_sid, auth_token)

        message = client.messages.create(
            from_='+18142598705',
            body="We, The Mosquitoes Congress, remind you of lowering the temperature as it's your duty.\n It's damn hot!!",
            to='+972585522362'
        )
        print('Message sent successfully.')


def handle_out_of_range(parameter, value):
    # This function will be called when a parameter is out of the specified range
    # Append the data to out_of_range.csv
    line = [datetime.now().strftime("%Y-%m-%d %H:%M:%S"), parameter, value]
    body = f'Out of range Alert!\n\nTime: {line[0]}\nParameter: {line[1]}\nValue: {line[2]}'
    try:
        send_email(body)
        send_sms()
    except Exception as e:
        print(f"Failed to send alert: {e}")

    with open('out_of_range.csv', 'a', newline='') as file:
        writer = csv.writer(file)
        writer.writerow(line)

def write_csv(file_path, data):
    with open(file_path, 'w', newline='') as file:
        writer = csv.writer(file)
        writer.writerows(data)

def main():
    global min_temperature_larvae, max_temperature_larvae, min_temperature_adults, max_temperature_adults

    last_recorded_time = datetime.now() - timedelta(minutes=30)
    start_time = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    file_path = f'recordings_started_at_{start_time}.csv'

    # Create the CSV file if it doesn't exist and write the headers
    if not os.path.isfile(file_path):
        write_csv(file_path, [['Time', 'Adults Room Temperature', 'Adults Room Humidity', 'Larvae Room Temperature', 'Max Larvae', 'Min Larvae', "Max Adults", "Min Adults"],
                              ['', '', '', '', '', '']])
    # Create out_of_range.csv if it doesn't exist
    if not os.path.isfile(f'oor_started_at_{start_time}.csv'):
        with open('oor_started_at_{start_time}.csv', 'w', newline='') as file:
            writer = csv.writer(file)
            writer.writerow(['Time', 'Parameter', 'Value'])

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
            min_temperature_adults = min(adults_temperature,
                                         min_temperature_adults) if min_temperature_adults is not None else adults_temperature
            max_temperature_adults = max(adults_temperature,
                                         max_temperature_adults) if max_temperature_adults is not None else adults_temperature

            min_temperature_larvae = min(larvae_temperature,
                                         min_temperature_larvae) if min_temperature_larvae is not None else larvae_temperature
            max_temperature_larvae = max(larvae_temperature,
                                         max_temperature_larvae) if max_temperature_larvae is not None else larvae_temperature
            # Get the current time
            now = datetime.now()

            # Print the current time and measurements
            print(f'Measurements at: [{now.strftime("%Y-%m-%d %H:%M:%S")}]\n')
            print(f'Adults Room Temperature: {adults_temperature:.2f}°C\n')
            print(f'Adults Room Humidity: {adults_humidity:.2f}%\n')
            print(f'Larvae Room Temperature: {larvae_temperature:.2f}°C\n')
            # Load the existing data
            with open(file_path, 'r') as file:
                data = list(csv.reader(file))
            # Update min and max temperature in the first row
            data[1][6], data[1][7] = max_temperature_adults, min_temperature_adults
            data[1][4], data[1][5] = max_temperature_larvae, min_temperature_larvae
            if not Range_Dict["Temperature_larvae"][0] <= larvae_temperature <= Range_Dict["Temperature_larvae"][1]:
                handle_out_of_range("Temperature_larvae", larvae_temperature)

            if not Range_Dict["Temperature_adults"][0] <= adults_temperature <= Range_Dict["Temperature_adults"][1]:
                handle_out_of_range("Temperature_adults", adults_temperature)

            if not Range_Dict["Humidity_adults"][0] <= adults_humidity <= Range_Dict["Humidity_adults"][1]:
                handle_out_of_range("Humidity_adults", adults_humidity)
            # Write to CSV every 30 minutes
            if (now - last_recorded_time) >= timedelta(minutes=30):
                # Append the new row
                data.append([now.strftime("%Y-%m-%d %H:%M:%S"), adults_temperature, adults_humidity, larvae_temperature, '', '', '', ''])
                last_recorded_time = now
            # Write the data back to the CSV
            write_csv(file_path, data)
        except serial.SerialException as e:
            print(f"Error reading from serial port: {e}")
            time.sleep(10)  # Sleep before trying to read again

        time.sleep(5*60)  # Wait for 5 minutes before reading again

if __name__ == "__main__":
    # main()
