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
* Any Arduino board or ESP8266 or ESP32
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