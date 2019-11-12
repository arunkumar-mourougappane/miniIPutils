CC=gcc
CXX=g++

CFLAGS += -g -Wall -Werror
CXXFLAGS += -g -Wall -Werror

INC_DIRS += -I./include

COMPILE.cc = $(CXX) $(CXXFLAGS) $(CDEFS) $(INC_DIRS) -c

TREE_DIRS = \
	build/lib/ip_address \
	build/app/test_mini_ip_utils

LIBS = \
	build/lib/libmini_ip_utilies.a

APPS =


all: tree libs apps

tree:
	mkdir -p $(TREE_DIRS)

clean: 
	rm -fr $(TREE_DIRS)

libs: $(LIBS)

apps: $(APPS)

build/lib/ip_address/%.o: ./src/lib/ip_address/%.cpp
	$(COMPILE.cc) -std=c++0x -o$@ $<

build/lib/libmini_ip_utilies.a: \
	build/lib/ip_address/ip_address.o
	ar -r -o $(build/lib/ip_address) $@ $^