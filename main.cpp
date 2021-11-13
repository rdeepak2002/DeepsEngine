#include <glew.h>
#include <glfw3.h>
#include <iostream>
using namespace std;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    //If you press ESC and set windowShouldClose to True, the external loop will close the application
    if(key==GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    std::cout<<"ESC"<<mode;
}

int main(void)
{
    //Initialize GLFW Library
    if(!glfwInit())
        return -1;
    //Create window and context
    GLFWwindow* window = glfwCreateWindow(640, 480, "hello world", NULL, NULL);
    if(!window)
    {
        //NULL will be returned if creation fails
        glfwTerminate();
    }
    //Establish the context of the current window
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, key_callback); //Registering Callbacks
    //Loop until the user closes the window
    while(!glfwWindowShouldClose(window))
    {
        /*******Polling events*******/
        glfwPollEvents();

        /*******Rendering*******/
        //Select empty color RGBA
        glClearColor(0.2, 0.3, 0.3, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        //Start drawing a triangle
        glBegin(GL_TRIANGLES);
        glColor3f(1, 0, 0); //Red
        glVertex3f(0, 1, 1);

        glColor3f(0, 1, 0); //Green
        glVertex3f(-1, -1, 0);

        glColor3f(0, 0, 1); //Blue
        glVertex3f(1, -1, 0);
        //End a drawing step
        glEnd();

        glBegin(GL_POLYGON);
        //Draw another trapezoid, and pay attention to the stroke order
        glColor3f(0.5, 0.5, 0.5); //Grey
        glVertex2d(0.5, 0.5);
        glVertex2d(1, 1);
        glVertex2d(1, 0);
        glVertex2d(0.5, 0);
        glEnd();


        /******Exchange buffer, update content on window******/
        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}