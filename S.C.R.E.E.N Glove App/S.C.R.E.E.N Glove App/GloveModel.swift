//
//  GloveModel.swift
//  S.C.R.E.E.N Glove App
//
//  Created by Bogdan on 10/22/21.
//

import Foundation

struct GloveModel: Identifiable {
    
    let id: String
    let name: String
    let rssi: Int
    
    init(id: String = UUID().uuidString, name: String, rssi: Int = 0) {
        self.id = id
        self.name = name
        self.rssi = rssi
    }
    
    func updateCompletion() -> GloveModel {
        
        return GloveModel(id: id, name: name, rssi: rssi)
    }
}
