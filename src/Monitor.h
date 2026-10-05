/* Copyright 2015-2016 Kirk Rader */

#ifndef MONITOR_H_
#define MONITOR_H_

#include <pthread.h>

/*!
 * \file Monitor.h
 *
 * \brief Declarations for examples::Monitor
 */

namespace examples {

/*!
 * \class Monitor
 *
 * \brief Thread synchronization monitor.
 */
class Monitor {

public:

    /*!
     * \brief Initialize the pthread_mutex_t and pthread_cond_t wrapped by this instance.
     */
    Monitor();

    /*!
     * \brief Destroy the pthread_mutex_t and pthread_cond_t wrapped by this instance.
     */
    virtual ~Monitor();

    /*!
     * \brief Send notification to all thread currently awaiting this Monitor.
     *
     * \see signal()
     * \see wait()
     */
    void broadcast();

    /*!
     * \brief Send notification to one thread currently awaiting this Monitor.
     *
     * \see broadcast()
     * \see wait()
     */
    void signal();

    /*!
     * \brief Block the calling thread until it is notified by this monitor.
     *
     * \see broadcast()
     * \see signal()
     */
    void wait();

private:

    /*!
     * \brief Prevent copying instances of this class.
     */
    Monitor(const Monitor&);

    /*!
     * \brief Prevent assigning instances of this class.
     */
    Monitor& operator=(const Monitor&);

    /*!
     * \brief Lock this Monitor
     *
     * \see Lock::Lock(Monitor&)
     */
    void lock();

    /*!
     * \brief Unlock this Monitor
     *
     * \see Lock::~Lock()
     */
    void unlock();

    /*!
     * \brief The pthread_mutex_t wrapped by this instance.
     */
    pthread_mutex_t mutex;

    /*!
     * \brief The pthread_cond_t wrapped by this instance.
     */
    pthread_cond_t condition;

    friend class Lock;

};

}

#endif /* MONITOR_H_ */
