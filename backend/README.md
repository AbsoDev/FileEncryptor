#Getting Started

###Cryptopp

This requires [cryptopp](https://www.cryptopp.com/) library.
Use `git submodule init` `git submodule update` to check out [cryptopp]
Setup instructions for [Linux](https://www.cryptopp.com/wiki/Linux#Build_and_Install_the_Library), [iOS](https://www.cryptopp.com/wiki/IOS_(Xcode)#Build_the_Library)

###Compile and Run

Compile:
```
g++ -o exec ./main.cpp ./crypto.cpp -std=c++11 -I PATH_TO_CRYPTOPP_MASTER -Lcryptopp-master -l:libcryptopp.a
```
Run Encryption:
```
exec -i INPUT_FILE -o OUTPUT_FILE -k KEY_FILE -e
```
Run Decryption:
```
exec -i INPUT_FILE -o OUTPUT_FILE -k KEY_FILE -d
```
