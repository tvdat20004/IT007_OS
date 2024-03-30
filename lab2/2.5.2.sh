#!/bin/sh 
echo -n "Enter your name:"
read name
echo -n "Enter your student ID:" 
read id
while [ "$id" != "22520235" ]; do
    echo "Wrong ID, try again"
    read id 
done
echo "Congratulation!!"
exit 0