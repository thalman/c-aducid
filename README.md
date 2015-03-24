C/C++ SDK for ADUCID authentication
===================================

Compile
-------
C/C++ ADUCID SDK uses autotools for compiling.
************************************************************************
./configure
make
make install
************************************************************************

Demo
----
Demo application uses tntnet library therefore the demo works on POSIX systems.
The code is pretty strightforward and shows ADUCID usage.

To start the demo, You need
* Working AIM server.
* POSIX machine with tntnet ( >= 2.2 ) and c compiler and libcurl.
* Edit the doc/demos/login/defs.h, and fix the AIMSERVER  with propper hostname.
* Compile ADUCID library ( ./configure && make ).
* Compile demo application ( cd doc/demos/login ; make ).
* Start the tntnet server ( cd doc/demos/login ; make test ).
* Point Your browswer to http://localhost:8000 .
