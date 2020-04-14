#include <stdlib.h>
#include <string.h>

#include "circular_queue.h"

#define IS_FULL(cs) ((cs)->nof_items == (cs)->capacity)
#define IS_EMPTY(cs) ((cs)->nof_items == 0)

#define NOT_EMPTY_CHECK(cs)                                                    \
  do {                                                                         \
    if (IS_EMPTY(cs)) {                                                        \
      return CIRCULAR_QUEUE_EMPTY_ECODE;                                       \
    }                                                                          \
  } while (0)

static inline uint prev_index(struct circular_queue *cs, uint idx) {
  return (cs->capacity + idx - 1) % cs->capacity;
}

static inline uint next_index(struct circular_queue *cs, uint idx) {
  return (idx + 1) % cs->capacity;
}

int init_circular_queue(struct circular_queue *cs, uint capacity,
                        uint element_sz_bytes) {
  cs->data = calloc(capacity, element_sz_bytes);
  cs->capacity = capacity;
  cs->element_sz_bytes = element_sz_bytes;
  cs->front_position = 0;
  cs->back_position = 0;
  cs->nof_items = 0;

  return CIRCULAR_QUEUE_SUCCESS_ECODE;
}

int clean_circular_queue(struct circular_queue *cs) {
  free(cs->data);
  return CIRCULAR_QUEUE_SUCCESS_ECODE;
}

int push_circular_queue(struct circular_queue *cs, char *element) {
  if (IS_FULL(cs)) {
    return CIRCULAR_QUEUE_CANT_ADD_MORE_ELEMENTS_ECODE;
  }

  memcpy(cs->data + cs->back_position * cs->element_sz_bytes, element,
         cs->element_sz_bytes);
  cs->back_position = next_index(cs, cs->back_position);
  cs->nof_items++;

  return CIRCULAR_QUEUE_SUCCESS_ECODE;
}

int pop_back_circular_queue(struct circular_queue *cs, char *result) {
  NOT_EMPTY_CHECK(cs);

  uint prev_idx = prev_index(cs, cs->back_position);
  memcpy(result, cs->data + prev_idx * cs->element_sz_bytes,
         cs->element_sz_bytes);

  cs->nof_items--;
  cs->back_position = prev_idx;

  return CIRCULAR_QUEUE_SUCCESS_ECODE;
}

int pop_front_circular_queue(struct circular_queue *cs, char *result) {
  NOT_EMPTY_CHECK(cs);

  memcpy(result, cs->data + cs->front_position * cs->element_sz_bytes,
         cs->element_sz_bytes);

  cs->front_position = next_index(cs, cs->front_position);
  cs->nof_items--;

  return CIRCULAR_QUEUE_SUCCESS_ECODE;
}

int front_circular_queue(struct circular_queue *cs, char *result) {
  NOT_EMPTY_CHECK(cs);

  memcpy(result, cs->data + cs->front_position * cs->element_sz_bytes,
         cs->element_sz_bytes);

  return CIRCULAR_QUEUE_SUCCESS_ECODE;
}

int back_circular_queue(struct circular_queue *cs, char *result) {
  NOT_EMPTY_CHECK(cs);

  uint prev_idx = prev_index(cs, cs->back_position);

  memcpy(result, cs->data + prev_idx * cs->element_sz_bytes,
         cs->element_sz_bytes);

  return CIRCULAR_QUEUE_SUCCESS_ECODE;
}

int front_reference_circular_queue(struct circular_queue *cs, char **result) {
  NOT_EMPTY_CHECK(cs);

  *result = cs->data + cs->front_position * cs->element_sz_bytes;

  return CIRCULAR_QUEUE_SUCCESS_ECODE;
}

int back_reference_circular_queue(struct circular_queue *cs, char **result) {
  NOT_EMPTY_CHECK(cs);

  *result = cs->data + prev_index(cs, cs->back_position) * cs->element_sz_bytes;

  return CIRCULAR_QUEUE_SUCCESS_ECODE;
}

int size_circular_queue(struct circular_queue *cs, uint *result) {
  *result = cs->nof_items;
  return CIRCULAR_QUEUE_SUCCESS_ECODE;
}

int empty_circular_queue(struct circular_queue *cs, int *result) {
  *result = IS_EMPTY(cs);
  return CIRCULAR_QUEUE_SUCCESS_ECODE;
}

int full_circular_queue(struct circular_queue *cs, int *result) {
  *result = IS_FULL(cs);
  return CIRCULAR_QUEUE_SUCCESS_ECODE;
}
