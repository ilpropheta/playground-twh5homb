#!/bin/sh

if test "$#" -eq 1; then
	make && ./$1
else
	make && ./$1 $2
fi