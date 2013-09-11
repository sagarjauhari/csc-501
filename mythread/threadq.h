#ifndef THREADQ_H
#define THREADQ_H

#include "mythread.h"
#include "mythreadlib.h"

Node * q_create();
void q_insert(_MyThread* thread, Node *head);
_MyThread* q_remove(Node *head);
void q_print(Node *head, int type);
#endif /* THREADQ_H */
