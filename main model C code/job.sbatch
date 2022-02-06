#!/bin/bash

#SBATCH --job-name=wtree
#SBATCH --error=wtree
#SBATCH --time=2:00:00
#SBATCH --array=1-100
#SBATCH --ntasks=1
#SBATCH --partition=broadwl

module load gcc/6.2
module load gsl/2.2.1

module load openmpi

mpiexec ./long_model_main