#!/usr/bin/env python3

import sys
import os
import matplotlib.pyplot as plt
import pandas as pd 
import numpy as np

"""
This script takes a results.csv-file and generates plots comparing the different solvers for
the different types of instances.
"""

# only analysing the literature instances for now
#instance_types = ['DenseMap', 'DenseRect', 'HardGrid', 'MunichDrillholes', 'RandomMap', 'RandomRect', 'RegularGrid', 'VariableDensity'] 
instance_types= ['RandomRect']
#solvers = ["Trivial", "FALP", "POP", "SA"]
solvers = ["Baseline", "Base_Heuristic", "Base_Heuristic_Lazy", "Base_Heuristic_Lazy_Cut"]

def plot(df, inst_type, output_folder):

    plt.figure(inst_type, figsize=(10,6))

    # step 2: for each of the solvers, filter the dataframe to only those of the desired solver
    for i, solver in enumerate(solvers):
        solver_df = df[df['Solver'] == solver]
        #print(solver_df.head())

        #sizes = solver_df['Points'].unique()
        sizes = [250 * x for x in range(1,13)]
        
        y = []
        for size in sizes:
            #labels = solver_df[solver_df['Points'] == size]['Labels'].to_numpy()
            labels = solver_df[solver_df['Name'].str.contains("_"+f"{size:04d}"+"_")]
            y.append(np.mean(labels))

        plt.plot(sizes, y, c='C'+str(i), label=solver)


    plt.title('Solver Performance for '+inst_type, fontweight='bold')
    plt.xlabel('number of points', fontweight='bold')
    plt.ylabel('runtime in seconds ', fontweight='bold')
    plt.legend()
    plt.tight_layout()
    plt.savefig(os.path.join(output_folder, 'line', inst_type + '.png'))
    plt.close()


def bar(df, inst_type, output_folder):

    plt.figure(inst_type, figsize=(10,6))

    # step 2: for each of the solvers, filter the dataframe to only those of the desired solver
    performance = []
    for solver in solvers:
        solver_df = df[df['Solver'] == solver]

        solver_df = solver_df[solver_df['Name'].str.contains('3000')]

        solver_perf = solver_df['Labels'].mean()

        performance.append(solver_perf)

    if inst_type == 'MunichDrillholes':
        print([s+': ' for s in solvers])
        print(performance)

    
    y_pos = np.arange(len(solvers))
    bars = plt.bar(y_pos, performance, align='center', width=0.5)
    for i in range(len(solvers)):
        bars[i].set_color('C'+str(i))
    plt.xticks(y_pos, solvers)
        
    plt.title('Solver Performance for '+inst_type, fontweight='bold')
    plt.xlabel('Solver', fontweight='bold')
    plt.ylabel('Accumulated number of labels ', fontweight='bold')
    plt.legend()
    plt.tight_layout()
    plt.savefig(os.path.join(output_folder, 'bar', inst_type + '.png'))
    plt.close()


def digest_file(path, output_folder):
    df = pd.read_csv(path) 
   # print(df.head()) 

    # creating one plot for each of the instance_types
    for inst_type in instance_types:

        # step 1: filter the dataframe to only contain the desired instance type
        inst_df = df[df['Name'].str.contains(inst_type)] #df.filter(like=inst_type, axis=0)
        #print(inst_df.head())

        # step 2: sort the dataframe by ascending number of points
        sorted_inst_df = inst_df.sort_values(by=['Points'])
        #print(sorted_inst_df.head())

        bar(sorted_inst_df, inst_type, output_folder)
        plot(sorted_inst_df, inst_type, output_folder) 
        


if __name__ == "__main__":

    if len(sys.argv) != 3:
        raise ValueError('Scripts needs a path to csv-file and path to folder for plots')

    csv_path = sys.argv[1]
    plot_path = sys.argv[2]

    if not os.path.exists(csv_path):
        raise ValueError('Path to csv-file does not exist!')

    if not os.path.exists(plot_path):
        os.makedirs(os.path.join(plot_path, 'bar/'))
        os.makedirs(os.path.join(plot_path, 'line/'))

    digest_file(csv_path, plot_path)
