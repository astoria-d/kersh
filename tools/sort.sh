#!/bin/bash

function print_usage() {
    echo "$0 usage:"
    echo "      $0 [cs]"
    echo "      c: show symbol description"
    echo "      s: sort by type"
}

if [ "$1" == "-h" ] ; then
    print_usage
    exit 100
fi

if [ -z "$1" ] ; then
    sort  vmlinux.sym
elif [ "$1" == "s" ] ; then
    sort --key=2 vmlinux.sym
elif [ "$1" == "c" ] ; then
    echo "found following symbol type."
    awk '{print "      "  $2}' < vmlinux.sym | sort | uniq
    echo "-------------------------------"
    cat nm-desc
else
    print_usage
fi


