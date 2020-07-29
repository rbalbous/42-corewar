#!/bin/bash

# This is some bash script that you can use to check and compare the corewar's virtual memory at any cycle of the game
#
# HOW TO USE IT
# You just have to write this command in yor terminal and change the value of x and y
# "for i in {x..y}; do sh diff.sh $i; done;"
#
# Make sure to have colordiff installed
# "brew install colordiff"

echo "--------${1}--------"
rm -f tutu toto.out
iburel/corewar -n 1 vm_champs/championships/2017/iburel/gateau.cor -n 2 vm_champs/championships/2017/iburel/gateau.cor -n 3 vm_champs/championships/2017/iburel/gateau.cor -d ${1} > tutu
./corewar -n 1 vm_champs/championships/2017/iburel/gateau.cor -n 2 vm_champs/championships/2017/iburel/gateau.cor -n 3 vm_champs/championships/2017/iburel/gateau.cor -dump ${1} 1> /dev/null
diff toto.out tutu | colordiff