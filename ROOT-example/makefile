CC=gcc
CXX=g++

CFLAGS  = -O2

ROOTFLAGS = $(shell root-config --cflags)
ROOTLIBS = $(shell root-config --libs)
ROOTGLIBS = $(shell root-config --glibs)
CXXFLAGS = -Wall $(ROOTFLAGS) 
CXXLIBS = $(ROOTLIBS)


TARGET= example3-3
OBJS=   example3-3.o

.PHONY: all
all: $(TARGET)

%.o : %.cc
	$(CXX) $(CFLAGS) -c -o $@ $< -MMD $(CXXFLAGS)

$(TARGET):$(OBJS)
	$(CXX) $(CFLAGS) -o $@ $^ $(CXXLIBS) $(CXXFLAGS)

.PHONY: clean
clean:
	rm -f $(TARGET).d $(TARGET).o $(TARGET)

