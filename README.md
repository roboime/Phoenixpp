# Phoenixpp
Phoenixpp is the RoboIME's SSL Robot soccer software.
It is a multithreading application built in C++ and developed with [CLion IDE](https://www.jetbrains.com/clion/).

The application provides a protobuf client for [SSL_Vision](https://github.com/RoboCup-SSL/ssl-vision) and [SSL_Referee](https://github.com/RoboCup-SSL/ssl-game-controller/tree/master) applications and implements the RoboIME's AI software with the goal of competing on Robocup's Small Size League robot soccer.
It also provides support for [grSim simulator](https://github.com/RoboCup-SSL/grSim).

## Usage
You need to install the following dependencies:
- [CMake](https://cmake.org/)
- [Protobuf](https://developers.google.com/protocol-buffers)
- [nlohmann/json](https://github.com/nlohmann/json)
- [Qt 6.7.0](https://www.qt.io/)

Alternatively, if you are using CLion on windows, you can easily install the dependencies with [Vcpkg](https://www.jetbrains.com/help/clion/package-management.html#install-vcpkg).
I also recommend installing plantUml plugin on CLion to visualize the UML diagrams.

To use Clion you need a [student license](https://www.jetbrains.com/shop/eform/students.) as well.