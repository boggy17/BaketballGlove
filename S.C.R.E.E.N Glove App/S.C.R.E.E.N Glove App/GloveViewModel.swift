//
//  GloveViewModel.swift
//  S.C.R.E.E.N Glove App
//
//  Created by Bogdan on 10/22/21.
//

import Foundation
import CoreBluetooth

//let an int be converted to Data
extension Numeric {
    var data: Data {
        var source = self
        // This will return 1 byte for 8-bit, 2 bytes for 16-bit, 4 bytes for 32-bit and 8 bytes for 64-bit binary integers. For floating point types it will return 4 bytes for single-precision, 8 bytes for double-precision and 16 bytes for extended precision.
        return .init(bytes: &source, count: MemoryLayout<Self>.size)
    }
}

class GloveViewModel: NSObject, ObservableObject, CBCentralManagerDelegate, CBPeripheralDelegate {
    
    
    var myCentral: CBCentralManager!
    
    var connectedPeripheral: CBPeripheral?
    var targetService: CBService?
    var writableCharacteristic: CBCharacteristic?
    var readCharacteristic: CBCharacteristic?
    
    @Published var glove: GloveModel = GloveModel(name: "Not Found")
    
    @Published var bluetoothDevices: [CBPeripheral] = [] //simply for displaying the list in the pairing view
    
    @Published var bluetoothOn: Bool = false
    @Published var connectionStatus: String = ""
    @Published var sensorValue: Int = 0
    
    let serviceUUID = "180F"
    let writeCharUUID = "19B10001-E8F2-537E-4F6C-D104768A1214"
    let readChar = "2A19"
    
    override init() {
        super.init()
        myCentral = CBCentralManager(delegate: self, queue: nil)
        myCentral.delegate = self
    }
    
    //will exzecute when the bluetooth on the phone is turned off or on
    func centralManagerDidUpdateState(_ central: CBCentralManager) {
         if central.state == .poweredOn {
             bluetoothOn = true
         }
         else {
             bluetoothOn = false
         }
    }
    
    //will execute when scanning has begun and there are devices discovered
    //once those devices discovered at than to a list of bluetoothDevices and add
    func centralManager(_ central: CBCentralManager, didDiscover peripheral: CBPeripheral, advertisementData: [String : Any], rssi RSSI: NSNumber) {
        
        //if the peripheral device has a name retrieve it
        //if the peripheral that is discovered does is not named do not do anything
        if let name = advertisementData[CBAdvertisementDataLocalNameKey] as? String {
            print(peripheral)
            let newGlove = GloveModel(id: glove.id, name: name, rssi: RSSI.intValue)
            glove = newGlove.updateCompletion()
            bluetoothDevices.append(peripheral)
            connectedPeripheral = peripheral
        }
    }
    
    //will fire if the device connected successfully
    func centralManager(_ central: CBCentralManager, didConnect peripheral: CBPeripheral) {
        print("successfully connected")
        connectionStatus = "Connected!"
        
        //if you know the service you're looking for enter it below else nil will discover all services available
        let serviceUUID = CBUUID(string: serviceUUID)
        peripheral.discoverServices([serviceUUID]) //takes in a list of services
        peripheral.delegate = self
    }
    
    //will execute if the connection to the device was not successfull
    func centralManager(_ central: CBCentralManager, didFailToConnect peripheral: CBPeripheral, error: Error?) {
            print(error!.localizedDescription)
        connectionStatus = "Connection Failed."
    }
      
    //scan for BLE Devices in the area
    func startScanning() {
        print("startScanning")
        myCentral.scanForPeripherals(withServices: nil, options: nil)
    }
    
    //stop scanning for new BLE devices in the area
    func stopScanning() {
        print("stopScanning")
        myCentral.stopScan()
    }
    
    //send a signal to the esp
    func writeValue() {
//        guard let peripheral = connectedPeripheral, let characteristic = writableCharacteristic else {
//            return
//        }
        guard let peripheral = connectedPeripheral, let characteristic = readCharacteristic else {
            return
        }

        let data = 48.data
        //peripheral.writeValue(data, for: characteristic, type: .withResponse)
        
            peripheral.readValue(for: characteristic)
        
    }

    //will be called when connected to a peripheral and didDiscover services was called
    func peripheral(_ peripheral: CBPeripheral, didDiscoverServices error: Error?) {
    
        if let services = peripheral.services {
            print("discovered service")
            //discover characteristics of services
            for service in services {
                peripheral.discoverCharacteristics(nil, for: service)
            }
        }
    }
    
    func peripheral(_ peripheral: CBPeripheral, didDiscoverCharacteristicsFor service: CBService, error: Error?) {
        let characUUID = CBUUID(string: readChar)
        if let charac = service.characteristics {
            for characteristic in charac {
                //MARK:- Light Value
                if characteristic.uuid == characUUID {
                    self.readCharacteristic = characteristic
                }
            }
        }
    }
    
    func peripheral(_ peripheral: CBPeripheral, didWriteValueFor characteristic: CBCharacteristic, error: Error?) {
        print("WRITE VALUE : \(characteristic)")
    }
    
    func peripheral(_ peripheral: CBPeripheral, didUpdateValueFor characteristic: CBCharacteristic, error: Error?) {
        guard let data = characteristic.value else {
                return
        }
        let value = data.first?.bigEndian
        sensorValue = Int(value!)
        print(value ?? "none")
    }
    
}



