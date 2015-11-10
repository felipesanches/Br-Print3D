## BR-Print3D

BR-Print3D is a libre software 3D printing host.

## Licensing terms

**TO-DO:** Add licensing information here.

## Build Instructions

Grab the source code from this repository using git and then
run the following commands to install dependencies and to build the program:

```sh
git clone https://github.com/Simple-BR/Br-Print3D.git
sudo apt-get install libxmu-dev qttools5-dev qttools5-dev-tools freeglut3-dev
mkdir build
cd build
cmake ..
make
```