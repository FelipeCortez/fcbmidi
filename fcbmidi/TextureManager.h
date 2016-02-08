//
//  TextureManager.h
//  fcbmidi
//
//  Created by Felipe Cortez on 24/10/15.
//  Copyright (c) 2015 Felipe Cortez. All rights reserved.
//

#ifndef __fcbmidi__TextureManager__
#define __fcbmidi__TextureManager__

#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <map>

class TextureManager {
    private:
    std::map<std::string, sf::Texture> textures;
    
    public:
    void loadTexture(const std::string& name, const std::string &filename);
    
    sf::Texture& getRef(const std::string& texture);
    
    TextureManager() {}
};

#endif /* defined(__fcbmidi__TextureManager__) */
