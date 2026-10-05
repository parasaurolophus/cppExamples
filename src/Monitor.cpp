/* Copyright 2015-2016 Kirk Rader */

#include "Monitor.h"

namespace examples {

Monitor::Monitor() {

    pthread_mutexattr_t mutexattr;
    pthread_mutexattr_init(&mutexattr);
    pthread_mutexattr_settype(&mutexattr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&mutex, &mutexattr);
    pthread_mutexattr_destroy(&mutexattr);

    pthread_condattr_t condattr;
    pthread_condattr_init(&condattr);
    pthread_cond_init(&condition, &condattr);
    pthread_condattr_destroy(&condattr);

}

Monitor::~Monitor() {

    pthread_cond_destroy(&condition);
    pthread_mutex_destroy(&mutex);

}

void Monitor::broadcast() {

    pthread_cond_broadcast(&condition);

}

void Monitor::signal() {

    pthread_cond_signal(&condition);

}

void Monitor::wait() {

    pthread_cond_wait(&condition, &mutex);

}

void Monitor::lock() {

    pthread_mutex_lock(&mutex);

}

void Monitor::unlock() {

    pthread_mutex_unlock(&mutex);

}

}
