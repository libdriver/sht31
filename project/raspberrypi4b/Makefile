CC     := gcc
SRC    := $(wildcard ./interface/src/*.c) \
		  $(wildcard ./driver/src/*.c) \
		  $(wildcard ./src/*.c) \
		  $(wildcard ../../src/*.c) \
		  $(wildcard ../../test/*.c) \
		  $(wildcard ../../example/*.c)
CFLAGS := -O3 \
		  -I ./interface/inc/ \
		  -I ../../interface/ \
		  -I ../../src/ \
		  -I ../../test/ \
		  -I ../../example/
sht31 : $(SRC)
		 "$(CC)" $(CFLAGS) $^ -o $@