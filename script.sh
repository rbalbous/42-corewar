#!/bin/bash
echo > file1
echo > file2
for filename in ./vm_champs/*.s; do
    echo "$filename" >> file1
    ./vm_champs/asm "$filename"
    if [ -e "${filename/.s/.cor}" ]
    then
        hexdump -C "${filename/.s/.cor}" >> file1
    fi
    echo "$filename" >> file2
    ./asm -d "$filename"
    if [ -e "${filename/.s/.cor}" ]
    then
        hexdump -C "${filename/.s/.cor}" >> file2
    fi
done
for filename in ./vm_champs/**/*.s; do
    echo "$filename" >> file1
    ./vm_champs/asm "$filename"
    if [ -e "${filename/.s/.cor}" ]
    then
        hexdump -C "${filename/.s/.cor}" >> file1
    fi
    echo "$filename" >> file2
    ./asm -d "$filename"
    if [ -e "${filename/.s/.cor}" ]
    then
        hexdump -C "${filename/.s/.cor}" >> file2
    fi
done
for filename in ./Test_42-master/corewar/*.s; do
    echo "$filename" >> file1
    ./vm_champs/asm "$filename"
    if [ -e "${filename/.s/.cor}" ]
    then
        hexdump -C "${filename/.s/.cor}" >> file1
    fi
    echo "$filename" >> file2
    ./asm -d "$filename"
    if [ -e "${filename/.s/.cor}" ]
    then
        hexdump -C "${filename/.s/.cor}" >> file2
    fi
done
for filename in ./ASM_Corewar_tests/*.s; do
    echo "$filename" >> file1
    ./vm_champs/asm "$filename"
    if [ -e "${filename/.s/.cor}" ]
    then
        hexdump -C "${filename/.s/.cor}" >> file1
    fi
    echo "$filename" >> file2
    ./asm -d "$filename"
    if [ -e "${filename/.s/.cor}" ]
    then
        hexdump -C "${filename/.s/.cor}" >> file2
    fi
done

echo ""
diff file1 file2
echo "done"
