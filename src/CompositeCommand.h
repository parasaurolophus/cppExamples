/* Copyright 2015-2016 Kirk Rader */

#ifndef COMPOSITECOMMAND_H_
#define COMPOSITECOMMAND_H_

#include <stddef.h>
#include <deque>

#include "Command.h"

namespace examples {

/*!
 * \class CompositeCommand
 *
 * \brief Combine a sequence of Command instances into one.
 */
class CompositeCommand: public Command {

public:

    /*!
     * \brief Initialize commands.
     *
     * The first parameter is the number of Command instances.
     * The remaining arguments must be pointers to those Command
     * instances.
     *
     * \param count The number of Command instances.
     */
    explicit CompositeCommand(size_t count, ...);

    /*!
     * \brief Execute commands.
     */
    void execute();

private:

    /*!
     * The Command instances to execute.
     *
     * \see execute()
     */
    std::deque<Command*> commands;

};

}

#endif /* COMPOSITECOMMAND_H_ */
