# Lego RC Car enhancement based on LEGO 42065 Tracked Racer

Original product: [LEGO 42065 Tracked Racer](https://www.eurobricks.com/forum/index.php?/forums/topic/145708-review-42065-tracked-racer/)

## Video streaming

* [MJPEG Streamer for Linux](https://github.com/ccrisan/streameye) is a simple HTTP MJPEG streamer for RPi

## WebRTC and RPi open source

* [Webrtc.org Rpi camera streamer](https://github.com/kclyu/rpi-webrtc-streamer) is a native daemon implementing Webcam server
* [Webrtc streamer using Janus](https://www.rs-online.com/designspark/building-a-raspberry-pi-2-webrtc-camera) using Janus & raspivid + gstreamer
* [Webrtc streamer from v4l2 or rtsp](https://github.com/mpromonet/webrtc-streamer)
* [Build Gstreamer using Cerbero in Docker](https://gist.github.com/maxmcd/a83af48c453141502404f73d1dbf5ea9)

### Rpi-WebRTC-Streamer

Dockerfile for RPi/RPiZero

```
FROM resin/rpi-raspbian

ARG RWS_DEB_URL=https://github.com/kclyu/rpi-webrtc-streamer-deb/raw/master/rws_0.73.1_RaspiZeroW_armhf.deb

RUN apt-get update -y

ADD $RWS_DEB_URL /tmp/

RUN dpkg -i /tmp/*.deb

RUN apt-get install libasound2

ENV LD_LIBRARY_PATH /opt/vc/lib

EXPOSE 8888
EXPOSE 8889

CMD /opt/rws/webrtc-streamer --verbose
```

It is possible to build the image for the RPi Zero or others passing the deb URL or local path
```
docker build --build-arg RWS_DEB_URL=http://... -t rpi-webrtc-streamer-zero:1.0 .
```

Running with the following command makes it work properly:
```
docker run --rm -it --network host -p 8889:8889 -p 8888:8888 --device /dev/vchiq -v /opt/vc/lib:/opt/vc/lib rpi-webrtc-streamer-zero:1.0
```

## Frameworks in Go
* https://github.com/hybridgroup/gort
* https://github.com/hybridgroup/gobot/

## Lego IR interface

* [Arduino library for Lego Power Functions IR](https://github.com/jurriaan/Arduino-PowerFunctions/) is an Arduino library to send IR commands to a Lego Power Function receiver
* [Rpi library for Lego Power Functions IR](https://github.com/iConor/lego-lirc) is a collection of Lirc configuration files to send commands to Lego Power Function receiver

## Self driving

* [open-tx](http://www.open-tx.org/)
* [os-rc](http://www.os-rc.com/en/)
* [udacity/self-driving-car](https://github.com/udacity/self-driving-car/)
* [wroscoe/donkey](https://github.com/wroscoe/donkey)
* [hamuchiwa/AutoRCCar](https://github.com/hamuchiwa/AutoRCCar)
* [aimotive](https://aimotive.com/)

## WebRTC open source solutions

* https://github.com/lynckia/licode
* https://github.com/Kurento/kurento-media-server
* https://github.com/priologic/easyrtc
* https://webrtc.org/start/
* https://www.openwebrtc.org/
* https://jitsi.org/
* https://github.com/meetecho/janus-gateway
* https://mediasoup.org
* https://github.com/feross/simple-peer
* [Comparison](https://docs.google.com/spreadsheets/d/13YeU90Fb8Tk_mrtjGqKP-o_PaR5FmxjA8QYypmENphE/edit#gid=0)
* [Comparison Webrtc vs RTSP or RTMP](https://flashphoner.com/browser-based-webrtc-stream-from-rtsp-ip-camera-with-low-latency/)
* [Deep dive in Webrtc and client-server web games](http://blog.brkho.com/2017/03/15/dive-into-client-server-web-games-webrtc/)
* [WebRTC HTML5](https://www.html5rocks.com/en/tutorials/webrtc/basics/)

## Streaming various links

* [V4L2 RTSP Server](https://github.com/mpromonet/v4l2rtspserver)
* [RPi cam web interface](https://elinux.org/RPi-Cam-Web-Interface)
* [Theory audio and video streaming](https://developer.mozilla.org/en-US/Apps/Fundamentals/Audio_and_video_delivery/Live_streaming_web_audio_and_video)
* [nginx-rtmp-module](https://github.com/arut/nginx-rtmp-module)
* [RTSP Rpi multi camera](https://community.ubnt.com/t5/UniFi-Video/Tutorial-RTSP-Raspberry-Pi-B-Viewer-6-Cam-4-Cam/td-p/1536448)
* [Remote RC over 4G streaming MJPEG](https://hackaday.com/2017/09/12/video-streaming-like-your-raspberry-pi-depended-on-it/)
* [Reddit thread about low latency streaming](https://www.reddit.com/r/linux/comments/1498is/live_low_latency_peer_to_peer_video_streaming/)
* [Low latency streaming state of art](http://www.zender.tv/news/2018/3/23/ultra-low-latency-streaming-the-current-state)

## RPi Camera module

* [RPi Camera Module](http://www.geeetech.com/wiki/index.php/Raspberry_Pi_Camera_Module)
* [RPi camera howto](https://www.ics.com/blog/raspberry-pi-camera-module)

```
 load the module
sudo modprobe bcm2835-v4l2

# viewfinder
v4l2-ctl --overlay=1 # enable viewfinder
v4l2-ctl --overlay=0 # disable viewfinder

# record video
v4l2-ctl --set-fmt-video=width=1920,height=1088,pixelformat=4
v4l2-ctl --stream-mmap=3 --stream-count=100 --stream-to=somefile.264

# capture jpeg
v4l2-ctl --set-fmt-video=width=2592,height=1944,pixelformat=3
v4l2-ctl --stream-mmap=3 --stream-count=1 --stream-to=somefile.jpg

# set bitrate
v4l2-ctl --set-ctrl video_bitrate=10000000

# list supported formats
v4l2-ctl --list-formats
```

## Streaming from RPi Camera

### [Source](https://raspberrypi.stackexchange.com/questions/26675/modern-way-to-stream-h-264-from-the-raspberry-cam)
```
v4l2-ctl --set-fmt-video=width=$width,height=$height,pixelformat=4
v4l2-ctl --set-ctrl=rotate=$rotation
v4l2-ctl --overlay=1
v4l2-ctl -p $framerate
v4l2-ctl --set-ctrl=video_bitrate=4000000 //or whatever
gst-launch-1.0 v4l2src ! video/x-h264, width=$width, height=$height, framerate=$framerate/1 ! h264parse ! rtph264pay config-interval=1 pt=96 ! udpsink sync=false host=$host port=$port
```

### [Source](https://wiki.marcluerssen.de/index.php?title=Raspberry_Pi/Camera_streaming)
```
raspivid -a 12 -t 0 -w 1280 -h 720 -hf -ih -fps 30 -o udp://192.168.1.10:5000
```

## GStreamer

* [Gstreamer RPi with Omx](https://wiki.jmk.hu/wiki/Live_Video_Streaming_with_Raspberry_Pi_camera_module)
* [GStreamer RPi with Omx blog](http://nginx-rtmp.blogspot.fr/2013/07/gstreamer-and-raspberry-pi.html)
* [GStreamer](https://gstreamer.freedesktop.org/)
* [GStreamer MMAL for RPi camera](https://github.com/youviewtv/gst-mmal)
* [GStreamer lab](http://www.z25.org/static/_rd_/videostreaming_intro_plab/)
* [Gstreamer low latency RPi](http://blog.tkjelectronics.dk/2013/06/how-to-stream-video-and-audio-from-a-raspberry-pi-with-no-latency/)
* [GStreamer low latency udp](https://altax.net/blog/low-latency-raspberry-pi-video-transmission/)
* [Gstreamer WebRTC](http://blog.nirbheek.in/2018/02/gstreamer-webrtc.html)
* [Gstreamer WebRTC Demos](https://github.com/centricular/gstwebrtc-demos/)
* [Gstreamer WebRTC article](https://opensource.com/article/19/1/gstreamer)

## UV4L
* [uv4l html5 streaming](https://www.linux-projects.org/uv4l/tutorials/custom-webapp-with-face-detection/)
* [uv4l installation](https://www.linux-projects.org/uv4l/installation/)

## Motor control

* [L289N tutorial](http://howtomechatronics.com/tutorials/arduino/arduino-dc-motor-control-tutorial-l298n-pwm-h-bridge/)

## IR Lego Power Functions

* [Rpi prototype web Power Functions IR](https://github.com/braek/legoirblaster)
* [Rpi prototype web Power Functions IR](http://www.internetoflego.com/lego-train-automation-ir-power-functions-with-nodejs-and-lirc/)

## FFMpeg

* [FFMpeg streaming guide](https://trac.ffmpeg.org/wiki/StreamingGuide)
* [Low latency streaming of desktop with ffmpeg and netcat](https://gist.github.com/Brainiarc7/4636a162ef7dc2e8c9c4c1d4ae887c0e)
* [FFMpeg example commands](https://news.mistserver.org/news/71/An+introduction+to+encoding+and+pushing+with+ffmpeg)
* [FFMpeg examples](https://rwdy15.wordpress.com/2015/02/12/streaming-with-ffmpeg-and-receiving-with-vlc/)
* [FFMpeg low latency desktop streaming](http://fomori.org/blog/?p=1213)

## Parts

* [Lego case](https://coolcomponents.co.uk/collections/raspberry-pi/products/pi-blox-legor-compatible-case-for-raspberry-pi-pi-camera-black)
* [Orangepi lite](http://www.orangepi.org/orangepilite/)
* [Orangepi zero plus 2](http://www.orangepi.org/OrangePiZeroPlus2/)
* [IR camera csi](https://it.aliexpress.com/item/New-Raspberry-Pi-3-IR-CUT-Camera-Night-Vision-Focal-Adjustable-5-MP-OV5647-Automatically-Switch/32831783732.html)
* [Orangepi zero plus 2](https://it.aliexpress.com/item/2MP-Camera-for-Orange-PC-Pi-One-PC-Plus-Plus2e-Zero-Plus-2/32831026461.html)
* [Bnggood L293D](https://www.banggood.com/MINI-L293D-Arduino-Motor-Drive-Expansion-Board-Mini-L293D-Motor-Drive-Module-p-1202756.html?rmmds=cart)
* [Banggood L911S H bridge](https://www.banggood.com/L9110S-H-Bridge-Stepper-Motor-Dual-DC-Driver-Controller-Module-p-914880.html?rmmds=cart)
* [Banggood SR04 ultrasonic](https://www.banggood.com/5Pcs-HC-SR04-Ultrasonic-Ranging-Sensor-Ultrasonic-Module-For-Arduino-p-943142.html?rmmds=cart)
