#/bin/bash

TARDIR="/var/ftp/hsienmu/c/"
NAME="c"

for i in ` find . | egrep '\.c$|\.h$|\.sh$|Makefile$|\.prot$|\.txt$'`
do
	tar -rf ${TARDIR}${NAME}-`date +%F`.tar  $i
done
