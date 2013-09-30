High Level
-

1.)	Allocate proper variables
2.)	Parse and open file 
3.)	Grab a handle for each stream (video, audio etc)
4.) 	Loop through each frame of the stream and create an AVFrame
5.)	For each frame, queue it up to be encoded into the proper format 

AVFrame
-

-	structure to hold buffers etc for each frame
-	can be an audio or video stream
-	reference this [documentation](http://ffmpeg.org/doxygen/trunk/structAVFrame.html#details)

Sample Programs
-

[Decode->Encode](http://ffmpeg.org/pipermail/libav-user/2012-December/003378.html)
[Basic Tutorial](http://www.inb.uni-luebeck.de/~boehme/using_libavcodec.html)
[Old Tutorial](http://dranger.com/ffmpeg/tutorial01.c)

Transport Streams
-

-	[Overview](http://documentation.apple.com/en/compressor/usermanual/index.html#chapter=18%26section=3%26tasks=true)
-	Application: transport streams -- contain several mpeg-2 content channels and associated audio. 




