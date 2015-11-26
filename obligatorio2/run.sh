#!/bin/bash

if [ `uname` == "Linux" ]
then
	make -f Makefile3.linux run
else
	make -f Makefile3.mac run
fi
