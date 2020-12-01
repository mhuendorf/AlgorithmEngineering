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
instance_types = ['DenseMap', 'DenseRect', 'HardGrid', 'MunichDrillholes', 'RandomMap', 'RandomRect', 'RegularGrid', 'VariableDensity'] 
solvers = ["Trivial", "FALP"]


def plot(df, inst_type, output_folder):

    plt.figure(inst_type, figsize=(10,6))

    # step 2: for each of the solvers, filter the dataframe to only those of the desired solver
    for i, solver in enumerate(solvers):
        solver_df = df[df['Solver'] == solver]
        print(solver_df.head())

        sizes = solver_df['Points'].unique()

        y = []
        for size in sizes:
            labels = solver_df[solver_df['Points'] == size]['Labels'].to_numpy()
            y.append(np.mean(labels))

        plt.plot(sizes, y, c='C'+str(i), label=solver)


    plt.title('Solver Performance for '+inst_type, fontweight='bold')
    plt.xlabel('number of points', fontweight='bold')
    plt.ylabel('number of labels ', fontweight='bold')
    plt.legend()
    plt.tight_layout()
    plt.savefig(os.path.join(output_folder, inst_type + '.png'))
    plt.close()


def digest_file(path, output_folder):
    df = pd.read_csv(path) 
    print(df.head()) 

    # creating one plot for each of the instance_types
    for inst_type in instance_types:

        # step 1: filter the dataframe to only contain the desired instance type
        inst_df = df[df['Name'].str.contains(inst_type)] #df.filter(like=inst_type, axis=0)
        print(inst_df.head())

        # step 2: sort the dataframe by ascending number of points
        sorted_inst_df = inst_df.sort_values(by=['Points'])
        print(sorted_inst_df.head())

        plot(sorted_inst_df, inst_type, output_folder) 
        


if __name__ == "__main__":

    if len(sys.argv) != 3:
        raise ValueError('Scripts needs a path to csv-file and path to folder for plots')

    csv_path = sys.argv[1]
    plot_path = sys.argv[2]

    if not os.path.exists(csv_path):
        raise ValueError('Path to csv-file does not exist!')

    if not os.path.exists(plot_path):
        os.makedirs(plot_path)

    digest_file(csv_path, plot_path)
