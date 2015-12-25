QwikPirate - "ARRRG-vee, Matey!"
================================
                     _____
                  .-" .-. "-.
                _/ '=(0.0)=' \_
              /`   .='|m|'=.   `\
              \________________ /
          .--.__///`'-,__~\\\\~`
         / /6|__\// a (__)-\\\\
         \ \/--`((   ._\   ,)))
         /  \\  ))\  -==-  (O)(
        /    )\((((\   .  /)))))
       /  _.' /  __(`~~~~`)__
      //"\\,-'-"`   `~~~~\\~~`"-.
     //  /`"              `      `\
    //


A silly C++ library to parse command line parameters for your C and C++ programs*.

(c)2015-2015 Geoffrey John Atkinson
geoffrey_atkinso@hotmail.com (yes, this is a spam account)

Ascii art by "jgs" at http://ascii.co.uk/  Nice work "jgs"!

*At some point I actually *do* plan on a C API for this.

[1.0] Introduction
==================

Is it really so complicated to parse a command line?  Judging by the plethora
of bloated/convoluted/obfuscated "solutions" for such... one might think so.

QwikPirate attemps to simplify this with an 20/80 approach:  20% of the work will
satisfy 80% of the population. As for the other 20% of the population... I dunno.
Boost maybe.

This project is also meant to serve as an example.  Primarily for some C++11 
(and later C++14) techniques.  Additionally, it is also little tutorial for 
learning basic CMake, and eventually Google Mock.  

These tutorial aspects will never take precedence over the primary mission of 
being a simple command line parser with no external dependencies - aside from 
GMock/GTest and the standard C++ library.

Note that this is FOSS released under the LGPL v2.1.  See the file LICENSE
for details.

So here it is.

[1.1] Source Code
-----------------

At the time of this writing, the source code can be found at:

https://github.com/gatkinso/qwikpirate

[2.0] Build Requirements
========================

CMake 3.1.0 or greater

[2.1] Build Requirements (Windows)
----------------------------------

Visual Studio 13 or greater

[2.2] Build Requirements (Linux)
--------------------------------

gcc 4.9 or greater

[2.3] Build Requirements (OSX)
------------------------------

LLVM capable of C++11.  Whatever the latest XCode ships with (Dec 2015) should 
suffice.

[3.0] Build Instructions (Windows)
==================================

> cmake -G "Visual Studio 12 Win64" <source directory>
> cmake --build . --config [Debug|Release|DebWithRelInfo|MinRelSize]

[3.1] Build Instructions (Linux/OSX)
------------------------------------

> cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug <source directory>
> cmake --build . --config [Debug|Release|DebWithRelInfo|MinSizeRel]

Feel free to experiment with other generators, esp XCode.  Hint hint.

[3.2] Build Shared Libraries
----------------------------

To build the cli library as a shared library define the CMake variable 
BUILD_SHARED_LIB:

-DBUILD_SHARED_LIB

[4.0] Unit tests
================

QwikPirate uses Google Mock and Google Test for the unit test framework.

To build the unit tests define the CMake variable BUILD_UNIT_TESTS:

    -DBUILD_UNIT_TESTS

The following environment variables need to be set:

	GOOGLE_TEST_INC_DIR : location of gtest headers
	GOOGLE_MOCK_INC_DIR : location of gmock headers
	GOOGLE_TEST_LIB_DIR : location of gtest libraries
	GOOGLE_MOCK_LIB_DIR : location of gmock libraries
	
If not statically linking to the Google libraries, be sure to be able to
resolve the GTest/GMock shared libraries when running the unit tests.





