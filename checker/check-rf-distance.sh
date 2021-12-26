#!/bin/bash

python ../third-party/fastmulrfs/python-tools/compare_two_trees.py --tree1=${2} --tree2=${3} | cut -d, -f6
