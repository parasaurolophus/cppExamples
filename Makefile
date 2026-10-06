OBJS = src/unit_tests.o src/CommandQueue.o src/CompositeCommand.o src/Monitor.o src/Thread.o

unit_tests : $(OBJS)
	g++ -o unit_tests $(OBJS)

.PHONY : clean cleanall cleandocs docs

docs : cleandocs
	-doxygen

clean :
	-rm src/*.o

cleanall : clean cleandocs
	-if ( -f unit_tests ); then rm unit_tests; fi

cleandocs :
	-if ( -d docs ); then rm -rf docs; fi
