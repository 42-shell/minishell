#!/bin/bash
RED='\033[0;31m'
NC='\033[0m'
NAME="minishell"
TTY="/dev/tty"$(ps u | grep -E '[.]/'${NAME} | awk 'END {print $7}')
option=$1


while :
do

	if [ -z "$option"]
	then
		echo
	else
		clear
	fi

	PID=$(ps u | grep -E '[.]/'${NAME} | awk '{print $2}' | xargs echo )
	IFS=' ' read -r -a pids <<< "${PID}"
	for pid in "${pids[@]}"
	do
		echo -e "${RED}PID : ${pid} TTY : ${TTY}"
		echo -e "Opend FD${NC}"
		lsof -p ${pid} 2>/dev/null | awk -v tty=${TTY} '{if($5 == "PIPE" || $5 == "CHR") print $4, $5, $9}'
	done
	echo "============================================================"
	sleep 2
done
