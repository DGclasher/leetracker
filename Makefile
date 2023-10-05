OS:=$(shell uname)

CXX:= g++
CXXFLAGS:= -std=c++11

SRCS:= leetracker.cpp env_reader.cpp
EXEC:= leetracker

LINUX_FLAGS:= -lmysqlcppconn

all: linux
# Target for linux
linux:
ifeq ($(OS), Linux)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(EXEC) $(LINUX_FLAGS)
else
	@echo "Makefile only supported for Linux."
endif

clean:
	rm -f $(EXEC)