if [[ $# -ne 1 ]] ; then
   echo nr insuficient de argumente
   exit 1
fi



while true; do
   echo " >>" 
   read n 
   if [[ $n -ne 0 ]]; then
    n1=$n
   else 
     break
   fi
done

n=$n1

echo "introduceti un nume de fisier: "
read fisier 
touch $fisier

line=""

while read word; do
   n1=$(( $n1-1 ))
   line+="$word "
   if [[ $n1 -eq 0 ]]; then
         echo $line >> $fisier
         line=""
         n1=$n
   fi
done < $1

echo " fisier: $fisier"
echo " linii: `cat $fisier | wc -l` , cuvinte: `cat $fisier | wc -w`, caractere: `cat $fisier | wc -m` "
