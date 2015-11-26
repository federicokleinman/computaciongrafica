#!/bin/bash

if [ `uname` == "Linux" ]
then
	make -f Makefile2.linux clean
else
	make -f Makefile2.mac clean
fi

