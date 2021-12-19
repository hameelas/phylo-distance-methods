# python newick2matrix.py -i test.tre -o testout
# ./quicktree -in m ../testout
../third-party/quicktree/quicktree -in m ${INPUT} > ${OUTPUT}
