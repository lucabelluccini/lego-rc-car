# Links

* [Interface of Lego Power functions with Scratch](https://github.com/dspinellis/lego-power-scratch)

* [Lirc configuration files for LEGO IR & Python API](https://github.com/iConor/lego-lirc)

* [Dockerfile to run lirc in docker](https://github.com/bgulla/hypriot-lirc)

* [WS to Lirc in Python](https://github.com/artizirk/fast-lircd-websocket-bridge)

* [Go package to interact with Lirc](https://github.com/chbmuc/lirc)

# Commands

pi@raspberrypi:~ $ sudo apt-get install lirc

pi@raspberrypi:~ $ sudo cat /etc/modules
```
# /etc/modules: kernel modules to load at boot time.
#
# This file contains the names of kernel modules that should be loaded
# at boot time, one per line. Lines beginning with "#" are ignored.

i2c-dev
cuse
lirc_dev
lirc_rpi gpio_in_pin=18 gpio_out_pin=17
```

pi@raspberrypi:~ $ sudo cat /boot/config.txt 
```
# For more options and information see
# http://rpf.io/configtxt
# Some settings may impact device functionality. See link above for details
.......
# Uncomment this to enable the lirc-rpi module
dtoverlay=lirc-rpi,gpio_in_pin=18,gpio_out_pin=17
```

pi@raspberrypi:~ $ cat /etc/lirc/lircd.conf
```
include "lircd.conf.d/*.conf"
include "lircd.conf.d/lego/*"
```


pi@raspberrypi:~ $ cat /etc/lirc/lirc_options.conf
```
# These are the default options to lircd, if installed as
# /etc/lirc/lirc_options.conf. See the lircd(8) and lircmd(8)
# manpages for info on the different options.
#
# Some tools including mode2 and irw uses values such as
# driver, device, plugindir and loglevel as fallback values
# in not defined elsewhere.

[lircd]
nodaemon        = False
driver          = default
device          = auto
output          = /var/run/lirc/lircd
pidfile         = /var/run/lirc/lircd.pid
plugindir       = /usr/lib/arm-linux-gnueabihf/lirc/plugins
permission      = 666
allow-simulate  = No
repeat-max      = 600
#effective-user =
#listen         = [address:]port
#connect        = host[:port]
#loglevel       = 6
#uinput         = ...
#release        = ...
#logfile        = ...

[lircmd]
uinput          = False
nodaemon        = False

# [modinit]
# code = /usr/sbin/modprobe lirc_serial
# code1 = /usr/bin/setfacl -m g:lirc:rw /dev/uinput
# code2 = ...


# [lircd-uinput]
# release-timeout = 200
```

```
for command in `irsend LIST LEGO_Combo_PWM "" | cut -d' ' -f2`; do irsend SEND_ONCE LEGO_Combo_PWM $command; sleep 1; done
for command in `irsend LIST LEGO_Combo_Direct "" | cut -d' ' -f2`; do irsend SEND_ONCE LEGO_Combo_PWM $command; sleep 1; done
```
