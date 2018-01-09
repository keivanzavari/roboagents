/* rand example: guess the number */
#include <iostream>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

int main ()
{
    int map_size = 10;
    int num_blocked = 10;

    /* initialize random seed: */
    srand (time(NULL));

    int rand_row, rand_col;
    int num_rand_generated = 1;

    while (num_rand_generated < num_blocked) {
        /* generate random number between 1 and map_size-1 */
        rand_row = rand() % (map_size - 2) + 1;
        rand_col = rand() % (map_size - 2) + 1;
        // map_[rand_int][rand_int] = '1';

        std::cout << "(" << rand_row << "," << rand_col << ")  ";
        num_rand_generated++;
    }
    std::cout << std::endl;
    return 0;
}
