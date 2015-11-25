#!/bin/bash

if [ `uname` == "Linux" ]
then
	make -f Makefile2.linux run
else
	make -f Makefile2.mac run
fi
