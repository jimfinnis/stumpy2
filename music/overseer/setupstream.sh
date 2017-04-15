#!/bin/bash
diamond server -d  # just to make sure

rm jobslist

jackd -R -d dummy -r 44100 &
echo "Jack (allegedly) started"
sleep 2
jack_lsp || { echo "Jack startup failed"; exit 1;}
echo "Jack check OK"


darkice -c darkice.cfg &
sleep 1

../build/music $* &


~/jackmix/build/jackmix -n jackmix &

sleep 4

xvfb-run -a sclang bells.scd &
sleep 2

a2jmidid -u &

jack_connect jackmix:out0 darkice:left
jack_connect jackmix:out1 darkice:right

sleep 3
jack_connect stumpymusic:out jackmix:midi
jack_connect stumpymusic:out "a2j:SuperCollider (playback): in0"

jobs -p >joblist
