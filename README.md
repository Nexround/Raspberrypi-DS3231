# Raspberrypi-DS3231
 A Raspberrypi Library for DS3231 Real-Time Clocks

## Function

* read date from DS3231's registers and format them (includes time and temperature)

* synchronize DS3231's time with system time,you can also set every single part by corresponding function

## Usage
```c
#include "ds3231lib.h"
```
Attention: the wiringPi library provides function to access I2C,so you need to make you sure you have already installed the wiringPi library.
```shell
gcc -c yourfile.c ds3231lib.c
gcc -o main yourfile.o ds3231lib.o -lwiringPi
./main
```
[![Raspberrypi-DS3231](https://img.shields.io/badge/readme%20style-standard-brightgreen.svg?style=flat-square)](https://github.com/Nexround/Raspberrypi-DS3231)
