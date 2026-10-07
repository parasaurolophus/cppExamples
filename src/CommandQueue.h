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
 * @mermaid
 * swimlane-beta TB
 *
 * subgraph command queue thread
 *     dequeue[wait for command,<br>dequeue]
 *     execute
 *     terminate
 * end
 *
 * subgraph application thread
 *     start[create command queue]
 *     work1[...some work...]
 *     enqueue1[enqueue]
 *     work2[...some more work...]
 *     enqueue2[enqueue]
 *     work3[...continue...]
 *     delete[delete command queue]
 *     join
 * end
 *
 * start --> work1
 * work1 --> enqueue1
 * enqueue1 --> work2
 * work2 --> enqueue2
 * enqueue2 --> work3
 * work3 --> delete
 * delete --> join
 *
 * dequeue -- command --> execute
 * execute --> dequeue
 * dequeue -- detach --> terminate
 *
 * start -- constructor --> dequeue
 * enqueue1 -- command --> dequeue
 * enqueue2 -- command --> dequeue
 * delete -- destructor --> dequeue
 * terminate --> join
 * @endmermaid
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
     * @mermaid
     * ---
     * title: CommandQeue
     * ---
     * stateDiagram
     * [*] --> dequeue
     *     dequeue --> run: command
     *     run --> dequeue: command->execute()
     *     run --> catch: exception
     *     catch --> dequeue: log(exception)
     * @endmermaid
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
