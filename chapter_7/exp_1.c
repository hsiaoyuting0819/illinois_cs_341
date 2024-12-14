#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    pthread_mutex_t m;
    int count;
    double* values;
} stack_t;

stack_t* stack_create(int capacity) {
    stack_t* ret = malloc(sizeof(stack_t));
    ret->count = 0;
    ret->values = malloc(sizeof(double) * capacity);
    pthread_mutex_init(&ret->m, NULL);
    return ret;
}

void stack_destroy(stack_t* s) {
    free(s->values);
    pthread_mutex_destroy(&s->m);
    free(s);
}

void push(stack_t* s, double num) {
    pthread_mutex_lock(&s->m);
    s->values[(s->count)++] = num;
    pthread_mutex_unlock(&s->m);
}

double pop(stack_t* s) {
    pthread_mutex_lock(&s->m);
    double ret = s->values[--(s->count)];
    pthread_mutex_unlock(&s->m);
    return ret;
}

// Functions that return sizes are ususally removed or deprecated,
// in thread_safe data structures,
// since its result may already be out-of-date
int isEmpty(stack_t* s) {
    pthread_mutex_lock(&s->m);
    int ret = (s->count == 0);
    pthread_mutex_unlock(&s->m);
    return ret;
}

int main() {
    return 0;
}
