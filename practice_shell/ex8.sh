touch temp
cat df.fake | sed -e '1d' -e's/M//g' -e 's/'%'//g' > temp 
size=$(cat temp | wc -l)


for i in $(seq 1 $size)
do 
  line=$(sed -n ''$i'p' temp)
  size=$(echo $line | awk '{print $2}')
  name=$(echo $line | awk '{print $6}')
  use=$(echo $line | awk '{print $5}')
  if [[ $size -lt 1024 || $use -gt 80 ]]; then
     echo $name
  fi
done
