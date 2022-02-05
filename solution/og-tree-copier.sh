#!/bin/bash

set -ex

test_name=$(echo ${INPUT} | rev | cut -d/ -f1 | rev | cut -d. -f1)
gen_summary=${BASE_DIR}/tests/gen_summary
manual_dir=${BASE_DIR}/gen/manual
res=${BASE_DIR}/erin_resources

test -f ${gen_summary}
line=$(grep "^${test_name}\t" ${gen_summary})

matrix_address="${res}/$(echo ${line} | cut -d' ' -f4)"
tree_address=${matrix_address/.mat/}

cp ${tree_address} ${OUTPUT}
