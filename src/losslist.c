#include <inttypes.h>

#include "losslist.h"
#include "config.h"

static uint32_t loss_list[MAX_LOSS_SIZE];
static int last = 0;

int loss_list_getindex(uint32_t);

/* TODO: Optimize this to not use O(n) time */

int loss_list_add(uint32_t seqnum)
{
    if (last >= MAX_LOSS_SIZE) return -1;
    if (loss_list_getindex(seqnum) == -1) return -1;

    loss_list[last] = seqnum;
    last++;
    return 0;
}

int loss_list_remove(uint32_t seqnum)
{
    int i;
    i = loss_list_getindex(seqnum);
    if (i == -1) return -1;

    for (; i < MAX_LOSS_SIZE - 1; ++i) {
        loss_list[i] = loss_list[i + 1];
    }

    last--;
    return 0;
}

int loss_list_getindex(uint32_t seqnum)
{
    for (int i = 0; i < MAX_LOSS_SIZE; ++i) {
        if (loss_list[i] == seqnum) return i;
    }
    return -1;
}
