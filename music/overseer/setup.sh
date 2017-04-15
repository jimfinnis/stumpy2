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

xterm -e ~/jackmix/build/jackmix jackmix &

sleep 4

sclang bells.scd &
sleep 2

a2jmidid -u &

jack_connect jackmix:out0 system:playback_1
jack_connect jackmix:out1 system:playback_2

sleep 3
jack_connect stumpymusic:out jackmix:midi
jack_connect stumpymusic:out "a2j:SuperCollider (playback): in0"

jobs -p >joblist
