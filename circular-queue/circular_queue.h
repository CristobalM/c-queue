#ifndef _CIRCULAR_QUEUE_H_
#define _CIRCULAR_QUEUE_H_

#define CIRCULAR_QUEUE_SUCCESS_ECODE 0
#define CIRCULAR_QUEUE_CAPACITY_REACHED_ECODE 1
#define CIRCULAR_QUEUE_CANT_ADD_MORE_ELEMENTS_ECODE 2
#define CIRCULAR_QUEUE_EMPTY_ECODE 3

typedef unsigned int uint;

struct circular_queue {
  char *data;
  uint capacity;
  uint element_sz_bytes;
  uint front_position;
  uint back_position;
  uint nof_items;
};

int init_circular_queue(struct circular_queue *cs, uint capacity,
                        uint element_sz_bytes);
int clean_circular_queue(struct circular_queue *cs);

int reset_circular_queue(struct circular_queue *cs);

int push_circular_queue(struct circular_queue *cs, char *element);
int pop_back_circular_queue(struct circular_queue *cs, char *result);
int pop_front_circular_queue(struct circular_queue *cs, char *result);

int front_circular_queue(struct circular_queue *cs, char *result);
int back_circular_queue(struct circular_queue *cs, char *result);
int front_reference_circular_queue(struct circular_queue *cs, char **result);
int back_reference_circular_queue(struct circular_queue *cs, char **result);

int size_circular_queue(struct circular_queue *cs, uint *result);
int empty_circular_queue(struct circular_queue *cs, int *result);
int full_circular_queue(struct circular_queue *cs, int *result);

#endif /* _CIRCULAR_QUEUE_H_ */
