#!/bin/bash

for input in $(ls tests/*.in); do
	echo "in ${input}"
	cnt=0
	while IFS= read -r line; do
		to_echo="${line}"
		if [ ${cnt} -ne 0 ]; then
			to_echo="X${to_echo}"
		fi
		echo ${to_echo}
		cnt=$(expr ${cnt} + 1)
	done < ${input} > ${input}.cc
done

for output in $(ls tests/*.out); do
	echo "out ${output}"
	python -c "print('salam')" < ${output} > ${output}.cc
done
