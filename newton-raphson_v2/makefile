# C compiler
CC = gcc -std=c99 -std=gnu99 -g
CC_FLAGS = -fopenmp

destDir = /tmp/newton

all: gen_bin gen_data mv_bin

gen_bin: newton.c
	$(CC) $(CC_FLAGS) newton.c -o newton

gen_data: gen_bin
	python generateSequence.py input_500k.txt 500000 0.000002
	./newton input_500k.txt gold_500k.txt

mv_bin: gen_data
	mkdir -p $(destDir)
	mv newton gold_500k.txt $(destDir)
	cp input_500k.txt $(destDir)
	@echo "All Done, executables should be in the $(destDir)"


clean: 
	rm *.o
