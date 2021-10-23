//
//  PairGloveView.swift
//  S.C.R.E.E.N Glove App
//
//  Created by Bogdan on 10/22/21.
//

import Foundation


import SwiftUI
import CoreBluetooth

struct PairGloveView: View {
    
    @Environment(\.presentationMode) var presentationMode
    @EnvironmentObject var gloveViewModel: GloveViewModel
    
    @State var showConnectingStatus: Bool = false
    @State var connectedStatus: String
    @State var selectedRow: String
    var body: some View {
        ZStack {
            
            Color(.gray)
                .ignoresSafeArea()
            VStack {
                
                HStack {
                    
                    Button(action: {
                    self.presentationMode.wrappedValue.dismiss()
                        }){
                    Image(systemName: "arrow.left")
                        .foregroundColor(.white)
                        .font(.title2)
                
                    }.padding()
                    Spacer()
                    Text("S.C.R.E.E.N")
                        .foregroundColor(.white)
                        .font(.title)
                    Spacer()
                        
                    Spacer()
                }
                MyDivider(width: 3)
            
                List {
                    
                    ForEach(gloveViewModel.bluetoothDevices, id: \.self) { device in
                        
                        Text(device.name ?? "No Name")
                        .padding()
                        .font(.title)
                        .foregroundColor(.black)
                        .lineLimit(1).fixedSize(horizontal: false, vertical: true)
                        .onTapGesture {
                            gloveViewModel.myCentral.connect(device, options: nil)
                            print("attempting to connect the device \(device.name!)")
                            selectedRow = device.name ?? "No Name"
                            
                        }
                        .listRowBackground(selectedRow == device.name! ? Color("AccentColor") : Color(.gray))
                    
                    }
                    .listRowBackground(Color("Background"))
                    
                    
                }
                VStack {
                    Button(action: gloveViewModel.writeValue, label: {
                        Text("sendSignal")
                            .foregroundColor(.white)
                            .font(.headline)
                            .frame(height: 55)
                            .frame(maxWidth: .infinity)
                            .background(Color.accentColor)
                            .cornerRadius(10)
                        
                    }).padding(.horizontal)
                    HStack {
                    Button(action: gloveViewModel.startScanning, label: {
                        Text("Scan For Devices")
                            .foregroundColor(.white)
                            .font(.headline)
                            .frame(height: 55)
                            .frame(maxWidth: .infinity)
                            .background(Color.accentColor)
                            .cornerRadius(10)
                        
                    })
                    .padding(.vertical)
                    .padding(.leading)
                        Button(action: gloveViewModel.stopScanning, label: {
                        Text("Stop Scanning")
                            .foregroundColor(.white)
                            .font(.headline)
                            .frame(height: 55)
                            .frame(maxWidth: .infinity)
                            .background(Color.accentColor)
                            .cornerRadius(10)
                        
                    })
                    .padding(.vertical)
                    .padding(.trailing)
                    
                    }
                    //show bluetooth status
                    if gloveViewModel.bluetoothOn {
                        
                        Text("BLE On")
                    } else {
                        Text("BLE Off")
                    }
                    
                    if showConnectingStatus {
                        
                        RoundedRectangle(cornerRadius: 16)
                            .frame(width: 250, height: 55)
                            .opacity(0.5)
                            .overlay(
                                Text(gloveViewModel.connectionStatus)
                                    .font(.headline)
                                    .foregroundColor(.black)
                            )
                            .foregroundColor(.white)
                    }
                }
                
                Spacer()
            }
        }.navigationBarHidden(true)
    }
    
    func connectionRequested() {
        
        showConnectingStatus = true
        
        DispatchQueue.main.asyncAfter(deadline: .now() + 1, execute: {
                self.showConnectingStatus = false
            
        })
        
    }
}

struct PairGloveView_Previews: PreviewProvider {
    static var previews: some View {
        
        NavigationView {
            PairGloveView(connectedStatus: "", selectedRow: "")
            
        }.environmentObject(GloveViewModel())
    }
}
