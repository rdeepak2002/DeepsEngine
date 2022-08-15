//
// Created by Deepak Ramalingam on 8/6/22.
//

#include "SphereMesh.h"

DeepsEngine::SphereMesh::SphereMesh() {
    unsigned int xSegments = 20;
    unsigned int ySegments = 20;

    for (unsigned int y = 0; y <= ySegments; ++y)
    {
        for (unsigned int x = 0; x <= xSegments; ++x)
        {
            float xSegment = (float)x / (float)xSegments;
            float ySegment = (float)y / (float)ySegments;
            float xPos = std::cos(xSegment * 2 * glm::pi<float>()) * std::sin(ySegment * glm::pi<float>()); // TAU is 2PI
            float yPos = std::cos(ySegment * glm::pi<float>());
            float zPos = std::sin(xSegment * 2 * glm::pi<float>()) * std::sin(ySegment * glm::pi<float>());

            Positions.push_back(glm::vec3(xPos, yPos, zPos));
            UV.push_back(glm::vec2(xSegment, ySegment));
            Normals.push_back(glm::vec3(xPos, yPos, zPos));
        }
    }

    bool oddRow = false;
    for (int y = 0; y < ySegments; ++y)
    {
        for (int x = 0; x < xSegments; ++x)
        {
            Indices.push_back((y + 1) * (xSegments + 1) + x);
            Indices.push_back(y       * (xSegments + 1) + x);
            Indices.push_back(y       * (xSegments + 1) + x + 1);

            Indices.push_back((y + 1) * (xSegments + 1) + x);
            Indices.push_back(y       * (xSegments + 1) + x + 1);
            Indices.push_back((y + 1) * (xSegments + 1) + x + 1);
        }
    }

    Finalize();
}

void DeepsEngine::SphereMesh::Finalize() {
    bool interleaved = true;

    // initialize object IDs if not configured before
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // preprocess buffer data as interleaved or seperate when specified
    std::vector<float> data;
    if (interleaved)
    {
        for (int i = 0; i < Positions.size(); ++i)
        {
            data.push_back(Positions[i].x);
            data.push_back(Positions[i].y);
            data.push_back(Positions[i].z);
            if (UV.size() > 0)
            {
                data.push_back(UV[i].x);
                data.push_back(UV[i].y);
            }
            if (Normals.size() > 0)
            {
                data.push_back(Normals[i].x);
                data.push_back(Normals[i].y);
                data.push_back(Normals[i].z);
            }
//            if (Tangents.size() > 0)
//            {
//                data.push_back(Tangents[i].x);
//                data.push_back(Tangents[i].y);
//                data.push_back(Tangents[i].z);
//            }
//            if (Bitangents.size() > 0)
//            {
//                data.push_back(Bitangents[i].x);
//                data.push_back(Bitangents[i].y);
//                data.push_back(Bitangents[i].z);
//            }
        }
    }
    else
    {
        // if any of the float arrays are empty, data won't be filled by them.
        for (int i = 0; i < Positions.size(); ++i)
        {
            data.push_back(Positions[i].x);
            data.push_back(Positions[i].y);
            data.push_back(Positions[i].z);
        }
        for (int i = 0; i < UV.size(); ++i)
        {
            data.push_back(UV[i].x);
            data.push_back(UV[i].y);
        }
        for (int i = 0; i < Normals.size(); ++i)
        {
            data.push_back(Normals[i].x);
            data.push_back(Normals[i].y);
            data.push_back(Normals[i].z);
        }
//        for (int i = 0; i < Tangents.size(); ++i)
//        {
//            data.push_back(Tangents[i].x);
//            data.push_back(Tangents[i].y);
//            data.push_back(Tangents[i].z);
//        }
//        for (int i = 0; i < Bitangents.size(); ++i)
//        {
//            data.push_back(Bitangents[i].x);
//            data.push_back(Bitangents[i].y);
//            data.push_back(Bitangents[i].z);
//        }
    }

    // configure vertex attributes (only on vertex data size() > 0)
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
    // only fill the index buffer if the index array is non-empty.
    if (Indices.size() > 0)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(unsigned int), &Indices[0], GL_STATIC_DRAW);
    }
    if (interleaved)
    {
        // calculate stride from number of non-empty vertex attribute arrays
        size_t stride                      = 3 * sizeof(float);
        if (UV.size() > 0)         stride += 2 * sizeof(float);
        if (Normals.size() > 0)    stride += 3 * sizeof(float);
//        if (Tangents.size() > 0)   stride += 3 * sizeof(float);
//        if (Bitangents.size() > 0) stride += 3 * sizeof(float);

        size_t offset = 0;
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
        offset += 3 * sizeof(float);
        if (UV.size() > 0)
        {
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
            offset += 2 * sizeof(float);
        }
        if (Normals.size() > 0)
        {
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
            offset += 3 * sizeof(float);
        }
//        if (Tangents.size() > 0)
//        {
//            glEnableVertexAttribArray(3);
//            glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
//            offset += 3 * sizeof(float);
//        }
//        if (Bitangents.size() > 0)
//        {
//            glEnableVertexAttribArray(4);
//            glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset);
//            offset += 3 * sizeof(float);
//        }
    }
    else
    {
        size_t offset = 0;
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)offset);
        offset += Positions.size() * sizeof(float);
        if (UV.size() > 0)
        {
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)offset);
            offset += UV.size() * sizeof(float);
        }
        if (Normals.size() > 0)
        {
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)offset);
            offset += Normals.size() * sizeof(float);
        }
//        if (Tangents.size() > 0)
//        {
//            glEnableVertexAttribArray(3);
//            glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)offset);
//            offset += Tangents.size() * sizeof(float);
//        }
//        if (Bitangents.size() > 0)
//        {
//            glEnableVertexAttribArray(4);
//            glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)offset);
//            offset += Bitangents.size() * sizeof(float);
//        }
    }
    glBindVertexArray(0);
}

