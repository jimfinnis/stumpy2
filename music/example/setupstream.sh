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

zynaddsubfx -I jack -l silkpad.xmz -U &


linuxsampler &
sleep 3
netcat localhost 8888 <example.lscp
../build/music $* &

xvfb-run -a jack_mixer -c jackmixer --no-lash &
xvfb-run -a jack-rack jackrack &


sleep 3

jack_connect PianoQuiet:0 "jack_mixer:PianoQuiet L"
jack_connect PianoQuiet:1 "jack_mixer:PianoQuiet R"

jack_connect PianoNormal:0 "jack_mixer:Piano L"
jack_connect PianoNormal:1 "jack_mixer:Piano R"

jack_connect zynaddsubfx:out_1 "jack_mixer:Synth L"
jack_connect zynaddsubfx:out_2 "jack_mixer:Synth R"

jack_connect "jack_mixer:MAIN L" jack_rack:in_1
jack_connect "jack_mixer:MAIN R" jack_rack:in_2

jack_connect jack_rack:out_1 darkice:left
jack_connect jack_rack:out_2 darkice:right

jack_connect stumpymusic:out LinuxSampler:midi_in_0
jack_connect stumpymusic:out zynaddsubfx:midi_input
jack_connect stumpymusic:out "jack_mixer:midi in"

jobs -p >joblist
