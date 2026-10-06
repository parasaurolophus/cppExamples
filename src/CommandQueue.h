/* Copyright 2015-2016 Kirk Rader */

#ifndef COMMANDQUEUE_H_
#define COMMANDQUEUE_H_

#include <deque>

#include "Command.h"
#include "Monitor.h"
#include "Thread.h"

/*!
 * \file CommandQueue.h
 *
 * \brief Declarations for examples::CommandQueue
 */

namespace examples {

/*!
 * \class CommandQueue
 *
 * \brief Asynchronous FIFO queue.
 *
 * Executes a sequence of Command objects in a worker thread.
 *
 * For example, the following diagram depicts the asynchronous
 * execution of two commands followed by application
 * termination, but only after both commands have completed.
 *
 * [TODO: insert mermaid diagram here]
 */
class CommandQueue: public Thread<void, void> {

public:

    /*!
     * \brief Start the worker thread.
     */
    CommandQueue();

    /*!
     * \brief Append the given Command to the FIFO queue.
     */
    void enqueue(Command*);

protected:

    /*! \brief Command processing loop.
     *
     * Executed in the worker thread.
     *
     * [TODO: insert mermaid here]
     *
     * \param argument Worker thread procedure's
     *                 argument.
     *
     * \return 0
     */
    void* execute(void* argument);

private:

    /*!
     * \brief Prevent copying instances of this class.
     */
    CommandQueue(const CommandQueue&);

    /*!
     * \brief Prevent assigning instances of this class.
     */
    CommandQueue& operator=(const CommandQueue&);

    /**
     * \brief Return the next item from the FIFO queue.
     *
     * Blocks the calling thread while the queue is empty.
     *
     * \return The next Command to execute or `null`.
     */
    Command* dequeue();

    /*!
     * \brief FIFO queue
     */
    std::deque<Command*> queue;

    /*!
     * \brief Monitor used to synchronize access to queue.
     */
    Monitor monitor;

};

}

#endif /* COMMANDQUEUE_H_ */
