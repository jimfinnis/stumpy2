#!/bin/bash
kill $(cat joblist)
rm joblist
killall scsynth
killall Xvfb
