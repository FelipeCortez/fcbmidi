//
//  PortState.h
//  fcbmidi
//
//  Created by Felipe Cortez on 24/10/15.
//  Copyright (c) 2015 Felipe Cortez. All rights reserved.
//

#ifndef __fcbmidi__PortState__
#define __fcbmidi__PortState__

#include <iostream>
#include "AppState.h"

class PortState : public AppState {
    public:
    PortState(App* app);
    
    virtual void draw(const float dt);
    virtual void update(const float dt);
    virtual void handleInput();
    
    int selPort;
    std::vector<sf::Text> ports;
    sf::Text bracket;
};

#endif /* defined(__fcbmidi__PortState__) */
