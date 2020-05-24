#!/bin/bash

set -x

DELIM=" | "
SCRIPTDIR=${HOME}/.dwm/status
declare -a SCRIPTS=(
    'vpn'
    'battery'
    'time'
)

echo ${SCRIPTS[@]}

while true;
do
	OUTPUT=""
	idx=1
	for script in ${SCRIPTS[@]}; do
		[ -x "${SCRIPTDIR}/${script}.sh" ] || continue

		OUTPUT_PRE=${OUTPUT}
		OUTPUT="${OUTPUT}$(${SCRIPTDIR}/${script}.sh)"

		if [ $idx -lt ${#SCRIPTS[@]} ]; then
			[ ${#OUTPUT_PRE} -eq ${#OUTPUT} ] || OUTPUT="${OUTPUT}${DELIM}"
			idx=$((idx + 1))
		fi
	done
	xsetroot -name " ${OUTPUT} "
	sleep 1m
done
