#ifndef UTIL_H_RSWIA2KL
#define UTIL_H_RSWIA2KL

#define linked_list_add(BUFFER, BLOCK) \
{ \
    if (BUFFER.size == 0) { \
        BUFFER.first = BLOCK; \
    } else { \
        BLOCK -> next = BUFFER.last; \
        BLOCK -> next -> next = BLOCK; /* BUFFER.last -> lext = BLOCK */ \
        BLOCK -> next = NULL; \
    } \
    BUFFER.last = BLOCK; \
    BUFFER.size++; \
}

#define linked_list_get(BUFFER, BLOCK) \
{ \
    if (BUFFER.size == 0) { \
        BLOCK = NULL; \
    } else { \
        BLOCK = BUFFER.first; \
        BUFFER.first = BLOCK -> next; \
        BUFFER.size--; \
    } \
}

typedef long unsigned int tid_t;
typedef void * (*thread_worker_t) (void *);

tid_t thread_start (thread_worker_t, void *); 
void  thread_stop  (tid_t);

#endif /* end of include guard: UTIL_H_RSWIA2KL */
