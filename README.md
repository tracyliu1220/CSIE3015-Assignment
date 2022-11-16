# CSIE3015 Assignment Sample Code

## Installation

Please follow [the instructions](https://openfhe-development.readthedocs.io/en/latest/sphinx_rsts/intro/installation/linux.html) to install OpenFHE in a system directory.

Or, execute the following commands.

```
git clone https://github.com/openfheorg/openfhe-development
cd openfhe-development
mkdir build
cd build
cmake ..
make -j4
sudo make install
```

## Build

Construct Makefile.
```
cd build
cmake ..
```

Compile and generate executables. (under directory `build`)
```
make
```

## Test

Run local tests. (under root directory)
```
./test/run <student id>
```

## Contact

Please feel free to contact the TA through tracyliu981220@gmail.com if you have any questions.
