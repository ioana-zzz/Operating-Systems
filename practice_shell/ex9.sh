#!/bin/bash

files=($(find dir -type f))
size=${#files[@]}

for i in  $(seq 0 $(($size-2)) )
do 
  sum_i=$(shasum "${files[$i]}" | awk '{print $1}')
  for j in $(seq $(($i+1)) $(($size-1)) )
  do
   sum_j=$(shasum "${files[$j]}" | awk '{print $1}' )
   if [[ "$sum_i" == "$sum_j" ]]; then
    echo "${files[$i]}", "${files[$j]}"
   fi
  done
done
