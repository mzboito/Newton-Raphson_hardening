#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INPUTSIZE 500001

float function(float value) {
	return (value * value * value - value * value + 2);
}

float derived_function (float value) {
	return (3 * value * value - 2 * value);
}

void readInput(char *filename, float vetor[INPUTSIZE]) {
	FILE *finput;
	int i = 0;

	if (finput = fopen(filename, "rb")) {
		while(!feof(finput) ) {
			fscanf(finput, "%f", &vetor[i]);
			i++;
		}
	} else {
		printf("Error reading input file");
		exit(1);
	}
}

void writeOutput(char *filename, float result[INPUTSIZE-1]) {
	FILE *foutput;
	int i = 0;

	if (foutput = fopen(filename, "wb")) {
		while (i < INPUTSIZE-1) {
			fprintf(foutput, "%f\n", result[i]);
			i++;
		}
	}	else {
		printf("Error reading output file");
		exit(1);
	}
}

float newton_raphson_method(float value, float allowed_error) {
  float m = function(value) / derived_function(value);

  for ( ;abs(m) >= allowed_error; ) {
        m = function(value) / derived_function(value);
        value = value - m;
  }

  return value;
}

int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf("\nERROR\n\nUsage: \n newton <inputFile>.txt <outputFile>.txt\n\n\n");
		exit(1);
	}
	float vetor[INPUTSIZE], allowed_error, result[INPUTSIZE-1];

	readInput(argv[1] , vetor);

	int i;
	float value;
	allowed_error = vetor[INPUTSIZE-1];
	for(i=0; i<INPUTSIZE-1; i++){
		float value = vetor[i];
		result[i] = newton_raphson_method(value, allowed_error);
	}

	writeOutput(argv[2], result);

	return 0;
}
