#Getting Started

###Cryptopp

This requires [cryptopp](https://www.cryptopp.com/) library.

Use `git submodule init`, `git submodule update` to check out [cryptopp]

Setup instructions for [Linux](https://www.cryptopp.com/wiki/Linux#Build_and_Install_the_Library), [iOS](https://www.cryptopp.com/wiki/IOS_(Xcode)#Build_the_Library)

###Build

You'll need CMake v2.8+ and gcc 4.4.7+ to build

Create a folder on the same level as backend folder, i.e. backend_build
go to backend_build

`cmake ../backend/`
`make`

this should build the Backend application

on windows you can use mingw32-make:

`cmake ../backend -G "MinGW Makefiles"`
`mingw32-make`
