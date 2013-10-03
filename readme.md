C Encoder
=

Overview
-

-	1.) Simple C program for encoding videos to multiple output
-	2.) Minimal environment needed to run
	

Installation
-

-	Mac Install [link](http://ffmpeg.org/trac/ffmpeg/wiki/MacOSXCompilationGuide)
-	dependencies for special compilation to enable various different libraries etc

		brew install automake celt faac fdk-aac git lame libass libtool libvorbis libvpx \
		libvo-aacenc opencore-amr openjpeg opus sdl schroedinger shtool speex texi2html \
		theora wget x264 xvid yasm libaacs

-	ffmpeg 2.0.1 [source](http://www.ffmpeg.org/releases/ffmpeg-2.0.1.tar.bz2)
-	`wget sourceUrl && tar jxf download`
-	configure ffmpeg to use all of the revelent libraries needed

		./configure --enable-gpl --enable-version3 --enable-nonfree --enable-postproc --enable-libaacplus \
		--enable-libass --enable-libcelt --enable-libfaac --enable-libfdk-aac --enable-libfreetype --enable-libmp3lame \
		--enable-libopencore-amrnb --enable-libopencore-amrwb --enable-libopenjpeg --enable-openssl \
		--enable-libopus --enable-libschroedinger --enable-libspeex --enable-libtheora --enable-libvo-aacenc \
		--enable-libvorbis --enable-libvpx --enable-libx264 --enable-libxvid --prefix=/usr/local

-	make && make install`

Things to Consider
-

-	To Encode we need to dynamically determine:

	-	pix_fmt -- (1080p / 420p etc)
	-	fps -- frames per second

-	Encoding Job - lets attach methods to initialize the encoding job from the inputPath etc

Notes
-

-	[Encode/Decode Example](http://stackoverflow.com/questions/13565062/fps-porblem-when-saving-video-in-mp4-container)
-	[FFMPEG Example](http://ffmpeg.org/doxygen/trunk/doc_2examples_2decoding_encoding_8c-example.html)




