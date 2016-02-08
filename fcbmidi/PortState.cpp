//
//  PortState.cpp
//  fcbmidi
//
//  Created by Felipe Cortez on 24/10/15.
//  Copyright (c) 2015 Felipe Cortez. All rights reserved.
//

#include "PortState.h"
#include "BoardState.h"

PortState::PortState(App* app)
{
    this->app = app;
    
    try {
        app->midiout = new RtMidiOut();
    } catch ( RtMidiError &error ) {
        error.printMessage();
        exit( EXIT_FAILURE );
    }
    
    try {
        app->midiin = new RtMidiIn();
        app->midiout = new RtMidiOut();
    } catch ( RtMidiError &error ) {
        error.printMessage();
    }
    
    selPort = 0;
    
    bracket = sf::Text(">", app->appFont);
    bracket.setCharacterSize(16);
    bracket.setColor(sf::Color(58, 58, 58));
    
    unsigned int i = 0, nPorts = app->midiin->getPortCount();
    if (nPorts == 0) {
        std::cout << "No input ports available!" << std::endl;
        return false;
    } else {
        for (i = 0; i < nPorts; i++) {
            sf::Text text(app->midiin->getPortName(i), app->appFont);
            text.setCharacterSize(16);
            text.setColor(sf::Color(58, 58, 58));
            text.setPosition(35, (i * 30) + 30);
            ports.push_back(text);
        }
    }

}

void PortState::update(const float dt) {
    bracket.setPosition(15, (selPort * 30) + 30);
}

void PortState::draw(const float dt) {
    app->window.clear(sf::Color(209, 209, 209));
    app->window.draw(bracket);
    
    for(int i = 0; i < ports.size(); i++) {
        app->window.draw(ports[i]);
    }
    
    app->window.display();
}

void PortState::handleInput() {
    sf::Event event;
    
    while(app->window.pollEvent(event)) {
        if(event.type == sf::Event::Closed) {
            app->window.close();
        } else if(event.type == sf::Event::KeyPressed) {
            switch(event.key.code) {
                case sf::Keyboard::Down:
                    selPort = (selPort + 1) % ports.size();
                    break;
                case sf::Keyboard::Up:
                    if(selPort == 0) {
                        selPort = ports.size() - 1;
                    } else {
                        selPort = selPort - 1;
                    }
                    break;
                case sf::Keyboard::Return:
                case sf::Keyboard::Space:
                    app->midiin->openPort(selPort);
                    app->midiout->openVirtualPort(std::string("FCB1010+"));
                    app->pushState(new BoardState(app));
                default:
                    break;
            }
        }

    }
}