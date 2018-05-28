# C compiler
CC = gcc -std=c99 -std=gnu99 -g
CC_FLAGS = -fopenmp

destDir = /tmp/newton

all: gen_bin gen_data mv_bin

gen_bin: newton.c
	$(CC) $(CC_FLAGS) newton.c -o selective_2

gen_data: gen_bin
	./selective_2 ../inputs/input_500k.txt ../inputs/gold_500k.txt

mv_bin: gen_data
	mkdir -p $(destDir)
	mv selective_2 $(destDir)
	cp ../inputs/input_500k.txt ../inputs/gold_500k.txt $(destDir)
	@echo "All Done, executables should be in the $(destDir)"


clean: 
	@echo "nothing to remove"
