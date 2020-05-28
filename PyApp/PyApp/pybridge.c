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

void python(const char* resourcePath)
{
    printf("Initializing the Python interpreter\n");
    
    // Set python home
    wchar_t *resources = Py_DecodeLocale(resourcePath, NULL);
    Py_SetPythonHome(resources);
    
    // Set paths
    char paths[10000];
    snprintf(paths, sizeof(paths),
             "%s/lib/" \
             ":%s/lib/python38.zip" \
             ":%s/lib/python3.8/" \
             ":%s/lib/python3.8/site-packages",
             resourcePath, resourcePath, resourcePath, resourcePath);
    
    wchar_t *wchar_paths = Py_DecodeLocale(paths, NULL);
    Py_SetPath(wchar_paths);
    
    // Initialize
    Py_InitializeEx(0);
    
    // Run something
    PyRun_SimpleString("print('Hello from Python')");
    
    // Finalize
    Py_Finalize();
}
