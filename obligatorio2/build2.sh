#!/bin/bash

if [ `uname` == "Linux" ]
then
	make -f Makefile2.linux all
else
	make -f Makefile2.mac all
fi

