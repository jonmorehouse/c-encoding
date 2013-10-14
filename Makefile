# initialize project structure
DIR:=$(CURDIR)
SRCDIR=src
OBJDIR=obj
INCDIR=include
EXECUTABLES=test.c main.c

# http://www.gnu.org/software/make/manual/make.html#Phony-Targets
# declare dependencies etc
FFMPEG_LIBS = libavdevice   \
	      libavformat   \
	      libavfilter   \
	      libavcodec    \
	      libswresample \
	      libswscale    \
	      libavutil     \
		
# initialize cflags and libraries 
# CFLAGS += -Wall -g -Wno-unused -pedantic
# enable gstabs to prevent the dsym folder output etc
CFLAGS += -g -gstabs -I$(INCDIR)
CFLAGS := $(shell pkg-config --cflags $(FFMPEG_LIBS)) $(CFLAGS) 
LDLIBS := $(shell pkg-config --libs $(FFMPEG_LIBS)) $(LDLIBS)

# initialize project files
# http://www.gnu.org/software/make/manual/make.html#File-Name-Functions
# grab all of the raw names from the srcs directory
# http://www.gnu.org/software/make/manual/html_node/Wildcard-Function.html
SOURCES=$(notdir $(wildcard $(SRCDIR)/**.c))

# remove executables from objects list
SOURCES:=$(filter-out $(EXECUTABLES), $(SOURCES))

# initialize all of our objects
OBJECTS:=$(addprefix $(OBJDIR)/, $(SOURCES:.c=.o))

# output file
test: $(OBJECTS) $(SRCDIR)/test.c

	@$(CC) $(CFLAGS) $(LDLIBS) $(OBJECTS) $(SRCDIR)/test.c -o test.out

# debug version
debug: $(OBJECTS) $(SRCDIR)/test.c

	@$(CC) $(CFLAGS) -g $(LDLIBS) $(OBJECTS) $(SRCDIR)/test.c -o test.out

# main output file
main.out: $(OBJECTS) $(SRCDIR)/main.c

	@$(CC) $(CFLAGS) $(LDLIBS) $(OBJECTS) $(SRCDIR)/main.c -o main.out

# build an individual object
$(OBJDIR)/%.o: $(SRCDIR)/%.c

	@$(CC) -c $(CFLAGS) $< -o $@

# remove object directories
clean:
	rm -f $(OBJDIR)/*
	rm -f $(wildcard *.out)

.PHONY: clean

