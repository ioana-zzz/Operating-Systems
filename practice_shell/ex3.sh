files=$(find dir -name "*.log")

touch temp

for file in $files
do
  cat $file | sort >> temp
  mv temp $file
done

