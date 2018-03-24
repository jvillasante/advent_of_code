CC=/usr/local/opt/llvm/bin/clang++
LDFLAGS=-L/usr/local/opt/llvm/lib -lc++ -lc++experimental
CPPFLAGS=-I/usr/local/opt/llvm/include/ -I/usr/local/opt/llvm/include/c++/v1/
CPPFLAGS_COMMON=-std=c++17 -stdlib=libc++ -Wall -Wextra -Wshadow -pedantic
CFLAGS=$(LDFLAGS) $(CPPFLAGS) $(CPPFLAGS_COMMON) -g -DDEBUG -O2
SRC=src
BIN=bin
RM=rm -rf
CP=cp -rf

# The Cleaner
clean:
	@$(RM) $(BIN)/*

2015: clean
	$(CP) $(SRC)/2015/inputs $(BIN)
	$(CC) $(CFLAGS) -o $(BIN)/day01 $(SRC)/2015/solutions/day01.cpp
	$(CC) $(CFLAGS) -o $(BIN)/day02 $(SRC)/2015/solutions/day02.cpp
	$(CC) $(CFLAGS) -o $(BIN)/day03 $(SRC)/2015/solutions/day03.cpp
	$(CC) $(CFLAGS) -o $(BIN)/day04 $(SRC)/2015/common/md5.cpp $(SRC)/2015/solutions/day04.cpp
	$(CC) $(CFLAGS) -o $(BIN)/day05 $(SRC)/2015/solutions/day05.cpp
