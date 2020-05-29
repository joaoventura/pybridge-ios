//
//  ViewController.swift
//  PyApp
//
//  Created by João Ventura on 28/05/2020.
//  Copyright © 2020 Ventura. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    @IBOutlet weak var label: UILabel!

    override func viewDidLoad() {
        super.viewDidLoad()
        
        // Start the python interpreter
        PyBridge.start(path: Bundle.main.resourcePath!)
        
        // Create dictionary
        var req : [String:Any] = [:]
        req["function"] = "greet"
        req["name"] = "Python 3.8"
        
        // Invoke function
        let result = PyBridge.call(req: req)
        
        // Set the label text
        label.text = result
        
        // Finalize the python interpreter
        PyBridge.stop()
    }
}

