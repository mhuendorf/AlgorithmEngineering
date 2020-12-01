#!/bin/bash

# assert that exactly 2 arguments were passed:
if [ $# -ne 1 ]
then
    echo "Wrong number of parameters: expected 1 (directory with results) but got: "$#>&2
    exit 1
fi

# check if path to main directory of instances is legit:
if [ -d $1 ]   
then
    echo "Instance directory is present."
    instance_dir=$1
else
    echo "Instance directory not present!">&2
    exit 2
fi

# build the project
cmake ..
make -j4


# function to recursively loop over directory
expand_dirs () {
    for dir in $1/*; do
        name=$(basename "$dir")
        if [ -d $dir ]
        then
            expand_dirs $dir 
        else 
            if [ ${dir: -4} == ".txt" ]
            then
                echo "Validating: "$name
                read -r labels < $dir
                # trivial solver
                result=$(./label_map -eval $dir)      # result is number of labelled 'points \t time'

                re='^[0-9]+$'
                if ! [[ $result =~ $re ]] 
                then
                    echo "error: Not a number! ">&2
                    echo $result >&2 
                    exit 3
                fi
            fi
              
        fi 
    done
}

expand_dirs $instance_dir

# just storing my path to the benchmark instances for convenience
# /Users/thomasklein/Uni/11_Semester/Algorithm_Engineering/Projekt/Benchmark_Instances_CLPP/benchmark_instances