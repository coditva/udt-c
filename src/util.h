#ifndef UTIL_H_RSWIA2KL
#define UTIL_H_RSWIA2KL

#define linked_list_add(BUFFER, BLOCK) \
{ \
    if (BUFFER.size == 0) { \
        BUFFER.first = BLOCK; \
    } else { \
        BUFFER.last -> next = BLOCK; \
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

#endif /* end of include guard: UTIL_H_RSWIA2KL */
