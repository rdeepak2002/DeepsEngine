//
// Created by Deepak Ramalingam on 11/14/21.
//

#include "Renderer.h"
#include <string>
#include <glm.hpp>
#include <ext/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "uuid.h"

// base 64 string table
static const unsigned char base64_table[65] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

/**
* base64_encode - Base64 encode
* @src: Data to be encoded
* @len: Length of the data to be encoded
* @out_len: Pointer to output length variable, or %NULL if not used
* Returns: Allocated buffer of out_len bytes of encoded data,
* or empty string on failure
*/
std::string base64_encode(const unsigned char *src, size_t len) {
    unsigned char *out, *pos;
    const unsigned char *end, *in;

    size_t olen;

    olen = 4 * ((len + 2) / 3); /* 3-byte blocks to 4-byte */

    if (olen < len)
        return std::string(); /* integer overflow */

    std::string outStr;
    outStr.resize(olen);
    out = (unsigned char *) &outStr[0];

    end = src + len;
    in = src;
    pos = out;
    while (end - in >= 3) {
        *pos++ = base64_table[in[0] >> 2];
        *pos++ = base64_table[((in[0] & 0x03) << 4) | (in[1] >> 4)];
        *pos++ = base64_table[((in[1] & 0x0f) << 2) | (in[2] >> 6)];
        *pos++ = base64_table[in[2] & 0x3f];
        in += 3;
    }

    if (end - in) {
        *pos++ = base64_table[in[0] >> 2];
        if (end - in == 1) {
            *pos++ = base64_table[(in[0] & 0x03) << 4];
            *pos++ = '=';
        } else {
            *pos++ = base64_table[((in[0] & 0x03) << 4) |
                                  (in[1] >> 4)];
            *pos++ = base64_table[(in[1] & 0x0f) << 2];
        }
        *pos++ = '=';
    }

    return outStr;
}

void Renderer::saveImage() {
//    if(updateScreenSize) {
////        glfwSetWindowSize(window, scrWidth, scrHeight);
//        glViewport(0, 0, scrWidth, scrHeight);
//        updateScreenSize = false;
//    }
//    else {
//        int width, height;
//        glfwGetFramebufferSize(window, &width, &height);
//        GLsizei nrChannels = 3;
//        GLsizei stride = nrChannels * width;
//        stride += (stride % 4) ? (4 - stride % 4) : 0;
//        GLsizei bufferSize = stride * height;
//        std::vector<char> buffer(bufferSize);
//        glPixelStorei(GL_PACK_ALIGNMENT, 4);
//        glReadBuffer(GL_FRONT);
//        glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, buffer.data());
//
//        // convert the buffer to an opencv image and return the base64 encoded version of it
//        cv::Mat img(height, width, CV_8UC3, buffer.data());
//        // TODO: compress image to improve efficiency
////    cv::Mat scaled_down_img;
////    double scale = 0.5;
////    int newWidth = int(width * scale);
////    int newHeight= int(height * scale);
////    resize(img, scaled_down_img, cv::Size(newHeight, newWidth), cv::INTER_LINEAR);
//        cv::Mat flipped_img;
//        flip(img, flipped_img, 0);
//        cv::Mat BGR_img;
//        cvtColor(flipped_img, BGR_img, cv::COLOR_RGB2BGR);
//        std::vector<uchar> buffer1;
//        buffer1.resize(static_cast<size_t>(BGR_img.rows) * static_cast<size_t>(BGR_img.cols));
//        cv::imencode(".png", BGR_img, buffer1);
//        std::string encoding = base64_encode(buffer1.data(), buffer1.size());
//        cachedFrame = encoding;
//    }
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    scrWidth = width;
    scrHeight = height;
    glViewport(0, 0, width, height);
}

int Renderer::init() {
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // make window invisible
    if (!showWindow)
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    // glfw window creation
    // --------------------
    window = glfwCreateWindow(scrWidth, scrHeight, "LearnOpenGL", NULL, NULL);

    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
//    float vertices[] = {
//            // positions          // colors           // texture coords
//            0.5f, 0.5f, 0.0f, 1.0f, 1.0f, // top right
//            0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
//            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
//            -0.5f, 0.5f, 0.0f,  0.0f, 1.0f  // top left
//    };
    float vertices[] = {
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

//    unsigned int indices[] = {
//            0, 1, 3, // first triangle
//            1, 2, 3  // second triangle
//    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
//    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

//    // position attribute
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
//    glEnableVertexAttribArray(0);
//    // color attribute
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
//    glEnableVertexAttribArray(1);
//    // texture coord attribute
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
//    glEnableVertexAttribArray(2);


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile shaders
    std::string vertexShaderPath = projectPath + "/shaders/shader.vert";
    std::string fragmentShaderPath = projectPath + "/shaders/shader.frag";
//    Shader ourShader(vertexShaderPath.c_str(), fragmentShaderPath.c_str());
    ourShader = new Shader(vertexShaderPath.c_str(), fragmentShaderPath.c_str());

    // define texture uniform variables for textures
    ourShader->use();
    // either set it manually like so:
    ourShader->setInt("texture1", 0);
    // or set it via the texture class
    ourShader->setInt("texture2", 1);

    // load and create a texture
    // -------------------------
    // texture 1
    // ---------
    std::string texture1Path = projectPath + "/textures/container.jpg";
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                    GL_REPEAT);    // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char *data = stbi_load(texture1Path.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    // texture 2
    // ---------
    std::string texture2Path = projectPath + "/textures/awesomeface.png";
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                    GL_REPEAT);    // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    data = stbi_load(texture2Path.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    // return 0 on success
    return 0;
}

void Renderer::render() {
//    scrWidth = glutGet(GLUT_WINDOW_WIDTH);
//    scrHeight = glutGet(GLUT_WINDOW_HEIGHT);

    // input
    // -----
    processInput(window);

    // render
    // ------
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

    // bind textures on corresponding texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    // activate shader
    ourShader->use();

    // create transformations
    glm::mat4 view          = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 projection    = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float)scrWidth / (float)scrHeight, 0.1f, 100.0f);
    view       = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    // pass transformation matrices to the shader
    ourShader->setMat4("projection", projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
    ourShader->setMat4("view", view);

    // render boxes
    glBindVertexArray(VAO);

    for (auto const& keyValueCS : componentSystems)
    {
        ComponentSystem* cs = keyValueCS.second;
        for(auto const& keyValueComponent : cs->components) {
            Component* comp = keyValueComponent.second;

            std::string compName = comp->getName();
            std::string compData = comp->getData();

            if(compName == "transform") {
                std::cout << "comp data: " << compData << std::endl;

                // TODO: parse json string from comp data
                // TODO: parse json string from comp data
                // TODO: parse json string from comp data
                // TODO: parse json string from comp data
                // TODO: parse json string from comp data
                // TODO: parse json string from comp data
                // TODO: parse json string from comp data
                // TODO: parse json string from comp data
                // TODO: parse json string from comp data
                // TODO: parse json string from comp data

                float x = 0;
                float y = 0;
                float z = 0;

                int i = 0;

                // calculate the model matrix for each object and pass it to shader before drawing
                glm::mat4 model = glm::mat4(1.0f);
                glm::vec3 modelPos = glm::vec3(x, y, z);
                model = glm::translate(model, modelPos);
                float angle = 20.0f * (i + 1);
                model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
                ourShader->setMat4("model", model);

                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
            else {
                printf("unknown component type\n");
            }
        }
    }

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(window);
    glfwPollEvents();

    // save frame to image file
    if (saveOutputRender)
        saveImage();
}

bool Renderer::shuttingDown() {
    // glfw: check whether window should close.
    // ------------------------------------------------------------------
    return glfwWindowShouldClose(window);
}

void Renderer::shutDown() {
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
//    glDeleteBuffers(1, &EBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
}

void Renderer::processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void Renderer::handleEditorResize(int width, int height) {
    scrWidth = width;
    scrHeight = height;
    updateScreenSize = true;
}

void Renderer::addComponentSystem(ComponentSystem *componentSystem) {
    // ensure component is non-null
    if(!componentSystem) {
        printf("Error: component system is null\n");
        return;
    }

    // insert the component system into the map
    componentSystems.insert(std::pair<std::string, ComponentSystem*>(componentSystem->getName(), componentSystem));
}

std::string Renderer::addEntity(std::string name) {
    // create a new entity and insert it into the entites map
    // TODO: generate guid
    std::string entityGuid = uuid::generate_uuid_v4();
    entities.insert(std::pair<std::string, std::string>(entityGuid, name));

    // add a transform component to this new entity
    Component* transformComponent = new Component(entityGuid, "transform", "{x: 0, y: 0, z: 0}");
    addComponent(transformComponent);

    // return the newly generated entity id
    return entityGuid;
}

void Renderer::addComponent(Component* component) {
    // ensure component is non-null
    if(!component) {
        printf("Error: component is null\n");
        return;
    }

    // ensure entity id exists
    if(entities.count(component->getEntityId()) == 0) {
        printf("Error: entity with id %s does not exist\n", component->getEntityId().c_str());
        return;
    }

    // add component to components map to link it to an entity
    components.insert(std::pair<std::string, Component*>(component->getId(), component));

    // add component to its array in component system map to link it to a component system
    std::string componentName = component->getName();

    if(componentSystems.count(componentName) == 0) {
        // create entry in map if it does not exist
        addComponentSystem(new ComponentSystem(componentName));
    }

    ComponentSystem* cs = componentSystems[componentName];
    component->setComponentSystemId(cs->getId());
    cs->addComponent(component);
}