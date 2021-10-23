//
//  ContentView.swift
//  S.C.R.E.E.N Glove App
//
//  Created by Bogdan on 10/22/21.
//

import SwiftUI

struct MainView: View {
    @Environment(\.presentationMode) var presentationMode
    @EnvironmentObject var gloveViewModel: GloveViewModel
    
    @State var showConnected: Bool = false
    var body: some View {
        ZStack {
            Color(.gray)
                .ignoresSafeArea()
            
            VStack {
                
                HStack {
                    
                    Spacer()
                    Spacer()
                    Text("S.C.R.E.E.N")
                        .foregroundColor(.white)
                        .font(.title)
                    Spacer()
                    
                    NavigationLink(destination: PairGloveView(connectedStatus: "", selectedRow: ""), label: {
                        
                        
                            Text("Pair")
                                .padding(.horizontal)
                                .foregroundColor(.white)
                        
                    })
                }
                MyDivider(width: 3)
                VStack {
                    Button(action: gloveViewModel.writeValue, label: {
                        Text("Read Values")
                            .foregroundColor(.white)
                            .font(.headline)
                            .frame(height: 55)
                            .frame(maxWidth: .infinity)
                            .background(Color.accentColor)
                            .cornerRadius(10)
                        
                    })
                        .padding(.horizontal)
                    
                    Text("Sensor Value: " + String(gloveViewModel.sensorValue))
                        .foregroundColor(.black)
                        .font(.headline)
                        .frame(height: 55)
                        .frame(maxWidth: .infinity)
                        .background(Color.white)
                        .cornerRadius(10)
                        .padding()
                    
                }
                Spacer()
                
                
            }
        }.navigationBarHidden(true)
    }
}

struct MainView_Previews: PreviewProvider {
    static var previews: some View {
        NavigationView {
            MainView()
        }.environmentObject(GloveViewModel())
    }
}
