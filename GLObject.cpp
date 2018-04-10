//
//  GLObject.cpp
//  openGlExample
//
//  Created by Centro Agdigital on 3/1/18.
//  Copyright © 2018 Fransebas. All rights reserved.
//

#include "GLObject.hpp"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

GLObject::GLObject()
{
}

void GLObject::addVertex(float * vertex, int n, int drawType)
{
    this->vertex = vertex;
    this->n = n;
    this->drawType = drawType;
}

void GLObject::addColor(float * colors, int n, int drawType)
{
    this->colors = colors;
    this->colorN = n;
    this->colorDrawType = drawType;
}

void GLObject::addTextureCoords(float * textureCoords, int n, int drawType)
{
    this->textureCoords = textureCoords;
    this->textureN = n;
    this->colorDrawType = drawType;
}

void GLObject::initMemory()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    this->bind();
    
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*n + sizeof(float)*this->colorN + sizeof(float)*this->textureN, 0, this->drawType);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)*n, this->vertex);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    if (this->colors)
    {
        glBufferSubData(GL_ARRAY_BUFFER,  sizeof(float)*n, sizeof(float)*this->colorN, this->colors);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)((sizeof(float)*n)) );
    }
    
    if (this->textureCoords)
    {
        glBufferSubData(GL_ARRAY_BUFFER,  sizeof(float)*n + sizeof(float)*this->colorN, sizeof(float)*this->textureN, this->textureCoords);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(float)*n + sizeof(float)*this->colorN) );
    }
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
}

void GLObject::draw()
{
    glEnableVertexAttribArray(0);
    if (this->colors)
            glEnableVertexAttribArray(1);
    this->bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(0);
}


