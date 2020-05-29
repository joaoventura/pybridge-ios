# PyBridge-iOS

PyBridge is a C implementation that allows to use Python code in native iOS applications. It allows to send String or JSON messages to the Python interpreter without the need for any web frameworks. Instead of using web applications, you can reuse your Python backend code and implement truly native iOS applications.

Shameless plug: I do contract work, check out my website at http://joaoventura.net/ or buy my apps!


## Overview

This repository shows the source code of an empty Xcode Swift project with a Label. When the application starts, it starts the Python interpreter and calls a Python function that returns a greet message that is then set on the Label.

![App image](https://github.com/joaoventura/pybridge-ios/blob/master/docs/pybridge-ios.png)


## Running the project

Clone this project and open it on Xcode. All the libraries and python files are included.

Run the project and you should see a `Hello Python 3.8` message in the screen. You can also check the Xcode output to see some debug things.


## How it works?

I've documented all the process in the [references document](https://github.com/joaoventura/pybridge-ios/blob/master/docs/references.md). It shows how to compile a Python  3 distribution, how to include the libraries, and how everything works. 

It's mostly a document for myself, but you can use and learn from it!
