# Phoenixpp
Phoenixpp is the RoboIME's SSL Robot soccer software.
It is a multithreading application built in C++ and developed with [CLion IDE](https://www.jetbrains.com/clion/).

The application provides a protobuf client for [SSL_Vision](https://github.com/RoboCup-SSL/ssl-vision) and [SSL_Referee](https://github.com/RoboCup-SSL/ssl-game-controller/tree/master) applications and implements the RoboIME's AI software with the goal of competing on Robocup's Small Size League robot soccer.
It also provides support for [grSim simulator](https://github.com/RoboCup-SSL/grSim).
## Description
The project is divided into the following modules:
- **Core**: Implements an Agent base class that is inherited
by the other modules. Each agent is responsible for performing some 
specific task and then share their updated data with other agents.
The AgentController class is responsible for managing the agents execution in concurrent threads.
It will also choose each Agent implementation dynamically based on the [strategy pattern](https://refactoring.guru/design-patterns/strategy).
- **Qt**: Implements a Qt GUI for the project. 
- **Factories**: Implement factories that will instantiate the agents
based on the strategy pattern. See [factory pattern](https://refactoring.guru/design-patterns/factory-method).
- **Messaging**: Is responsible for the communication between the agents. It is based on the [observer pattern](https://refactoring.guru/design-patterns/observer).
Each Agent will have a Publisher instance that will distribute the Message with the update.
As the Listener have to deal with different kind of Messages, it will accept the visitor implementation of the corresponding Message.
See [visitor pattern](https://refactoring.guru/design-patterns/visitor).
This way, every Agent will have a Listener for each Message it wants to have updates from.
- **IO**: Implements classes for receiving and sending Serial and Udp data.
- **Vision**: The vision is responsible for decoding the protobuf messages from camera and filtering the data with Kalman.
- **Referee**: Similarly to the vision, it will decode protobuf messages from the referee or produce manual commands.
- **Feedback**: Decode information sent by the robots such as battery level, wheel velocity, spinner sensor, etc.
- **AI**: Responsible for the decision-making of the robots. It will receive the filtered data from the Vision, commands
Referee and Feedback from robots, send commands to the robots.
- **PathPlanning**: 
- **Navigation**: 
- **Communicator**: 
## Install dependencies
We are using QT installed from the [official website](https://www.qt.io/download-dev), install the latest 6.x version with the QT installer along with the recommended dependencies in the default path. If you are using Windows QT will be installed on "C:/Qt/...", you'll need to write these lines to the CMakeLists.txt file or change if they are already in there:

```cmake
set(QT6_DIR "C:/Qt/6.7.2/mingw_64/lib/cmake/Qt6")
set(CMAKE_PREFIX_PATH "C:/Qt/6.7.2/mingw_64" ${CMAKE_PREFIX_PATH})
```
These two lines are set in my computer for the version 6.7.2, if you installed other version change it accordingly.

You need to install the following dependencies:
- [CMake](https://cmake.org/)
- [Protobuf](https://developers.google.com/protocol-buffers)
- [nlohmann/json](https://github.com/nlohmann/json)
- [GTest](https://github.com/google/googletest)
- boost-atomic

If you are using CLion on windows, you can easily install the dependencies with [Vcpkg](https://www.jetbrains.com/help/clion/package-management.html#install-vcpkg). If you are having problems instaling packages via the vcpkg plugin on Clion try installing them directly via terminal, for that you'll need to find where your vcpkg is installed, open a terminal in that folder and run the command to install the package. Example: `.\vcpkg.exe install qtbase`.

I also recommend installing plantUml plugin on CLion to visualize the UML diagrams.

To use Clion you need a [student license](https://www.jetbrains.com/shop/eform/students.) as well.
