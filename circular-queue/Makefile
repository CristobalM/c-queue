ROOT_PATH=$(shell pwd)/..

all: build clean

build: circular_queue.o libcircular_queue.a
	mkdir -p ${ROOT_PATH}/bin && cp libcircular_queue.a ${ROOT_PATH}/bin/

circular_queue.o: circular_queue.c
	$(CC) ${CFLAGS} -c circular_queue.c -o circular_queue.o

libcircular_queue.a:
	ar rcs libcircular_queue.a circular_queue.o

clean:
	rm -f circular_queue.o libcircular_queue.a


