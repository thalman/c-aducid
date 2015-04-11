C/C++ SDK for ADUCID authentication
===================================

Getting source code
-------------------
Use git tool to download the project

    git clone https://github.com/thalman/c-aducid.git

Compile & install
-----------------

C/C++ ADUCID SDK uses autotools for compiling. Try autoreconf if You have
different version of autotools.

    git clone https://github.com/thalman/c-aducid.git
    cd c-aducid
    # autoreconf -vfi
    ./configure 
    make
    make install

Building the documentation
--------------------------

Documentation is written in doxygen, build it with following commands:

    cd c-aducid
    doxygen Doxyfile

Documentation is stored in doc/html directory.

Creating RPM package
--------------------

There is SPEC file in tools directory. Creating rpm from tar archive is easy.

1. Clone ADUCID C SDK into c-aducid directory.

        git clone https://github.com/thalman/c-aducid.git

2. Pack the directory into tar archive.

        tar -czf c-aducid.tgz c-aducid

3. Build rpm package.

        rpmbuild -ta c-aducid.tgz

Hint: install the doxygen first if You want documentation in devel rpm.

Build on windows
----------------

### MS Visual studio
1. Make sure that Your devenv.exe is on PATH.
2. Run build.bat script.

        cd c-aducid
        build.bat

### Mingw
1. Make sure Your Mingw is properly installed.
2. Install libcurl including development packages.
3. Check compilation options on top of the Makefile.mingw file.
4. Run make to compile

        cd c-aducid
        make -f Makefile.mingw

Demo
----
Demo application uses tntnet library therefore the demo works on POSIX systems.
The code is pretty straightforward and shows ADUCID usage.

To start the demo, You need

* Working AIM server.
* POSIX machine with tntnet ( >= 2.2 ) and c compiler and libcurl.
* Edit the doc/demos/*/defs.h, and fix the AIMSERVER  with propper hostname.
* Compile ADUCID library ( ./configure && make ).
* Compile demo application ( cd doc/demos/login ; make ).
* Start the tntnet server ( cd doc/demos/login ; make test ).
* Point Your browswer to http://localhost:8000 .
