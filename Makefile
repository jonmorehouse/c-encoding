# declare dependencies etc
FFMPEG_LIBS = libavdevice   \
	      libavformat   \
	      libavfilter   \
	      libavcodec    \
	      libswresample \
	      libswscale    \
	      libavutil     \
		
# initialize cflags and libraries 
CFLAGS += -Wall -g
CFLAGS := $(shell pkg-config --cflags $(FFMPEG_LIBS)) $(CFLAGS)
LDLIBS := $(shell pkg-config --libs $(FFMPEG_LIBS)) $(LDLIBS)

decode.o: decode.c decode.h

	gcc -c $(CFLAGS) $(LDFLAGS) decode.c
	
test: decode.o

	gcc $(CFLAGS) $(LDLIBS) decode.o test.c -o test

clean: 
	rm *.o

