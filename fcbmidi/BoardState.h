//
//  BoardState.h
//  fcbmidi
//
//  Created by Felipe Cortez on 24/10/15.
//  Copyright (c) 2015 Felipe Cortez. All rights reserved.
//

#ifndef __fcbmidi__BoardState__
#define __fcbmidi__BoardState__

#include <iostream>
#include "AppState.h"
#include "GraphicFootswitch.h"
#include "TextField.h"

class BoardState : public AppState {
public:
    BoardState(App* app);
    
    virtual void draw(const float dt);
    virtual void update(const float dt);
    virtual void handleInput();
    
    bool shift;
    bool ctrl;
    GraphicFootswitch fs[10];
    TextField filenameField;
    sf::RectangleShape logoRect;
};

#endif /* defined(__fcbmidi__BoardState__) */
