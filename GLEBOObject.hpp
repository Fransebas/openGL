//
//  GLEBOObject.hpp
//  openGlExample
//
//  Created by Centro Agdigital on 3/3/18.
//  Copyright © 2018 Fransebas. All rights reserved.
//

#ifndef GLEBOObject_hpp
#define GLEBOObject_hpp

#include <stdio.h>
#include "GLObject.hpp"

class GLEBOObject : public GLObject
{
public:
    GLEBOObject(unsigned int * index, int indexSize) : GLObject()
    {
        this->index = index;
        this->indexSize = indexSize;
    }
    virtual void draw()
    {
        glEnableVertexAttribArray(0);
        this->bind();
        glDrawElements(GL_TRIANGLES, this->indexSize, GL_UNSIGNED_INT, 0);
        glDisableVertexAttribArray(0);
    }

    virtual void initMemory()
    {
        GLObject::initMemory();
        glGenBuffers(1, &EBO);
        
        this->bind();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*this->indexSize, this->index, this->drawType);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        
        glEnableVertexAttribArray(0);
    }
    virtual void bind()
    {
        GLObject::bind();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    }
private:
    GLuint EBO;
    unsigned int * index;
    int indexSize;
};

#endif /* GLEBOObject_hpp */
