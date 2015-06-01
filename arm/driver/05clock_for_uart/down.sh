#!/bin/sh
	echo 'reset' > /dev/ttyUSB0
	sleep 0.5
	echo 'nihao' >/dev/ttyUSB0
	sleep 0.1
	echo 'dnw 50000000' >/dev/ttyUSB0
	sleep 0.5
	dnw arm.bin
	sleep 0.1
	dnw arm.bin
	sleep 0.3
	echo 'go 50000000' >/dev/ttyUSB0
