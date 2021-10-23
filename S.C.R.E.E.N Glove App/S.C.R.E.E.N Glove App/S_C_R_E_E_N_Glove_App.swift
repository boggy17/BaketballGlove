//
//  S_C_R_E_E_N_Glove_AppApp.swift
//  S.C.R.E.E.N Glove App
//
//  Created by Bogdan on 10/22/21.
//

import SwiftUI

@main
struct S_C_R_E_E_N_Glove_App: App {
    init() {
        UITableView.appearance().backgroundColor = UIColor(Color("Backgorund"))
    }
    
    @StateObject var gloveViewModel: GloveViewModel = GloveViewModel()
    var body: some Scene {
        WindowGroup {
            NavigationView {
                
                MainView()
            }
            .environmentObject(gloveViewModel)
        }
    }
}


//custom divider structure
struct MyDivider: View {
    var color: Color = .black
    var width: CGFloat = 1
    var body: some View {
        Rectangle()
            .fill(color)
            .frame(height: width)
            .edgesIgnoringSafeArea(.horizontal)
    }
}
