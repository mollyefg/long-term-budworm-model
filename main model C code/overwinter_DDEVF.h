
double DDEVF_OVERWINTER(void *Winterstuff, double Fnaught, size_t winterdim, double (*overwinter_results))

{

STRUCTURE2* Winterpars;
Winterpars = (STRUCTURE2*) Winterstuff;

int DIM = 3;  //MG number of diffeqs

double t=h2;		double t_next=h2;	double t_0=h2;
double y_ode[DIM];
double F, G1, G2;

int i,j, k;
for(i = 0; i<4; i++){
		overwinter_results[i]=0.0;
}

for(i=0;i<DIM;i++){
	y_ode[i] = 0.00001;
	}

double initF = Fnaught;
//double initG1 = Pnaught1;
//double initG2 = Pnaught2;

// -------------------------- integrate until next stoppage event ---------------------------------- //

    double maxt = winterdim;

    t = 0;
//printf("initF = %e, %e, %e, %e\n", initF, initG1, initG2, initG3);

y_ode[0]=initF;
//y_ode[1]=initG1;
//y_ode[2]=initG2;

y_ode[1]=0.0;
y_ode[2]=0.0;


//printf("y_ode[0] = %e  y_ode[1] = %e  y_ode[2] = %e  y_ode[3] = %e\n", y_ode[0], y_ode[1], y_ode[2], y_ode[3]);
//getc(stdin);
//double sumF;
//double sumG1, sumG2, sumG3;

    while(t<maxt){

		F = 0.0;
		G1 = 0.0;
		G2 = 0.0;

	    t_next = t + 1;
		//printf("before ODES: in loop: y_ode[0] = %e\n", y_ode[0]);

		t=Overwinter_ODES(t,t_next,Winterpars,y_ode);		//MG// y_ode[0] is the first equation, 1 is the second, etc.
		//printf("in loop: y_ode[0] = %e\n", y_ode[0]);
		F = y_ode[0];
		G1 = y_ode[1];
		G2 = y_ode[2];
		//printf("y_ode[3] in the loop = %e\n", y_ode[3]);
		//printf("y_ode[0] = %e\n", y_ode[0]);
		//printf("t = %e, F = %e, G = %e \n", t, F, (G1 + G2 + G3));

		} //MG close the while loop
		//printf("outside the loop: F = %e, G = %e %e %e\n", F, G1, G2, G3);
		overwinter_results[0]=F;
		overwinter_results[1]=G1;
		overwinter_results[2]=G2;
	return 0;
}	//MG close double DDEVF