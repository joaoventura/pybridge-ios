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
        
        // Greet
        let msg = String(cString: greet("iPhone"))
        label.text = msg
    }
}

