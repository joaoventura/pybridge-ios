# References for creating PyBridge-iOS

This document contains the necessary steps to create an Xcode project from scratch and embedding the Python 3 interpreter. It's mostly to document what I've done as a beginner in the iOS stack.


## Empty Xcode project

Create an empty Xcode project (Single View Application) named PyApp.

Add a Label to the storyboard and connect it to ViewController.swift (use Ctrl and drag the label from the storyboard to ViewController.swift). Set the label's text in `viewDidLoad` to see something working (`label.text = "Hello World"`) and run it.

Commits
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

Commits
- https://github.com/joaoventura/pybridge-ios/commit/8330b6e618c0fb13957fec29efb8eb7f05d7fcb0
