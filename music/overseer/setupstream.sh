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

a2jmidid -u &
xvfb-run -a jack_mixer -c jackmixer --no-lash &
xvfb-run -a jack-rack jackrack &

sleep 3

sclang bells.scd &

sleep 3

jack_connect "jack_mixer:MAIN L" jack_rack:in_1
jack_connect "jack_mixer:MAIN R" jack_rack:in_2

jack_connect jack_rack:out_1 darkice:left
jack_connect jack_rack:out_2 darkice:right

jack_connect stumpymusic:out "jack_mixer:midi in"
jack_connect stumpymusic:out "a2j:SuperCollider (playback): in0"

jobs -p >joblist
