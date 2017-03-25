# HEURISTICS

## Compiling
### Windows
on window run the build.bat. Note you need cl.exe (included in visual studios) with version >= vs2012 (this is need for c++11 support) and 64 bit machine (you can change the bat to 32 bit).
### Linux 
on linux run make file or run.sh (runs make and then runs the program with simple test)
## Running 
To run the program
### Windows
```
bin/driver.exe [path to .csv file] [source id]
```
### Linux
```
bin/driver.o [path to .csv file] [source id] 
```
## CSV file format:
The first column must be type for the row
then attributes

Example file:
```
type, arg_1, arg_2, ... , arg_n
type, arg_1, arg_2, ... , arg_n
```
### Defined types:
#### Node (type=N)
type,id,name
#### Edge (type=E)
type,source,target,cost
