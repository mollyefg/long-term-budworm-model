#include "head_winter.h"
gsl_rng *v;

int crash;

int main(int argc, char *argv[])
{

STRUCTURE Params;
STRUCTURE2 Winterpars;
// ------------------------------------------------------------------------------------------------------------------ //
int i=0; int j;int ii; int jj; int k;
// -------------------------------------------- MISER STUFF --------------------------------------------------------- //
inputdata(&Params);

size_t dim = 49;
double PARS[70];
const gsl_rng_type *T2;
long seed;
seed = time(NULL)*(int)getpid();  //use process id
//seed = -1;  //use process id

gsl_rng_env_setup ();
gsl_rng_default_seed = seed;
T2 = gsl_rng_default;
v = gsl_rng_alloc(T2);

//printf("Params.lag %d \n", Params.lag);
//printf("%d \n", Params.which_file);


/// define the filename for output based on the parameter set:
char file_start[128] = "G1_up_";

char file_scenario[128];
char file_lag[128];
char file_defol[128];

// scenarios 0-5:
char f0[128] = "central_past";
char f1[128] = "east_past";
char f2[128] = "north_past";
char f3[128] = "central_future";
char f4[128] = "east_future";
char f5[128] = "north_future";

if(Params.which_file == 0){
	strcpy(file_scenario, f0);
}
if(Params.which_file==1){
	strcpy(file_scenario, f1);
}
if(Params.which_file == 2){
	strcpy(file_scenario, f2);
}
if(Params.which_file==3){
	strcpy(file_scenario, f3);
}
if(Params.which_file == 4){
	strcpy(file_scenario, f4);
}
if(Params.which_file==5){
	strcpy(file_scenario, f5);
}

// defoliation lag:
char lag10[128] = "_10yearlag_";
char lag13[128] = "_13yearlag_";
char lag15[128] = "_15yearlag_";

if(Params.lag==10){
	strcpy(file_lag, lag10);
}
if(Params.lag==13){
	strcpy(file_lag, lag13);
}
if(Params.lag==15){
	strcpy(file_lag, lag15);
}

// is defoliation occurring?:
char defolon[128] = "defolON_";
char defoloff[128] = "defolOFF_";

if(Params.defol_switch==0){
	strcpy(file_defol, defoloff);
}
if(Params.defol_switch==1){
	strcpy(file_defol, defolon);
}

char sim[128] = "sim_";
char trees[128] = "trees_";
char final[128] = "final";

char output_name[128];

int pid;
pid = getpid();  //getting the process id
char *strFileType = ".dat";
strcpy(output_name, file_start);
strcat(output_name, file_scenario);
strcat(output_name, file_lag);
strcat(output_name, file_defol);


// the simulation output, for time series analysis
char sim_output[128];
strcpy(sim_output, output_name);

	char *sim_file[] =
	{
		strcat(sim_output, sim),
	};
char blank1[128];
sprintf(blank1, "%d", pid);
//strcat(blank0, blank1);
strcat(sim_output, blank1);
strcat(sim_output,strFileType);

// the tree output, currently off -  not in use; see line ~1242
char tree_output[128];
strcpy(tree_output, output_name);

	char *tree_file[] =
	{
		strcat(tree_output, trees),
	};
char blank0[128];
sprintf(blank0, "%d", pid);
strcat(tree_output, blank0);
strcat(tree_output,strFileType);


// the final output
char final_output[128];
strcpy(final_output, output_name);

	char *final_file[] =
	{
		strcat(final_output, final),
	};
strcat(final_output,strFileType);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/// Parameter values (fitted) for the SEIR odes
//MG  here we'll read (or type in) in parameter values for the SEIR model: G1 (quality affects linear density-dependence)
double SEIRPARS[7] = {87.06402, 4788.836, 0.19767, 1, 0.191644, 1.0, 4.0};  // Model G1  (best pars)

Params.PARS[3] = -1;
Params.PARS[4] = SEIRPARS[0];  //87.06402
Params.PARS[7] = SEIRPARS[1];// 4788.836
Params.PARS[8] = SEIRPARS[2]; //0.19767
Params.PARS[9] = SEIRPARS[3]; //1
Params.PARS[17] = -1;
Params.PARS[18] = SEIRPARS[4];  //0.191644
Params.PARS[19] = Params.PARS[4]; // 87.06402
Params.PARS[21] = Params.PARS[4]; // 87.06402
Params.PARS[27] = Params.PARS[9];  //1
Params.PARS[28] = Params.PARS[9]; // 1
Params.PARS[29] = Params.PARS[7]; // 4788.836
Params.PARS[30] = Params.PARS[7]; // 4788.836
Params.PARS[31] = Params.PARS[18];// 0.191644
Params.PARS[32] = Params.PARS[18];// 0.191644
Params.PARS[33] = SEIRPARS[5];    // 1.0
Params.PARS[34] = SEIRPARS[6];    // 4.0

/*
double SEIRPARS[7] = {167.182504,	10002.3, 	0.5312,	1,	0.849042, 0.218272,	7};  /// best pars: Model H1: it's like G1, but with no tree quality

Params.PARS[3] = -1;
Params.PARS[4] = SEIRPARS[0];
Params.PARS[7] = SEIRPARS[1];
Params.PARS[8] = SEIRPARS[2];
Params.PARS[9] = SEIRPARS[3];
Params.PARS[13] = SEIRPARS[4];
Params.PARS[17] = -1;
Params.PARS[18] = SEIRPARS[5];
Params.PARS[19] = Params.PARS[4];
Params.PARS[21] = Params.PARS[4];
Params.PARS[27] = Params.PARS[9];
Params.PARS[28] = Params.PARS[9];
Params.PARS[29] = Params.PARS[7];
Params.PARS[30] = Params.PARS[7];
Params.PARS[31] = Params.PARS[18];
Params.PARS[32] = Params.PARS[18];
Params.PARS[33] = -1;
Params.PARS[34] = SEIRPARS[6];*/


/*double SEIRPARS[5] = {13.038656, 259.611199,  0.797577, 1, 0.510833};/// Model N1: it's terrible

Params.PARS[3] = -1;
Params.PARS[4] = SEIRPARS[0];
Params.PARS[7] = SEIRPARS[1];
Params.PARS[8] = SEIRPARS[2];
Params.PARS[9] = SEIRPARS[3];
Params.PARS[13] = -1;
Params.PARS[17] = -1;
Params.PARS[18] = SEIRPARS[4];
Params.PARS[19] = Params.PARS[4];
Params.PARS[21] = Params.PARS[4];
Params.PARS[27] = Params.PARS[9];
Params.PARS[28] = Params.PARS[9];
Params.PARS[29] = Params.PARS[7];
Params.PARS[30] = Params.PARS[7];
Params.PARS[31] = Params.PARS[18];
Params.PARS[32] = Params.PARS[18];
Params.PARS[33] = -1;
Params.PARS[34] = -1;
*/

///
//double winter[3] = {10.3, 3.10, 3.10}; // likelihood:	492.3543905
//double winter[3] = {10.5, 0.5, 0.5}; // longer period? (no)

//double winter[3] = {5.5, 0.5, 0.5}; // longer period?

//to make the period ~3.1:
//double winter[3] = {18.7, 0.46, 1.98};

//to make the period as long as possible ~9.1:
//double winter[3] = {10.5, 6.2, 0.5};

//Winterpars.PARS2[0] = winter[0]; //lambda winter
//Winterpars.PARS2[1] = winter[1]; //alpha1winter
//Winterpars.PARS2[2] = winter[2]; //alpha2winter


int lag = Params.lag;
printf("lag = %d \n", lag);

////DO NOT exceed 500 years (unless you update your weather data to have more than 500 years)
//use even numbers
int maxyears = 500; //500

//double Hn0 = 3.5;
double Hn0 = 0.908;
double Pn01 = 0.096;
double Pn02 = 0.004;
double Pn03 = 0.00001;

double Hnprime; //adult budworms at the end of the summer
double Pnaught1; //total # of parasitoids produced over the summer
double Pnaught2; //total # of parasitoids produced over the summer
double Pnaught3; //total # of parasitoids produced over the summer

double Hnext; //springtime baby budworms, year 2 (etc.)
double Pnext1, Pnext2, Pnext3;

double Ptot1;
double Ptot2;
double Ptot3;
double Hn, Pn1, Pn2, Pn3;
Hn = Hn0;
Pn1 = Pn01;
Pn2 = Pn02;
Pn3 = Pn03;

Hnext = 0.0;
Pnext1 = 0.0;
Pnext2 = 0.0;
Pnext3 = 0.0;

int years;
double sim_results[55][5];
int maxweeksHP2 = 7;
int maxweeksP1 = 5;

double Hstore[maxyears];

double lambda;
double Fnaught;
double Ffinal;
double Gfinal1;
double Gfinal2;
double overwinter_lresults[3];

//////////////////////////////////////////////////////////					  Tree stuff
//// matrix of trees
// do not exceed 250 without checking the input file
//stick with a minimum of 5

//double maxtrees = 150;
double maxtrees = 50;

//initial sizes
double minDBH = 1.0;	//minimum size for a living or dead tree
double maxDBH = 60.0;
double smallbound = 1.0;  //minimum initial size for a tree
double largebound = maxDBH;  //max initial size for a tree

double row = maxtrees;
double col = maxtrees;

double Hsum;
double Psum1;
double Psum2;
double Psum3;

double Q = 0.0;

//double g;//growth term that will be updated for each tree within the loop
double d, dtemp;
int deathticker;
double germination;

double f;

int treeticker;
double treeend; // holds DBH at the end of the loop
double temp_treeend; // for updating pre-suppression, etc.

int lifemat; //holds life info at the end of the loop
double forestsum; //total DBH for all cells in the matrix
double alivesum; //only cells with living trees
double deadsum; //only cells with dead trees

forestsum = 0.0;
alivesum = 0.0;
deadsum = 0.0;

double alivecount = 0;
double alive0 = 0;
double deadcount = 0;
double emptycount = 0;
double prev_alivecount = 0;

double forestsum_squares;
double avgforest; // average DBH size for output to csv file

double avg_aliveforest;
double avg_deadforest;
double avg_aliveanddeadforest;

double square_avgforest;
double yearly_avgforest[maxyears];
double yearly_varforest[maxyears];
double yearly_CVofDBH[maxyears];

double yearly_alivecount[maxyears];
double yearly_deadcount[maxyears];
double yearly_emptycount[maxyears];

double yearly_avg_aliveforest[maxyears];
double square_aliveforest;
double alivesum_squares;
double yearly_CValive[maxyears];
double yearly_avg_deadforest[maxyears];
double yearly_avg_aliveanddeadforest[maxyears];

double final_alivecount;
double final_deadcount;
double final_emptycount;

double final_avg_aliveforest;
double final_avg_deadforest;
double final_avg_aliveanddeadforest;

double Qmortperhost_sum;
double Qmortperhost;
double Pmortperhost_sum;
double Pmortperhost;

double	Qmortpermort_sum;
double Qmortpermort;
double avg_Qmortperhost;
double avg_Pmortperhost;
double avg_Qmortpermort;

double yearly_avg_Qmortperhost[maxyears];
double final_avg_Qmortperhost;
double yearly_avg_Qmortpermort[maxyears];
double final_avg_Qmortpermort;
double yearly_char_height[maxyears];
double final_avg_char_height;


double final_avgforest;
double final_varforest;
double final_CVofDBH;
double final_CValive;


/// start a loop over winter pars here:
int len_WP1 = 3;
int len_WP2 = 1;

//double WP1[19] = {5.0, 5.5, 6.0, 6.5, 7.0, 7.5, 8.0, 8.5, 9.0, 9.5, 10.0, 10.5, 11.0, 11.5, 12.0, 12.5, 13.0, 13.5, 14.0};
//double WP2[7] = {2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0};


double WP1[3] = {6.0, 10.0, 14.0};
//double WP1[1] = {6.0};
double WP2[1] = {3.0};


double winter[3] = {0.0, 0.0, 0.0};
int w; int x;
for(w=0; w < len_WP1; w++){
	winter[0] = WP1[w];
	for(x=0; x < len_WP2; x++){
		winter[1] = WP2[x];
		winter[2] = WP2[x];

		Winterpars.PARS2[0] = winter[0]; //lambda winter
		Winterpars.PARS2[1] = winter[1]; //alpha1winter
		Winterpars.PARS2[2] = winter[2]; //alpha2winter




////////////////////////////////////////////////////					Generate 10 years of defoliation data

//defoliation stuff:  need to store the level of defoliation, from 0-100%, each year, for fire predictions; generate the first 10 years randomly
//double defoliation[maxyears+10];
double defoliation[maxyears+lag];
printf("check = %e, len %d \n", defoliation[0], maxyears+lag);

double current_defoliation;

for(i = 0; i < lag; i++){
	defoliation[i] = (double)gsl_ran_gaussian(v, 25);	//draw Gaussian values: mean = 25%
	if(defoliation[i]<=0){
		defoliation[i] = 0;
		}
	printf("defoliation = %e \n", defoliation[i]);
	}


///////////////////														Some empty vectors for storage

int halfyears = maxyears/2;
double Hnew[halfyears];

double avgforest_new[halfyears];
double varforest_new[halfyears];
double CVofDBH_new[halfyears];
double alivecount_new[halfyears];
double CValive_new[halfyears];
double deadcount_new[halfyears];
double emptycount_new[halfyears];
double avg_aliveforest_new[halfyears];
double avg_deadforest_new[halfyears];
double avg_aliveanddeadforest_new[halfyears];
double avg_Qmortperhost_new[halfyears];
double avg_Qmortpermort_new[halfyears];
double Amp[maxyears];
double Prd[maxyears];
double MaxP[maxyears];
double OutbreakYear[maxyears];
int Last[1];
double AvgAmp;
double AvgPd;
double AvgMaxP;
double avg_char_height[halfyears];

int deaths;
int germinations;

double mean(int length, double *x){									//  this function calculates a mean
	int i;
	double answer = 0.0;
	for(i=0;i<length;i++) answer += x[i];
	answer /= length;
	return(answer);
}



/////////////////												 Greg's calculations for amplitude and period
//																These would be external in a better world

int ReturnTime(int End, double *TimeSeries, double *Amp, double *Prd, int *Last, double *MaxP, double *OutbreakYear){
	double Periods[1000];
	int FirstTime = 0;
	int UpFirst = 0;
	int DownFirst = 0;
	int Flag1 = 0;
	int Flag2 = 0;
	int Above = 0;
	int Below = 0;
	int i;
	int MaxTimeStart, MaxTimeStop, MinTimeStart, MinTimeStop;
	int FirstTrans = 0;
	double UpTime[1000];
	//double OutbreakYear[1000];
	double DownTime[1000];
	double AmpDiff[1000];
	double PrdDiff[1000];
	double Biggest[1000], Smallest[1000];
	double MaxPop[1000];
	double MinPop[1000];
	int j = 0;
	int k = 0;
	//double AvgAmp = 0;
	MaxPop[0] = -1e10;
	MinPop[0] = 1e10;
	double TestStat = mean(End,TimeSeries);
	for(i=1;i<(End-1);i++){
	if(FirstTrans==0){
			if((TimeSeries[i-1]<TestStat)&&(TimeSeries[i]>TestStat)){ FirstTrans = 1; Below = 1;}  //You were above, now you're below
			if((TimeSeries[i-1]>TestStat)&&(TimeSeries[i]<TestStat)){FirstTrans = 1; Above = 1;} //You were below,  now you're above
	}
	if(FirstTrans==1){
		if(TimeSeries[i]>TestStat){


				if(Below==1){ //if you just switched from below to above

						OutbreakYear[j] = UpTime[j] = i;
						MaxPop[j] = TimeSeries[i]; //Set MaxPop equal to the current pop size
						Below = 0; //switch to below mode
						Above = 1; //switch to above mode
						if(Flag2 == 1) k = k + 1; //next time you go below, you want to have a higher "below number"
						//printf("1st Above:%d i:%d TimeSeries[i]:%f j:%d UpTime[j]:%f MaxPop[j]:%f\n",Below,i,TimeSeries[i],j,UpTime[j],MaxPop[j]);
				}else{

						if(TimeSeries[i]>MaxPop[j]){  //if you didn't just switch, only save the pop size if it's bigger
							OutbreakYear[j] = i;
							MaxPop[j] = TimeSeries[i];
						}
				}

				Flag1 = 1;
				if(FirstTime==0){
					FirstTime = 1;
					UpFirst = 1;
				}
		} //TimeSeries[i]>TestStat
		if(TimeSeries[i]<TestStat){
				if(Above==1){ //if you just switched from below to above
					DownTime[k] = i;
					MinPop[k]= TimeSeries[i]; //Set MaxPop equal to the current pop size
					Above = 0;
					Below = 1;
					if(Flag1==1) j = j + 1;
					//printf("1st Below:%d i:%d TimeSeries[i]:%f k:%d DownTime[k]:%f MinPop[k]:%f\n",Below,i,TimeSeries[i],k,DownTime[k],MinPop[k]);
				}else{
					if(TimeSeries[i]<MinPop[k])
						MinPop[k] = TimeSeries[i];
				}
				Flag2 = 1;
				if(FirstTime==0){
					FirstTime = 1;
					UpFirst = 0;
				}
		}
          }//FirstTrans
	} //
	if(k>j){
		Last[0] = j;
	}else{
		Last[0] = k;
	}
	for(i=0;i<Last[0];i++){

		MaxP[i] = MaxPop[i];
		Amp[i] = MaxPop[i] - MinPop[i];
		if(i==0){
			Prd[i] = -1;
		} else{
			Prd[i] = ((int) fabs((double) (UpTime[i] - UpTime[i-1])));
		}


		//printf("i:%d Max:%f Min:%f Amp:%f Prd:%f UpTime[i]:%f UptTime[i-1]:%f\n",i,MaxPop[i],MinPop[i],Amp[i],Prd[i],UpTime[i],UpTime[i-1]);
	}
} //#End of ReturnTime

///////////////////											initialize the status of each tree in the forest: 10% chance empty cell, 10% chance dead tree, 80% chance living tree
double ltemp;
for(i = 0; i<row; i++){
	for(j = 0; j<col; j++){
		ltemp = (double)gsl_ran_flat(v,0.0, 1.0);
		if(ltemp<0.10){ 					//10% chance
			Params.lifematrix[i][j] = 0;	//no tree
			emptycount ++;
		}
		if(ltemp>=0.10 & ltemp < 0.20){		//10% chance
			Params.lifematrix[i][j] = 1;	//dead tree
			deadcount++;
		}
		if(ltemp>=0.20){  					//80% chance
			Params.lifematrix[i][j] = 2;	//living tree
			alivecount++;
		}
	}
}

////////////////////										initialize the DBH of all living and dead trees in the forest, from 1 - 60 cm (uniform)
double ttemp;
int dbh_loop_length = Params.dbh_length;

for(i = 0; i<row; i++){
	for(j = 0; j<col; j++){
		ttemp = (double)gsl_ran_flat(v,smallbound, largebound);	//choosing a DBH
		if(Params.lifematrix[i][j]==0){		// no tree = no DBH
			Params.forest[i][j] = 0.0;
			Params.agemat[i][j] = 0;
			Params.Hmat[i][j] = 0.0;
			Params.Pmat1[i][j] = 0.0;
			Params.Pmat2[i][j] = 0.0;
			Params.Pmat3[i][j] = 0.0;
		}
		if(Params.lifematrix[i][j]==1){		// dead tree
			Params.forest[i][j] = ttemp;
			Params.agemat[i][j] = 0;
			deadsum += Params.forest[i][j];
			Params.Hmat[i][j] = 0.0;
			Params.Pmat1[i][j] = 0.0;
			Params.Pmat2[i][j] = 0.0;
			Params.Pmat3[i][j] = 0.0;
		}
		if(Params.lifematrix[i][j]==2){		// living tree
			Params.forest[i][j] = ttemp;
			if(ttemp < Params.dbh_increase[0]){
				Params.agemat[i][j] = 0;
			}
					else{
					for(k=1; k < dbh_loop_length+1; k++){																	// defining the age of the tree, based on the randomly drawn value for DBH
						if(Params.forest[i][j] < Params.dbh_increase[k] & Params.forest[i][j] > Params.dbh_increase[k-1]){ // update when you find the right spot in the vector
							Params.agemat[i][j] = k;
							break;
						}
					}
				}

			alivesum += Params.forest[i][j];
			alivesum_squares += pow(Params.forest[i][j],2);
			Params.Hmat[i][j] = Hn0;
			Params.Pmat1[i][j] = Pn01;
			Params.Pmat2[i][j] = Pn02;
			Params.Pmat3[i][j] = Pn03;
		}
		forestsum += Params.forest[i][j];
		forestsum_squares += pow(Params.forest[i][j],2);
	}
}

avg_aliveforest = alivesum/alivecount;
avg_deadforest = deadsum/deadcount;

avgforest = (forestsum)/(row*col);
square_avgforest = (forestsum_squares)/(row*col);

square_aliveforest = (alivesum_squares)/(alivecount);

//////////////////////////////////////////////////////  		Draw some random variates for chance of normal death and chance of dying in a fire
for(i = 0; i < row; i++){
	for(j = 0; j < col; j++){
		for(k  = 0; k < maxyears; k ++){

			d = (double)gsl_ran_flat(v,0.0,1.0);			//random chance of death for each tree
			Params.death[i][j][k] = d;

			f = (double)gsl_ran_flat(v,0.0,1.0);			//chance of dying in a fire
			Params.fire_death[i][j][k] = f;
		}
	}
}

////////////////////////////////////////////////////					Fire stuff:

int fire[maxyears];
double fire_death_prob;
int fire_intensity[maxyears];

//random variates to determine if there will be a fire, and how intense it will be
double fire_variate[maxyears];
int years_since_fire;


////////////////											random variate to choose how long it's been since there was a fire in this system (0-60 years)
years_since_fire = round((double)gsl_ran_flat(v,0,60));


//////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////     Start the simulations:
///////////////////////////////////////////////////////////////////////////////////



for(years=0; years<maxyears ; years++){					//////////////////////////////  The big loop over years

	// read in: adj_dc and adj_fwi and also fsi

	/////////////////////////////       First, calculate this year's defoliation level, based on the number of larvae (Hn0 or Hnext) that we start with:
	double worms;
	double sim_worms;
	if(years==0){
		worms = Hn0;
	}else{
		worms = Hnext;
	}
	sim_worms = log10(worms*100);
	double a_def = -4.471; double b_def = 2.843;
	defoliation[years + lag] = 100*(1/(1 + exp(-a_def - b_def*sim_worms)));  // on a zero-100% scale, how much defoliation there will be this year

	//current_defoliation = defoliation[years + 10];
	current_defoliation = defoliation[years + lag];

	//printf("worms %e sim_worms %e defoliation %e \n", worms, sim_worms, defoliation[years + lag]);
	//getc(stdin);

	double adj_defol;
	double subset_defol[lag];
	double defol_lag  = 0.0;
	for(i=0; i < lag; i++){
		subset_defol[i] = defoliation[years + i]; 			//defoliation years 0-9 have been randomly generated outside of the annual loop
		defol_lag = defol_lag + subset_defol[i];
		}
	double mean_defol;
	mean_defol = mean(lag, subset_defol);

	double sum1 = 0;
	double var_defol;
	for(i=0; i<lag; i++)
	{
		sum1 = sum1 + pow((subset_defol[i] - mean_defol),2);
	}
	var_defol = sum1/9.0;  // 9 = n-1

	//var_defol = 300;	// stop it

	adj_defol = (defol_lag - mean_defol)/var_defol;

	//printf("adj_defol %e defol_10 %e mean_defol %e var_defol %e last year's defol %e this year's defol %e \n", adj_defol, defol_lag, mean_defol, var_defol, defoliation[years - 1], defoliation[years]);
	//getc(stdin);


	/////////////////////////////////////////////////////////////////////			Fire weather stuff: now based on real data
																		//			Read in from external source
	double adj_fwi; //median value from weather data
	double adj_dc; // median value from weather data

	//update:
	adj_dc = Params.fire_weather[years][1];
	adj_fwi = Params.fire_weather[years][0];

	/////////////////////////////       Next, based on adj_defolation (which accounts for defoliation in the past 10 years), adj_dc, and adj_fwi, we calculate this year's fire probability

	double logit_fire_prob;
	//logit_fire_prob = -3.0 + 0.17817*adj_defol + 0.40747*adj_dc + 0.32745*adj_fwi; //  16.67 year fire interval
	//logit_fire_prob = -1.6 + 0.17817*adj_defol + 0.40747*adj_dc + 0.32745*adj_fwi; //  5.6 year fire interval
	//logit_fire_prob = -1.5 + 0.17817*adj_defol + 0.40747*adj_dc + 0.32745*adj_fwi; // 4.24
	//logit_fire_prob = -1.55 + 0.17817*adj_defol + 0.40747*adj_dc + 0.32745*adj_fwi; // 5.05
	//logit_fire_prob = -2.25 + 0.17817*adj_defol + 0.40747*adj_dc + 0.32745*adj_fwi; // 10.4
	//logit_fire_prob = -3.25 + 0.17817*adj_defol + 0.40747*adj_dc + 0.32745*adj_fwi; // 20.8
	//logit_fire_prob = -3.965 + 0.17817*adj_defol + 0.40747*adj_dc + 0.32745*adj_fwi; // 33.3
	//logit_fire_prob = -3.91 + 0.17817*adj_defol + 0.40747*adj_dc + 0.32745*adj_fwi; // 55.6 (?)
	//logit_fire_prob = -3.9 + 0.17817*adj_defol + 0.40747*adj_dc + 0.32745*adj_fwi; // 55.5 (?)
	//logit_fire_prob = -2.5 + 0.24766*adj_defol + 0.56638*adj_dc + 0.45516*adj_fwi; // scale all the coefficients: multiplied by 1.39
	//logit_fire_prob = -2.5 + 0.40747*adj_dc + 0.32745*adj_fwi; // no defoliation effect (otherwise, same as the values used for most simulations)
	//logit_fire_prob = -2.5 + 0.56638*adj_dc + 0.45516*adj_fwi; // scale all the coefficients: multiplied by 1.39; and turn off the effect of defoliation
	//logit_fire_prob = -1.81521 + 0.17817*adj_defol + 0.40747*adj_dc + 0.32745*adj_fwi; // original formula
	//logit_fire_prob = -1.81521 + 0.40747*adj_dc + 0.32745*adj_fwi; // original formula with NO DEFOLIATION EFFECT
	//logit_fire_prob = 0.17817*adj_defol + 0.40747*adj_dc + 0.32745*adj_fwi; // original formula with NO INTERCEPT

	// set defoliation = 0
	// controlled now in the input file
	if(Params.defol_switch==0){
		adj_defol = 0.0;
		printf("no defoliation\n");
		}

	//logit_fire_prob = -2.5 + 0.17817*adj_defol + 0.40747*adj_dc + 0.32745*adj_fwi; // 'down coeffs'
	logit_fire_prob = -3.0 + 1.78*adj_defol + .407*adj_dc + 3.27*adj_fwi; // UP COEFFS --- used for most simulations

	double fire_prob = 1/(1 + exp(-logit_fire_prob));

	//printf("year %d: larvae %e  defoliation %e fire_prob %e \n", years, worms, defol_10, fire_prob);
	//getc(stdin);
	/// finally, given that probability, will a fire occur?

	////////////////////////////

	fire_variate[years] = (double)gsl_ran_flat(v,0.0,1.0);

/// no fire if there has been a fire in the past 5 years:
if(years_since_fire <= 5){
	fire[years] = 0;
	years_since_fire = years_since_fire + 1;
}else{
	if(fire_prob > fire_variate[years]){
		fire[years] = 1;
		printf("year %d Fire occurs: %e > %e \n", years, fire_prob, fire_variate[years]);
		//getc(stdin);
		years_since_fire = 0;
	}else{
		fire[years] = 0;
		years_since_fire = years_since_fire + 1;
	}
}

///////////////////////////////////////////////////////////////////					if you want to turn OFF fires:
//fire[years] = 0;
/////

/////////////////////												just set everything to zero to start, to be safe
treeticker = 0;
deathticker = 0;
forestsum = 0.0;
alivesum = 0.0;
deadsum = 0.0;
avgforest = 0.0;
forestsum_squares = 0.0;
square_avgforest = 0.0;
alivesum_squares = 0.0;
square_aliveforest = 0.0;

avg_aliveforest = 0.0;
avg_deadforest = 0.0;
avg_aliveanddeadforest = 0.0;

avg_Qmortperhost = 0.0;
avg_Qmortpermort = 0.0;

alive0 = 0;

Hsum = 0.0;
Psum1 = 0.0;
Psum2 = 0.0;
Psum3 = 0.0;

Qmortperhost_sum = 0.0;
Pmortperhost_sum = 0.0;
Qmortpermort_sum = 0.0;

alivecount = 0;
deadcount = 0;
emptycount = 0;

deaths = 0;
germinations = 0;
double germ_rand;

int trees_with_cones = 0;
double mean_char_height = 0.0;


//// 									start loops over tree matrix here: at the beginning, trees have different sizes, but insects are distributed evenly on live trees
for(i=0; i < row; i++){
	for(j = 0; j < col; j++){

	germ_rand = round((double)gsl_ran_flat(v,0,1));

	temp_treeend = 0.0;
	treeend = 0.0;
	Q = Params.forest[i][j];
	Params.PARS[10] = Q;

	if(Params.lifematrix[i][j]==0){
		//printf("start with an empty cell\n");
		Hn = 0.0;
		Pn1 = 0.0;
		Pn2 = 0.0;
	}
	if(Params.lifematrix[i][j]==1){
		//printf("start with a dead tree\n");
		Hn = 0.0;
		Pn1 = 0.0;
		Pn2 = 0.0;
	}
	if(Params.lifematrix[i][j]==2){
		//printf("start with a living tree\n");
		if(years>0){
			Hn = Hnext;
			Pn1 = Pnext1;
			Pn2 = Pnext2;
			Pn3 = Pnext3;
		}
		if(years==0){
			Hn = Hn0;
			Pn1 = Pn01;
			Pn2 = Pn02;
			Pn3 = Pn03;
		}
	}

//printf("Hn = %e\n", Hn);
Hnprime = 0.0;											//  zero out the insect variables

Ptot1 = 0.0;
Ptot2 = 0.0;
Ptot3 = 0.0;

Pnaught1 = 0.0;
Pnaught2 = 0.0;
Pnaught3 = 0.0;


	/// true across all trees; then use these to draw a random variate for each tree & calculate the probability that there are pollen cones
	double logitbud = -2.5758*((defoliation[years - 1])/100.0) + 1.5016;
	double logitvar = 0.6105;


///   																		wrapper loop: only bother with this if the tree is currently alive
if(Params.lifematrix[i][j] == 2){
	//printf("opening the alive tree loop\n");
	lifemat = 2;	//start by assuming lifemat stays the same
//to turn insects off; here and ~1344 (?)


	double this_tree_Hn = Hn;
	double this_tree_Pn1 = Pn1;
	double this_tree_Pn2 = Pn2;
	double this_tree_Pn3 = Pn3;

	//// for each tree: draw a random variate - some probability, based on previous year's defoliation, that the tree produces no pollen cones
	/// if no pollen cones are produced, all the budworms die; set Hn equal to zero (and Pn_all, as well)
	double pollencone_norm = 0.0;
	pollencone_norm = logitbud + (double)gsl_ran_gaussian(v,logitvar);
	//prob that we have pollen cones:
	double prob_cones = 1/(1 + exp(-pollencone_norm));
	double rand_prob_cones = (double)gsl_ran_flat(v,0,1);


//// turn off the pollen cone effects: just kill this if/else statement

	if(rand_prob_cones > prob_cones){
		//printf("no pollen cones\n");

		this_tree_Hn = 0.0;
		this_tree_Pn1 = 0.0;
		this_tree_Pn2 = 0.0;
		this_tree_Pn3 = 0.0;

		}else{
		//printf("yes pollen cones\n");
		trees_with_cones++;
	}



	//printf("defoliation %e, normal variate %e, prob %e uniform variate %e \n", defoliation[years - 1], pollencone_norm, prob_cones, rand_prob_cones);
	//printf("Insect values %e %e %e %e \n",  this_tree_Hn, this_tree_Pn1, this_tree_Pn2, this_tree_Pn3);

	//getc(stdin);


	//DDEVF(&Params, Hn, Pn1, Pn2, Pn3, dim, sim_results);  //			// AN EXTERNAL FUNCTION: this is where we actual run the budworm SEIR model
	DDEVF(&Params, this_tree_Hn, this_tree_Pn1, this_tree_Pn2, this_tree_Pn3, dim, sim_results);  //			// AN EXTERNAL FUNCTION: this is where we actual run the budworm SEIR model

	Ptot1 = sim_results[maxweeksP1][1];
	Ptot2 = sim_results[maxweeksHP2][2];
	Ptot3 = sim_results[maxweeksHP2][3];

	Hnprime = sim_results[maxweeksHP2][0];

	alive0++;

	//  different sources of mortality:
	Qmortperhost = 0.0;
	Pmortperhost = 0.0;
	Qmortpermort = 0.0;

	Qmortperhost = (sim_results[maxweeksHP2][4])/(Hn+Pn1+Pn2+Pn3);
	Pmortperhost = (Ptot1+Ptot2+Ptot3)/(Hn+Pn1+Pn2+Pn3);
	Qmortpermort = (sim_results[maxweeksHP2][4])/(Hn-Hnprime);

	Qmortperhost_sum += Qmortperhost;
	Pmortperhost_sum += Pmortperhost;
	Qmortpermort_sum += Qmortpermort;

	Pnaught1 = Ptot1;
	Pnaught2 = Ptot2;
	Pnaught3 = Ptot3;

	if(Pnaught1 <= 0.0){
		Pnaught1  = 0.0;
	}
	if(Pnaught2 <= 0.0){
		Pnaught2  = 0.0;
	}
	if(Pnaught3 <= 0.0){
		Pnaught3  = 0.0;
	}

	////////////////////////////////////////////////////////////////////////         Now we simulate tree growth
	//printf("line 780: tree size %e \n", Params.forest[i][j]);
	//  define the current growth term for this particular tree

	// how much should it grow
	if(Params.forest[i][j] < Params.dbh_increase[0]){ //if DBH smaller than the first size in the vector, just set to the first size in the vector
		temp_treeend = Params.dbh_increase[0];
		}else{
		for(k=1; k < dbh_loop_length+1; k++){
			if(Params.forest[i][j] <= Params.dbh_increase[k] & Params.forest[i][j] > Params.dbh_increase[k-1]){ // update when you find the right spot in the vector
				temp_treeend = Params.dbh_increase[k];
				//printf("Params.forest[i][j] %e k %d inc of k-1 %e  inc of k %e temp_treeend %e \n", Params.forest[i][j], k, Params.dbh_increase[k-1], Params.dbh_increase[k], temp_treeend);
				break;
			}
			if(Params.forest[i][j] > Params.dbh_increase[k]){		// if the tree is too big to keep growing, just set to max size:
			//printf("k %d  Params.forest[i][j] %e  increase %e \n", k, Params.forest[i][j], Params.dbh_increase[k]);
				temp_treeend = maxDBH;
			}
		}
	}
//printf("temp_treeend %e \n", temp_treeend);
	// and how much of that growth actually occurs -- some could be suppressed due to defoliation

	int defol_loop_length = Params.supp_length;
	double suppression;
	for(k=1; k < defol_loop_length+1; k++){
				if(current_defoliation < Params.dbh_supp[k][0] & current_defoliation >= Params.dbh_supp[k-1][0]){ // update when you find the right spot in the vector
					suppression = Params.dbh_supp[k][1];
					//printf("suppression %e \n", suppression);
					break;
				}
		}

	// update end size based on suppression of growth:
	treeend = Params.forest[i][j] + suppression*(temp_treeend - Params.forest[i][j]); //update to final value, depending on how much growth suppression occurs
	/// but all trees with DBH greater than a semi-arbitrary maximum just stop growing eventually
	if(treeend>maxDBH){
			treeend = maxDBH;
	}

	//printf("treeend %e \n", treeend);


	if(Params.forest[i][j] > treeend){
		printf("problem with growth - line 790: Params.forest[i][j] %e treeend %e \n", Params.forest[i][j], treeend);
		getc(stdin);
	}
	////////////////////////////////////////////////////////////////////////         Now some trees will die, due to defoliation, fire, or random chance

		dtemp = 0.0;
		dtemp = Params.death[i][j][years];  // this was already randomized outside the loops

		//death probabilities:   in the absence of defolation & fire effects, this just depends on tree age
		double death_prob;
		double defol_death_prob;
		double final_death_prob;
		if (Params.agemat[i][j] < 20){
			death_prob = 0.0047;
		}
		if (Params.agemat[i][j] >= 20 & Params.agemat[i][j] < 25){
			death_prob = 0.0322;
		}
		if (Params.agemat[i][j] >= 25 & Params.agemat[i][j] < 30){
			death_prob = 0.0514;
		}
		if (Params.agemat[i][j] >= 30 & Params.agemat[i][j] < 35){
			death_prob = 0.0794;
		}
		if (Params.agemat[i][j] >= 35 & Params.agemat[i][j] < 41){
			death_prob = 0.0531;
		}
		if (Params.agemat[i][j] >= 41 & Params.agemat[i][j] < 46){
			death_prob = 0.0586;
		}
		if (Params.agemat[i][j] >= 46 & Params.agemat[i][j] < 51){
			death_prob = 0.0436;
		}
		if (Params.agemat[i][j] >= 56){
			death_prob = 0.0198;
		}

		//but what if there are insects causing mortality also:
		// this bit comes from McCullough 1996: mortality prob. is based on current and previous year's defoliation levels
		// see mortality_due_to_defoliation.R
		double thing;
		thing = 4.872597 -0.0106722*current_defoliation - 0.03705807*defoliation[years+9];  // defoliation[years+9] is the defoliation in the previous year; we have 10 randomly generated years of defoliation to start
																							// so the count is offset from the year
		defol_death_prob = 1/(1 + exp(thing));

		if (defol_death_prob > death_prob){		// currently we'll just choose whichever probability of death is higher (age-related or defoliation-related)
												// another option would be to add the probabilities together
			final_death_prob = defol_death_prob;
		}else{
			final_death_prob = death_prob;
		}

		if(dtemp < final_death_prob){ //death is rare-ish for young trees, when budworms and fire aren't a problem
			// natural death occurs
			lifemat = 1;
		}


		/// but if there was a fire that year, everything might be different for the living trees:
		//	if the tree dies, all insects set to zero
		double temp_pmort;
		if(fire[years]==1){
			double Hely_1 = 3.2362; double Hely_2 = 0.0141; double Hely_3 = -0.4821;
			//let's assume C4 type forest for now:

			mean_char_height = Params.fire_weather[years][3]; //0 = fwi; 1 = dc; 2 = C3 char height; 3 = C4 char height
			temp_pmort = Hely_1 + Hely_2*mean_char_height + Hely_3*Params.forest[i][j];
			fire_death_prob = 1.0/(1.0 + exp(-temp_pmort));
			//printf("temp p mort %e  fire death prob %e DBH %e \n", temp_pmort, fire_death_prob, Params.forest[i][j]);

			if(Params.fire_death[i][j][years] > 1.0 - fire_death_prob){
							treeend = 0.0;
							lifemat = 0;
							Hnprime = 0.0;
							Pnaught1 = 0.0;
							Pnaught2 = 0.0;
							Pnaught3 = 0.0;
						 	//printf("fire killed tree end = %e\n", treeend);
				}
		}

		if(lifemat == 0){
			deaths++;
		}
		if(lifemat == 1){
			deaths++;
		}

	}//closing the wrapper loop around living trees: includes SEIR model and growth and death


////////////////////////////////													Let seedlings germinate sometimes in empty cells
if(Params.lifematrix[i][j]==0){
	lifemat = 0;

	Hnprime = 0.0;
	Pnaught1 = 0.0;
	Pnaught2 = 0.0;
	Pnaught3 = 0.0;

	if(fire[years]==1){
		//if(germ_rand < 0.80){
			germination = 1;					// in fire years, empty cells have a 100% chance of germinating
		//}
	}else{
		if(germ_rand < 0.20){
			germination = 1;
		}else{
			germination = 0;					// in non-fire years, empty cells have a 20% chance of germinating
		}
	}

	if(germination==1){  //germ_prob == if there is a fire; 0 otherwise
		treeend = minDBH;
		lifemat = 2;
		germinations++;
	}else{		//no germination
		treeend = 0.0;
	}
}


//////////////////////////////////////////											Trees that were already dead can be eliminated through burning
if(Params.lifematrix[i][j]==1){
	lifemat = 1;
	Hnprime = 0.0;
	Pnaught1 = 0.0;
	Pnaught2 = 0.0;
	Pnaught3 = 0.0;

	//assuming there's no fire
	treeend = Params.forest[i][j];

	if(fire[years]==1){
				// assume that given a fire, an already-dead tree will be burned
				/*double Hely_1 = 3.2362; double Hely_2 = 0.0141; double Hely_3 = -0.4821;
				//let's assume C4 type forest for now:
				double mean_char_height; double temp_pmort;
				mean_char_height = Params.fire_weather[years][2]; //0 = fwi; 1 = dc; 2 = C3 char height; 3 = C4 char height
				temp_pmort = Hely_1 + Hely_2*mean_char_height + Hely_3*Params.forest[i][j];
				fire_death_prob = 1.0/(1.0 + exp(-temp_pmort));
				//printf("temp p mort %e  fire death prob %e DBH %e \n", temp_pmort, fire_death_prob, Params.forest[i][j]);

				if(Params.fire_death[i][j][years] > 1.0 - fire_death_prob){
								treeend = 0.0;
								lifemat = 0;
							 	//printf("fire tree removed by burning = %e\n", treeend);
					}*/
			treeend = 0.0;
			lifemat = 0;
		}
}//if the tree is dead


//////
/////
																			//    now update the matrices, and calculate empty/dead/alive/and sums
							 												//    finally, update status and size of trees
																			//    set the final DBH size of the tree

int death_occurs = 0;
if(Params.lifematrix[i][j] == 2 && lifemat != 2){
	death_occurs = 1;
}



//FILE *outtree;
//outtree = fopen(tree_output,"a");		// print the tree size before it's updated in the matrix, and then whether it died this year
//	fprintf(outtree, "%d, %d, %d, %d, %d, %d, %e, %e\n", years, i, j, Params.lifematrix[i][j], lifemat, death_occurs, Params.forest[i][j], treeend);
//	fclose(outtree);



//update the matrices with tree size and status
Params.forest[i][j] = treeend;
Params.lifematrix[i][j] = lifemat;

if(Params.lifematrix[i][j]==0){
	emptycount++;
	Params.agemat[i][j] = 0;
}
if(Params.lifematrix[i][j]==1){
	deadcount++;
	Params.agemat[i][j] = 0;
	deadsum+=Params.forest[i][j];
}
if(Params.lifematrix[i][j]==2){
	Params.agemat[i][j]++;
	alivecount++;
	alivesum+=Params.forest[i][j];
	alivesum_squares += (Params.forest[i][j])*(Params.forest[i][j]);
}

forestsum += Params.forest[i][j];
forestsum_squares += (Params.forest[i][j])*(Params.forest[i][j]);

Params.Hmat[i][j] = Hnprime;		//bugs are NOT evenly dispersed across trees at the END of the season; final insect density per tree depends on status of individual trees
Params.Pmat1[i][j] = Pnaught1;
Params.Pmat2[i][j] = Pnaught2;
Params.Pmat3[i][j] = Pnaught3;

Hsum += Params.Hmat[i][j];
Psum1 += Params.Pmat1[i][j];
Psum2 += Params.Pmat2[i][j];
Psum3 += Params.Pmat3[i][j];

treeticker = treeticker + 1;





}} //close loops over forest matrix

//printf("year %d  tree total %e, trees with cones %d \n", years, maxtrees*maxtrees, trees_with_cones);
//// 																						re-disperse insects evenly across living trees:

Hnprime = (Hsum)/(alivecount);
Pnaught1 = (Psum1)/(alivecount);
Pnaught2 = (Psum2)/(alivecount);
Pnaught3 = (Psum3)/(alivecount);



// calculate average size of trees in the forest; don't report each individual tree every year
if(forestsum == 0.0){
	avgforest = 0.0;
}else{
avgforest = (forestsum)/(row*col);
}

if(forestsum_squares == 0.0){
	square_avgforest = 0.0;
}else{
	square_avgforest = (forestsum_squares)/(row*col);
}

if(alivecount>0.0){
	avg_aliveforest = alivesum/alivecount;
	square_aliveforest = (alivesum_squares)/(alivecount);

	avg_Qmortperhost = Qmortperhost_sum/alive0;  //different than alivecount, because Qmortality is calculated (if and only if) the tree was
												//alive when the loop started -- do not use newly germinated trees, do include trees that were alive but then burned or died
	avg_Pmortperhost = Pmortperhost_sum/alive0;
	avg_Qmortpermort = Qmortpermort_sum/alive0;

}else{
	avg_aliveforest = 0.0;
	avg_Qmortperhost = 0.0;
	avg_Pmortperhost = 0.0;
	avg_Qmortpermort = 0.0;
	square_aliveforest =0.0;
}

if(deadcount>0.0){
	avg_deadforest = deadsum/deadcount;
}else{
	avg_deadforest = 0.0;
}

if(alivecount+deadcount>0.0){
	avg_aliveanddeadforest = (alivesum+deadsum)/(alivecount+deadcount);
}else{
	avg_aliveanddeadforest = 0.0;
}

yearly_avgforest[years] = avgforest;
yearly_varforest[years] = square_avgforest - (avgforest)*(avgforest);
yearly_CVofDBH[years] = pow((square_avgforest - (avgforest)*(avgforest)),0.5)/(avgforest);
yearly_CValive[years] = pow((square_aliveforest)-((avg_aliveforest)*(avg_aliveforest)),0.5)/(avg_aliveforest);

yearly_alivecount[years] = alivecount;
yearly_deadcount[years] = deadcount;
yearly_emptycount[years] = emptycount;

yearly_avg_aliveforest[years] = avg_aliveforest;
yearly_avg_deadforest[years] = avg_deadforest;
yearly_avg_aliveanddeadforest[years] = avg_aliveanddeadforest;

yearly_avg_Qmortperhost[years] = avg_Qmortperhost;
yearly_avg_Qmortpermort[years] = avg_Qmortpermort;
yearly_char_height[years] = mean_char_height;

Hstore[years] = Hnext;

////////////////////////////////  																	End SUMMER
///////////////////////////////   																	Begin WINTER



Hnext = 0.0;
Pnext1 = 0.0;
Pnext2 = 0.0;

lambda = Winterpars.PARS2[0];
Fnaught = 0.0;

Winterpars.PARS2[3] = Pnaught1;
Winterpars.PARS2[4] = Pnaught2;
Fnaught = lambda*Hnprime;
size_t winterdim =1.0;		//This is in days

Ffinal = 0.0;
Gfinal1 = 0.0;
Gfinal2 = 0.0;

DDEVF_OVERWINTER(&Winterpars, Fnaught, winterdim, overwinter_lresults);  //

Ffinal = overwinter_lresults[0];
Gfinal1 = overwinter_lresults[1];
Gfinal2 = overwinter_lresults[2];

Hnext = Ffinal;
if(Hnext<=0.0){
	Hnext = 0.0;
}

Pnext1 = Gfinal1;
Pnext2 = Gfinal2;


if(Pnext1 <=0.0 ){
	Pnext1 = 0.0; // no migration
	}
if(Pnext2 <=0.0 ){
	Pnext2 = 0.0; // no migration
	}


//to turn insects off: here and at ~920
/*
Hnext = 0.0;
Pnext1 = 0.0;
Pnext2 = 0.0;
Pnext3 = 0.0;*/



// annual data:
// also appended with outbreak years AFTER the year loop
//FILE *fp3;
//fp3 = fopen(testbuff,"a");
//	fprintf(fp3, "%d, %e, %e, %e, %e, %e, %e, %e, %d, %e, %d, %d, %e, %e \n", years, Hnext, Pnext1 + Pnext2, deadcount, emptycount, alivecount, avg_aliveforest, alivesum, fire[years], current_defoliation, deaths, germinations, mean_char_height, adj_defol);
//	fclose(fp3);
//}		///////////////////////////////////											Close the year loop

FILE *outsim;
outsim = fopen(sim_output, "a");
	fprintf(outsim, "%d, %e, %e, %e, %e, %e, %e, %e, %d, %e, %d, %d, %e, %e \n", years, Hnext, Pnext1 + Pnext2, deadcount, emptycount, alivecount, avg_aliveforest, alivesum, fire[years], current_defoliation, deaths, germinations, mean_char_height, adj_defol);
	fclose(outsim);
}
///////////////////////////////////
/////////////

double num_fires;
num_fires = 0.0;
double fire_interval;
for(i = 0; i < maxyears; i++){
	num_fires +=  fire[i];
}
fire_interval = maxyears/num_fires;

for(i = 0; i < halfyears; i++){
	Hnew[i] = Hstore[i+halfyears];
	avgforest_new[i] = yearly_avgforest[i+halfyears];
	varforest_new[i] = yearly_varforest[i+halfyears];
	CVofDBH_new[i] = yearly_CVofDBH[i+halfyears];
	alivecount_new[i] = yearly_alivecount[i+halfyears];
	CValive_new[i] = yearly_CValive[i+halfyears];
	deadcount_new[i] = deadcount_new[i+halfyears];
	emptycount_new[i] = emptycount_new[i+halfyears];
	avg_aliveforest_new[i] = yearly_avg_aliveforest[i+halfyears];
	avg_deadforest_new[i] = yearly_avg_deadforest[i+halfyears];
	avg_aliveanddeadforest_new[i] = yearly_avg_aliveanddeadforest[i+halfyears];
	avg_Qmortperhost_new[i] = yearly_avg_Qmortperhost[i+halfyears];
	avg_Qmortpermort_new[i] = yearly_avg_Qmortpermort[i+halfyears];
	avg_char_height[i] = yearly_char_height[i+halfyears];
}

ReturnTime(halfyears, Hnew, Amp, Prd, Last, MaxP, OutbreakYear);
//printf("OutbreakYear %e \n", OutbreakYear[5]);

for(i = 1; i < Last[0]; i++){
	AvgAmp += Amp[i];
	AvgPd += Prd[i];
	AvgMaxP += MaxP[i];
}
AvgAmp = AvgAmp/(Last[0]-1);
AvgPd = AvgPd/(Last[0]-1);
AvgMaxP = AvgMaxP/(Last[0]-1);


	//sim_worms = log10(worms*100);
	double a_def = -4.471; double b_def = 2.843;
	//defoliation[years + 10] = 100*(1/(1 + exp(-a_def - b_def*sim_worms)));  // on a zero-100% scale, how much defoliation there will be this year

double AvgMaxDefol = 100*(1/(1 + exp(-a_def - b_def*log10(AvgMaxP))));

/*
int Outbreaks[maxyears];
for(i=0; i < maxyears; i++){
	Outbreaks[i] = 0;
	}

for(i=0; i < maxyears; i++){
	int this_index = OutbreakYear[i];
	if(this_index > 1e-6){
		Outbreaks[this_index] = 1;
	}
}

// append the annual data here:
FILE *fp3;
fp3 = fopen(testbuff,"a");
for(i=0; i < maxyears; i++){
	fprintf(fp3, "%d\n", Outbreaks[i]);
}
	fclose(fp3);*/

final_avgforest = mean(halfyears, avgforest_new);
final_varforest = mean(halfyears, varforest_new);
final_CVofDBH = mean(halfyears, CVofDBH_new);
final_alivecount = mean(halfyears, alivecount_new);
final_CValive = mean(halfyears, CValive_new);
final_deadcount = mean(halfyears, deadcount_new);
final_emptycount = mean(halfyears, emptycount_new);
final_avg_aliveforest = mean(halfyears, avg_aliveforest_new);
final_avg_deadforest = mean(halfyears, avg_deadforest_new);
final_avg_aliveanddeadforest = mean(halfyears, avg_aliveanddeadforest_new);
final_avg_Qmortperhost = mean(halfyears, avg_Qmortperhost_new);
final_avg_Qmortpermort = mean(halfyears, avg_Qmortpermort_new);
final_avg_char_height = mean(halfyears, avg_char_height);

//// this is the usual output file:
//fp_fin = fopen(testbuff_fin,"a");
//	fprintf(fp_fin, "%e, %e, %d, %e, %e, %e, %e, %e, %e, %e,  %e, %e, %e, %e, %e \n",
//AvgPd, AvgAmp, maxyears,
//final_alivecount, final_avg_aliveforest, final_CValive, final_avg_Qmortperhost, final_avg_Qmortpermort,
//num_fires, fire_interval,  maxtrees, Hnext, Winterpars.PARS2[0], Winterpars.PARS2[1], AvgMaxDefol);
//fclose(fp_fin);

FILE *finalout;
finalout = fopen(final_output, "a");
fprintf(finalout, "%e, %e, %d, %e, %e, %e, %e, %e, %e, %e,  %e, %e, %e, %e, %e \n",
	AvgPd, AvgAmp, maxyears,
	final_alivecount, final_avg_aliveforest, final_CValive, final_avg_Qmortperhost, final_avg_Qmortpermort,
	num_fires, fire_interval,  maxtrees, Hnext, Winterpars.PARS2[0], Winterpars.PARS2[1], AvgMaxDefol);
fclose(finalout);

AvgAmp = 0.0;
AvgPd = 0.0;

//printf("finished with a rep: lambda %e alpha %e \n",Winterpars.PARS2[0], Winterpars.PARS2[1]);

}}// loops over winter params

gsl_rng_free(v);
free_dmatrix(Params.forest,0,maxtrees,0,maxtrees);
free_dmatrix(Params.Hmat,0,maxtrees,0,maxtrees);
free_dmatrix(Params.Pmat1,0,maxtrees,0,maxtrees);
free_dmatrix(Params.Pmat2,0,maxtrees,0,maxtrees);
free_dmatrix(Params.Pmat3,0,maxtrees,0,maxtrees);
free_d3tensor(Params.death,0,maxtrees,0,maxtrees,0,maxyears);
//free_d3tensor(Params.germination,0,maxtrees,0,maxtrees,0,maxyears);

}  // closes main
