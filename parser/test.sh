#!/bin/bash

#input_file=test-input-c.txt
input_file=../tools/entry-preproc.c

echo "input text (${input_file}):"
#cat ${input_file}

echo "--------------------"
echo "parse..."
./cpars < ${input_file}
