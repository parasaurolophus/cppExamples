/* Copyright 2015-2016 Kirk Rader */

#ifndef THREAD_H_
#define THREAD_H_

#include <pthread.h>

namespace examples {

/*! \brief Wrapper for pthread_t.
 *
 * This class is not intended for direct use.
 * Use Thread<ARGUMENT, RESULT> instead.
 *
 * \see Thread<ARGUMENT, RESULT>
 */
class GenericThread {

public:

    /*! \brief Detach thread.
     *
     * This calls pthread_detach(), allowing threads
     * to be launched in a "fire and forget" style
     * using this class.
     */
    virtual ~GenericThread();

protected:

    /*! \brief Start this thread.
     *
     * This will invoke _execute() in
     * a separate thread of execution.
     *
     * \param argument The thread's parameter.
     *
     *\see run(void*)
     * \see _execute()
     */
    GenericThread(void* argument);

    /*! \brief The worker thread procedure.
     *
     * This method will be invoked in
     * its own thread of execution.
     *
     * \param argument Worker thread procedure's
     *                 argument.
     *
     * \return The result of the worker
     *         thread's calculation.
     */
    virtual void* _execute(void* argument) = 0;

    /*! \brief Block the calling thread
     *         until this one terminates.
     *
     * \return The result returned by _execute()
     *         in the worker thread.
     */
    void* _join();

private:

    /*! \brief Start the given GenericThread
     *
     * "Glue" between the object-oriented API provided
     * by this class and the non-object-oriented pthread API.
     *
     * \param genericThread Pointer to the GenericThread to start.
     *
     * \return The result returned by the given
     *         GenericThread::_execute() function.
     */
    static void* run(void* genericThread);

    /*! \brief Prevent copying instances of this class.
     */
    GenericThread(const GenericThread&);

    /*! \brief Prevent assigning instances of this class.
     */
    GenericThread& operator=(const GenericThread&);

    /*! \brief The worker thread procedure's argument.
     */
    void* argument;

    /*! \brief The wrapped pthread_t.
     */
    pthread_t thread;

};

/*! \brief Type-safe wrapper for pthread_t
 *
 * \param ARGUMENT The worker thread procedure's
 *                 parameter type.
 *
 * \param RESULT The worker thread procedure's
 *               result type.
 */
template<class ARGUMENT, class RESULT>
class Thread: public GenericThread {

public:

    /*! \brief Block the calling thread until this one terminates.
     *
     * \return The result returned by execute() in the worker thread.
     */
    RESULT* join() {

        return reinterpret_cast<RESULT*>(_join());

    }

protected:

    /*! \brief Start the worker thread
     *
     * \param argument The worker thread procedure's argument.
     */
    explicit Thread(ARGUMENT* argument) :
            GenericThread(argument) {

    }

    /*! \brief Worker thread procedure.
     *
     * This function will be invoked in its own thread of execution.
     *
     * \param argument Worker thread procedure's
     *                 argument.
     *
     * \return The result of the worker thread's calculation.
     */
    virtual RESULT* execute(ARGUMENT* argument) = 0;

    /*! \brief Call execute().
     *
     * \param argument Worker thread procedure's
     *                 argument.
     *
     * \return Whatever is returned by execute().
     */
    void* _execute(void* argument) {

        return execute(argument);

    }
};

}

#endif /* THREAD_H_ */
