#!/bin/bash
kill $(cat joblist)
rm joblist
killall Xvfb
killall scsynth
