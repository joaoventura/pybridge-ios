# References for creating PyBridge-iOS

This document contains the necessary steps to create an Xcode project from scratch and embedding the Python 3 interpreter. It's mostly to document what I've done as a beginner in the iOS stack.


## Empty Xcode project

Create an empty Xcode project (Single View Application). 

Add a Label to the storyboard and connect it to ViewController.swift (use Ctrl and drag the label from the storyboard to ViewController.swift). Set the label's text in `viewDidLoad` to see something working (`label.text = "Hello World"`) and run it.