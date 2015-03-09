#/bin/bash

TARDIR="/var/ftp/hsienmu/apue/"
NAME="apue_weekend"

for i in ` find . | egrep '\.c$|\.h$|\.sh$|Makefile$|\.prot$|\.txt$'`
do
	tar -rf ${TARDIR}${NAME}-`date +%F`.tar  $i
done
