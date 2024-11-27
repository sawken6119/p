#include <stdio.h>
#include "map.h"
#include "phase.h"
#include "tree.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "MemoryLeak"

int main() {
    t_map map = createMapFromFile("..\\maps\\example1.map");
    printf("Map created with dimensions %d x %d\n", map.y_max, map.x_max);
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%d ", map.soils[i][j]);
        }
        printf("\n");
    }
    // printf the costs, aligned left 5 digits
    printf("\n");

    phase();
    return 0;

}


#pragma clang diagnostic pop
