#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INPUTSIZE 500001

float function(float value) {
	return (value * value * value - value * value + 2);
}

float derived_function(float value) {
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


void main_wrapper(char *path, float *vector, float *result) {
	read_input(path, vector);
	int i;
	float value;
	float allowed_error = vector[INPUTSIZE-1];
	for(i=0; i<INPUTSIZE-1; i++){
		float value = vector[i];
		result[i] = newton_raphson_method(value, allowed_error);
	}
}

void cat_log(char *log_path) {
	FILE *log;
	if(log = fopen(log_path,"a")) {
		fprintf(log, "1\n");
		fclose(log);
	}

}

int main(int argc, char *argv[]) {
	if (argc != 4) {
		printf("\nERROR\n\nUsage: \n <name> <inputFile>.txt <outputFile>.txt <detection_log>.txt\n\n\n");
		exit(1);
	}
	float vector1[INPUTSIZE], result1[INPUTSIZE-1];
	float vector2[INPUTSIZE], result2[INPUTSIZE-1];
	
	main_wrapper(argv[1], vector1, result1);
	main_wrapper(argv[1], vector2, result2);
	char *log_path = argv[3];

	//result2[0] = -200; // << this checks that the memcmp is working
	if(memcmp(result1,result2,INPUTSIZE) != 0) {
		cat_log(log_path);
	}

	write_output(argv[2], result1);
	return 0;
}
