//
//  Shader.hpp
//  openGlExample
//
//  Created by Centro Agdigital on 3/1/18.
//  Copyright © 2018 Fransebas. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <string>
#include <iostream>
#include <stdio.h>
#if defined(__APPLE__)
#include <GL/glew.h>
#else
#include <glad/glad.h>
#endif
#include <fstream>
#include <sstream>


using std::stringstream;
using std::ifstream;

bool ReadFile(std::string fileName, std::string &buffer)
{
    ifstream inFile;
    inFile.open(fileName);//open the input file
    
    if (!inFile.is_open())
        return false;
    
    stringstream strStream;
    strStream << inFile.rdbuf();//read the file
    buffer = strStream.str();//str holds the content of the file
    
    inFile.close();
    
    return true;
}


class Shader
{
public:
    GLuint shaderProgram;
    std::string vertexPath;
    std::string fragmentPath;
    int type;
    Shader(std::string vertexPath, std::string fragmentPath)
    {
        this->vertexPath = vertexPath;
        this->fragmentPath = fragmentPath;
        this->type = type;
    }
    void compile()
    {
        this->compileShader(this->vertexPath, GL_VERTEX_SHADER);
        this->compileShader(this->fragmentPath, GL_FRAGMENT_SHADER);
    }
    void AddShader(const char* pShaderText, GLenum ShaderType)
    {
        GLuint ShaderObj = glCreateShader(ShaderType);
        if (ShaderObj == 0) {
            fprintf(stderr, "Error creating shader type %d\n", ShaderType);
            exit(0);
        }
        
        const GLchar* p[1];
        p[0] = pShaderText;
        GLint Lengths[1];
        Lengths[0]= strlen(pShaderText);
        glShaderSource(ShaderObj, 1, p, Lengths);
        glCompileShader(ShaderObj);
        GLint success;
        glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
        if (!success) {
            GLchar InfoLog[1024];
            glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
            fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
            exit(1);
        }
        
        glAttachShader(Shader::shaderProgram, ShaderObj);
    }
    void use()
    {
        glUseProgram(this->shaderProgram);
    }
    GLuint getShaserProgram()
    {
        return this->shaderProgram;
    }
private:
    void compileShader(std::string name, int type)
    {
        
        if (this->shaderProgram == 0) this->shaderProgram = glCreateProgram();
        
        if (this->shaderProgram == 0) {
            fprintf(stderr, "Error creating shader program\n");
            exit(1);
        }
        std::string str;
        
        if (!ReadFile(name, str)) {
            std::cout << "Error reading the file " << name << "\n";
            exit(1);
        };
        std::cout << "The code is : " << std::endl;
        std::cout << str << std::endl;
        AddShader(str.c_str(), type);
        
        GLint Success = 0;
        GLchar ErrorLog[1024] = { 0 };
        
        glLinkProgram(this->shaderProgram);
        glGetProgramiv(this->shaderProgram, GL_LINK_STATUS, &Success);
        if (Success == 0) {
            glGetProgramInfoLog(this->shaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
            fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
            exit(1);
        }
        
        /*glValidateProgram(Shader::shaderProgram);
         glGetProgramiv(Shader::shaderProgram, GL_VALIDATE_STATUS, &Success);
         if (!Success) {
         glGetProgramInfoLog(Shader::shaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
         fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
         exit(1);
         }*/
    }
};
#endif /* Shader_hpp */
