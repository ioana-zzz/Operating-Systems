files=$(find dir -type l)

for file in $files
do
  -e $file || echo "$file"
done
