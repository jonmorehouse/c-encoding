# declare dependencies etc
INCLUDE = -lavcodec -lavformat

# initialize variables for calling correct compiler commands
COMPILER = gcc
COMPILERFLAGS = $(INCLUDE)

# now actually initialize our command etc
all:
	$(COMPILER) $(COMPILERFLAGS) *.c -o test.out
	./test.out
