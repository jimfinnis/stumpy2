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

jack_mixer -c jackmixer --no-lash &
jack-rack jackrack &


sleep 3

jack_connect LinuxSampler:0 "jack_mixer:Piano L"
jack_connect LinuxSampler:1 "jack_mixer:Piano R"
jack_connect zynaddsubfx:out_1 "jack_mixer:Synth L"
jack_connect zynaddsubfx:out_2 "jack_mixer:Synth R"

jack_connect "jack_mixer:MAIN L" jack_rack:in_1
jack_connect "jack_mixer:MAIN R" jack_rack:in_2

jack_connect jack_rack:out_1 system:playback_1
jack_connect jack_rack:out_2 system:playback_2

jack_connect stumpymusic:out LinuxSampler:midi_in_0
jack_connect stumpymusic:out zynaddsubfx:midi_input

jobs -p >joblist
