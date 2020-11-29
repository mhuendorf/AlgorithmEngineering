#!/bin/bash

# assert that exactly 2 arguments were passed:
if [ $# -ne 2 ]
then
    echo "Wrong number of parameters: expected 2 (instances-dir and target-dir).">&2
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

# check if path to target dir is not already legit, then create it: (So that we never accidentally overwrite anything)
if [ -d $2 ]   
then
    echo "ERROR: target directory does already exist (I never overwrite).">&2
    exit 3
else
    echo "Target directory does not exist, will create it now."
    mkdir $2
    res=$?
    null=0
    if [ $res -eq $null ]
    then
        target_dir=$2
    else 
        echo "ERROR: Could not create target directory!">&2
        exit 4
    fi
fi

# build the project
cmake ..
make -j4

# create csv file for results
res_file=$target_dir/results.csv
touch $res_file

# function to recursively loop over directory
expand_dirs () {
    for dir in $1/*; do
        name=$(basename "$dir")
        if [ -d $dir ]
        then
            mkdir $2/$name/ # TODO maybe also check here if that worked
            expand_dirs $dir $2/$name
        else 
            echo "Solving: "$name
            result=$(./label_map -in $dir -out $2/$name)
            result=${result/$'\t'/,}
            result=$name','$result  
            #echo $result >> $res_file
            echo $result >> $res_file
        fi 
    done
}

expand_dirs $instance_dir $target_dir

# just storing the path to the benchmark instances for convenience
# /Users/thomasklein/Uni/11_Semester/Algorithm_Engineering/Projekt/Benchmark_Instances_CLPP/benchmark_instances