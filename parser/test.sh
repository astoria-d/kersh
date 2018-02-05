#!/bin/bash

input_file=test-input-c.txt

    echo "input text (${input_file}):"
cat ${input_file}

echo "--------------------"
echo "parse..."
./cpars < ${input_file}
