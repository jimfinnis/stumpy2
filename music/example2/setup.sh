#!/bin/bash
diamond server -d  # just to make sure

rm jobslist

#jackd -d alsa -d hw:iO2 &
jackd -d alsa &
echo "Jack (allegedly) started"
sleep 2
jack_lsp || { echo "Jack startup failed"; exit 1;}
echo "Jack check OK"

zynaddsubfx -I jack -l silkpad.xmz -U &


linuxsampler &
sleep 3
netcat localhost 8888 <example.lscp
../build/music &

sleep 3

sclang mixer.scd &

sleep 3

jack_connect stumpymusic:out LinuxSampler:midi_in_0
jack_connect stumpymusic:out zynaddsubfx:midi_input

jobs -p >joblist
