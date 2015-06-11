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
@property (atomic) int evalFn;

- (void)createLuaState;
- (void)destroyLuaState;
- (BOOL)protectedCallAndTraceback:(int)nargs nresults:(int)nresults;

@end
