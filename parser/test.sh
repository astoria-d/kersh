#!/bin/bash

#input_file=test-input-c.txt
input_file=test-input-symbol.txt

echo "input text (${input_file}):"
#cat ${input_file}

echo "--------------------"
./cpars < ${input_file}
