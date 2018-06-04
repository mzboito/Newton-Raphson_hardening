#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#define INPUTSIZE 500001

typedef struct arg_struct {
	char *input;
	char *output;
	float *result;

} ARGS;

float function(float value) {
	return (value * value * value - value * value + 2);
}

float derived_function (float value) {
	return (3 * value * value - 2 * value);
}

void read_input(char *filename, float vector[INPUTSIZE]) {
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

void write_output(char *filename, float result[INPUTSIZE-1]) {
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

void *interface(ARGS *s_args) {
	//duplicate everything
	float vector[INPUTSIZE], allowed_error; //, result[INPUTSIZE-1];
	read_input(s_args->input , vector);
	int index;
	float value;
	allowed_error = vector[INPUTSIZE-1];
	for(index=0; index<INPUTSIZE-1; index++) {
		float value = vector[index];
		s_args->result[index] = newton_raphson_method(value, allowed_error);
	}
	write_output(s_args->output , s_args->result);

}

int main(int argc, char *argv[]) {
	if (argc < 3) {
		printf("\nERROR\n\nUsage: \n newton <inputFile>.txt <outputFile>.txt\n\n\n");
		exit(1);
	}
	pthread_t id1, id2;
	ARGS s_args1, s_args2;
	//float v1[INPUTSIZE], v2[INPUTSIZE];

	s_args1.input = argv[1];
	s_args1.output = argv[2];
	s_args1.result = (float *)malloc(sizeof(float)*INPUTSIZE);

	s_args2.input = argv[1];
	s_args2.output = argv[2];
	s_args2.result = (float *)malloc(sizeof(float)*INPUTSIZE);


	pthread_create(&id1, NULL, (void *) interface, &s_args1);
	pthread_create(&id2, NULL, (void *) interface, &s_args2);
    pthread_join(id1, NULL);
	pthread_join(id2, NULL);

	if(memcmp(s_args1.result,s_args2.result,INPUTSIZE) != 0) {
		fprintf(stderr,"[NEWTON] SDC DETECTED\n");
	}  else {
		fprintf(stderr,"[NEWTON] PASSED\n");
	}


	return 0;
}
