# Sort Command

## This is a C program to simulate the Linux Sort Command and it works on the External Merge Sort Algorithm.

## Primary use cases include sorting of files beyond the primary memory and additional options to sort based on order.

### Functioning of the algorithm

1. Reads an input file from the user and splits into smaller parts readable in the main memory.
2. Uses Merge Sort for sorting the smaller parts and store them on the secondary memory.
3. Run the merging of the sorted files and combine the output into a single file.

### To run this project

`Clone the repository`

```
#Build the project
make

#Run the program
Run ./a.out [option] filename [filename]
```

## Usage

```This program can be built and run using autotools
    Run the following commands to get started with the tool

    ./configure
    make
    sudo make install

    cd src && ./mysort.o filename [options]
```

## Options available

```
-r The default order of sorting is ascending. Use this flag to sort in descending order

-b Sort lines by ignoring the leading blank spaces

-o Store the output of the result in a file specified as a parameter

-f Ignore the case of the aplhabets on sorting.

-d Sort based on dictionary order

-n Sort based on numerical values

-m Merges files specified as operands in a sorted order

-u Prints out the unique lines in the sorted file

-nr Numeric reverse sort

-i Sort by ignoring non printable characters

-k Sorts by the . delimiter

```
