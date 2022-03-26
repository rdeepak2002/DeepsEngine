#include <SDL2/SDL.h>
//#include <GLES2/gl2.h>
#include <SDL2/SDL_opengles2.h>
#include <string>
#include <iostream>
#include <cassert>

#include "game.hpp"

#define enum_case(str)\
	case str:\
	std::cerr << SDL_GetTicks() << "--" << file << ", " << line << ": " #str "\n";\
	break;


void gl_error_check(std::string file, int line)
{
    GLenum err = glGetError();

    switch (err) {
        enum_case(GL_INVALID_ENUM)
        enum_case(GL_INVALID_VALUE)
        enum_case(GL_INVALID_OPERATION)
        enum_case(GL_INVALID_FRAMEBUFFER_OPERATION)
        enum_case(GL_OUT_OF_MEMORY)
        default:
            break;
    }
}

#define GL_ERR_CHECK \
do {\
gl_error_check(__FILE__, __LINE__); \
} while(0)


class game_impl {
public:
    virtual void draw() = 0;
};

class game_impl3 : public game_impl {

    GLuint program_object_, vbuffer_;

    GLuint LoadShader(GLenum type, const char *shaderSrc)
    {
        GLuint shader;
        GLint compiled;
        // Create the shader object
        shader = glCreateShader(type);
        if(shader == 0)
            return 0;
        // Load the shader source
        glShaderSource(shader, 1, &shaderSrc, NULL);
        // Compile the shader
        glCompileShader(shader);
        // Check the compile status
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

        if(!compiled)
        {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
            if(infoLen > 1)
            {
                char* infoLog = static_cast<char*>(malloc(sizeof(char) * infoLen));
                glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
                fprintf(stderr, "Error compiling shader:\n%s\n", infoLog);
                free(infoLog);
            }
            glDeleteShader(shader);
            return 0;
        }
        return shader;
    }
///
// Initialize the shader and program object
//
    bool Init()
    {
        const char vShaderStr[] =
                "attribute vec4 vPosition;   \n"
                "void main()                 \n"
                "{                           \n"
                "   gl_Position = vPosition; \n"
                "}                           \n";
        const char fShaderStr[] =
#ifdef EMSCRIPTEN
                "precision mediump float;                   \n"
#endif
                "void main()                                \n"
                "{                                          \n"
                "  gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0); \n"
                "}                                          \n";
        GLuint vertexShader;
        GLuint fragmentShader;
        GLuint programObject;
        GLint linked;
        // Load the vertex/fragment shaders
        vertexShader = LoadShader(GL_VERTEX_SHADER, vShaderStr);
        fragmentShader = LoadShader(GL_FRAGMENT_SHADER, fShaderStr);
        // Create the program object
        programObject = glCreateProgram();
        if(programObject == 0)
            return 0;
        glAttachShader(programObject, vertexShader);
        glAttachShader(programObject, fragmentShader);
        // Bind vPosition to attribute 0
        glBindAttribLocation(programObject, 0, "vPosition");
        // Link the program
        glLinkProgram(programObject);
        // Check the link status
        glGetProgramiv(programObject, GL_LINK_STATUS, &linked);
        if(!linked)
        {
            GLint infoLen = 0;
            glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);
            if(infoLen > 1)
            {
                char* infoLog = static_cast<char *>(malloc(sizeof(char) * infoLen));
                glGetProgramInfoLog(programObject, infoLen, NULL, infoLog);
                fprintf(stderr, "Error linking program:\n%s\n", infoLog);
                free(infoLog);
            }
            glDeleteProgram(programObject);
            return false;
        }
        GL_ERR_CHECK;

        // Store the program object
        program_object_ = programObject;

        // Load the vertex buffer
        GLfloat vVertices[] = {0.0f,  0.5f, 0.0f,
                               -0.5f, -0.5f, 0.0f,
                               0.5f, -0.5f,  0.0f};

        glGenBuffers(1, &vbuffer_);
        GL_ERR_CHECK;
        glBindBuffer(GL_ARRAY_BUFFER, vbuffer_);
        GL_ERR_CHECK;
        glBufferData(GL_ARRAY_BUFFER, 9 *sizeof(GLfloat), &vVertices[0], GL_STATIC_DRAW);
        GL_ERR_CHECK;
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        GL_ERR_CHECK;
        return true;
    }

///
// Draw a triangle using the shader pair created in Init()
//
    void Draw()
    {
        // Set the viewport
        // Use the program object
        glUseProgram(program_object_);
        GL_ERR_CHECK;

        // Bind the vertex buffer
        glBindBuffer(GL_ARRAY_BUFFER, vbuffer_);
        GL_ERR_CHECK;

        // Load the vertex data
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        GL_ERR_CHECK;
        glEnableVertexAttribArray(0);
        GL_ERR_CHECK;
        glDrawArrays(GL_TRIANGLES, 0, 3);
        GL_ERR_CHECK;

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

public:
    game_impl3() {
        assert(Init());
    }

    void draw() {
        GL_ERR_CHECK;
        Draw();
    }

};


game::game()
        : me(new game_impl3())
{}

game::~game()
{}

void game::draw()
{
    me->draw();
}