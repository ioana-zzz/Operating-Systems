names=$(cat $1)
result=""

for name in $names
do
  result+="$name@scs.ubbcluj.ro, "
done

echo ${result%", "}

