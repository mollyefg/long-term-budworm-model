
double DDEVF(void *Paramstuff, double Hn, double Pn1, double Pn2, double Pn3, size_t dim,double (*sim_results)[5])
{
STRUCTURE* Params;
Params = (STRUCTURE*) Paramstuff;
int DIM = Params->PARS[9] + Params->PARS[27] + Params->PARS[28] + 5;  //MG ?

double Qmort;

int m1 = Params->PARS[9];
int m2 = Params->PARS[27];
int m3 = Params->PARS[28];

double t=h;		double t_next=h;	double t_0=h;
double y_ode[DIM];
double S,I1,E1,I2,E2,I3,E3;
int day;
int week;

double alpha1;
double phi;
double alpha2;
double alpha3;


int ticker;

int i,j, k;
for(i = 0; i<55; i++){
	for(j=0;j<4;j++){
		sim_results[i][j]=0.0;
	}
}

for(i=0;i<DIM;i++){
	y_ode[i] = 0.00000000000;
	}

double initialS = Hn;
double initialP1 = Pn1;
double initialP2 = Pn2;
double initialP3 = Pn3;
// -------------------------- integrate until next stoppage event ---------------------------------- //

double maxt = dim;
alpha1 = Params->PARS[4];
alpha2 = Params->PARS[19];
alpha3 = Params->PARS[21];

phi = Params->PARS[8];

t = 0;

double initS = initialS;
double initE1 = initialP1;
double initE2 = initialP2;
double initE3 = initialP3;

y_ode[0]=initS;
//printf("initS = %e\n", initS);
y_ode[1]=initE1;
y_ode[m1+1] = initE2;
y_ode[m1 + m2 + 1] = initE3;

y_ode[m1 + m2 + m3 + 4] = 0.0;

double sumE1;
double sumE2;
double sumE3;

double Q = Params->PARS[10];

week = 3;
 	ticker = 0;
    while(t<maxt){

		Params->PARS[15] = alpha1;		//try this dummy holder
		Params->PARS[20] = alpha2;		//try this dummy holder
		Params->PARS[22] = alpha3;		//try this dummy holder
		phi = 1.0;
		Params->PARS[16] = phi;

		S = 0.0;
		sumE1 = 0.0;
		sumE2 = 0.0;
		sumE3 = 0.0;

	    t_next = t + 1;

		t=ODE_Solver(t,t_next,Params,y_ode);		//MG// y_ode[0] is the first equation, 1 is the second, etc.

				S = y_ode[0];
				if(isnan(S)==1){
					printf("S isnan\n");
				}
				for(i=1;i<m1+1;i++){
						sumE1 += y_ode[i];
					}
				for(i=m1+1;i<m1+m2+1;i++){
						sumE2 += y_ode[i];
					}
				for(i=m1+m2+1;i<m1+m2+m3+1;i++){
						sumE3 += y_ode[i];
					}

				//new bit:
				Qmort = y_ode[m1+m2+m3+4];
				//printf("Qmort = %e\n", Qmort);
				//getc(stdin);
				day = t;

				//printf("day = %d\n", day);
		if (day%7==0)	{
					week=week+1;
					/*
					sim_results[week][0]=S;
					sim_results[week][1]=sumE1;
					sim_results[week][2]=sumE2;
					sim_results[week][3]=sumE3;
					*/
					sim_results[week][0]=S;
					sim_results[week][1]= y_ode[m1+m2+m3+1]+sumE1;
					sim_results[week][2]= y_ode[m1+m2+m3+2]+sumE2;
					sim_results[week][3]= y_ode[m1+m2+m3+3]+sumE3;
					//printf("sim_results[week][3] = %e, initialP3 = %e, y_ode = %e, sumE3 = %e\n", sim_results[week][3], initialP3, y_ode[m1+m2+m3+3], sumE3);

					sim_results[week][4] = y_ode[m1+m2+m3+4];

					//printf("week = %d, S = %e, P1 = %e, P2 = %e, P3 = %e\n", week, y_ode[0], y_ode[m1+m2+m3+1] + sumE1,  y_ode[m1+m2+m3+2] + sumE2,  y_ode[m1+m2+m3+3] + sumE3);
					//getc(stdin);
				}

			ticker++;

		} //MG close the while loop

	return 0;
}	//MG close double DDEVF