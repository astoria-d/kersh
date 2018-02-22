#!/bin/bash

echo "#ifndef __idtbl_h__" > idtbl.h
echo "#define __idtbl_h__" >> idtbl.h
echo >> idtbl.h

echo "#define null_index 0" >> idtbl.h

indx=1;
for ent in $(grep post_reduce_action kersh.y | sed 's@^.*(@@g' | sed 's@); }\r@@' ) ; do echo "#define $ent $indx"; indx=$(expr $indx + 1); done  >> idtbl.h

echo >> idtbl.h

echo "#define IDTBL_SIZE $indx" >> idtbl.h
echo >> idtbl.h

echo "#endif /*__idtbl_h__*/" >> idtbl.h

