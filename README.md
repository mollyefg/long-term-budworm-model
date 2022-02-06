# long-term-budworm-model
Code and files associated with the long-term dynamics of jack pine budworm

The full model code and associated data files are located in 'main model C code'. The script uses a gcc compiler and requires gsl routines.

Compile the script with the command: 
./BatchMake_beast.sh long_model_main

You can then run the script interactively, or edit the job.sbatch file as needed to select the number of jobs, output names, etc. Submit with the command:
sbatch job.sbatch

----

The main file is long_model_main.c

The filenames are assembled in the first 140 lines or so. The defolition condition, climate condition, defoliation lag, and PID will all update automatically. You can add text as necessary to differentiate them further - for example, if changing the fire probability coefficients.

The fire probability coefficients are hard-coded into the model, in line 776 of the main file. The preceding 25 or so lines of code show previous coefficients that have been tried, and in some cases the rough associated fire interval is also noted.

There are three output files: the 'sim' file contains printed fairly output for each year of a simulation, and the 'final' file contains a final summary when the simulation is done. When simulations are run with the same filenames and conditions, the final summary output should print to the same final file, so you'll have one line per completed simulation.
The third output file, for tree data, is turned off. This prints detailed data about individual trees throughout the simulation, and should only be used for a shorter simulation run and a small number of jobs, to avoid using an excess of computing time and storage space. Refer to line 1199 to turn this output back on.
For a complete breakdown of the data in the output files, see output_documentation.txt

----

In the winter_input.h file, you can turn defoliation on and off with the 'defol_switch' parameter on line 11, and choose the weather conditions with the which_file parameter (past/future, and central/east/north) on line 13. The lagging defoliation effect as it applies to the fire probability can also be changed in this file if necessary, but this doesn't have a noticeable impact on outcomes. Changes to these parameters should automatically update in the output filenames.

The three supported full models are G1, H1, and N1. G1 is the full model with plant quality effects, H1 does not include plant quality effects, and N1 is the simplest base model with no density-dependence. The scripts are set to run model G1; to change this, edit the head_winter.h file to include the desired set of ODEs, and in long_model_main.c, change the SEIRPARS vector to match (roughly lines 150-220), and change the output filename appropriately (roughly line 33). 



