#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INPUTSIZE 500001

float function1(float value) {
	return (value * value * value - value * value + 2);
}

float function2(float value) {
	return (value * value * value - value * value + 2);
}

float derived_function1(float value) {
	return (3 * value * value - 2 * value);
}

float derived_function2(float value) {
	return (3 * value * value - 2 * value);
}

void read_input1(char *filename, float *vector) {
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

void read_input2(char *filename, float *vector) {
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

void write_output1(char *filename, float *result) {
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

void write_output2(char *filename, float *result) {
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

float newton_raphson_method1(float value, float allowed_error) {
  float m = function1(value) / derived_function1(value);

  for ( ;abs(m) >= allowed_error; ) {
        m = function1(value) / derived_function1(value);
        value = value - m;
  }
  return value;
}

float newton_raphson_method2(float value, float allowed_error) {
  float m = function2(value) / derived_function2(value);

  for ( ;abs(m) >= allowed_error; ) {
        m = function2(value) / derived_function2(value);
        value = value - m;
  }
  return value;
}

void main_loop1(float *vector, float *result) {
	int i;
	float value;
	float allowed_error = vector[INPUTSIZE-1];
	for(i=0; i<INPUTSIZE-1; i++){
		float value = vector[i];
		result[i] = newton_raphson_method1(value, allowed_error);
	}
}

void main_loop2(float *vector, float *result) {
	int i;
	float value;
	float allowed_error = vector[INPUTSIZE-1];
	for(i=0; i<INPUTSIZE-1; i++){
		float value = vector[i];
		result[i] = newton_raphson_method2(value, allowed_error);
	}
}

int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf("\nERROR\n\nUsage: \n newton <inputFile>.txt <outputFile>.txt\n\n\n");
		exit(1);
	}
	float vector1[INPUTSIZE], result1[INPUTSIZE-1];
	float vector2[INPUTSIZE], result2[INPUTSIZE-1];

	read_input1(argv[1] , vector1);
	read_input2(argv[1] , vector2);

	main_loop1(vector1, result1);
	main_loop2(vector2, result2);

	write_output1(argv[2], result1);
	write_output2(argv[2], result2);

	//result2[0] = -200;
	if(memcmp(result1,result2,INPUTSIZE) != 0) {
		fprintf(stderr,"[NEWTON] SDC DETECTED\n");
	}  else {
		fprintf(stderr,"[NEWTON] PASSED\n");
	}
	return 0;
}
