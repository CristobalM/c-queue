
CURRENT_PATH=$(shell pwd)

MODULES_DIRS := src
CFLAGS :=  -Wall -Wextra -std=c99 -pedantic -Wmissing-prototypes -Wstrict-prototypes \
    -Wold-style-definition -Werror -O3

DEBUG_FLAGS := -Wall -Wextra -std=c99 -pedantic -Wmissing-prototypes -Wstrict-prototypes \
    -Wold-style-definition -Werror -g

INCLUDES=-I${CURRENT_PATH}/include

MAKE_FLAGS=CFLAGS="${CFLAGS}" INCLUDES="${INCLUDES}"
DEBUG_MAKE_FLAGS=CFLAGS="${DEBUG_FLAGS}" INCLUDES="${INCLUDES}"

build: modules

all: format modules test-all

re: clean all

clean:
	for dir in ${MODULES_DIRS}; do \
		$(MAKE) clean -C $$dir ${MAKE_FLAGS};  \
	done

	rm -rf test/build/

modules:
	for dir in ${MODULES_DIRS}; do \
		$(MAKE) -C $$dir ${MAKE_FLAGS}; \
	done

debug-build:
	for dir in ${MODULES_DIRS}; do \
		$(MAKE) -C $$dir ${DEBUG_MAKE_FLAGS}; \
	done


test-all:
	cd test && mkdir -p build && cd build && cmake .. && make && ./circular_queue_test


format:
	find . -regex '.*\.\(c\|h\)' -exec clang-format -style=file -i {} \;

clean-all: clean
	rm -rf bin