#!/bin/bash

#SBATCH --job-name=fixed_G1_wdefol_future_north_upcoeffs
#SBATCH --error=fixed_G1_wdefol_future_north_upcoeffs
#SBATCH --time=2:00:00
#SBATCH --array=1-5
#SBATCH --ntasks=1
#SBATCH --partition=broadwl

module load gcc/6.2
module load gsl/2.2.1

module load openmpi

mpiexec ./long_model_main