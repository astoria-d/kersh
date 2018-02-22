#!/bin/bash

printf "/* %3s %-40s */ NULL,\n" "0" "null_index"
indx=1;
for ent in $(grep post_reduce_action kersh.y | sed 's@^.*(@@g' | sed 's@); }\r@@' )
do
    printf "/* %3s %-40s */ NULL,\n" $indx $ent
    indx=$(expr $indx + 1)
done

