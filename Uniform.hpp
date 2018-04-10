//
//  Uniform.hpp
//  openGlExample
//
//  Created by Centro Agdigital on 3/4/18.
//  Copyright © 2018 Fransebas. All rights reserved.
//

#ifndef Uniform_hpp
#define Uniform_hpp

#include <stdio.h>
#include <string>

#include "GLObject.hpp"
#include "GLEBOObject.hpp"
#include "Shader.hpp"

using std::string;
class Uniform
{
public:
    Uniform(Shader * shader, string name)
    {
        this->shader = shader;
        this->name = name;
    }
    void read()
    {
        this->pointer = glGetUniformLocation(this->shader->getShaserProgram(), this->name.c_str());
    }
    void writeMatrix4(float *matrix)
    {
        glUniformMatrix4fv(this->pointer, 1, GL_FALSE, matrix);
    }
private:
    Shader * shader;
    string name;
    GLuint pointer;
};

#endif /* Uniform_hpp */
