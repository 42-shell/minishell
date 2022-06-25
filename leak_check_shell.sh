#!/bin/bash
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'
NAME="minishell"
TTY="/dev/tty"$(ps u | grep -E '[.]/'${NAME} | awk 'END {print $7}')
option=$1

while :
do
	if [ -z "$option" ]
	then
		echo
	else
		clear
	fi

	PID=$(ps u | grep -E '[.]/'${NAME} | awk '{print $2}' | xargs echo )
	IFS=' ' read -r -a pids <<< "${PID}"
	for pid in "${pids[@]}"
	do
		echo -e "\n${GREEN}PID : ${pid}${NC}   TTY : ${TTY}"
		LEAK=$(leaks ${pid} | grep Process | awk -F ":" 'NR == 4 {print $2}')
		echo -e "\n${RED}$LEAK${NC}\n"
	done
	echo "============================================================"
	sleep 2
done

