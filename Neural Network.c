#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "libann.h"

int trIn[NUMTRAIN][NUMINPUT] = {0};
int trOut[NUMTRAIN] = {0};
double current_o[NUMTRAIN] = {0};



/* 
 * Function to read training data.  Data from "in.csv" is stored in array
 * "trIn", and that from "out.csv" in array "trOut".
 *
 * Returns zero if success, or one if there is an error.
 */
int read_data(void) {


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void) {
	FILE * openin = fopen("in.csv", "r");
	int ch;
	int i = 0;
	int j = 0;

	if (openin == NULL){
		printf("File not found and cannot be printed.\n");
		return 1;
	}
	int trIn[4][2];

	while((ch = fgetc(openin)) != EOF){
		if (ch != '\n' && ch != ',' ){
			trIn[i][j] = ch - 48;
		}
		else if (ch == ','){
			j++;
		}
		else if (ch == '\n'){
			i++;
			j = 0;
		}
	}
	/*for (i = 0; i<4; i++)
    {
        for (j = 0; j < 2; j++)
        {
            printf("%d\n", trIn[i][j]);

        }
    }*/

	fclose(openin);
	
	FILE * openout = fopen("out.csv", "r");

	if(openout == NULL){
		printf("File not found and cannot be printed.\n");
		return 1;
	}
	int trOut[4];

	i = 0;

	while((ch = fgetc(openout)) != EOF){
		if (ch != '\n'){
			trOut[i] = ch - 48;
		}
		else if(ch == '\n'){
			i++;
		}
	}

	for (i = 0; i<4; i++)
    {
        for (j = 0; j < 2; j++)
        {
            printf("%d\n", trIn[i][j]);
          

        }
    }

    for (i = 0; i<4; i++)
    {  
             printf("%d\n", trOut[i]);

    }

	fclose(openout);
	return 0;
}
	

}

/* Function to produce output of one neuron */
double neuron(const int num_in, const double input[num_in], const double weight[num_in], const double bias) {

	double a, z, total = 0;
	float sigmoid_function;

	for (int i = 1; i <= num_in ; ++i)
	{
		total = total + (input[i-1] * weight[i-1]);
	}
	a = total + bias;
	sigmoid_function = 1/(1 + exp(-1 * a));
	return sigmoid_function;


}

void learn(void) {
	int i, k, p;
	double DeltaWeightIH[NUMHIDDEN][NUMINPUT], 
		   DeltaWeightHO[NUMOUTPUT][NUMHIDDEN],
		   DeltaBiasIH[NUMHIDDEN],
		   DeltaBiasHO[NUMOUTPUT];
	double WeightIH[NUMHIDDEN][NUMINPUT], WeightHO[NUMOUTPUT][NUMHIDDEN];
	double DeltaO[NUMOUTPUT+1], SumDOW[NUMHIDDEN+1], DeltaH[NUMHIDDEN+1];
	double biasIH[NUMHIDDEN], biasHO[NUMOUTPUT];
	double eta = 0.5, alpha = 0.9, smallwt = 0.5;
	int index[NUMTRAIN]={0};
	double error;

	init_network(DeltaWeightIH, DeltaWeightHO, DeltaBiasIH, DeltaBiasHO,
			WeightIH, WeightHO, biasIH, biasHO, smallwt);


	error = 0;

	for (int i = 0; i < NUMTRAIN; ++i)
	{
		index[i] = i;
		for (k = 1; k<= 1000; ++k){
			error = update_network(DeltaWeightIH, DeltaWeightHO, 
			        DeltaBiasIH, DeltaBiasHO,
					WeightIH, WeightHO, biasIH, biasHO,
					DeltaO, DeltaH, SumDOW, eta, alpha, index[1]);

		}
		shuffle_index(index);
	}

	printf("\n\nPat\t") ;   // print network outputs
	for( i = 1 ; i <= NUMINPUT ; i++ ) {
		fprintf(stdout, "Input%-1d\t", i) ;
	}
	for( k = 1 ; k <= NUMOUTPUT ; k++ ) {
		fprintf(stdout, "Target%-1d\tOutput%-1d\t", k, k) ;
	}
	for( p = 0 ; p < NUMTRAIN ; p++ ) {
		fprintf(stdout, "\n%d\t", p) ;
		for( i = 0 ; i < NUMINPUT ; i++ ) {
			fprintf(stdout, "%d\t", trIn[p][i]) ;
		}
		for( k = 1 ; k <= NUMOUTPUT ; k++ ) {
			fprintf(stdout, "%d\t%f\t", trOut[p], current_o[p]) ;
		}
	}
	printf("\n");
	return;
}
