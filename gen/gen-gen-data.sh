for type in deep recent; do for count in 10 100 1000; do ls -1 gen/manual/yule_trees/$count-taxa_$type-speciation | while read line; do echo manual yule_trees/$count-taxa_$type-speciation/$line; done; done; done