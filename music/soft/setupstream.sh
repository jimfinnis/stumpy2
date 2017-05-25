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

zynaddsubfx -I jack -l soft.xmz -U &

sleep 3

netcat localhost 8888 <piano.lscp

a2jmidid -u &

jack_connect jackmix:out0 darkice:left
jack_connect jackmix:out1 darkice:right

sleep 3
jack_connect stumpymusic:out jackmix:midi
jack_connect stumpymusic:out zynaddsubfx:midi_input
 
jack_connect zynaddsubfx:out_1 jackmix:soft_L
jack_connect zynaddsubfx:out_2 jackmix:soft_R

jobs -p >joblist
