#!/bin/bash

echo > headers
for ent in $(cat header-dirs) ; do
    d=$KERNEL_SRC/$(echo $ent | sed s@-I\./@@g)
#    echo $d
    find $d -name "*.h" | sed s@$KERNEL_SRC/@@g >> headers
done

echo > entry.c
for f in $(cat headers); do
#    test -n "$(echo $f | grep 'asm/rwsem.h\|hardware/sa1111.h\|mtd-xip.h\|coresight.h')" && continue
#    test -n "$(echo $f | grep 'asm/rwsem.h')"
    echo "#include <$f>" >> entry.c
done


cat entry.c

