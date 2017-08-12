# HomeDHT: A clean and lean DHT22 web application

1. HW

You need a DHT22 sensor, a 10k pull up resistor, wires, solder, connector pins and heat shrink tube for this project.

2. Sketch

Copy the content under the Sketch/ folder into your Arduino sketch folder.

Launch the Arduino IDE.

If it's not installed already, install the DHT sensor library by Adafruit using the Library Manager.

Upload the sketch to your Yún.

3. HW hookup

Make sure the pull up is in place.

Connect the data line of the DHT22 to Pin 2 on the Yún.

Connect the Vcc and GND leads of the DHT22 to the 5V and GND female header connectors on the Yún respectively.

4. Web application

Copy the content under Web/ to /mnt/sda1/arduino/www/WebDHT/ on your Yún.

If the SD card is not setup yet, you may want to read this description first.
[Extending the disk space on your Yún](https://github.com/imrehorvath/ArduinoYun#extending-the-disk-space)

5. Usage

You can navigate to http://arduino.local/sd/WebDHT/ to see the readings on your local network with your smartphone, tablet or desktop computer.

(c) Imre Horvath 2017
