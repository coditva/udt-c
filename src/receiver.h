#ifndef RECEIVER_H_OCZYMGVT
#define RECEIVER_H_OCZYMGVT

#include "core.h"

typedef int receiverid_t;

receiverid_t receiver_start (conn_t *);
void receiver_stop (receiverid_t);

#endif /* end of include guard: RECEIVER_H_OCZYMGVT */
