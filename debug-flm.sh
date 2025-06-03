#!/bin/bash

# This script is used to debug the STM32 flash algorithm.
# It uses the patched STM32 DFP pack and pyocd to load the flash algorithm.
# Then, it tries to load data to flash using pyocd commander.
# If the flash algorithm has a loop within it like the following:
# volatile uint32_t i = 0;
# while (i == 0) { /* Wait for debugger to connect */ }
# The script will halt on the loop, allowing you to debug the flash algorithm.
# Pyocd will then timeout after a while, which is expected.
# The script will then extract the address where the code was loaded and
# start gdb with the appropriate commands to debug the flash algorithm.
# you can then use a command like `set i = 1` to break out of the loop
# Usage: ./debug-flm.sh <unique_id_of_stlink>

if [ $# -ne 1 ]; then
	echo "Error, provide the unique ID of the ST-link debugger to run this script"
	exit 1
fi

file=$(mktemp)

echo "Running pyocd and attempting to flash a file- you should have a loop somewhere in your code to halt on"
echo "timeout will take a while..."
# Load the flash algorithm and attempt to program flash
pyocd commander -vvv -u $1 --pack projectfiles/stm32_dfp_patched.pack \
	--target STM32G0B1CEUx -c load \
	projectfiles/make_gcc_arm/stm32g0xx_spi/build/stm32g0xx_spi.bin  0x80000000 > $file 2>&1
addr=$(awk '{
    while (match($0, /code=0x[0-9a-f]*/)) {
        n++;
        if (n==2) {
            hex = substr($0, RSTART + 5, RLENGTH - 5);  # extract just the "0xNNN" part
            print hex;
            exit
        }
        $0 = substr($0, RSTART+RLENGTH)
    }
}' $file)
echo "Code loaded to $addr"
rm $file
gdbinit=$(mktemp)
elf=projectfiles/make_gcc_arm/stm32g0xx_spi/build/stm32g0xx_spi.elf
echo "file $elf" > $gdbinit
echo "add-symbol-file $elf 0x0 -s PrgCode $addr" >> $gdbinit
echo "target remote localhost:3333" >> $gdbinit
echo "sourcing $gdbinit, starting gdb"

# Start another pyocd server, for debugging
pyocd gdbserver --target STM32G0B1CEUx -u $1 --pack projectfiles/stm32_dfp_patched.pack &
gdb-multiarch $elf -ex "source $gdbinit"
