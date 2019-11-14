CC?=gcc
CXX?=g++

CFLAGS += -g -Wall -Werror
CXXFLAGS += -g -Wall -Werror

INC_DIRS += -I./include \
				-I./googletest/googletest/include \
				-I./src/app/include_app 



LIB_DIRS += \
	-L./build/lib \
	-L./gtest/lib

COMPILE.cc = $(CXX) $(CXXFLAGS) $(CDEFS) $(INC_DIRS) -c
LINKXX = $(CXX) $(LDFLAGS) $(LIB_DIRS)

TREE_DIRS = \
	build/lib/ip_address \
	build/app/gtest_mini_ip_utilities

LIBS = \
	build/lib/libmini_ip_utilities.a

APPS = \
	build/app/gtest_mini_ip_utilities/gtest_mini_ip_utilities

GTEST_MINI_IP_UTILITIES_OBJS = \
	build/app/gtest_mini_ip_utilities/gtest_ip_address.o \
	build/app/gtest_mini_ip_utilities/gtest_mini_ip_utilities.o


all: gtest tree libs apps

gtest:
	./build_gtest.sh

tree:
	mkdir -p $(TREE_DIRS)

clean: 
	rm -fr $(TREE_DIRS) googletest gtest

libs: $(LIBS)

apps: $(APPS)

run-test: 
	./build/app/gtest_mini_ip_utilities/gtest_mini_ip_utilities

build/lib/ip_address/%.o: ./src/lib/ip_address/%.cpp
	$(CXX) $(CXXFLAGS) $(CDEFS) $(INC_DIRS) -c -std=c++11 -o$@ $<

build/app/gtest_mini_ip_utilities/%.o: ./src/app/gtest_mini_ip_utilities/%.cpp
	$(CXX) $(CXXFLAGS) $(CDEFS) $(INC_DIRS) -c -std=c++11 -o$@ $<

build/lib/libmini_ip_utilities.a: \
	build/lib/ip_address/ip_address.o
	ar -r -o $(build/lib/ip_address) $@ $^

build/app/gtest_mini_ip_utilities/gtest_mini_ip_utilities: $(GTEST_MINI_IP_UTILITIES_OBJS) ./build/lib/libmini_ip_utilities.a 
	$(LINKXX) -o $@ $(GTEST_MINI_IP_UTILITIES_OBJS) -Wl,--start-group -lmini_ip_utilities -lpthread -lrt -lz -lc -lgtest -Wl,--end-group
