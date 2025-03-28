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
      fileno=$((fileno+1))
      cat $input | sort | grep -E "^[A-Z]"

    else
      other=$((other+1))
   fi
   read input
done

total=$((fileno+dirno))
total=$((total+other))

echo "Files: $(( (fileno*100)/total ))%,  Directories:  $(( (dirno*100)/total ))%,  Other:  $(( (other*100)/total ))% "
