# long-term-budworm-model
Code and files associated with the long-term dynamics of jack pine budworm

The full model code and associated data files are located in 'main model C code'. The script uses a gcc compiler and requires gsl routines.

Compile the script with the command: 
./BatchMake_beast.sh long_model_main

You can then run the script interactively, or edit the job.sbatch file as needed to select the number of jobs, output names, etc. Submit with the command:
sbatch job.sbatch

----

The main file is long_model_main.c

In the winter_input.h file, you can turn defoliation on and off with the 'defol_switch' parameter on line 11, and choose the weather conditions with the which_file parameter (past/future, and central/east/north) on line 13. The lagging defoliation effect as it applies to the fire probability can also be changed in this file if necessary, but this doesn't have a noticeable impact on outcomes. 


The three supported full models are G1, H1, and N1. G1 is the full model with plant quality effects, H1 does not include plant quality effects, and N1 is the simplest base model with no density-dependence. The scripts are set to run model G1; to change this, edit the head_winter.h file to include the desired set of ODEs, and in long_model_main.c, change the SEIRPARS vector to match (roughly lines 150-220), and change the output filename appropriately (roughly line 33). Changes to these parameters should automatically update in the output filenames.




