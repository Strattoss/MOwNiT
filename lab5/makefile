FILE_NAME=matrix_multip
RESULTS_NAME=results
CC=gcc
FLAGS=-Wall -lgsl

all: $(FILE_NAME).exe

generate: $(FILE_NAME).exe
	./$(FILE_NAME).exe > $(RESULTS_NAME).csv

$(FILE_NAME).exe: $(FILE_NAME).c
	$(CC) $(FLAGS) $< -o $@
