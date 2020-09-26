CC?=gcc
CXX?=g++
CFLAGS?=-Og -g
CXXFLAGS=-O3
prefix?=/usr/local
bindir?=$(prefix)/bin
datadir?=$(prefix)/share/benni

objects=bin/bench_single bin/bench_multi bin/is_prime bin/is_perfect \
				bin/countdown

all: $(objects)
	cp src/*.sh bin/
	chmod +x bin/*.sh
	ln -sf is_perfect bin/count_divisors
	ln -sf is_perfect bin/list_perfects

bin:
	mkdir -p bin
bin/bench_single: src/bench.c bin
	$(CC) -o $@ $< $(CFLAGS) -pthread

bin/bench_multi: src/bench.c bin
	$(CC) -o $@ $< $(CFLAGS) -DMULTICORE -pthread

bin/is_prime: src/is_prime.c bin
	$(CC) -o $@ $< $(CFLAGS) -DPRINT_UNIX

bin/is_perfect: src/is_perfect.cpp bin
	$(CXX) -o $@ $< $(CXXFLAGS) -DUNIX -std=c++17

bin/countdown: src/countdown.c bin
	$(CC) -o $@ $< $(CFLAGS)

install: all
	mkdir -p $(bindir) $(datadir)
	#tmp=$$(echo $(datadir) | sed 's/\//\\\//g'); sed -i "s/datadir=/datadir=$$tmp/g" bin/timer.sh
	cp -a bin/* $(bindir)
	tmp=$$(echo $(datadir) | sed 's/\//\\\//g'); sed -i "4s/.*/datadir=$$tmp/g" $(bindir)/timer.sh
	cp share/* $(datadir)/

clean:
	rm -rf bin

.PHONY: all install clean
