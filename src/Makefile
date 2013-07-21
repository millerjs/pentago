C = g++

ifndef os
   os = LINUX
endif

ifndef arch
   arch = IA32
endif

CCFLAGS = -Wall -lstdc++

ifeq ($(arch), IA32)
   CCFLAGS += -DIA32
endif

ifeq ($(arch), POWERPC)
   CCFLAGS += -mcpu=powerpc
endif

ifeq ($(arch), IA64)
   CCFLAGS += -DIA64
endif

ifeq ($(arch), SPARC)
   CCFLAGS += -DSPARC
endif

LDFLAGS = -lpthread -lm

ifeq ($(os), UNIX)
   LDFLAGS += -lsocket
endif

ifeq ($(os), SUNOS)
   LDFLAGS += -lrt -lsocket
endif

DIR = $(shell pwd)

APP = pentago

all: $(APP)

%.o: %.cpp
	$(C) $(CCFLAGS) $< -c

pentago: pentago.o pentago_client.o pentago_server.o pentago_threads.o
	$(C) $^ -o $(APP) $(LDFLAGS)

clean:
	rm -f *.o $(APP) 

install:
	export PATH=$(DIR):$$PATH
