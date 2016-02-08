//
//  AppState.h
//  fcbmidi
//
//  Created by Felipe Cortez on 24/10/15.
//  Copyright (c) 2015 Felipe Cortez. All rights reserved.
//

#ifndef __fcbmidi__AppState__
#define __fcbmidi__AppState__

#include <iostream>

#include "App.h"

class AppState {
    public:
    
    App* app;
    
    virtual void update(const float dt) = 0;
    virtual void draw(const float dt) = 0;
    virtual void handleInput() = 0;
};

#endif /* defined(__fcbmidi__AppState__) */