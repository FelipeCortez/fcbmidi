//
//  BoardState.cpp
//  fcbmidi
//
//  Created by Felipe Cortez on 24/10/15.
//  Copyright (c) 2015 Felipe Cortez. All rights reserved.
//

#include "BoardState.h"
#include <fstream>

void callback(double deltatime, std::vector<unsigned char> *message, void *userData) {
    BoardState* board = static_cast<BoardState*>(userData);
    
    std::vector<unsigned char> messageOut;
    bool noMessage = false;
    
    unsigned int nBytes = message->size();
    for (unsigned int i = 0; i < nBytes; i++ ) {
        std::cout << (int) message->at(i) << " | ";
    }
    
    std::cout << deltatime << std::endl;
    
    // TODO: Change hardcoded channel info
    // Currently accepting at Channel 3
    // http://www.midi.org/techspecs/midimessages.php
    
    if((int)message->at(0) == 146) {
        int footSwitch = (int) message->at(1) - 51;
            
        if((int) message->at(2) == 0) {
            if(board->fs[footSwitch].fs.behaviour == App::MOMENTARY) {
                board->fs[footSwitch].fs.state = false;
            } else if(board->fs[footSwitch].fs.behaviour == App::ALT) {
                noMessage = true;
            }
        } else {
            if(board->fs[footSwitch].fs.behaviour == App::ALT) {
                board->fs[footSwitch].fs.state = true;
            } else {
                board->fs[footSwitch].fs.state = !board->fs[footSwitch].fs.state;
            }
        }

        std::cout << board->fs[footSwitch].fs.behaviour << " | " << board->fs[footSwitch].fs.state << std::endl;

        std::cout << "---" << std::endl;

        if(!noMessage) {
            messageOut.push_back(178);
            messageOut.push_back((int) message->at(1));

            if(board->fs[footSwitch].fs.invert) {
                std::cout << "invert" << std::endl;
                messageOut.push_back(!board->fs[footSwitch].fs.state * 127);
            } else {
                messageOut.push_back(board->fs[footSwitch].fs.state * 127);
            }

            board->app->midiout->sendMessage(&messageOut);
        }
    } else if((int)message->at(0) == 178) {
        switch((int) message->at(1)) {
            case 21:
                std::cout << "left: " << (int) message->at(2) << std::endl;
                board->app->midiout->sendMessage(message);
                break;
            case 22:
                std::cout << "right: " << (int) message->at(2) << std::endl;
                board->app->midiout->sendMessage(message);
                break;
            default:
                break;
        }
    }
}

BoardState::BoardState(App* app) {
    this->app = app;
    
    app->midiin->setCallback(&callback, this);
    
    logoRect.setPosition(sf::Vector2f(17, 13));
    logoRect.setSize(sf::Vector2f(137, 37));
    logoRect.setTexture(&app->texmgr.getRef("logo"));
    
    filenameField.move(sf::Vector2f(301, 18));
    
    for(int i = 0; i < 10; i++) {
        fs[i].setTextures(&app->texmgr);
        fs[i].updateTexture();
    }
    
    fs[0].move(sf::Vector2f(12, 199));
    fs[1].move(sf::Vector2f(119, 199));
    fs[2].move(sf::Vector2f(225, 199));
    fs[3].move(sf::Vector2f(332, 199));
    fs[4].move(sf::Vector2f(438, 199));
    fs[5].move(sf::Vector2f(65, 60));
    fs[6].move(sf::Vector2f(170, 60));
    fs[7].move(sf::Vector2f(277, 60));
    fs[8].move(sf::Vector2f(384, 60));
    fs[9].move(sf::Vector2f(490, 60));
    
    fs[0].setLabel(&app->texmgr.getRef("n1"));
    fs[1].setLabel(&app->texmgr.getRef("n2"));
    fs[2].setLabel(&app->texmgr.getRef("n3"));
    fs[3].setLabel(&app->texmgr.getRef("n4"));
    fs[4].setLabel(&app->texmgr.getRef("n5"));
    fs[5].setLabel(&app->texmgr.getRef("n6"));
    fs[6].setLabel(&app->texmgr.getRef("n7"));
    fs[7].setLabel(&app->texmgr.getRef("n8"));
    fs[8].setLabel(&app->texmgr.getRef("n9"));
    fs[9].setLabel(&app->texmgr.getRef("n10"));
    
    shift = false;
    ctrl = false;

}

void BoardState::update(const float dt) {
}

void BoardState::draw(const float dt) {
    app->window.clear(sf::Color(209, 209, 209));
    
    app->window.draw(logoRect);
    //app->window.draw(filenameField);
    
    for(int i = 0; i < 10; i++) {
        fs[i].updateLed();
        app->window.draw(fs[i]);
    }
    
    app->window.display();
}

void BoardState::handleInput() {
    sf::Event event;
    
    while(app->window.pollEvent(event)) {
        if(event.type == sf::Event::Closed) {
            app->window.close();
        } else if(event.type == sf::Event::KeyPressed) {
            shift = event.key.shift;
            ctrl = event.key.control;
            int footswitch = -1;
            
            switch(event.key.code) {
                case sf::Keyboard::Num1:
                    footswitch = 0;
                    break;
                case sf::Keyboard::Num2:
                    footswitch = 1;
                    break;
                case sf::Keyboard::Num3:
                    footswitch = 2;
                    break;
                case sf::Keyboard::Num4:
                    footswitch = 3;
                    break;
                case sf::Keyboard::Num5:
                    footswitch = 4;
                    break;
                case sf::Keyboard::Num6:
                    footswitch = 5;
                    break;
                case sf::Keyboard::Num7:
                    footswitch = 6;
                    break;
                case sf::Keyboard::Num8:
                    footswitch = 7;
                    break;
                case sf::Keyboard::Num9:
                    footswitch = 8;
                    break;
                case sf::Keyboard::Num0:
                    footswitch = 9;
                    break;
                case sf::Keyboard::S:
                {
                    std::ofstream outfile;
                    std::string name = "Aow bicho";
                    
                    //openSaveDialog();
                    
                    outfile.open(appSupportPath() + "fs1.fcb", std::ios::out | std::ios::binary);
                    outfile << name.length();
                    outfile.write(name.c_str(), sizeof(int) * name.length());
                    
                    for(int i = 0; i < 10; i++) {
                        outfile << fs[i].fs.behaviour;
                    }
                    outfile.close();
                    break;
                }
                case sf::Keyboard::L:
                {
                    std::ifstream infile;
                    infile.open(appSupportPath() + "fs1.fcb", std::ios::in | std::ios::binary);
                    
                    //openOpenDialog();
                    
                    unsigned long strLen;
                    infile >> strLen;
                    char tempstr[strLen];
                    infile.read(tempstr, sizeof(int) * strLen);
                    std::string name(tempstr);
                    std::cout << name << std::endl;
                    
                    for(int i = 0; i < 10; i++) {
                        infile >> fs[i].fs.behaviour;
                        fs[i].updateTexture();
                    }
                    infile.close();
                    
                    break;
                }

                default:
                    break;
            }
            
            if(footswitch != -1) {
                fs[footswitch].changeBehaviour();
                fs[footswitch].updateTexture();
            }
        } else if(event.type == sf::Event::KeyReleased) {
            shift = event.key.shift;
            ctrl = event.key.control;
        } else if(event.type == sf::Event::MouseButtonPressed) {
            if(event.mouseButton.button == sf::Mouse::Right) {}
            
            filenameField.inside(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
            
            for(int i = 0; i < 10; i++) {
                fs[i].inside(sf::Vector2f(event.mouseButton.x, event.mouseButton.y), shift, ctrl);
            }
            
        } else if(event.type == sf::Event::TextEntered) {
            // https://en.wikipedia.org/wiki/List_of_Unicode_characters
            // Support characters other than a-Z later
            if((event.text.unicode >= 34 && event.text.unicode >= 59) ||
               (event.text.unicode >= 66 && event.text.unicode <= 91)) {
                std::wcout << "ASCII character typed: " << event.text.unicode << std::endl;
            }
        }
    }
}