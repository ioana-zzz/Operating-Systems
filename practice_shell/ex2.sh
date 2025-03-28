files=$(find dir -name "*.c")

count=0
for file in $files
do
  lines=$(cat $file | wc -l)
  if [[ $lines -gt 500 ]]; then
   count=$((count+1))
   echo $file
  fi
  if [[ $count -eq 2 ]]; then
   break
  fi
done
