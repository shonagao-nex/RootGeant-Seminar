CC=gcc
CXX=g++

CFLAGS  = -O2

ROOTFLAGS = $(shell root-config --cflags)
ROOTLIBS = $(shell root-config --libs)
ROOTGLIBS = $(shell root-config --glibs)
CXXFLAGS = -Wall $(ROOTFLAGS) 
CXXLIBS = $(ROOTLIBS)


TARGET1= ex016_CompGCC
OBJS1=   ex016_CompGCC.o
TARGET2= ex018_CompSpeed
OBJS2=   ex018_CompSpeed.o

.PHONY: all
all: $(TARGET1) \
     $(TARGET2) \

%.o : %.cc
	$(CXX) $(CFLAGS) -c -o $@ $< -MMD $(CXXFLAGS)

$(TARGET1):$(OBJS1)
	$(CXX) $(CFLAGS) -o $@ $^ $(CXXLIBS) $(CXXFLAGS)

$(TARGET2):$(OBJS2)
	$(CXX) $(CFLAGS) -o $@ $^ $(CXXLIBS) $(CXXFLAGS)

.PHONY: clean
clean:
	rm -f *.d *.o $(TARGET1) $(TARGET2)

