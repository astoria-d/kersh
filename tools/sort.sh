#!/bin/bash

if [ "$1" == "-h" ] ; then
    echo "$0 usage:"
    echo " $0 [cs]"
    exit 100
fi

if [ "$1" == "s" ] ; then
    sort --key=2 vmlinux.sym
elif [ "$1" == "c" ] ; then
    echo "found following symbol type."
    awk '{print "      "  $2}' < vmlinux.sym | sort | uniq
    echo "-------------------------------"
    cat nm-desc
else
    sort  vmlinux.sym
fi


