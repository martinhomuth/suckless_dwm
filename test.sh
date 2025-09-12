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

Xephyr +xinerama -screen 1024x768 -screen 1024x768 -ac :1 &
sleep 0.5
DISPLAY=:1.0 ./dwm

