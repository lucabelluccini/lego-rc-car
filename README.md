# Lego RC Car (work in progress)

Remote controlled Lego RC Car with onboard camera (e.g. LEGO 42065 Tracked Racer).

See this [gist](https://gist.github.com/lucabelluccini/23d5954faed92bd11597e6be6fbfe0d2) for more info.

The long term implementation would be to have a WebRTC Lego RC Car.
I'm checking what is the best implementation out there to proceed.

In the meanwhile, this prototype implementation is required to validate the feasibility of the solution.

The architecture could be simplified using [LIRC](http://www.lirc.org/) and irsend (thanks to [lego-lirc](https://github.com/iConor/lego-lirc)), removing the need of an arduino compatible board. But I do not like the need to setup the lirc daemon just for sending few commands.

I'll check if it is feasible to use the following [library](https://github.com/bschwind/ir-slinger), really well detailed explaination at this [page](http://blog.bschwind.com/2016/05/29/sending-infrared-commands-from-a-raspberry-pi-without-lirc/).

## Current architecture

* The user can access the RC car web ui over HTTP
* The web ui sends the driving directions via websocket
* The server handling the websocket forwards the driving directions via serial port
* The arduino compatible board reads the driving directions and sends them via infrared
* The LEGO 42065 Tracked Racer has an embedded IR receiver and receives the directions

## Current hardware requirements

* Raspberry Pi 3 or Zero W (any other battery powered board is potentially compatible)
* Raspicam (or any compatible camera)
* Any Arduino board or ESP8266 or ESP32 (for a compact board with RpiZeroW, [ESP IoT pHat](https://github.com/pimoroni/espiot-phat)
* An IR Led and a resistor

## Current features

* Live streaming via HTTP of MJPEG stream coming from CSI-2
* Web UI to control the car
* 7 different speed steps per DC motor, per direction, via PWM

## Current external dependencies

* [Lego power functions library for Arduino](https://github.com/jurriaan/Arduino-PowerFunctions)
* [Streameye for RPi](https://github.com/ccrisan/streameye)
* [Gorilla/websocket for Go](github.com/gorilla/websocket)
* [Serial for Go](go.bug.st/serial.v1)
* [Arduino CLI](https://github.com/arduino/arduino-cli)
* [Arduino ESP8266](https://github.com/esp8266/Arduino)

## Useful links related to Pimoroni ESP IoT pHat

* https://github.com/pimoroni/espiot-phat
* https://learn.pimoroni.com/tutorial/hal13/micropython-on-esp-iot-phat
* https://learn.pimoroni.com/tutorial/hal13/getting-started-with-iot-phat
* https://techhobbynotes.blogspot.com/2017/04/programming-esp8266-phat-from-raspberry.html

## How to run

```
# Install Go & dependencies
# Flash the Arduino sketch on your Arduino compatible board
# Install Streameye and run the following command
./raspimjpeg.py -w 1280 -h 720 -r 60 -q 10  | ../streameye
# Connect the Arduino board via USB & check which port it is using via dmesg
# Start the controller
go run legorc.go
```

## How to build and upload the sketch on Arduino

To install latest version of Go
```
url=`curl https://golang.org/dl/ | grep armv6l | sort --version-sort | tail -1 | grep -o -E https://dl.google.com/go/go[0-9]+\.[0-9]+((\.[0-9]+)?).linux-armv6l.tar.gz` 
wget ${url}
sudo tar -C /usr/local -xvf `echo ${url} | cut -d '/' -f5`
cat >> ~/.bashrc << 'EOF'
export GOPATH=$HOME/go
export PATH=/usr/local/go/bin:$PATH:$GOPATH/bin
EOF
source ~/.bashrc
```

In case you are on a RPi Zero W and you end up with no more virtual memory:

```
# Set CONF_SWAPSIZE=1024 in /etc/dphys-swapfile
sudo /etc/init.d/dphys-swapfile stop
sudo /etc/init.d/dphys-swapfile start
```

To disable HDMI:
```
/usr/bin/tvservice -o # add it to /etc/rc.local for permanent 
```

To disable Wireless power management:
```
wireless-power off # to be added to /etc/network/interfaces
```

Install the tools:

- Download [arduino-cli](https://github.com/arduino/arduino-cli) and add it in your `$PATH`
- Download [Arduino Power Functions library](https://github.com/jurriaan/Arduino-PowerFunctions) and install them in `~/Arduino/libraries`
- Download [espiot-phat tools](https://github.com/pimoroni/espiot-phat)

Add the support for ESP8266 to Arduino:

```
echo << EOF > ~/.cli-config.yml
board_manager:
  additional_urls:
    - http://arduino.esp8266.com/stable/package_esp8266com_index.json
EOF

arduino-cli core update-index
arduino-cli core install esp8266:esp8266
```

Prepare the sketch in this repo and store it in `~/Arduino/legorc/legorc.ino`.

To build for ESP8266:

```
arduino-cli compile --fqbn esp8266:esp8266:nodemcu ~/Arduino/legorc
```

To upload:

```
# Run ~/Pimoroni/espiotphat/firmware/espflash.py in a separate shell
arduino-cli upload -p /dev/ttyAMA0 --fqbn esp8266:esp8266:nodemcu ~/Arduino/legorc
# Stop espflash.py
# Run espreset.py
```
