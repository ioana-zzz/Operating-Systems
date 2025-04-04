#!/bin/bash

if [[ $# -ne 2 ]]; then
   echo Numar insuficient de argumente
   echo Utilizare: $0 fisier_comenzi fisier_propozitii
   exit 1
fi 

touch tmp

while read line; do
  # daca e cu replace  word
  if [[ `echo $line |grep  "REPLACE WORD"` ]]; then
     echo rep word
     word1=$( echo $line | awk '{print $3}' )
     word2=$(echo $line | awk '{print $4}')
     sed "s/$word1/$word2/g"  $2  > tmp
     cat tmp > $2

  # daca e cu replace char
  elif [[ `echo  $line | grep  "REPLACE CHAR"` ]]; then
    echo rep char
   char1=$( echo $line | awk '{print $3}' )
   if [[ $(echo $line | wc -w) -eq 3 ]]; then
    char2=" "
   else
     char2=$(echo $line | awk '{print $4}')
   fi
   sed "s/$char1/$char2/g" $2  > tmp
   mv tmp $2

  #daca e cu append line 
  elif [[ ` echo $line | grep "APPEND LINE"` ]]; then
    echo ap line 
   text=$(echo $line | awk '{print $3}')
   echo $text >> $2
 

 #daca e cu insert line 
 elif [[ `echo $line | grep "INSERT LINE"` ]]; then
    echo ins line
    number=$(echo $line | awk '{print $3}')
   newline=$(echo $line | awk '{print $4}')
   sed ''$number' i '$newline'' $2  > tmp
   mv tmp $2

 fi

done < $1

rm tmp
