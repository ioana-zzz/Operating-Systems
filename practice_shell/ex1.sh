#!/bin/bash

users=`cat who.fake | awk '{print $1}'|sort |uniq `
echo ${#users[@]}
echo ${users[@]}

echo "---REPORT----"

for user in $users 
do
 number=$(cat ps.fake | awk '{print $1}' | grep "$user" |  wc -l)
 echo $user, $number
done
