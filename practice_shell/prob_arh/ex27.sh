#!/bin/bash

dirno=0
fileno=0
other=0

read input

while [[ $input != "stop" ]] ; do
    if [[ -d $input ]]; then
     dirno=$((dirno+1))
     files=$(find $input -type f)
     maxsize=0
     for file in $files; do
       size=$(du -b $file | awk '{print $1}')
       if [[ $size -gt $maxsize ]]; then
           maxsize=$size
           maxfile=$file
       fi
     done
     echo "The largest file in $input is : $maxfile"

    elif [[ -f $input ]]; then
      fileno=((dirno+1))
      cat $input | sort > tmp.txt
      grep -e "^[A-Z]" tmp.txt

    else
      other=$((other+1))
   fi
   read input
done

total=$((dirno+files+other))
echo "Files: $((fileno/total*100))%     Directories: $((dirno/total*100))%     Other:  $((other/total*100))%"
