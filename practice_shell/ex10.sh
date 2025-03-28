#!/bin/bash

start=$(date +"%Y-%m-01")
today=$(date +"%Y-%m-%d")

touch temp

users=$(last -s $start -t $today | head -n -2 | awk '{print $1}' | sort | uniq )
result=$(last -s $start -t $today | head -n -2 | awk '{print $1}')
size=${#users[@]}



for user in $users; do
    number=0
    for line in "${result[@]}"; do
        if [[ "$user" == "$line" ]]; then
            number=$((number+1))
        fi
    done
    echo "$number", "$user" >> temp
done

cat temp | sort -k 1 -r
rm temp

