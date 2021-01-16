# HueMonitor
C++ program that integrates with the Philips Hue Platform to monitor light state changes. The program should print out all of the lights tied to the user (id, name, on state, brightness). On every refresh, the program will check to see if the brightness or on state of each light has changed and record the changes to print out. 

## System Requirements
- GCC version 4.9 or higher
- CMake 2.8 or higher
- Ubuntu 18.04

## External Dependencies 
- CmdParser
  - v1.0.0
  - https://github.com/FlorianRappl/CmdParser
- cpp-httplib 
  - v0.8.0
  - https://github.com/yhirose/cpp-httplib
  - Modified httplib.h on line 2192 from  ```using udl::operator""_;```  to ```using udl::operator"" _;``` due to compilation errors
- json 
  - v3.9.1 
  - https://github.com/nlohmann/json

## Setup and Building 
In order to build the project you will need CMake and GCC with at least the minimum versions listed above. The above external dependencies are already included in the **libs/** folder. If there are newer versions that want to be used, just update update the director name in the **CMakeLists.txt** file. Nagivate to the **build/** folder and and run **cmake ../**. This will generate the makefile needed to build the project. Once that is done, run **make** which will generate the executable **hue_monitor**.

## Usage
The executable will have the following options below:

```
  -h    --help
   This parameter is optional. The default value is ''.

  -i    --ip_address    (required)
   IP Address to connect to the bridge

  -p    --port
   Port number to connect to
   This parameter is optional. The default value is '8080'.

  -u    --user  (required)
   Authorized user to connect to bridge

  -r    --refresh_rate
   Rate for which the program checks for updates. This will be in milliseconds
   This parameter is optional. The default value is '1000'.
```

**Example:**
```
./hue_monitor -i localhost -p 8081 -u newdeveloper
```

## Testing
To test without using real philips hue smart lights, you can use the hue-simulator (https://www.npmjs.com/package/hue-simulator).
