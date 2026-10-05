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
 * @startuml{examples_CommandQueue_activity.png}
 * scale max 500*600
 * 'title Activity depicting asynchronous\ninvocation of two commands\nfollowed by application\ntermination after both\ncommands have completed
 * (*) --> ===B1===
 * partition "application thread" {
 *     --> "some work..." as one
 *     --> queue.enqueue(command1)
 *     --> "...more work..." as two
 *     --> queue.enqueue(command2)
 *     --> "...even more work..." as three
 *     --> queue.enqueue(null)
 *     --> queue.join()
 * }
 * --> ===B2===
 * --> (*)
 * partition "queue thread" {
 *     ===B1=== --> "dequeue()" as wait
 *     if "" then
 *         --> [null\ncommand] ===B2===
 *     else
 *         --> [valid\ncommand] command.execute()
 *         if "" then
 *             --> [command\nthrew\nexception] log(exception)
 *             --> wait
 *         else
 *             --> [command\nexited\nnormally] wait
 *         endif
 *     endif
 * }
 * @enduml
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
     * @startuml{examples_CommandQueue_state.png}
     * scale max 500*600
     * state wait
     * wait: dequeue()
     * state run
     * run: command->execute()
     * state error
     * error: log(exception)
     * [*] -> wait
     * wait -> run: valid command
     * wait --> [*]: null\ncommand
     * run -> wait: command exists normally
     * run --> error: command\nthrows\nexception
     * error -up-> wait : error\nlogged
     * @enduml
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
