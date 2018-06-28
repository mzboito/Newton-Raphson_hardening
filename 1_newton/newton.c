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

void read_input(char *filename, float *vector) {
	FILE *f_input;
	int index = 0;

	if (f_input = fopen(filename, "rb")) {
		while(!feof(f_input) ) {
			fscanf(f_input, "%f", &vector[index]);
			index++;
		}
	} else {
		printf("Error reading input file");
		exit(1);
	}
}

void write_output(char *filename, float *result) {
	FILE *f_output;
	int index = 0;

	if (f_output = fopen(filename, "wb")) {
		while (index < INPUTSIZE-1) {
			fprintf(f_output, "%f\n", result[index]);
			index++;
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
	float vector[INPUTSIZE], allowed_error, result[INPUTSIZE-1];

	read_input(argv[1] , vector);

	int i;
	float value;
	allowed_error = vector[INPUTSIZE-1];
	for(i=0; i<INPUTSIZE-1; i++){
		float value = vector[i];
		result[i] = newton_raphson_method(value, allowed_error);
	}

	write_output(argv[2], result);

	return 0;
}
