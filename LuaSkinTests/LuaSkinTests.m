//
//  LuaSkinTests.m
//  LuaSkinTests
//
//  Created by Chris Jones on 11/06/2015.
//  Copyright (c) 2015 Hammerspoon Product Authors. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <XCTest/XCTest.h>
#import "Skin.h"

@interface LuaSkinTests : XCTestCase {
    Skin *skin;
}

@end

@implementation LuaSkinTests

- (void)setUp {
    [super setUp];

    skin = [[Skin alloc] init];
    [skin createLuaState];
}

- (void)tearDown {
    [skin destroyLuaState];
    
    [super tearDown];
}

- (void)testSkinInit {
    XCTAssertNotNil(skin);
}

- (void)testLuaStateCreation {
    XCTAssert((skin.L != NULL));
}

- (void)testLuaStateDestruction {
    [skin destroyLuaState];
    XCTAssert((skin.L == NULL));
}

- (void)testPerformanceLuaStateLifecycle {
    [self measureBlock:^{
        [skin destroyLuaState];
        [skin createLuaState];
    }];
}

@end
