echo "Enter a number:"
read n
if [ $n -lt 2 ]; then
    echo "$n is NOT a prime number"
    exit
fi
flag=0
for ((i=2; i<=n/2; i++))
do
    if [ $((n % i)) -eq 0 ]; then
        flag=1
        break
    fi
done
if [ $flag -eq 0 ]; then
    echo "$n is a PRIME number"
else
    echo "$n is NOT a prime number"
fi
