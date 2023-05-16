# BME280 Sensor with Lolin 32 Lite and Google Apps Script

This project demonstrates how to connect a BME280 sensor to a Lolin 32 Lite board and transfer the sensor data to Google Sheets using Google Apps Script. The BME280 sensor provides temperature, humidity, and pressure measurements, which can be recorded and stored in a Google Sheets spreadsheet for further analysis.

## Prerequisites

Before starting, make sure you have the following:

1. Lolin 32 Lite board
2. BME280 sensor
3. Arduino IDE or PlatformIO installed
4. Google account

## Hardware Setup

1. Connect the VCC pin of the BME280 sensor to the 3.3V pin on the Lolin 32 Lite board.
2. Connect the GND pin of the BME280 sensor to the GND pin on the Lolin 32 Lite board.
3. Connect the SDA pin of the BME280 sensor to the SDA (GPIO pin 21) pin on the Lolin 32 Lite board.
4. Connect the SCL pin of the BME280 sensor to the SCL (GPIO pin 22) pin on the Lolin 32 Lite board.

## Software Setup

1. Open the Arduino IDE or PlatformIO.
2. Install the required libraries for the BME280 sensor. You can use the "Adafruit BME280" library.
3. Connect the Lolin 32 Lite board to your computer via USB.
4. Select the appropriate board and port in the Arduino IDE or PlatformIO.
5. Open the code editor and copy the one of the two code we provide (depending on your usecase --> if you operate with a battery, we recommend using the code with Deep Sleep Modus)
6. Modify the code if necessary, such as adjusting the Wi-Fi credentials and Google Sheets configuration (see the exmaple file for Data Transmission with Google Apps Script).
7. Upload the code to the Lolin 32 Lite board.

## Google Apps Script Setup

1. Log in to your Google account.
2. Open Google Drive and create a new Google Sheets spreadsheet.
3. Open the spreadsheet and go to "Tools" -> "Script editor" to open Google Apps Script.
4. In the Google Apps Script editor, create a new script file and copy the code from `google_apps_script.gs` file.
5. Save the script and give it a meaningful name.
6. Go to "Publish" -> "Deploy as web app" to deploy the script as a web application.
7. Configure the web app settings, such as access permissions and deployment version.
8. Once deployed, copy the generated web app URL.
(you can find a more detailed guide here: https://iotdesignpro.com/articles/esp32-data-logging-to-google-sheets-with-google-scripts)

## Integration

1. Open the code editor for the Lolin 32 Lite board.
2. Locate the line in the code that sends data to the Google Sheets spreadsheet.
3. Replace the placeholder URL with the web app URL obtained from the Google Apps Script deployment.
4. Save the changes and upload the modified code to the Lolin 32 Lite board.
5. Power on the Lolin 32 Lite board and let it run.
6. The BME280 sensor will collect data, and the Lolin 32 Lite board will send it to the Google Sheets spreadsheet via the Google Apps Script web app.

## Data Visualization and Analysis

1. Open the Google Sheets spreadsheet where the data is being stored.
2. Use the built-in features of Google Sheets to visualize and analyze the collected sensor data.
3. Apply formulas, create charts, and generate reports based on the recorded temperature, humidity, and pressure measurements.
