#!/bin/bash

if [ `uname` == "Linux" ]
then
	make -f Makefile3.linux clean
else
	make -f Makefile3.mac clean
fi

