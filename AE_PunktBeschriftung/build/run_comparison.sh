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
res_file=$target_dir/symphony.csv
touch $res_file
headline="Name,Solver,Points,Labels,Time"
echo $headline >> $res_file

print_results () {
    result=$1
    solver=$2
    path=$3
    read -r numOfPoints < $path                  # reading into numOfPoints the number of points of the instance
    result=$numOfPoints','$result 
    result=$solver','$result
    result=$name','$result                          # result = "Name,numOfPoints,labelledPoints,time"
    echo $result >> $res_file                       # appending to res_file
}

# function to recursively loop over directory
expand_dirs () {
    for dir in $1/*; do
        name=$(basename "$dir")
        if [ -d $dir ]
        then
            mkdir $2/$name/ # TODO maybe also check here if that worked
            expand_dirs $dir $2/$name
        else 
            #pat='(.+_)([0-9]+)_(0.*|3.*)'

            #if [[ $name =~ $pat ]]
            #then
                echo "Solving: "$name

                # Popmusic 
                result=$(./popmusic -in $dir -out $2/$name'_SYM.txt')      # result is number of labelled 'points \t time'
                result=${result/$'\t'/,}                        # replacing the tab with a comma
                print_results $result 'SYMPHONY' $dir

                # AbA
                #result=$(./sa -in $dir -out $2/$name'_SA.txt')      # result is number of labelled 'points \t time'
                #result=${result/$'\t'/,}                        # replacing the tab with a comma
                #print_results $result 'SA' $dir

                # GHK
                #result=$(./trivial -in $dir -out $2/$name'_Trivial.txt')      # result is number of labelled 'points \t time'
                #result=${result/$'\t'/,}                        # replacing the tab with a comma
                #print_results $result 'Trivial' $dir
                
            #fi
              
        fi 
    done
}

expand_dirs $instance_dir $target_dir

# just storing my path to the benchmark instances for convenience
# /Users/thomasklein/Uni/11_Semester/Algorithm_Engineering/Projekt/Benchmark_Instances_CLPP/benchmark_instances
