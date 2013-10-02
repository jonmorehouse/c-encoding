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

utilities.o: utilities.c utilities.h

	gcc -c $(CFLAGS) $(LDFLAGS) utilities.c

decode.o: decode.c decode.h

	gcc -c $(CFLAGS) $(LDFLAGS) decode.c

encode.o: encode.c encode.h

	gcc -c $(CLFAGS) $(LDFLAGS) encode.c
	
test: decode.o encode.o utilities.o test.c

	gcc $(CFLAGS) $(LDLIBS) decode.o encode.o utilities.o test.c -o test.out

clean: 
	rm *.o
	rm ./test.out


