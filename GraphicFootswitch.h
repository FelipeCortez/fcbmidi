//
//  GraphicalFootswitch.h
//  fcbmidi
//
//  Created by Felipe Cortez on 24/10/15.
//  Copyright (c) 2015 Felipe Cortez. All rights reserved.
//

#ifndef fcbmidi_GraphicalFootswitch_h
#define fcbmidi_GraphicalFootswitch_h

#include "Footswitch.h"

class GraphicFootswitch : public sf::Transformable, public sf::Drawable {
private:
    sf::RectangleShape bigRect;
    sf::RectangleShape smallRect;
    sf::RectangleShape textureRect;
    sf::RectangleShape labelRect;
    sf::RectangleShape invertRect;
    sf::CircleShape ledCircle;
    TextureManager* textures;
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();
        target.draw(bigRect, states);
        target.draw(smallRect, states);
        target.draw(textureRect, states);
        target.draw(labelRect, states);
        target.draw(ledCircle, states);
        if(fs.invert) {
            target.draw(invertRect, states);
        }
    }
    
public:
    Footswitch fs;
    
    GraphicFootswitch() {        
        bigRect.setSize(sf::Vector2f(61, 122));
        bigRect.setFillColor(sf::Color(26, 26, 26));
        
        smallRect.setSize(sf::Vector2f(42, 73));
        smallRect.setPosition(sf::Vector2f(10, 39));
        smallRect.setFillColor(sf::Color(58, 58, 58));
        
        textureRect.setSize(sf::Vector2f(42, 73));
        textureRect.setPosition(sf::Vector2f(10, 39));
        
        ledCircle.setRadius(4);
        ledCircle.setPosition(sf::Vector2f(9, 9));
        updateLed();
        
        labelRect.setSize(sf::Vector2f(37, 29));
        labelRect.setPosition(sf::Vector2f(13, 9));
        
        invertRect.setSize(sf::Vector2f(20, 20));
        invertRect.setPosition(sf::Vector2f(41, 0));
    }
    
    void setTextures(TextureManager* textures) {
        this->textures = textures;
        invertRect.setTexture(&textures->getRef("invert"));
    }
    
    void setLabel(sf::Texture* labelTexture) {
        labelRect.setTexture(labelTexture);
    }
    
    void changeBehaviour(bool plus = true) {
        if(plus) {
            fs.behaviour = (fs.behaviour + 1) % 3;
        } else {
            if(fs.behaviour != 0) {
                fs.behaviour -= 1;
            } else {
                fs.behaviour = 2;
            }
        }
    }
    
    void invert() {
        fs.invert = !fs.invert;
    }
    
    bool inside(sf::Vector2f mousePos, bool shift, bool ctrl) {
        if(smallRect.getGlobalBounds().contains(mousePos)) {
            if(ctrl) {
                invert();
            } else {
                changeBehaviour(!shift);
                updateTexture();
            }
            
            return true;
        }
        return false;
    }
    
    void updateTexture() {
        switch(fs.behaviour) {
            case App::LATCH:
                textureRect.setTexture(&textures->getRef("latch"));
                break;
            case App::MOMENTARY:
                textureRect.setTexture(&textures->getRef("moment"));
                break;
            case App::ALT:
                textureRect.setTexture(&textures->getRef("alt"));
                break;
        }
    }
    
    void updateLed() {
        // != inverts fs.state
        if(fs.state != fs.invert) {
            ledCircle.setFillColor(sf::Color(201, 0, 0));
        } else {
            ledCircle.setFillColor(sf::Color(100, 0, 0));
        }
    }
    
    void move(sf::Vector2f pos) {
        bigRect.move(pos);
        smallRect.move(pos);
        textureRect.move(pos);
        ledCircle.move(pos);
        labelRect.move(pos);
        invertRect.move(pos);
    }
    
};

#endif
