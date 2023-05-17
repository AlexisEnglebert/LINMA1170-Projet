# LINMA1170-Projet

# Instalation
You need: 
1. [OpenBlas](https://github.com/xianyi/OpenBLAS)
2. [GMSH](https://gitlab.onelab.info/gmsh/gmsh)
3. [SDL](https://wiki.libsdl.org/SDL2/Installation)

The firt 2 library *MUST* be in the parent directory of the projet. *NOT* inside the project.

# Compilation 
```code
make
```
# Run
```code
./build/project <k> <out> -v 0
```
```
./project <k> <out>
---------------------------- 
- k is the number of frequencies to compute. 
- out is the output file to write the frequencies. 
```

