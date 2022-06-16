# About OSCOPE2100
"Oscope 2100" is an oscilloscope software for Hantek DSO-2100 USB oscilloscope.

It is based on libusb and GTK libraries. 

Included is the firmware extraction utility `dsoextractfw` from the "HantekDSO" project (url http://sourceforge.net/projects/hantekdso), the utility is called "dsoextractfw"

DSO software depends on: 
- libusb (library to enable user space application programs to communicate with USB devices)
- GTKlib (GUI framework)
- The firmware file for the DSO-2100, which has to be extracted from the original DSO-2100 USB drivers package. The firmware extraction utility `dsoextractfw` from the "HantekDSO" project (url http://sourceforge.net/projects/hantekdso) is included.

To successfully build a project you need to have all development packages installed (libusb-dev, libgtk2.0-dev).

Also you need to have fxload utility installed in order to be able to upload firmware in to the oscilloscope.

# Building
```
$ cmake
$ make 
$ make install
```

# Installing the firmware file

1. Find `dso21001.sys` file on your DSO-2100 USB drivers CD. If you can't find your CD anymore, refer to this page https://how-to.fandom.com/wiki/How_to_use_the_Hantek_DSO-2100_USB_oscilloscope_in_Linux.
2. Run the program `dsoextractfw DSO2100`. It should find your `dso21001.sys` file and create two files named `DSO2100_firmware.hex` and `DSO2100_loader.hex`
3. Move `DSO2100_firmware.hex`  file to `$INSTALL_DIR/share/dso2100/`
4. Copy the file `$INSTALL_DIR/share/dso2100.rules` to `/etc/udev/rules.d/`
5. `udevadm control --reload-rules && udevadm trigger`

Now the firmware should be loaded automatically when the scope is connected to an USB port.
Once the firmware is loaded, the blue LED on the scope starts blinking.
You can now run software by typing "oscope2100" command in the console or make a shortcut on your desktop.
Make sure you have sufficient privilegies on the USB device or run as root (probably not recommended in the long run).

