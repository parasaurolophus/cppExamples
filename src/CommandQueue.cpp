/* Copyright 2015-2016 Kirk Rader */

#include "CommandQueue.h"

#include <exception>
#include <iostream>

#include "Lock.h"

namespace examples {

CommandQueue::CommandQueue() :
        Thread<void, void>(0) {

}

void CommandQueue::enqueue(Command* command) {

    Lock lock(monitor);
    queue.push_back(command);
    monitor.broadcast();

}

Command* CommandQueue::dequeue() {

    Lock lock(monitor);

    while (queue.empty()) {

        monitor.wait();

    }

    Command* command = queue.front();
    queue.pop_front();
    return command;

}

void* CommandQueue::execute(void*) {

    Command* command;

    while (0 != (command = dequeue())) {

        try {

            command->execute();

        } catch (std::exception& e) {

            std::cerr << e.what() << std::endl;

        }
    }

    return 0;

}

}
