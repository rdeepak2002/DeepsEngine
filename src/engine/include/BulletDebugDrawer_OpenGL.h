//
// Created by Deepak Ramalingam on 8/6/22.
//

#ifndef DEEPSENGINE_BULLETDEBUGDRAWER_OPENGL_H
#define DEEPSENGINE_BULLETDEBUGDRAWER_OPENGL_H

#include "OpenGLRenderer.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "btBulletDynamicsCommon.h"

// Helper class; draws the world as seen by Bullet.
// This is very handy to see it Bullet's world matches yours
// How to use this class :
// Declare an instance of the class :
//
// dynamicsWorld->setDebugDrawer(&mydebugdrawer);
// Each frame, call it :
// mydebugdrawer.SetMatrices(ViewMatrix, ProjectionMatrix);
// dynamicsWorld->debugDrawWorld();
class BulletDebugDrawer_OpenGL : public btIDebugDraw {
private:
    GLuint VBO, VAO;
public:
    virtual void drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
    {
        // Vertex data
        GLfloat points[12];

        points[0] = from.x();
        points[1] = from.y();
        points[2] = from.z();
        points[3] = color.x();
        points[4] = color.y();
        points[5] = color.z();

        points[6] = to.x();
        points[7] = to.y();
        points[8] = to.z();
        points[9] = color.x();
        points[10] = color.y();
        points[11] = color.z();

        glDeleteBuffers(1, &VBO);
        glDeleteVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(points), &points, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
        glBindVertexArray(0);

        glBindVertexArray(VAO);
        glDrawArrays(GL_LINES, 0, 2);
        glBindVertexArray(0);
    }
    virtual void drawContactPoint(const btVector3 &, const btVector3 &, btScalar, int, const btVector3 &) {}
    virtual void reportErrorWarning(const char *) {}
    virtual void draw3dText(const btVector3 &, const char *) {}
    virtual void setDebugMode(int p) {
        m = p;
    }
    int getDebugMode(void) const { return 3; }
    int m;
};

#endif //DEEPSENGINE_BULLETDEBUGDRAWER_OPENGL_H
