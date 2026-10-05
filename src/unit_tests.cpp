/* Copyright 2015-2016 Kirk Rader */

#include <stddef.h>
#include <deque>
#include <exception>
#include <iostream>

#include "Command.h"
#include "CommandQueue.h"
#include "Lock.h"
#include "Monitor.h"

using namespace std;

static examples::Monitor monitor;

static deque<unsigned> state;

class MockCommand: public examples::Command {

public:

    explicit MockCommand(unsigned i) :
            n(i) {

    }

    void execute() {

        examples::Lock lock(monitor);
        state.push_back(n);
        monitor.signal();

    }

private:

    unsigned n;

};

int main() {

    try {

        examples::CommandQueue commandQueue;
        MockCommand mockCommand1(1);
        MockCommand mockCommand2(2);
        MockCommand mockCommand3(3);
        commandQueue.enqueue(&mockCommand1);
        commandQueue.enqueue(&mockCommand2);
        commandQueue.enqueue(0);
        commandQueue.enqueue(&mockCommand3);
        commandQueue.join();
        examples::Lock lock(monitor);
        size_t size = state.size();

        if (2 != size) {

            cerr << "expected 2 items, found " << size << endl;

        }

        unsigned n;

        n = state.front();
        state.pop_front();

        if (1 != n) {

            cerr << "expected 1, found " << n << endl;

        }

        n = state.front();
        state.pop_front();

        if (2 != n) {

            cerr << "expected 2, found " << n << endl;

        }

        cout << "all tests passed" << endl;
        return 0;

    } catch (exception& e) {

        cerr << e.what() << endl;
        return 10;

    }
}
