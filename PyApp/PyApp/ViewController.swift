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
        let mainBundle = Bundle.main
        python_start(mainBundle.resourcePath)
        
        // Create dictionary
        var req : [String:Any] = [:]
        req["function"] = "greet"
        req["name"] = "Python 3.8"
        
        // Convert to string
        let reqString = try? String(data: JSONSerialization.data(withJSONObject: req), encoding: .utf8)!
        
        // Call the python interpreter
        let res = python_call(reqString)
        let resString = String(cString: res!)
        
        // Response
        struct PyBridgeResponse: Codable {
            var status: String
            var result: String
        }
        
        let resData = resString.data(using: .utf8)!
        let response = try! JSONDecoder().decode(PyBridgeResponse.self, from: resData)
        label.text = response.result
        
        // Finalize the python interpreter
        python_end()
    }
}

