#ifndef pybridge_h
#define pybridge_h

#include <stdio.h>

void python_start(const char* resourcePath);
void python_end(void);
const char* python_call(const char* payload);

#endif /* pybridge_h */
