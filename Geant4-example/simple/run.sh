#!/bin/sh

i=`expr $1 + 1000`
./build/main macro/gun.mac $i param/input.in

