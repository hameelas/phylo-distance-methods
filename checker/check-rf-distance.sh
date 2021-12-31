#!/bin/bash

distance=$(python ${THIRDPARTY}/fastmulrfs/python-tools/compare_two_trees.py --tree1=${2} --tree2=${3} | cut -d, -f6)
bc <<< "1-${distance}"
