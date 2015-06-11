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

    skin = [Skin shared];
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

- (void)testLuaCanExecute {
    int result = luaL_dostring(skin.L, "print('Lua executes')");
    XCTAssertFalse(result);
}

- (void)testLuaCanFailToExecute {
    int result = luaL_dostring(skin.L, "invalid mumbojumbo");
    XCTAssertTrue(result);
}

- (void)testProtectedCall {
    int loadResult = luaL_loadstring(skin.L, "print('Lua protected execution works')");
    XCTAssertFalse(loadResult);
    BOOL pcallResult = [skin protectedCallAndTraceback:0 nresults:0];
    XCTAssertTrue(pcallResult);
}

- (void)testProtectedCallWithFailure {
    int loadResult = luaL_loadstring(skin.L, "require('impossible_module')");
    XCTAssertFalse(loadResult);
    BOOL pcallResult = [skin protectedCallAndTraceback:0 nresults:0];
    XCTAssertFalse(pcallResult);
}

- (void)testPerformanceLuaStateLifecycle {
    [self measureBlock:^{
        [skin destroyLuaState];
        [skin createLuaState];
    }];
}

@end
