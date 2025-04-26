# LiftSync
An Elevator System Simulation application built in C++, utilizing asynchronous threading infrastructure.
The project provides a Docker-based development environment and uses CMake to build the application for x86 platforms.

Currently the elevator calls can be generated from ```main.cpp``` and must be made with ```100 ms``` difference between them to avoid inter-thread communication issues. 

Every elevator spawns a new thread which is responsible for executing movement tasks assigned to that evevator. Requests are placed into a message queue and mutex-protected for safe inter-thread communication. Futher, the requests are assigned to the nearest available elevator that is currently in an IDLE state.


## Build docker container
```
docker build -t ubuntu-dev-image .
```

## Run the docker container
```
docker run -it --mount type=bind,source="$(pwd)",target=/workspace ubuntu-dev-image
```

## Make a build directory 
```
cd LifySync
mkdir -p build
cd build
```

## Generate Makefiles using Cmake
```
cmake ..
```

## Build the application 
```
make -j12
```

## WIP
- Adding unit tests
- UI to register new requests
- Add priority/sequencing