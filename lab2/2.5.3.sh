#!/bin/sh
echo -n "Enter a number n (n < 10)":
read n
while [ $n -lt 10 ]; do
    echo -n "Try again:"
    read n 
done 
sum=$((n*(n+1)/2))
echo "Sum from 1 to n is $sum"
exit 0
