# References for creating PyBridge-iOS

This document contains the necessary steps to create an Xcode project from scratch and embedding the Python 3 interpreter. It's mostly to document what I've done as a beginner in the iOS stack.


## Empty Xcode project

Create an empty Xcode project (Single View Application) named PyApp.

Add a Label to the storyboard and connect it to ViewController.swift (use Ctrl and drag the label from the storyboard to ViewController.swift). Set the label's text in `viewDidLoad` to see something working (`label.text = "Hello World"`) and run it.

References
- https://github.com/joaoventura/pybridge-ios/commit/bdc1a2623c19c724ef475f26190645143d3262ba


## Interface with C code

The process to interface Swift with C code is quite simple. 

Over PyApp, right click, add a new C file and call it pybridge. This will create `pybridge.c` and `pybridge.h`. If it asks to create the Bridging header, do it as it will be necessary to export the C functions to swift. If not, just create an empty file called `PyApp-Bridging-Header.h` and `#import "pybridge.h"` inside it.

On `pybridge.c` write this function:

```
const char* greet(const char* name)
{
    char msg[200];
    snprintf(msg, sizeof msg, "Hello %s", name);
    printf("Will return: %s\n", msg);
    return strdup(msg);
}
```

On `pybridge.h` write the header:

```
const char* greet(const char* name);
```

And finally on `ViewController.swift`:

```
let msg = String(cString: greet("iPhone"))
label.text = msg
```

If everything works fine, you should see the label "Hello iPhone" in the simulator. You can now interface with C code from Swift.

References
- https://theswiftdev.com/how-to-call-c-code-from-swift/
- https://github.com/joaoventura/pybridge-ios/commit/8330b6e618c0fb13957fec29efb8eb7f05d7fcb0


## Compiling Python 3 for iOS

PyBridge-iOS uses the [kivy-ios](https://github.com/kivy/kivy-ios) toolchain to compile the Python static library (libpython3.a) and standard library modules.

Install the kivy-ios toolchain and run `toolchain build python3`. It will create a `build` and `dist` folder. The static libraries needed for the project are in `dist/lib`, the standard library is in `dist/root/python3/lib` and the include files (so that you can `#include "Python.h"` is in `dist/root/python3/include/python3.8`.

Copy `dist/lib` and `dist/root` for the root of your project (not inside the Xcode project!) to a folder called `python-for-ios`. You'll have `python-for-ios/dist/lib` and `python-for-ios/dist/root`.

References
- https://github.com/kivy/kivy-ios
- https://github.com/joaoventura/pybridge-ios/commit/6a06bb770d586a4def589b382d99a10318931b6f


## Include Python static libraries

Modify `pybridge.c` and include the following:

```
#include "Python.h"

void python()
{
    printf("Initializing the Python interpreter\n");
    Py_InitializeEx(0);
    Py_Finalize();
}
```

This will throw a lot of errors in Xcode, such that Xcode must be able to find `Python.h` and all the Python header files, and the static libraries we compiled in the previous step.

On Xcode, on the root of PyApp, select **Build Phases**. On `Link Binary with Libraries` add all the libraries in `python-for-ios/dist/lib` (use "Add Other"). Add also the local framework `libz.1.2.8.tbd` as Python needs some symbols declared there.

On **Build Settings**, on `Search Paths/User Header Search Paths`, add the location of the Python header files: `$(SRCROOT)/../python-for-ios/dist/root/python3/include/python3.8`. Set to find as "recursive".

Finally, still on **Build Settings**, on `Search Paths/Library Search Paths`, add the location of the libraries: `$(SRCROOT)/../python-for-ios/dist/lib`.

If everything is working as expected, the project will compile, although we are not calling the `python()` function.

References
- https://www.chilkatsoft.com/xcode-link-static-lib.asp
- https://www.accusoft.com/resources/blog/using-static-library-ios-app/
- https://github.com/joaoventura/pybridge-ios/commit/63359cbe28d0b7f305190226a624e48292dbe2a5


## Use the Python interpreter

On `ViewController.swift` call the Python function `python()`. It will show the following error in the Xcode output:

```
Initializing the Python interpreter
Could not find platform independent libraries <prefix>
Could not find platform dependent libraries <exec_prefix>
Consider setting $PYTHONHOME to <prefix>[:<exec_prefix>]
```

This happens because the python interpreter cannot find the standard library files. We must fix this in two steps: copy the standard library files to the device and setting the python path to find them.

**To copy standard library files**

On Xcode, on the root of PyApp, select **Build Phases** again, and on `Copy Bundle Resources` select the *lib* folder at `/python-for-ios/dist/root/python3/lib`. This will copy the files `python38.zip` (standard library python modules) and all the other files inside lib to the device.

**To set python path**

To set the python path, we must pass the location of the files to the C code. iOS has the concept of bundles. 

On `ViewController.swift`:

```
python(Bundle.main.resourcePath)
```

Update the arguments on `pybridge.c and pybridge.h` accordingly:

```
void python(const char* resourcePath)
```

Finally, and a big step here, include all the necessary code such that the Python interpreter finds the stdlib files.

```
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
```

If everything works fine, you should see **Hello from Python** in the Xcode output.

References
- https://github.com/joaoventura/pybridge-ios/tree/7922308461956b77d250242bdf0cf5d48db111be


## PyBridge routing

Finally, implement the necessary functions to be able to call a function on the Python interpreter.

Resources
- commit
