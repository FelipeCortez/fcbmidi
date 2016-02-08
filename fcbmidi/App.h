//
//  App.h
//  fcbmidi
//
//  Created by Felipe Cortez on 24/10/15.
//  Copyright (c) 2015 Felipe Cortez. All rights reserved.
//

#ifndef __fcbmidi__App__
#define __fcbmidi__App__

#include <iostream>
#include <stack>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <RtMidi.h>
#include "TextureManager.h"
#include "ResourcePath.hpp"

class AppState;

class App {
    public:
    void pushState(AppState* state);
    void popState();
    void changeState(AppState* state);
    AppState* peekState();
    
    void appLoop();
    
    std::stack<AppState*> states;
    
    sf::RenderWindow window;
    sf::Font appFont;
    
    RtMidiIn *midiin = 0;
    RtMidiOut *midiout = 0;
    
    enum SwitchState {LATCH, MOMENTARY, ALT};
    
    TextureManager texmgr;
    
    App();
    ~App();
};

#endif /* defined(__fcbmidi__App__) */
