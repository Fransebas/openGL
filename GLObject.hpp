//
//  GLObject.hpp
//  openGlExample
//
//  Created by Centro Agdigital on 3/1/18.
//  Copyright © 2018 Fransebas. All rights reserved.
//

#ifndef GLObject_hpp
#define GLObject_hpp

#include <stdio.h>

#if defined(__APPLE__)
    #include <GL/glew.h>
#else
    #include <glad/glad.h>
#endif

class GLObject
{
public:
    int drawType;
    
    GLObject()
    {
        
    }
    virtual void draw()
    {
        glEnableVertexAttribArray(0);
        if (this->colors)
            glEnableVertexAttribArray(1);
        this->bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(0);
    }
    virtual void initMemory()
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
    virtual void bind()
    {
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
    }
    virtual void addColor(float * colors, int n, int drawType)
    {
        this->colors = colors;
        this->colorN = n;
        this->colorDrawType = drawType;
    }
    virtual void addVertex(float * vertex, int n, int drawType)
    {
        this->vertex = vertex;
        this->n = n;
        this->drawType = drawType;
    }
    virtual void addTextureCoords(float * textureCoords, int n, int drawType)
    {
        this->textureCoords = textureCoords;
        this->textureN = n;
        this->colorDrawType = drawType;
    }
private:
    GLuint VBO, VAO;
    float * vertex;
    float * colors;
    float * textureCoords;
    int n = 0;
    int colorN = 0;
    int textureN = 0;
    int colorDrawType;
    
};

#endif /* GLObject_hpp */
