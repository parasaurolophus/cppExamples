/* Copyright 2015-2016 Kirk Rader */

#include "CompositeCommand.h"

#include <stdarg.h>
#include <stdexcept>

namespace examples {

CompositeCommand::CompositeCommand(size_t count, ...) {

    va_list alist;
    va_start(alist, count);

    for (size_t index = 0; index < count; ++index) {

        Command* command = va_arg(alist, Command*);

        if (0 == command) {

            throw std::domain_error("Command may not be null");

        }

        commands.push_back(command);

    }

    va_end(alist);

}

void CompositeCommand::execute() {

    std::deque<Command*>::iterator current = commands.begin();
    std::deque<Command*>::iterator end = commands.end();

    while (current != end) {

        Command* command = *current++;
        command->execute();

    }
}

}
