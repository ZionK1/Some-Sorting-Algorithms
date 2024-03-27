#include "batcher.h"
#include "gaps.h"
#include "heap.h"
#include "quick.h"
#include "set.h"
#include "shell.h"
#include "stats.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "Hahbsqr:n:p:"

// randomize array
static void rand_arr(uint32_t *A, uint32_t seed, uint32_t size) {
    srandom(seed); // set seed for random()
    for (uint32_t i = 0; i < size; i++) {
        uint32_t rand = random() & 0x3fffffff; // bit mask to 30 bits
        A[i] = rand;
    }
}

// print array
static void print_arr(uint32_t *A, uint32_t size) {
    for (uint32_t i = 0; i < size; i++) { // looping through array
        printf("%13" PRIu32, A[i]);
        if ((i + 1) % 5 == 0) { // every five elements print newline
            printf("\n");
        }
    }
    // if size of array is not multiple of 5 print new line
    if (size % 5 != 0) {
        printf("\n");
    }
}

// init stats struct
Stats stats;

int main(int argc, char **argv) {
    // set default values for sort tests
    uint64_t seed = 13371453;
    uint32_t size = 100;
    uint32_t elements = 100;

    // create Set struct
    Set s = set_empty();

    // enum sorts to check in set
    enum sorts { SHELL, BATCHER, HEAP, QUICK };

    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'H':
            printf("%s\n", "SYNOPSIS");
            printf("%s\n\n", "   A collection of comparison-based sorting algorithms.");
            printf("%s\n", "USAGE");
            printf("%s\n\n", "   ./sorting [-Hasbhqn:p:r:] [-n length] [-p elements] [-r seed]");
            printf("%s\n", "OPTIONS");
            printf("%s\n", "   -H              Display program help and usage.");
            printf("%s\n", "   -a              Enable all sorts.");
            printf("%s\n", "   -s              Enable Shell Sort.");
            printf("%s\n", "   -b              Enable Batcher Sort.");
            printf("%s\n", "   -h              Enable Heap Sort.");
            printf("%s\n", "   -q              Enable Quick Sort.");
            printf("%s\n", "   -n length       Specify number of array elements (default: 100).");
            printf(
                "%s\n", "   -p elements     Specify number of elements to print (default: 100).");
            printf("%s\n", "   -r seed         Specify random seed (default: 13371453).");
            return 0;
        case 'a':
            s = set_insert(s, SHELL);
            s = set_insert(s, BATCHER);
            s = set_insert(s, HEAP);
            s = set_insert(s, QUICK);
            break;
        case 'h': s = set_insert(s, HEAP); break;
        case 'b': s = set_insert(s, BATCHER); break;
        case 's': s = set_insert(s, SHELL); break;
        case 'q': s = set_insert(s, QUICK); break;
        case 'r': seed = strtoul(optarg, NULL, 10); break;
        case 'n': size = strtoul(optarg, NULL, 10); break;
        case 'p':
            elements = strtoul(optarg, NULL, 10);
            if (size < elements) {
                elements = size;
            }
            break;
        default:
            printf("%s\n", "SYNOPSIS");
            printf("%s\n\n", "   A collection of comparison-based sorting algorithms.");
            printf("%s\n", "USAGE");
            printf("%s\n\n", "   ./sorting [-Hasbhqn:p:r:] [-n length] [-p elements] [-r seed]");
            printf("%s\n", "OPTIONS");
            printf("%s\n", "   -H              Display program help and usage.");
            printf("%s\n", "   -a              Enable all sorts.");
            printf("%s\n", "   -s              Enable Shell Sort.");
            printf("%s\n", "   -b              Enable Batcher Sort.");
            printf("%s\n", "   -h              Enable Heap Sort.");
            printf("%s\n", "   -q              Enable Quick Sort.");
            printf("%s\n", "   -n length       Specify number of array elements (default: 100).");
            printf(
                "%s\n", "   -p elements     Specify number of elements to print (default: 100).");
            printf("%s\n", "   -r seed         Specify random seed (default: 13371453).");
            return -1;
        }
    }

    // dynamically allocate array used for sorting
    uint32_t *A = (uint32_t *) calloc(size, sizeof(uint32_t));

    // run shell sort
    if (set_member(s, SHELL)) {
        reset(&stats); // clear stats
        rand_arr(A, seed, size); // randomize array with given seed
        shell_sort(&stats, A, size); // run shell sort on array
        printf("%s, %" PRIu32 " elements, %" PRIu64 " moves, %" PRIu64 " compares\n", "Shell Sort",
            size, stats.moves, stats.compares); // print stats for sort
        if (size < elements) {
            print_arr(A, size);
        } else {
            print_arr(A, elements); // print sorted array with specified # of elements
        }
    }

    // run batcher sort
    if (set_member(s, BATCHER)) {
        reset(&stats); // clear stats
        rand_arr(A, seed, size); // randomize array with given seed
        batcher_sort(&stats, A, size); // run batcher sort on array
        printf("%s, %" PRIu32 " elements, %" PRIu64 " moves, %" PRIu64 " compares\n",
            "Batcher Sort", size, stats.moves, stats.compares); // print stats for sort
        if (size < elements) {
            print_arr(A, size);
        } else {
            print_arr(A, elements); // print sorted array with specified # of elements
        }
    }

    // run heap sort
    if (set_member(s, HEAP)) {
        reset(&stats); // clear stats
        rand_arr(A, seed, size); // randomize array with given seed
        heap_sort(&stats, A, size); // run heap sort on array
        printf("%s, %" PRIu32 " elements, %" PRIu64 " moves, %" PRIu64 " compares\n", "Heap Sort",
            size, stats.moves, stats.compares); // print stats for sort
        if (size < elements) {
            print_arr(A, size);
        } else {
            print_arr(A, elements); // print sorted array with specified # of elements
        }
    }

    // run quick sort
    if (set_member(s, QUICK)) {
        reset(&stats); // clear stats
        rand_arr(A, seed, size); // randomize array with given seed
        quick_sort(&stats, A, size); // run quick sort on array
        printf("%s, %" PRIu32 " elements, %" PRIu64 " moves, %" PRIu64 " compares\n", "Quick Sort",
            size, stats.moves, stats.compares); // print stats for sort
        if (size < elements) {
            print_arr(A, size);
        } else {
            print_arr(A, elements); // print sorted array with specified # of elements
        }
    }

    // free allocated memory for array
    free(A);
}
