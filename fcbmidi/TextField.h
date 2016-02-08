//
//  TextField.h
//  fcbmidi
//
//  Created by Felipe Cortez on 26/10/15.
//  Copyright (c) 2015 Felipe Cortez. All rights reserved.
//

#ifndef fcbmidi_TextField_h
#define fcbmidi_TextField_h

class TextField : public sf::Transformable, public sf::Drawable {
private:
    sf::RectangleShape bigRect;
    bool focus;
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();
        target.draw(bigRect, states);
    }
    
public:
    TextField() {
        bigRect.setSize(sf::Vector2f(252, 21));
        bigRect.setFillColor(sf::Color(120, 26, 26));
        focus = false;
    }
    
    void move(sf::Vector2f pos) {
        bigRect.move(pos);
    }
    
    bool inside(sf::Vector2f mousePos) {
        if(bigRect.getGlobalBounds().contains(mousePos)) {
            std::cout << "aowoww" << std::endl;
        }
        return false;
    }
    
};

#endif
