#!/bin/bash

i=1
while [ $i -le $1 ]
do
    echo $i
    i=$((i + 1))
    sleep 0.25
done
exit 0