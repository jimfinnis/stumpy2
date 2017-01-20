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

a2jmidid -u &
jack_mixer -c jackmixer --no-lash &
jack-rack jackrack &


sleep 3

sclang bells.scd &

sleep 3


jack_connect "jack_mixer:MAIN L" jack_rack:in_1
jack_connect "jack_mixer:MAIN R" jack_rack:in_2


jack_connect jack_rack:out_1 system:playback_1
jack_connect jack_rack:out_2 system:playback_2

sleep 3
jack_connect stumpymusic:out "jack_mixer:midi in"
jack_connect stumpymusic:out "a2j:SuperCollider (playback): in0"

jobs -p >joblist
