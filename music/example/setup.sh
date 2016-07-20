#!/bin/bash
jackd -d alsa &
sleep 2

zynaddsubfx -I jack -a -l slowpad.xmz -U &


linuxsampler &
sleep 3
netcat localhost 8888 <example.lscp
../build/music &

sleep 3
jack_connect LinuxSampler:0 system:playback_1
jack_connect LinuxSampler:1 system:playback_2
jack_connect stumpymusic:out LinuxSampler:midi_in_0
jack_connect stumpymusic:out zynaddsubfx:midi_input

