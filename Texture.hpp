//
//  Texture.hpp
//  openGlExample
//
//  Created by Centro Agdigital on 3/13/18.
//  Copyright © 2018 Fransebas. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <string>
#include <iostream>
#include <stdio.h>
#include <GL/glew.h>
#include <fstream>
#include <sstream>
#include <stdexcept>

#include "Texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


class Texture
{
public:
    std::string name;
    int width, height, nrChannels;
    unsigned char * data;
    GLuint texture;
    bool mipmap;
    Texture(std::string name, bool mipmap)
    {
        this->name = name;
        this->data = stbi_load(name.c_str(), &this->width, &this->height, &this->nrChannels, 0);
        if (!data)
        {
            throw std::invalid_argument( "can't open image" );
        }
        this->mipmap = mipmap;
        this->initMemory();
    }
    void initMemory()
    {
        glGenTextures(1, &this->texture);
        this->bind();
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->data);
        if (this->mipmap)
        {
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        stbi_image_free(this->data);
    }
    void bind()
    {
        glBindTexture(GL_TEXTURE_2D, this->texture);
    }
    void unbind()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
};

#endif /* Texture_hpp */
