#include <stdio.h>

void for_loop(int *valor_ptr, int iterations, int increment) {
    for (int i = 0; i < iterations; i++) {
        *valor_ptr = *valor_ptr + increment;
    }
}

int main()
{
    int valor= 8;
    for_loop(&valor, 4, 4);
    return 0;
}