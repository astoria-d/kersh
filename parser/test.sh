#!/bin/bash

echo "input text (test-input.txt):"
cat test-input.txt

echo "--------------------"
echo "parse..."
./cpars < test-input.txt
