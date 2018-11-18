#!/bin/bash

#  compiling commands
#  This script generates a directory and a log file
#  according to the first argument provided:
#  if it is gcc, the script uses gcc compiler for x86_64 platforms
#  and creates object files in the x86_64_platform directory. The log
#  file cointains informations regarding memory allocation of the code
#  Same behaviour if first argument is arm-none-eabi-gcc
#  Exit 1 is asserted in the wrong or missing argument case


if [[ $1 = gcc ]]
then

    $1 -Wall -c read.c 
    $1 -Wall -c draw.c 
    $1 -Wall -c main.c
    $1 -static -o universalDrawer main.o read.o draw.o
    chmod +x universalDrawer
    
    mkdir x86_64_platform
    mv *.o x86_64_platform
    cd x86_64_platform
    
    size main.o read.o draw.o | cat > sizeFile 
    printf "# size output\n\n" >> sizeFile
    nm main.o draw.o read.o | cat > nmFile
    cat sizeFile nmFile > universalDrawerx86_64Log
    printf "#nm output" >> universalDrawerx86_64Log
    
    rm sizeFile nmFile
    cd ..
    
elif [[ $1 = arm-none-eabi-gcc ]]
then
    $1 -Wall --specs=nosys.specs -c read.c 
    $1 -Wall --specs=nosys.specs -c draw.c 
    $1 -Wall --specs=nosys.specs -c main.c
    $1 -static --specs=nosys.specs -o universalDrawer main.o read.o draw.o
    chmod +x universalDrawer
    
    mkdir arm_platform
    mv *.o arm_platform
    cd arm_platform
    
    size main.o read.o draw.o | cat > sizeFile 
    printf "# size output\n\n" >> sizeFile
    nm main.o draw.o read.o | cat > nmFile
    cat sizeFile nmFile > universalDrawerArmLog
    printf "#nm output" >> universalDrawerArmLog
    
    rm sizeFile nmFile
    cd ..
    
else
    
    echo Invalid argument 1, you must insert gcc or arm-none-eabi-gcc
    exit 1
    
fi



