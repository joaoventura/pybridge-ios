//
//  pybridge.swift
//  PyApp
//

import Foundation

class PyBridge {
    
    class func start(path: String) {
        python_start(path)
    }
    
    class func stop() {
        python_end()
    }
    
    class func call(req: Dictionary<String, Any>) -> String {
        
        // Convert to string
        let reqString = try? String(data: JSONSerialization.data(withJSONObject: req), encoding: .utf8)!
        
        // Call the python interpreter
        let res = python_call(reqString)
        
        // Convert response to String and free the pointer
        let resString = String(cString: res!)
        free(UnsafeMutablePointer(res))
        
        // Response
        struct PyBridgeResponse: Codable {
            var status: String
            var result: String
        }
        
        // Convert to dictionary
        let resData = resString.data(using: .utf8)!
        let response = try! JSONDecoder().decode(PyBridgeResponse.self, from: resData)
        
        return response.result
    }
}
