# Assignment 3 Sorting: Putting your affairs in order

## Description:
	This program contains implementations of Shell, Batcher, Heap, and Quick sorts 
	based on provided pseudocode in C. A test harness is implemented to test each
	of these sorts by creating an array of pseudorandom elements and running each
	sort on it.
	
## Build:

To build the program:

```
$ make
```

## Running:

To run the program:

```
$ ./sorting [-Hasbhqn:p:r:] [-n length] [-p elements] [-r seed]
```

```
OPTIONS:
   -H              Display program help and usage.
   -a              Enable all sorts.
   -s              Enable Shell Sort.
   -b              Enable Batcher Sort.
   -h              Enable Heap Sort.
   -q              Enable Quick Sort.
   -n length       Specify number of array elements (default: 100).
   -p elements     Specify number of elements to print (default: 100).
   -r seed         Specify random seed (default: 13371453).
```

## Cleaning:

To clean the program files:

```
$ make clean
```

## Files:

### batcher.c
```
implements batcher sort
```

### batcher.h
```
specifies interface to batcher.c
```

### shell.c
```
implements shell sort
```

### shell.h
```
specifies interface to shell.c
```

### gaps.h
```
provides gap sequence to be used by shell sort
```

### heap.c
```
implements heap sort
```

### heap.h
```
specifies interface to heap.c
```

### quick.c
```
implements recursive quicksort
```

### quick.h
```
specifies interface to quick.c
```

### set.c
```
implements bitwise set operations
```

### set.h
```
specifies interface to set.c
```

### stats.c
```
implements the stats module
```

### stats.h
```
specifies interface to stats module
```

### sorting.c
```
contains main() and other functions necessary
```
