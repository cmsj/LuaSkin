//
//  Skin.h
//  LuaSkin
//
//  Created by Chris Jones on 11/06/2015.
//  Copyright (c) 2015 Hammerspoon Project Authors. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "lauxlib.h"
#import "lua.h"

@interface Skin : NSObject {
    lua_State *L;
}

@end
