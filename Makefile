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
#CFLAGS += -Wall -g -Wno-unused -pedantic
# enable gstabs to prevent the dsym folder output etc
CFLAGS += -g -gstabs
CFLAGS := $(shell pkg-config --cflags $(FFMPEG_LIBS)) $(CFLAGS)
LDLIBS := $(shell pkg-config --libs $(FFMPEG_LIBS)) $(LDLIBS)

# initialize project structure
SRCDIR=src
OBJDIR=obj
INCDIR=include

# initialize project files
#SOURCES=$($(SRCDIR)/*.c:$(SRCDIR)/=%.o)
# http://www.gnu.org/software/make/manual/make.html#File-Name-Functions

# grab all of the raw names from the srcs directory
# http://www.gnu.org/software/make/manual/html_node/Wildcard-Function.html
SOURCES=$(notdir $(wildcard $(SRCDIR)/**.c))

# initialize all of our objects
OBJECTS:=$(addprefix $(OBJDIR)/, $(SOURCES:.c=.o))

all: 
	@echo $(OBJECTS)

test.out: $(OBJECTS)
	
	@$(CC) $(CFLAGS) $(LDLIBS) $(OBJECTS) test.c -o test.out

.c.o:
	@$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -rf *.o
	rm test.out

.PHONY: clean


