//
//  Skin.m
//  LuaSkin
//
//  Created by Chris Jones on 11/06/2015.
//  Copyright (c) 2015 Hammerspoon Project Authors. All rights reserved.
//

#import "Skin.h"

@implementation Skin

#pragma mark - Skin Properties

@synthesize L = _L;

#pragma mark - Class lifecycle

- (id)init {
    self = [super init];
    if (self) {
        [self createLuaState];
    }
    return self;
}

#pragma mark - lua_State lifecycle

- (void)createLuaState {
    _L = luaL_newstate();
    luaL_openlibs(_L);
}

- (void)destroyLuaState {
    if (_L) {
        lua_close(_L);
    }
    _L = NULL;
}

#pragma mark - Methods for calling into Lua from C

/** Calls lua_pcall() with debug.traceback() as the message handler
 
 @code
 // First push a reference to the Lua function you want to call
 lua_rawgeti(L, LUA_REGISTRYINDEX, fnRef);
 
 // Then push the parameters for that function, in order
 lua_pushnumber(L, 1);
 
 // Finally, call protectedCallAndTraceback, telling it how 
 // many arguments you pushed, and how many results you expect
 BOOL result = [luaSkin protectedCallAndTraceback:1 nresults:0];
 
 // The boolean return tells you whether the Lua code threw
 // an exception or not
 if (!result) handleSomeError();
 @endcode
 
 @return NO if the Lua code threw an exception, otherwise YES
 @param nargs An integer specifying how many function arguments you have pushed onto the stack
 @param nresults An integer specifying how many return values the Lua function will push onto the stack
 */
- (BOOL)protectedCallAndTraceback:(int)nargs nresults:(int)nresults {
    // At this point we are being called with nargs+1 items on the stack, but we need to shove our traceback handler below that
    
    // Get debug.traceback() onto the top of the stack
    lua_getglobal(_L, "debug");
    lua_getfield(_L, -1, "traceback");
    lua_remove(_L, -2);

    // Move debug.traceback() to the bottom of the stack.
    // The stack currently looks like this:
    //  -1 debug.traceback()
    //  -2 argN
    //  -3 argN - 1
    //  -4 function
    //
    // The stack should look like this, for nargs == 3:
    //  -1 argN
    //  -2 argN - 1
    //  -3 argN - 2
    //  -4 function
    //  -5 debug.traceback()
    //
    // Or, for nargs == 0:
    //  -1 function
    //  -2 debug.traceback()
    int tracebackPosition = -nargs - 2;
    lua_insert(_L, tracebackPosition);
    
    if (lua_pcall(_L, nargs, nresults, tracebackPosition) != LUA_OK) {
        return NO;
    }
    
    return YES;
}

@end
