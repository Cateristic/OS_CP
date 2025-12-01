echo "Enter a string:"
read str
# Reverse the string
rev=$(echo "$str" | rev)
# Compare
if [ "$str" = "$rev" ]
then
    echo "It is a palindrome"
else
    echo "It is NOT a palindrome"
fi
