#!/bin/bash

echo -n "Enter a string:"
read string

if grep -q "$string" "test.txt"; then
    echo "File test.txt contains '$string'"
else
    echo "File test.txt does not contain '$string'"
fi