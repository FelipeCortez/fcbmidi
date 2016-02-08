//
//  TextureManager.cpp
//  fcbmidi
//
//  Created by Felipe Cortez on 24/10/15.
//  Copyright (c) 2015 Felipe Cortez. All rights reserved.
//

#include "TextureManager.h"
#include "ResourcePath.hpp"

void TextureManager::loadTexture(const std::string& name, const std::string& filename) {
    sf::Texture tex;
    tex.loadFromFile(resourcePath() + filename);
    
    this->textures[name] = tex;
}

sf::Texture& TextureManager::getRef(const std::string& texture) {
    return this->textures.at(texture);
}