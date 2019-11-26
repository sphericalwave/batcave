LINK.o = $(LINK.cc)

CC = gcc
CXX = g++
EXTRAS_DIR = ${TOP}
CPPFLAGS = -g -I ${EXTRAS_DIR}/include/3rdParty -D_GLIBCXX_DEBUG
LDFLAGS = -L ${EXTRAS_DIR}/lib -pipe -m64 -rdynamic
LDLIBS += -lboost_locale -lboost_system -lboost_program_options -lgtest -lgtest_main -lpthread

main: main.o ServerTcpChannel.o Server.o
