#!/bin/bash

programs=("$@")

while true; do
 for program in $programs
 do
     if [[ `ps  | grep "$program"` ]]; then
     pkill -x "$program"
     echo Process killed : "$program"
    fi 
 done
 
 sleep 1
done
