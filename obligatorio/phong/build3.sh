#!/bin/bash

if [ `uname` == "Linux" ]
then
	make -f Makefile3.linux all
else
	make -f Makefile3.mac all
fi

