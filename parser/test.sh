#!/bin/bash

echo "input text (test-input-c.txt):"
cat test-input-c.txt

echo "--------------------"
echo "parse..."
./cpars < test-input-c.txt
