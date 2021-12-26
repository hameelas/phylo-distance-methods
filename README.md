# phylo-distance-methods
An Empirical Study of the Distance Methods for Estimating Evolutionary Trees

This is a framework for straight-forward phylogeny tree estimation benchmarking. 
It is built on top of [**Task Preparation System (`tps`)**](https://github.com/ioi-2017/tps) 
engine which is originally desinged for preparing programming problems.

## Set Up

First make sure you have installed `tps` on your computer. To install `tps`,
follow the instructions in [this page](https://github.com/ioi-2017/tps#installation).
Then, you can run the following command to generate the test cases:

    tps gen
    
## Generating Test Data

This commands generates tests based on the `data` file inside `gen` directory.
To see or modify the the details of the generated test data, check out the following file:

    gen/data
    
## Invoking Solutions on Test Data

You can invoke the solutions inside `solution` directiry including existing distance methods 
using the following command:

    tps invoke <solution-name>
    
## Third-Part Libraries

The following distance methods are shipped by the repository by default. The packages
used to run these methods can be found in the `third-party` directory. In this project,
we add `bash` script support for solutions and the respective scripts for running
each third-part method can be found in `solution` directory.

- RapidNJ: [https://github.com/somme89/rapidNJ](https://github.com/somme89/rapidNJ)

    cd third-party/rapidnj
    make

- FastME: [https://gite.lirmm.fr/atgc/FastME/](https://gite.lirmm.fr/atgc/FastME/)

This library unlike other third-party libraries is on a local gitlab, but a snapshot of
this repository (accessible from the above link) is included in this project.

    cd third-party/fastme
    ./configure
    make
    sudo make install

- ClearCut: [https://github.com/sheneman/clearcut](https://github.com/sheneman/clearcut)

    cd third-party/clearcut
    make

- QuickTree: [https://github.com/khowe/quicktree](https://github.com/khowe/quicktree)

    cd third-party/quicktree
    make

We also use other third party libraries which are listed below:

- Misc: [Required Python Packages]

    pip install numpy
    pip install psutil
    pip install treeswift
    pip install matplotlib

- TPS: [https://github.com/ioi-2017/tps](https://github.com/ioi-2017/tps) 

    sudo source install-tps.sh

> A collection of tree generators designed for enforcing usual edge cases in tree problems
due to [Mohammad Reza Maleki](https://github.com/mruxim) is included in this project. 
This tool is publicly available inside the `tps` repository 
([the code](https://github.com/ioi-2017/tps/blob/master/samples/Batch/simurgh/gen/gencode.cpp)).
The are currently no results available on this dataset (TBD).

## Measuring the Error

- fastmulrfs: [https://github.com/ekmolloy/fastmulrfs/](https://github.com/ekmolloy/fastmulrfs/)

We use this repository for comparing two trees using the RF-distance method. This repository is
created by Prof. [Erin Molloy](https://github.com/ekmolloy). The default checker (RF-distance)
can be modified by changing the `global-checker` field in `subtasks.json`. The bash script
that uses this third-party library can be found at `checker/check-rf-distance.sh`.

    pip install dendropy

## Plotting the Results

To create plots for the result of an experiments, you first need to invoke each solution on
the generated test data. After running a solution, you need to run the following command
to collect the running time statistics of the most recent invokation, and store it in
`results` directory:

    tps collect-times <experiment-name>
    
To see a plot for a specific experiment, for which a file exist with the same name
in `results` directory, use the following command:

    tps plot
    
To modify the list of experiments shown in the resulting plot, edit the variable
named [`methods`](https://github.com/hameelas/phylo-distance-methods/blob/f1620e666a0c3fbc62b93b2a56162c09394056a3/scripts/plot.py#L8)
in `scripts/plot.py`. To add a new script to `tps` you only need to put it in `scripts` directory (`python` and `bash` are supported).
