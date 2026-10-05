/* Copyright 2015-2016 Kirk Rader */

#ifndef COMMAND_H_
#define COMMAND_H_

/*!
 * \file Command.h
 *
 * \brief Declarations for examples::Command
 */

namespace examples {

/*!
 * \class Command
 *
 * \brief Objects that can be invoked asynchronously using CommandQueue
 *
 * \see CommandQueue::enqueue(Command*)
 */
class Command {

public:

    /*!
     * \brief Virtual destructor
     */
    virtual ~Command() {

        // nothing to do in the base class

    }

    /*!
     * \brief Method invoked asynchronously using CommandQueue
     *
     * \see CommandQueue::enqueue(Command*)
     */
    virtual void execute() = 0;

};

}

#endif /* COMMAND_H_ */
