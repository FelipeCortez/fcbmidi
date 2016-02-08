//
//  App.cpp
//  fcbmidi
//
//  Created by Felipe Cortez on 24/10/15.
//  Copyright (c) 2015 Felipe Cortez. All rights reserved.
//

#include "App.h"
#include "AppState.h"

void App::pushState(AppState* state) {
    this->states.push(state);
    
    return;
}

void App::popState() {
    //delete this->states.top();
    this->states.pop();
    
    return;
}

void App::changeState(AppState* state) {
    if(!this->states.empty())
        popState();
    pushState(state);
    
    return;
}

AppState* App::peekState() {
    if(this->states.empty()) return nullptr;
    return this->states.top();
}

void App::appLoop() {
    sf::Clock clock;
    
    while(this->window.isOpen()) {

        sf::Time elapsed = clock.restart();
        float dt = elapsed.asSeconds();
        
        if(peekState() == nullptr) continue;
        peekState()->handleInput();
        peekState()->update(dt);
        peekState()->draw(dt);
    }
}

App::App() {
    this->window.create(sf::VideoMode(600, 329), "FCB1010+", sf::Style::Close);
    appFont.loadFromFile(resourcePath() + "Inconsolata-dz.otf");
    
    texmgr.loadTexture("latch", "latch_overlay.png");
    texmgr.loadTexture("moment", "moment_overlay.png");
    texmgr.loadTexture("alt", "alt_overlay.png");
    texmgr.loadTexture("invert", "invert_overlay.png");
    texmgr.loadTexture("n1", "1.png");
    texmgr.loadTexture("n2", "2.png");
    texmgr.loadTexture("n3", "3.png");
    texmgr.loadTexture("n4", "4.png");
    texmgr.loadTexture("n5", "5.png");
    texmgr.loadTexture("n6", "6.png");
    texmgr.loadTexture("n7", "7.png");
    texmgr.loadTexture("n8", "8.png");
    texmgr.loadTexture("n9", "9.png");
    texmgr.loadTexture("n10", "10.png");
    texmgr.loadTexture("logo", "logo.png");
}

App::~App()
{
    while(!this->states.empty()) popState();
}