files=$(find dir -perm -o=w)

for file in $files
do 
  echo `stat -c '%A' $file` $file
  chmod o-w $file
  echo `stat -c '%A' $file` $file
done
