#!/bin/bash

rm *.ex
echo "Compiling..."
gcc -Wall read.c draw.c tb.c -lm main.c -o run.ex
chmod +x run.ex
echo "Do you want to execute the program tb? (Y/n)"
read line
if (($line==n)); then
    exit 0
else
    if [[ -f ./run.ex ]]; then
        echo "halo"
	    ./run.ex
    else
	    echo "Can't run execution file. File not present!"
    fi
fi
