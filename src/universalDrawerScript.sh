#!/bin/bash

#  compiling commands
#  This script generates a directory and a log file
#  according to the first argument provided:
#  if it is gcc, the script uses gcc compiler for 86_64 platforms
#  and creates object files in the 86_64_platform directory. The log
#  file cointains informations regarding memory allocation of the code
#  Same behaviour if first argument is arm-none-eabi-gcc
#  Exit 1 is asserted in the wrong or missing argument case


if [[ $1 = gcc || $1 = arm-none-eabi-gcc ]]
then

    $1 -c read.c 
    $1 -c draw.c 
    $1 -c main.c
    $1 -o universalDrawer main.o read.o draw.o
    chmod +x universalDrawer
    if [[ $1 = gcc ]]
    then
	
	mkdir 86_64_platform
	mv *.o 86_64_platform
	cd 86_64_platform 
	size main.o read.o draw.o | cat > sizeFile 
	printf "# size output\n\n" >> sizeFile
	nm main.o draw.o read.o | cat > nmFile
	cat sizeFile nmFile > universalDrawer86_64Log
	printf "#nm output" >> universalDrawer86_64Log

    else

	mkdir arm_platform
	mv *.o arm_platform
	cd arm_platform 
	size main.o read.o draw.o | cat > sizeFile 
	printf "# size output\n\n" >> sizeFile
	nm main.o draw.o read.o | cat > nmFile
	cat sizeFile nmFile > universalDrawerArmLog
	printf "#nm output" >> universalDrawerArmLog
	
    fi
    
    rm sizeFile nmFile
    cd ..
    
else
    
    echo Invalid argument 1
    exit 1
    
fi



