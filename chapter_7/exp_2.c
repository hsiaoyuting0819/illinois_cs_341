// Ref: https://www.gnu.org/software/libc/manual/html_node/Feature-Test-Macros.html
// If you define this macro,
// everything is included:
// ISO C89, ISO C99, POSIX.1, POSIX.2, BSD, SVID, X/Open, LFS, and GNU extensions.
// In the cases where POSIX.1 conflicts with BSD,
// the POSIX definitions take precedence.
#define _GNU_SOURCE

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// An example of pthread_barrier_t

#define THREAD_COUNT 4

pthread_barrier_t barrier;

void* func(void* arg) {
    pthread_t id = pthread_self();

    int wait_sec = 1 + rand() % 5;
    printf("(%ld) thread%d() wait for %d seconds.\n", id, *((int*)arg), wait_sec);
    sleep(wait_sec);

    printf("(%ld) thread%d() ready.\n", id, *((int*)arg));
    pthread_barrier_wait(&barrier);
    printf("(%ld) thread%d() on-going.\n", id, *((int*)arg));
    return NULL;
}

int main() {
    srand(time(NULL));

    pthread_barrier_init(&barrier, NULL, THREAD_COUNT + 1);

    pthread_t ids[THREAD_COUNT];
    int print_ids[THREAD_COUNT];

    for (int i = 0; i < THREAD_COUNT; ++i) {
        print_ids[i] = i;
        pthread_create(&ids[i], NULL, func, &print_ids[i]);
    }

    printf("(%ld) main() is ready.\n", pthread_self());
    pthread_barrier_wait(&barrier);
    printf("(%ld) main() is on-going.\n", pthread_self());

    for (int i = 0; i < THREAD_COUNT; ++i) {
        pthread_join(ids[i], NULL);
    }

    pthread_barrier_destroy(&barrier);

    return 0;
}

