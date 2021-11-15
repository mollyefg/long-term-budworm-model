#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <omp.h>
#include <unistd.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_cdf.h>
#include <gsl/gsl_sf_gamma.h>
#include <gsl/gsl_complex.h>
#include <gsl/gsl_complex_math.h>
#include <gsl/gsl_monte_miser.h>
#include <gsl/gsl_errno.h>	// GSL_SUCCESS ...
#include <gsl/gsl_odeiv.h>	// ODE solver
#include <gsl/gsl_types.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_min.h>

#include "nrutil.c"

char *strFileNameDate;

#define NUM_PARS 70		        // number of parameters to be passed from main to hood
#define NUM_WPARS 20

const double h = 0.01;		        // time step
const double h2 = 0.01;

typedef struct
{
	double PARS[NUM_PARS];
	double **forest;
	int **lifematrix;
	//int **topkill;
	double **Hmat;
	double **Pmat1;
	double **Pmat2;
	double **Pmat3;

	int **agemat;

	double ***death;
	//double ***germination;
	double ***normvar;
	double ***fire_death;
	double sim_results[55][5];		// 1st entry larger than the number of weeks in any data set

	double *dbh_increase;
	int dbh_length;

	double **dbh_supp;
	int supp_length;

	double **fire_weather;
	int fire_weather_length;

	/////////////////////////////  parameters controlled in the input file:
	int lag;
	int defol_switch;
	int which_file;

}STRUCTURE;


typedef struct
{
	double PARS2[NUM_WPARS];
	double overwinter_results[3];		// 1st entry larger than the number of weeks in any data set

}STRUCTURE2;

#include "winter_input.h"
#include "winter_SEIR_G1_odes.h"
#include "winter_DDEVF.h"
#include "overwinter_odes.h"
#include "overwinter_DDEVF.h"