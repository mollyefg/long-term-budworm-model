

// --------------------------------Begin ODE system of overwintering --------------------------------------------//

int overwinter_odes(double t, const double y[], double dydt[],void *Winterstuff)
{

STRUCTURE2* Winterpars;
Winterpars = (STRUCTURE2*) Winterstuff;

int i, j;

//double lambdawinter = Winterpars->PARS2[0];

double alpha1winter = Winterpars->PARS2[1];   			//MG   the attack rate of the parasitoids
double alpha2winter = Winterpars->PARS2[2];   			//MG   the attack rate of the parasitoids

double P1 = Winterpars->PARS2[3];
double P2 = Winterpars->PARS2[4];

//printf("P1 = %e, P2 = %e\n", P1, P2);
//getc(stdin);
// ------------------------------------------ ODEs -------------------------------------------- //
if		(y[0]<.000001)	dydt[0]=0;
else

//dydt[0] = (-alpha1winter*y[0]*y[1])/(1+rho1winter*y[1]) - (alpha2winter*y[0]*y[2])/(1+rho2winter*y[2]);

//dydt[1] = (alpha1winter*y[0]*y[1])/(1+rho1winter*y[1]);
//dydt[2] = (alpha2winter*y[0]*y[2])/(1+rho2winter*y[2]);
dydt[0] = (-alpha1winter*y[0]*P1) - (alpha2winter*y[0]*P2);

dydt[1] = (alpha1winter*y[0]*P1);

dydt[2] = (alpha2winter*y[0]*P2);

//printf("alpha1 = %e, alpha2 = %e, alpha3 = %e, rho1 = %e, rho2 = %e, rho3 = %e\n", alpha1winter, alpha2winter, alpha3winter, rho1winter, rho2winter, rho3winter);

//printf("dydt[3] = %e\n", dydt[3]);
return GSL_SUCCESS;
}


// ------------------------------------------  ODE Solver  ----------------------------------------------- //
double Overwinter_ODES(double t_ode,double t_end,void *Winterstuff,double *y_ode)
{
int i;
int status_ode;
double h_init=1.0e-5;

STRUCTURE2* Winterpars;
Winterpars = (STRUCTURE2*) Winterstuff;

//int DIM = Params->PARS[9]+2;		//MG  updated
int DIM = 3;  //MG ?

const gsl_odeiv_step_type *solver_ode	= gsl_odeiv_step_rkf45; // Runge-Kutta Felberg (4, 5)

// returns pointer to a newly allocated instance of a stepping function of type 'solver_ode' for a system of DIM dimensions //
gsl_odeiv_step *step_ode	= gsl_odeiv_step_alloc(solver_ode, DIM);

gsl_odeiv_control *tol_ode	= gsl_odeiv_control_standard_new(1.0e-10, 1.0e-5, 1.0, 0.2);
gsl_odeiv_evolve *evol_ode	= gsl_odeiv_evolve_alloc(DIM);
gsl_odeiv_system sys_ode;
sys_ode.function  = overwinter_odes;
sys_ode.dimension = (size_t)(DIM);
sys_ode.params	  = Winterpars;
sys_ode.jacobian = NULL;

// ----------------------------------- Integrate Over Time ------------------------------------ //
while (t_ode<t_end)	{
	status_ode = gsl_odeiv_evolve_apply(evol_ode, tol_ode, step_ode, &sys_ode, &t_ode, t_end, &h_init, y_ode);

	for (i=0;i<DIM;i++)	{
		if (y_ode[i]<0)		{
		y_ode[i]=0;
		}
	}
}

// -------------------------------------- Clear Memory ----------------------------------------- //
gsl_odeiv_evolve_free(evol_ode);
gsl_odeiv_control_free(tol_ode);
gsl_odeiv_step_free(step_ode);
return (t_end);
}