# declare dependencies etc
INCLUDE = -lavformat -lavcodec

# initialize variables for calling correct compiler commands
COMPILER = gcc
COMPILERFLAGS = $(INCLUDE)

all:
	$(COMPILER) $(COMPILERFLAGS) *.c -o test.out
	./test.out
