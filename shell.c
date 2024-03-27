#include "gaps.h"
#include "stats.h"

#include <stdio.h>
#include <stdlib.h>

void shell_sort(Stats *stats, uint32_t *arr, uint32_t length) {
    for (uint32_t gap = 0; gap < (sizeof(gaps) / sizeof(uint32_t)); gap++) { // loop through gaps
        for (uint32_t i = gaps[gap]; i < length; i++) { // for each gap until length - 1
            uint32_t j = i;
            uint32_t temp = move(stats, arr[i]);
            while (j >= gaps[gap] && cmp(stats, temp, arr[j - gaps[gap]]) == -1) { //
                arr[j] = move(stats, arr[j - gaps[gap]]);
                j -= gaps[gap];
            }
            arr[j] = temp;
            arr[j] = move(stats, arr[j]);
        }
    }
}
