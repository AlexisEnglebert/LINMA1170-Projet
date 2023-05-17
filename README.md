# LINMA1170-Projet

# Instalation
You need: 
1. [OpenBlas](https://github.com/xianyi/OpenBLAS)
2. [GMSH](https://gitlab.onelab.info/gmsh/gmsh)
3. [SDL](https://wiki.libsdl.org/SDL2/Installation)

The first 2 library *MUST* be in the parent directory of the projet. *NOT* inside the project.

# Compilation 
```code
make
```
# Run
```code
./project <k> <out> [-s -H -h] [-o outputFile]
```
Here is an exemple
````code
./build/project 6 out.bin -v 0 -s -o fork.msh 
````
```
Usage: 
./project <k> <out> [-s -H -h] [-o outputFile]
---------------------------- 

 - k is the number of frequencies to compute. 
 - out is the output file to write the frequencies. 
 [-H] enable Harmony design
 [-s] enable sound simultation
 [-h] print the usage
 [-o] output file for geometry /!\ MUST END WITH .msh /!\ 
 
```

