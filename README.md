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


A silly C++ library to parse command line parameters for your C and C++ programs.

Copyright 2015 Geoffrey John Atkinson
geoffrey_atkinso@hotmail.com (yes, this is a spam account)

Ascii art by "jgs" at http://ascii.co.uk/  Nice work "jgs"!

At some point I actually *do* plan on a C API for this.

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

Note that this is FOSS released under the LGPL v3.  See the file LICENSE
for details.

So here it is.

[1.1] Source Code
-----------------

At the time of this writing, the source code can be found at:

https://github.com/gatkinso/qwikpirate

[1.2] How to use
----------------

The theory of operation is simple:  in your main() function, instantiate an ArgVee object.  

Call setOption() to add options for your program to handle -- at this time you can also add callbacks
for these options.  The flags can be specified as optional and flag only (no associated value).

Call ArgVee::parse() to parse and verify the argc and argv parameters passed into your main function.

If there are any errors, a list of them will be returned to you to present to the user (or whatever else
you feel like doing with them).

If you call the apply() function the registered callbacks for the individual options are called having 
the flag name and it's associated value passed into the callback.

The callbacks provide no thread synchronization.

The flags are parsed based on a regular expression.  Values are not verified - they simply cannot contain spaces.
The regex can be changed to suit your needs when you instantiate the ArgVee object.

You can then retrieve the pased in values with the getFlag() methods.  There are convienience methods to
pull out values as bools, doubles, ints, and strings.  The output to getValue() returns a list of values allowing
a flag to be passed in multiple times with multiple values.  Or, simply use the callback/apply method described
above.

The default flag regex is two dashes followed by an alphanumeric string.  Order is not enforced or preserved.
Flag evaluation is case sensitive.

Example:  > app.exe --flag1 value1 --flag2 --flag3 value3

Example (with code):   > myprogram  --matey --parrot Polly

    int main(int argc, const char* argv[])
    {
        std::vector<std::string> errors;
        
        qwikpirate::ArgVee arrrg;
        //Use: flag, optional?, flag only?, callback (optional - defaults to null)
        arrrg.setOption("--matey", true, true, nullptr);
        arrrg.setOption("--parrot", false, false);
        arrrg.setOption("--pegleg", true, true);
        
        bool success = a.parse(argc, argv, errors);
        if(!success) { //deal with it.... }
        
        // the rest of your program...
    }

When myprogram is run, the --parrot flag must be present and it must be trailed with a value.  --matey and --pegleg
are optional.  As shown, the success boolean would evaluate to true when run (--pegleg is optional).

Running...

    > myprogram  --matey --parrot --pegleg 

would have sucess evaluate to false (--parrot is missing its value).

See the unit tests for more examples.

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
> cmake --build . --target install --config [Debug|Release|DebWithRelInfo|MinRelSize]

[3.1] Build Instructions (Linux/OSX)
------------------------------------

> cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=[Debug|Release|DebWithRelInfo|MinSizeRel] <source directory>
> cmake --build . --target install

Feel free to experiment with other generators, esp XCode.  Hint hint.

[3.2] Build Shared Libraries
----------------------------

To build the cli library as a shared library define the CMake variable 
BUILD_SHARED_LIB:

-DBUILD_SHARED_LIB

Note that this is not quite working correctly on OS X yet.  It builds, but I need to deal with @rpath.

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

