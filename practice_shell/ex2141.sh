if [[ $# -eq 0 ]]; then
    echo "Numar incorect de argumente! "
    echo "Utilizare: $0 file1 file2..."
    exit 1
fi


while true; do
   read word 
   if [[ "$word" == "stop" ]]; then
     break
   else
    word1=$word
   fi
done

word=$word1

touch temp

for file in $@; do
  if [[ `file $file | grep "ASCII"` ]]; then
    echo "Fisier: $file"
    echo "Numar linii : `cat $file | wc -l` "
    i=0
    while read line; do
      i=$((i+1))
      number=$( echo $line | wc -w)
      echo "  *Linia $i: $number cuvinte"
      if [[ $((number%2)) -eq 0 ]]; then
          echo "$line" | sed "s/\b[AEIOUaeiou][a-zA-Z]\{0,\}\b/$word &/" >> temp
      else
          echo "$line" >> temp
      fi
    done < $file
    mv temp $file
   else
     echo "Fisier : $file"
     echo "Fisierul dat nu e de tip text."
   fi
 done
