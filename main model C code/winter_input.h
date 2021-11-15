int inputdata(void *Paramstuff)
{

STRUCTURE* Params;
Params = (STRUCTURE*) Paramstuff;


//////////////// changeable parameters:
int lag=10;	// lag between the defoliation occurrence and the effect on fires - goes into an algorithm

int defol_switch=0; // if zero, no defoliation; if 1, defoliation occurs

int which_file = 1; // the order is: 0-2: past, central-east-north;
					//                3-5: future, central-east-north


//
Params->lag = lag;
Params-> defol_switch = defol_switch;
Params-> which_file = which_file;

char filename[128];
char f0[128] = "central_past_short_weather_table.txt";
char f1[128] = "east_past_short_weather_table.txt";
char f2[128] = "north_past_short_weather_table.txt";
char f3[128] = "central_future_short_weather_table.txt";
char f4[128] = "east_future_short_weather_table.txt";
char f5[128] = "north_future_short_weather_table.txt";

if(which_file == 0){
	strcpy(filename, f0);
}
if(which_file==1){
	strcpy(filename, f1);
}
if(which_file == 2){
	strcpy(filename, f2);
}
if(which_file==3){
	strcpy(filename, f3);
}
if(which_file == 4){
	strcpy(filename, f4);
}
if(which_file==5){
	strcpy(filename, f5);
}

//char scenario[128] = "central_past_short";
//char fileend[128] = "_weather_table.txt";
//char filename[128];
//strcpy(filename, scenario);
//strcat(filename, fileend);
//printf("%s \n", filename);
//Params->filename = filename;
//printf("%s \n", Params->filename);


////////////////
int i, j, k;

#define MAX_TREES 250  //lots of trees

#define MAX_YEARS 1000 //lots of years
Params->forest = dmatrix(0, MAX_TREES, 0, MAX_TREES);
Params->lifematrix = imatrix(0, MAX_TREES, 0, MAX_TREES);

Params->agemat = imatrix(0, MAX_TREES, 0, MAX_TREES);

Params->Hmat = dmatrix(0, MAX_TREES, 0, MAX_TREES);
Params->Pmat1 = dmatrix(0, MAX_TREES, 0, MAX_TREES);
Params->Pmat2 = dmatrix(0, MAX_TREES, 0, MAX_TREES);
Params->Pmat3 = dmatrix(0, MAX_TREES, 0, MAX_TREES);

Params->death = d3tensor(0, MAX_TREES, 0, MAX_TREES, 0, MAX_YEARS);  /// this should be years*trees*trees, but let's assume for now that 10,000 years is plenty
Params->normvar = d3tensor(0, MAX_TREES, 0, MAX_TREES, 0, MAX_YEARS);  /// this should be years*trees*trees, but let's assume for now that 10,000 years is plenty
Params->fire_death = d3tensor(0, MAX_TREES, 0, MAX_TREES, 0, MAX_YEARS);

// read in DBH lookup table:
int dbh_length=100;
//int dbh_length=50;

Params->dbh_increase = dvector(0, dbh_length);
Params->dbh_length = dbh_length;

double dbh_lookup[dbh_length];

for (i=0;i<dbh_length;i++)	{
	FILE *ftp_data;
	ftp_data=fopen("dbh_increase_table.txt","r");
	if (ftp_data==0)	{printf("file %d open error \n",j);			}
		while (fscanf(ftp_data,"%lf\n",&dbh_lookup[i])!= EOF)			{
		Params->dbh_increase[i]=dbh_lookup[i];
		 i++;
	}
	fclose(ftp_data);
}

int supp_length=101;
Params->dbh_supp = dmatrix(0, supp_length, 0, 1);
Params->supp_length = supp_length;

double pct_def[supp_length];
double pct_growth[supp_length];

for (i=0;i<supp_length;i++){
	FILE *ftp_data;
	ftp_data=fopen("growth_suppression_table.txt","r");
	if (ftp_data==0)	{printf("file %d open error \n",j);			}
		while (fscanf(ftp_data,"%lf %lf \n",&pct_def[i],&pct_growth[i])!= EOF)			{
		Params->dbh_supp[i][0]=pct_def[i];
		Params->dbh_supp[i][1]=pct_growth[i];
		 i++;
	}

	fclose(ftp_data);
}

// read in fire weather table:
int fire_weather_length=500;
Params->fire_weather = dmatrix(0, fire_weather_length, 0, 3);

double fwi[fire_weather_length];
double dc[fire_weather_length];
double ch_C3[fire_weather_length];
double ch_C4[fire_weather_length];

for (i=0;i<fire_weather_length;i++)	{
	FILE *ftp_data;
	//ftp_data=fopen("north_future_short_weather_table.txt","r");
	ftp_data=fopen(filename,"r");

	if (ftp_data==0)	{printf("file %d open error \n",j);			}
		while (fscanf(ftp_data,"%lf %lf %lf %lf \n",&fwi[i],&dc[i],&ch_C3[i],&ch_C4[i])!= EOF)			{
		Params->fire_weather[i][0]=fwi[i];
		Params->fire_weather[i][1]=dc[i];
		Params->fire_weather[i][2]=ch_C3[i];
		Params->fire_weather[i][3]=ch_C4[i];
		 i++;
	}
	fclose(ftp_data);
}
return 0;
}

