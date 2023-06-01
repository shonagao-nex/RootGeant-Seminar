#!/bin/sh

i=`expr $1 + 1000`
./build/simple -b -p param/input.in -r $i -m macro/gun.mac

