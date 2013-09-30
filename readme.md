C Encoder
=

Overview
-

-	1.) Simple C program for encoding videos to multiple output
-	2.) Minimal environment needed to run
	

Installation
-

-	ffmpeg 2.0.1 [source](http://www.ffmpeg.org/releases/ffmpeg-2.0.1.tar.bz2)
-	`wget sourceUrl && tar jxf download`
-	`./configure --prefix=/usr/local && make && make install`

Things to Consider
-

-	To Encode we need to dynamically determine:

	-	pix_fmt -- (1080p / 420p etc)
	-	fps -- frames per second

-	Encoding Job - lets attach methods to initialize the encoding job from the inputPath etc

Notes
-

-	[Encode/Decode Example](http://stackoverflow.com/questions/13565062/fps-porblem-when-saving-video-in-mp4-container)




