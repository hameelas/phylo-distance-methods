# phylo-distance-methods
An Empirical Study of the Distance Methods for Estimating Evolutionary Trees

This is a framework for straight-forward phylogeny tree estimation benchmarking. 
It is built on top of [**Task Preparation System (`tps`)**](https://github.com/ioi-2017/tps) 
engine which is originally desinged for preparing programming problems.

The input data, which is a matrix representing the distance between each pair of species,
is assumed of [PHYLIP Format](https://mothur.org/wiki/phylip-formatted_distance_matrix/).
We use the python script `erin_resources/newick2matrix.py` provided by Prof. Erin Molloy
to convert the generated input trees into a distance matrix.

The output data, which is an estimated evolutionary of the taxa given in input,
uses [Newick Format](https://en.wikipedia.org/wiki/Newick_format) for representing
the guessed trees.

All the distance methods included in this repository are written in `C/C++` which
ensures there is no language-dependent biases in the calculated running time.


## Generating Test Data

First make sure you have installed `tps` on your computer. To install `tps`,
follow the instructions in [this page](https://github.com/ioi-2017/tps#installation).
Then, you can run the following command to generate the test cases:

    tps gen

This commands generates tests based on the `data` file inside `gen` directory.
To see or modify the the details of the generated test data, check out the following file:

    gen/data
    
## Invoking Solutions on Test Data

You can invoke the solutions inside `solution` directiry including existing distance methods 
using the following command:

    tps invoke <solution-name>
    
## Third-Party Libraries

The following distance methods are shipped by the repository by default. The packages
used to run these methods can be found in the `third-party` directory. In this project,
we add `bash` script support for solutions and the respective scripts for running
each third-party method can be found in `solution` directory. Before compiling the third-party
libraries, you first need to populate their submodules.

    git submodule init
    git submodule update

- RapidNJ: [https://github.com/somme89/rapidNJ](https://github.com/somme89/rapidNJ)

        cd third-party/rapidnj
        make

- FastME: [https://gite.lirmm.fr/atgc/FastME/](https://gite.lirmm.fr/atgc/FastME/)

        cd third-party/fastme
        ./configure
        make
        sudo make install

This library unlike other third-party libraries is on a local gitlab, but a snapshot of
this repository (accessible from the above link) is included in this project.


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

## Generating Tests on M1 Processors using Docker

Since RapidNJ is written for amd64 architectures, you may have issues compiling RapidNJ on M1 processors. 
It is possible to use the `buildx` feature of docker to emulate amd64 codes using qemu virtualizer.
Thus, you can use the following commands to generate the test since the default model solution
is set to RapidNJ. You can alternatively change the model solution (which is used to generate
test outputs) in `solutions.json`.

> You need to run following commands in the root directory of this project. Additionally, you need to
create a qemu container for emulating amd64 codes.

    export DOCKER_BUILDKIT=1
    docker buildx create --use --name=qemu
    docker buildx inspect --bootstrap


    docker build --platform linux/amd64 --tag darlene .
    docker rm <container-name> && docker create --platform linux/amd64 --name <container-name> darlene
    docker run --platform linux/amd64 -t -i darlene "tps gen"