//
//  Skin.h
//  LuaSkin
//
//  Created by Chris Jones on 11/06/2015.
//  Copyright (c) 2015 Hammerspoon Project Authors. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "lauxlib.h"
#import "lualib.h"
#import "lua.h"

@interface Skin : NSObject {
    lua_State *_L;
}

@property (atomic, readonly) lua_State *L;

/** Returns the singleton LuaSkin.Skin object
 @return Shared instance of LuaSkin.Skin
 */
+ (id)shared;

/** Prepares the Lua environment in the LuaSkin object
 @note This must be called once after accessing the shared LuaSkin object for the first time
 */
- (void)createLuaState;

/** Destroys the Lua environment in the LuaSkin object
 */
- (void)destroyLuaState;

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
- (BOOL)protectedCallAndTraceback:(int)nargs nresults:(int)nresults;

@end
