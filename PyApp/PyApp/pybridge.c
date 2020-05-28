#include <stdio.h>
#include <string.h>

#include "pybridge.h"
#include "Python.h"

const char* greet(const char* name)
{
    char msg[200];
    snprintf(msg, sizeof msg, "Hello %s", name);
    printf("Will return: %s\n", msg);
    return strdup(msg);
}

void python()
{
    printf("Initializing the Python interpreter\n");
    Py_InitializeEx(0);
    Py_Finalize();
}
