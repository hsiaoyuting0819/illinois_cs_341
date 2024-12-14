#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// Reader Writer Problem
/*
    Possible Console Output
    reader 0 starts reading.
    reader 0 ends reading.
    writer 0 starts writing.
    writer 0 ends writing.
    writer 1 starts writing.
    writer 1 ends writing.
    writer 3 starts writing.
    writer 3 ends writing.
    writer 2 starts writing.
    writer 2 ends writing.
    reader 3 starts reading.
    reader 1 starts reading.
    reader 2 starts reading.
    reader 3 ends reading.
    reader 2 ends reading.
    reader 1 ends reading.
*/

#define READER_CNT 4
#define WRITER_CNT 4

int writer;  // to prevent writer from starvation
int writing;
int reading;
pthread_mutex_t m;
pthread_cond_t cv;

pthread_barrier_t b;

void* myRead(void* arg) {
    pthread_barrier_wait(&b);

    pthread_mutex_lock(&m);
    while (writer)
        pthread_cond_wait(&cv, &m);
    // No need to wait writing here,
    // since writer == 0 -> writing == 0
    /*
    while (writing)
        pthread_cond_wait(&cv, &m);
    */

    ++reading;
    pthread_mutex_unlock(&m);

    // do read
    printf("reader %d starts reading.\n", *(int*)arg);
    sleep(1);
    printf("reader %d ends reading.\n", *(int*)arg);

    pthread_mutex_lock(&m);
    --reading;
    pthread_cond_broadcast(&cv);
    pthread_mutex_unlock(&m);

    return NULL;
}

void* myWrite(void* arg) {
    pthread_barrier_wait(&b);

    pthread_mutex_lock(&m);
    ++writer;
    while (writing || reading)
        pthread_cond_wait(&cv, &m);

    ++writing;
    pthread_mutex_unlock(&m);

    // do write
    printf("writer %d starts writing.\n", *(int*)arg);
    sleep(1);
    printf("writer %d ends writing.\n", *(int*)arg);

    pthread_mutex_lock(&m);
    --writing;
    --writer;
    pthread_cond_broadcast(&cv);
    pthread_mutex_unlock(&m);

    return NULL;
}

int main() {
    writer = 0;
    writing = 0;
    reading = 0;
    pthread_mutex_init(&m, NULL);
    pthread_cond_init(&cv, NULL);
    pthread_barrier_init(&b, NULL, READER_CNT + WRITER_CNT);

    pthread_t reader_id[READER_CNT];
    pthread_t writer_id[WRITER_CNT];
    int print_rid[READER_CNT];
    int print_wid[WRITER_CNT];
    {
        int i = 0;
        while (i < READER_CNT || i < WRITER_CNT) {
            if (i < READER_CNT) {
                print_rid[i] = i;
                pthread_create(&reader_id[i], NULL, myRead, &print_rid[i]);
            }
            if (i < WRITER_CNT) {
                print_wid[i] = i;
                pthread_create(&writer_id[i], NULL, myWrite, &print_wid[i]);
            }
            ++i;
        }
    }

    {
        int i = 0;
        while (i < READER_CNT || i < WRITER_CNT) {
            if (i < READER_CNT) {
                pthread_join(reader_id[i], NULL);
            }
            if (i < WRITER_CNT) {
                pthread_join(writer_id[i], NULL);
            }
            ++i;
        }
    }

    pthread_barrier_destroy(&b);
    pthread_cond_destroy(&cv);
    pthread_mutex_destroy(&m);
    return 0;
}
