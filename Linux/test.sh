#!/bin/sh

if [ $(sestatus | awk 'NR == 1 { print $3 }') == "enabled" ] ; then
	if [ $(LD_PRELOAD=$(pwd)/libunsandbox.so sestatus | awk 'NR == 1 { print $3 }') == "disabled" ] ; then
		echo "PASS: SELinux"
	else
		echo "FAIL: SELinux"
		exit 1
	fi
else
	echo "Skipping SELinux"
fi
