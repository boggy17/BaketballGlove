//
//  S_C_R_E_E_N_Glove_AppUITestsLaunchTests.swift
//  S.C.R.E.E.N Glove AppUITests
//
//  Created by Bogdan on 10/22/21.
//

import XCTest

class S_C_R_E_E_N_Glove_AppUITestsLaunchTests: XCTestCase {

    override class var runsForEachTargetApplicationUIConfiguration: Bool {
        true
    }

    override func setUpWithError() throws {
        continueAfterFailure = false
    }

    func testLaunch() throws {
        let app = XCUIApplication()
        app.launch()

        // Insert steps here to perform after app launch but before taking a screenshot,
        // such as logging into a test account or navigating somewhere in the app

        let attachment = XCTAttachment(screenshot: app.screenshot())
        attachment.name = "Launch Screen"
        attachment.lifetime = .keepAlways
        add(attachment)
    }
}
