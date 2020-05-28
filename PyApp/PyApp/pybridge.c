#include <stdio.h>
#include <string.h>

#include "pybridge.h"
#include "Python.h"

void python_start(const char* resourcePath)
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
    PyRun_SimpleString("import bootstrap");
}

void python_end()
{
    printf("Finalizing the Python interpreter\n");
    Py_Finalize();
}

const char* python_call(const char* payload)
{
    
    printf("Call into Python interpreter\n");
    
    // Import module
    PyObject* myModuleString = PyUnicode_FromString((char*) "bootstrap");
    PyObject* myModule = PyImport_Import(myModuleString);
    
    // Get reference to the router function
    PyObject* myFunction = PyObject_GetAttrString(myModule, (char*) "router");
    PyObject* args = PyTuple_Pack(1, PyUnicode_FromString(payload));
    
    // Call function and get the resulting string
    PyObject* myResult = PyObject_CallObject(myFunction, args);
    const char *myResultChar = PyUnicode_AsUTF8(myResult);
    
    // Cleanup
    Py_DECREF(myModuleString);
    Py_DECREF(myModule);
    Py_DECREF(myFunction);
    Py_DECREF(args);
    Py_DECREF(myResult);
    
    return myResultChar;
}
