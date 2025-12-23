#!/bin/bash
HUB="1-6"
PORT="3"

echo "[USB] Power OFF $HUB port $PORT"
sudo uhubctl -l $HUB -p $PORT -a off

sleep 1

echo "[USB] Power ON  $HUB port $PORT"
sudo uhubctl -l $HUB -p $PORT -a on

# 等待 CP210x 重新 enumerate
for i in {1..10}; do
    if ls /dev/ttyUSB* >/dev/null 2>&1; then
        echo "[USB] ttyUSB is back"
        ls /dev/ttyUSB*
        exit 0
    fi
    sleep 0.5
done

echo "[USB] ttyUSB did not reappear"
exit 1