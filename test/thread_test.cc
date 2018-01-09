#include <iostream>
#include <cstdlib>
#include <stdint.h> // intptr_t

#include <pthread.h>


#define NUM_THREADS 5


class Foo {
  public:
    static void* func(void* arg) {
      char *test = (char *) arg;
      std::cout << test << std::endl;
    }
};

void *PrintHello(void *threadid) {
    // long tid;
    long tid = (intptr_t) threadid;
    std::cout << "Hello World! Thread ID, " << tid << std::endl;
    pthread_exit(NULL);
}

int main () {
    pthread_t threads[NUM_THREADS];
    int rc;
    int i;

    for( i = 0; i < NUM_THREADS; i++ ) {
        std::cout << "main() : creating thread, " << i << std::endl;
        rc = pthread_create(&threads[i], NULL, PrintHello, (void *)(intptr_t)i);

    if (rc) {
        std::cout << "Error:unable to create thread," << rc << std::endl;
        exit(-1);
        }
    }

    char * msg = (char *)"Hi dude";
    Foo ins;
    pthread_t pt;
    pthread_create( &pt, NULL, ins.func, (void*)msg );
    pthread_join(pt, NULL);
    
    pthread_exit(NULL);
}