#!/bin/bash

# Script based on simulate.sh from
# simulation-scripts.zip downloaded from here:
# https://sites.google.com/eng.ucsd.edu/datasets/astral-ii

# Simpy Options:
# -rs : Number of species tree replicates
# -rl : Number of locus trees per species tree
# -rg : Number of gene trees per locus tree
# -st : Species tree height (time units)
# -si : Number of individuals per species
# -sl : Number of taxa (leaves)
# -sb : Speciation rate (events/time unit)
# -cp -> sp: Tree­wide effective population size
# -hs : Species­ specific branch rate heterogeneity modifiers
# -hl : Gene­-family-­specific rate heterogeneity modifiers
# -hg : Gene­-by-­lineage­-specific rate heterogeneity modifiers
# -cu -> su : Tree­wide substitution rate
# -so : Ratio between ingroup height and the branch from the root to the ingroup.
#       If this parameter is not set the outgroup is not simulated.
# -od : Activates the SQLite database output.
# -v : Verbosity
# -cs : Random number generator seed.
# -o : Common output prefix­name (for folders and files).

SIMPHY="/Users/ekmolloy/Dropbox/external/SimPhy_1.0.2/bin/simphy_mac64"

# Generate coalesecent trees
for NTAX in 10 100 1000 10000; do
    for TRLN in "10000000" "2000000" "500000"; do
        if [ $TRLN == "10000000" ]; then
            MODL=$NTAX-taxa_recent-speciation_low-ILS
        elif [ $TRLN == "2000000" ]; then
            MODL=$NTAX-taxa_recent-speciation_medium-ILS
        else
            MODL=$NTAX-taxa_recent-speciation_high-ILS
        fi

        # Run SimPhy
        if [ ! -d ${ntax}tax-${ngen}gen-$labl ]; then
            $SIMPHY \
                -rs 1 \
                -rl F:1 \
                -rg 50 \
                -st F:$TRLN \
                -si F:1 \
                -sl F:$NTAX \
                -sb F:0.000001 \
                -sp F:200000 \
                -su E:10000000 \
                -od 1 \
                -v 3  \
                -cs 293745 \
                -o $MODL
        fi

        # Organize data
        cd $MODL/1
        sed 's/_0_0//g' g_trees1.trees > tmp.txt
        for GENE in `seq 1 50`; do
            head -n${GENE} tmp.txt | tail -n1 > ../coalescent_gene_tree_${GENE}.tre
        done
        cd ../
        rm -rf 1
        cd ../
    done
done

exit

# Generate Yule trees
for NTAX in 10 100 1000 10000; do
    for RATE in "0.0000001" "0.000001"; do
        if [ $RATE == "0.0000001" ]; then
            MODL=$NTAX-taxa_deep-speciation
        else
            MODL=$NTAX-taxa_recent-speciation
        fi

        # Run SimPhy
        if [ ! -d ${ntax}tax-${ngen}gen-$labl ]; then
            $SIMPHY \
                -rs 50 \
                -rl F:1 \
                -rg 1 \
                -st F:2000000 \
                -si F:1 \
                -sl F:$NTAX \
                -sb F:$RATE \
                -sp F:200000 \
                -su E:10000000 \
                -od 1 \
                -v 3  \
                -cs 293745 \
                -o $MODL
        fi

        # Organize data
        cd $MODL
        for REPL in `seq -f "%02g" 1 50`; do
            mv $REPL/s_tree.trees yule_tree_repl${REPL}.tre
            rm -rf $REPL
        done
        cd ..
    done
done
