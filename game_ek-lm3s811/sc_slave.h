/*${.::sc_slave.h} .............................................................*/
#ifndef sc_slave_h
#define sc_slave_h
#include "sctp.h"

void sc_slave_send(void);
scd_err_t sc_slave_recv(void);

#endif  /* sc_slave_h */