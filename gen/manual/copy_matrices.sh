#!/bin/bash

ROOT="../../"
TREE2MAT="${ROOT}erin_resources/newick2matrix.py"

while read line; do
	echo "Converting ${line}..."
	dir="$(echo ${line} | cut -d / -f2,3)"
	mkdir ${dir}
	for tree in ${ROOT}${line}/*.tre; do
		python3 ${TREE2MAT} -i ${tree} -o "${dir}/$(echo ${tree} | cut -d / -f6).mat"
	done
done < ${1}
