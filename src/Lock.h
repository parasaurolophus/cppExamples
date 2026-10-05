/* Copyright 2015-2016 Kirk Rader */

#ifndef LOCK_H_
#define LOCK_H_

#include "Monitor.h"

/*!
 * \file Lock.h
 *
 * \brief Declarations for Lock
 */

namespace examples {

/*!
 * \class Lock
 *
 * \brief Lock on a Monitor
 */
class Lock {

public:

    /*!
     * \brief Lock the given Monitor.
     *
     * \param mtr The Monitor to lock.
     */
    explicit Lock(Monitor& mtr) :
            monitor(mtr) {

        monitor.lock();

    }

    /*!
     * \brief Unlock mutex
     */
    virtual ~Lock() {

        monitor.unlock();

    }

private:

    /*!
     * \brief Prevent copying instances of this class.
     */
    Lock(const Lock&);

    /*!
     * \brief Prevent assigning instances of this class.
     */
    Lock& operator=(const Lock&);

    /*!
     * \brief The locked pthread_mutex_t
     */
    Monitor& monitor;

};

}

#endif /* LOCK_H_ */
