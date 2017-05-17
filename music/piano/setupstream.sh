#!/bin/bash
diamond server -d  # just to make sure

rm jobslist

jackd -d dummy -r 44100 &
echo "Jack (allegedly) started"
sleep 2
jack_lsp || { echo "Jack startup failed"; exit 1;}
echo "Jack check OK"

darkice -c darkice.cfg &
sleep 1

../build/music $* &

~/jackmix/build/jackmix -n config &

sleep 4

linuxsampler &
sleep 3
netcat localhost 8888 <piano.lscp

a2jmidid -u &

jack_connect jackmix:out0 darkice:left
jack_connect jackmix:out1 darkice:right

sleep 3
jack_connect stumpymusic:out jackmix:midi
jack_connect stumpymusic:out LinuxSampler:midi_in_0

jack_connect PianoNormal:0 jackmix:piano_L
jack_connect PianoNormal:1 jackmix:piano_R

jack_connect PianoQuiet:0 jackmix:pianoquiet_L
jack_connect PianoQuiet:1 jackmix:pianoquiet_R

jobs -p >joblist
