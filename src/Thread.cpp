/* Copyright 2015-2016 Kirk Rader */

#include "Thread.h"

#include <stdexcept>

namespace examples {

void* GenericThread::run(void* p) {

    GenericThread* genericThread = reinterpret_cast<GenericThread*>(p);
    return genericThread->_execute(p);

}

GenericThread::GenericThread(void* arg) :
        argument(arg) {

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    int result = pthread_create(&thread, &attr, run, this);
    pthread_attr_destroy(&attr);

    if (0 != result) {

        throw std::logic_error("error starting thread");

    }
}

GenericThread::~GenericThread() {

    pthread_detach(thread);

}

void* GenericThread::_join() {

    void* result;
    pthread_join(thread, &result);
    return result;

}

}
