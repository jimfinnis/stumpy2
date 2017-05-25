#!/bin/bash
diamond server -d  # just to make sure

rm jobslist

#jackd -d alsa -d hw:iO2 &
jackd -d alsa &
echo "Jack (allegedly) started"
sleep 2
jack_lsp || { echo "Jack startup failed"; exit 1;}
echo "Jack check OK"

../build/music $* &

xterm -e ~/jackmix/build/jackmix  &

sleep 4

zynaddsubfx -I jack -l soft.xmz -U &

sleep 3

a2jmidid -u -e &

jack_connect jackmix:out0 system:playback_1
jack_connect jackmix:out1 system:playback_2

sleep 3

jack_connect stumpymusic:out jackmix:midi
jack_connect stumpymusic:out zynaddsubfx:midi_input
 
jack_connect zynaddsubfx:out_1 jackmix:soft_L
jack_connect zynaddsubfx:out_2 jackmix:soft_R

jobs -p >joblist
