C/C++ SDK for ADUCID authentication
===================================

Getting source code
-------------------
Use git tool to download project

    git clone https://github.com/thalman/c-aducid.git

Compile & install
-----------------

C/C++ ADUCID SDK uses autotools for compiling.

    git clone https://github.com/thalman/c-aducid.git
    cd c-aducid
    ./configure
    make
    make install

Creating RPM package
--------------------

There is SPEC file in tools directory. Creating rpm from tar archive is easy.

1. Clone ADUCID C SDK into c-aducid directory.

        git clone https://github.com/thalman/c-aducid.git

2. Pack the directory into tar archive

        tar -czf c-aducid.tgz c-aducid

3. Build rpm package

        rpmbuild -ta c-aducid.tgz

Demo
----
Demo application uses tntnet library therefore the demo works on POSIX systems.
The code is pretty straightforward and shows ADUCID usage.

To start the demo, You need

* Working AIM server.
* POSIX machine with tntnet ( >= 2.2 ) and c compiler and libcurl.
* Edit the doc/demos/login/defs.h, and fix the AIMSERVER  with propper hostname.
* Compile ADUCID library ( ./configure && make ).
* Compile demo application ( cd doc/demos/login ; make ).
* Start the tntnet server ( cd doc/demos/login ; make test ).
* Point Your browswer to http://localhost:8000 .
