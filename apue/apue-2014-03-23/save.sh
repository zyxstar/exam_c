#/bin/bash

TARDIR="/var/ftp/hsienmu/weekend_apue/"
NAME="weekend_apue"

for i in ` find . | egrep '\.c$|\.txt$|\.sh$|\.h$|Makefile$'`
do
	tar -rf ${TARDIR}${NAME}-`date +%F`.tar  $i
done
