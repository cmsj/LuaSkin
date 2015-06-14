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

@interface LuaSkin : NSObject {
    lua_State *_L;
}

@property (atomic, readonly) lua_State *L;

/** Returns the singleton LuaSkin.Skin object
 @return Shared instance of LuaSkin.Skin
 */
+ (id)shared;

/** Initialises a LuaSkin object
 @note Typically you are unlikely to want to use the alloc/init pattern. Instead, see @link shared shared @/link for getting the singleton object. You should only call alloc/init directly if you need to manage multiple Lua environments
 @return An initialised LuaSkin.Skin object
 */
- (id)init;

/** Prepares the Lua environment in the LuaSkin object
 @note This method should only ever be called after an explicit call to destroyLuaState. The class initialisation creats a Lua environment.
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

/** Defines a Lua library
 @code
 static const luaL_Reg myShinyLibrary[] = {
 {"doThing", function_doThing},
 {NULL, NULL} // Library arrays must always end with this
 }
 static const luaL_Reg myShinyMetaLibrary[] = {
 {"__gc", function_doLibraryCleanup},
 {NULL, NULL} // Library arrays must always end with this
 }
 [luaSkin registerLibrary:myShinyLibrary metaFunctions:myShinyMetaLibrary];
 @endcode
 
 @note Every C function pointer must point to a function of the form: static int someFunction(lua_State *L);
 
 @param functions - A static array of mappings between Lua function names and C function pointers. This provides the public API of the Lua library
 @param metaFunctions - A static array of mappings between special meta Lua function names (such as "__gc") and C function pointers.
 */
- (void)registerLibrary:(const luaL_Reg *)functions metaFunctions:(const luaL_Reg *)metaFunctions;

/** Defines a Lua library that creates objects, which have methods
 @code
 char *libraryName = "shinyLibrary";
 
 static const luaL_Reg myShinyLibrary[] = {
 {"newObject", function_createObject},
 {NULL, NULL} // Library arrays must always end with this
 }
 static const luaL_Reg myShinyMetaLibrary[] = {
 {"__gc", function_doLibraryCleanup},
 {NULL, NULL} // Library arrays must always end with this
 }
 static const luaL_Reg myShinyObjectLibrary[] = {
 {"doThing"}, function_objectDoThing},
 {"__gc"}, function_doObjectCleanup},
 {NULL, NULL} // Library arrays must always end with this
 }
 [luaSkin registerLibraryWithObject:libraryName functions:myShinyLibrary metaFunctions:myShinyMetaLibrary libraryObjectFunctions:myShinyObjectLibrary];
 @endcode

 @note Every C function pointer must point to a function of the form: static int someFunction(lua_State *L);

 @param functions - A static array of mappings between Lua function names and C function pointers. This provides the public API of the Lua library
 @param metaFunctions - A static array of mappings between special meta Lua function names (such as "__gc") and C function pointers.
 @param objectFunctions - A static array of mappings between Lua object method names and C function pointers. This provides the public API of objects created by this library. Note that this object is also used as the metatable, so special functions (e.g. "__gc") should be included here.
 */
- (void)registerLibraryWithObject:(char *)libraryName functions:(const luaL_Reg *)functions metaFunctions:(const luaL_Reg *)metaFunctions objectFunctions:(const luaL_Reg *)objectFunctions;

//TODO: Add methods for enforcing Lua function arguments
//TODO: Add methods for converting Lua<->objc types
@end
