#!/bin/bash -x

error() {
    printf "$@\n"
    exit 1
}

cleanup() {
    pgrep Xephyr >/dev/null && killall Xephyr
}
trap cleanup EXIT

command -v Xephyr || error "error: Xephyr not installed"

make -j$(nproc)

Xephyr -screen 1024x768 :1 &
sleep 0.1
DISPLAY=:1 ./dwm

