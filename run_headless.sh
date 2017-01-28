#!/bin/bash
ip="127.0.0.1:8303"
if [[ $# -ne 0 ]]; then
  ip=$1
fi
../teeworlds HEADLESS "player_name WASD-bot" "connect $ip"
