# Makefile

# the C++ compiler
CXX     = g++
CXXVERSION = $(shell g++ --version | grep ^g++ | sed 's/^.* //g')

# options to pass to the compiler
CXXFLAGS = -O0 -g3

ifeq "$(CXXVERSION)" "4.6.3"
	CXXFLAGS += -std=c++0x
else
	CXXFLAGS += -std=c++11
endif

All: all
all: main

main:	main.cpp Path.o ModelPriority.o Priority.h
	$(CXX) $(CXXFLAGS) main.cpp Path.o ModelPriority.o -o main

modelmain:	main.cpp ModelPath.o ModelPriority.o Priority.h
	$(CXX) $(CXXFLAGS) main.cpp Path.o ModelPriority.o -o modelmain

Path.o: Path.cpp Path.h
	$(CXX) $(CXXFLAGS) -c Path.cpp

deepclean: 
	-rm -f *~ *.o main *.stackdump *.exe

clean:
	-rm -f *~ *.o *.stackdump


