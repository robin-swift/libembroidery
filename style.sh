#!/bin/bash

for file in `find src`
do
	indent -linux -i4 -nut $file
done
