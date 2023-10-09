ifeq ($(OS), Windows_NT)
	OS:= Windows
else
	OS:= $(shell uname)
endif

CXX := g++
CXXFLAGS := -std=c++11
SRCS := leetracker.cpp lib/env_reader.cpp
EXEC := leetracker

LINUX_FLAGS := -lmysqlcppconn
WINDOWS_FLAGS := -lmysqlcppconn8

all: $(OS)

# Targets
Linux:
ifeq ($(OS), Linux)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(EXEC) $(LINUX_FLAGS)
endif

Windows:
ifeq ($(OS), Windows)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(EXEC) $(WINDOWS_FLAGS)
endif

clean:
	rm $(EXEC)