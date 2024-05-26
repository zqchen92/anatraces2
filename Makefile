
# Compiler and linker
CXX = g++
## gcc 4.8.5, ROOT5.34: c++11
CXXFLAGS = -O2 -Wall -Wextra -std=c++11 $(shell root-config --cflags) -lSpectrum -Iinc
LDFLAGS = $(shell root-config --libs) $(shell root-config --glibs) -lSpectrum

# Project files
SRCS = anaTraces2.cc src/lisa_febex.cc src/lisa_OutputManager.cc src/lisa_settings.cc src/lisa_ucesb.cc src/lisa_vis.cc src/lisa_scope.cc 

HDRS = inc/lisa_febex.hh inc/lisa_OutputManager.hh inc/lisa_settings.hh inc/lisa_ucesb.hh inc/lisa_vis.hh inc/lisa_scope.hh inc/lisa_Env.hh

#OBJS = build/anaTraces2.o build/lisa_febex.o build/lisa_OutputManager.o build/lisa_settings.o build/lisa_ucesb.o build/lisa_vis.o
OBJS = $(SRCS:%.cc=build/%.o)

# Output executable
EXEC = anaTraces2

# Default target
all: $(EXEC)

# Rule to build the executable
$(EXEC): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

# Rule to build object files
build/%.o: %.cc $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/%.o: src/%.cc inc/%.hh
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f build/*.o $(EXEC) build/src/*.o

# PHONY targets
.PHONY: all clean

