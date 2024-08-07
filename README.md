# Windows Service Template
This is a template for creating a Windows Service in C++.

## Project initialization
After cloning repository it is required to dowload dependencies / submodules:
```bash
git submodule update --init --recursive
```
## Service building
To build the service, you need to run the following commands:
```bash
cmake -B build -S .
cmake --build build
```

After that the service can be locate in `build` / `build/Debug` directory.

## Service installation
To install the service, you need to run the following command:
```bash
sc.exe create <your_loved_service_name> binPath= "<path_to_service_executable_dir>/service_temmplate.exe --service"
```

You can configure the service by using 'config.ini' file. The file should be located in the same directory as the service executable.

## Service running

You can run the program as a console application. It is use during the development process. To run the service as a console application, you need to run the following command:
```bash
<service_executable_dir>/service_template.exe
```

## Build unit tests
To build the unit tests, you need to run the following commands:
```bash
cmake -B build-unit-tests -S . -DBUILD_UNIT_TESTS=ON
cmake --build build-unit-tests
```

Tests can be run by executing the following command:
```bash
./build-unit-tests/Debug/unit_tests.exe
```
