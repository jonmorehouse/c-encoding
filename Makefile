# initialize project structure
SRCDIR=src
OBJDIR=obj
INCDIR=include

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
#SOURCES=$($(SRCDIR)/*.c:$(SRCDIR)/=%.o)
# http://www.gnu.org/software/make/manual/make.html#File-Name-Functions

# grab all of the raw names from the srcs directory
# http://www.gnu.org/software/make/manual/html_node/Wildcard-Function.html
SOURCES=$(notdir $(wildcard $(SRCDIR)/**.c))

# initialize all of our objects
OBJECTS:=$(addprefix $(OBJDIR)/, $(SOURCES:.c=.o))
OBJECT_OUTPUT:=$(addprefix $(OBJDIR)/, $(OBJECTS))

# output file
test.out: $(OBJECTS) $(SRCDIR)/test.c

	@$(CC) $(CFLAGS) $(LDLIBS) $(OBJECTS) $(SRCDIR)/test.c -o test.out


# main output file
main.out: $(OBJECTS)

	@$(CC) $(CFLAGS) $(LDLIBS) $(OBJECTS) main.c -o main.out

# build an individual object
$(OBJDIR)/%.o: $(SRCDIR)/%.c

	@$(CC) -c $(CFLAGS) $< -o $@

# remove object directories
clean:
	rm $(OBJDIR)/*
	rm test.out

.PHONY: clean

