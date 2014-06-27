easmon-ng is a fork of multimon-ng which is a fork of multimon. It decodes the following:
- EAS only
- Everything else has been removed to make this app lighter and easier to script on RaspberryPi
- (Assuming this damn thing will compile there)
- Removed all demods except EAS
- Removed X11
- Removed Windows support

Merged changes comments from before fork (refs to removed demods are deleted):
The following changes have been made so far:
- Fixes for x64
- Basic functionality on Mac OS X 'Lion' (Soundcard/OSS input is unsupported)
- `DUMMY_AUDIO` "backend" (Gets rid of the OSS dependency, breaks audio in doing so)
- `ONLY_RAW` disables the format conversion while getting rid of posix dependencies
- Verbose mode is now listed in `-h`
- Continued EAS/SAME development. The decoder now works, but it should be considered "alpha" quality. Do not rely on it for the reception of emergency alerts!
- Portability is a major goal
- PulseAudio support, contributed by inf_l00p_
- Now accepts raw samples as piped input

In addition to the deprecated legacy Makefile there is also a file for qmake which is the preferred way of building multimon-ng. It's recommended to use qmake to generate the Makefile.

```
mkdir build
cd build
qmake ../multimon-ng.pro
make
sudo make install
```

The installation prefix can be set by passing a 'PREFIX' parameter to qmake. e.g:
```qmake multimon-ng.pro PREFIX=/usr/local```

Files can be easily converted into multimon-ng's native raw format using *sox*. e.g:
```sox -t wav pocsag_short.wav -esigned-integer -b16 -r 22050 -t raw pocsag_short.raw```
GNURadio can also generate the format using the file sink in input mode *short*. 

You can also "pipe" raw samples into multimon-ng using something like
```sox -t wav pocsag_short.wav -esigned-integer -b16 -r 22050 -t raw - | ./multimon-ng -```
(note the trailing dash)

Packaging
---------

```
qmake multimon-ng.pro PREFIX=/usr/local
make
make install INSTALL_ROOT=/
```
