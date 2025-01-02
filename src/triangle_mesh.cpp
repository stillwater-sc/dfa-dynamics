#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "triangle_mesh.hpp"

TriangleMesh::TriangleMesh() {
    vertex_count = 3;

    std::vector<float> positions = {
         -1.0f, -1.0f, 0.0f,
          1.0f, -1.0f, 0.0f,
         -1.0f,  1.0f, 0.0f
    };
    
    std::vector<int> colorIndices = {
		0, 1, 2
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Vertex Buffer objects
    VBO.resize(2);
    glGenBuffers(2, VBO.data());

    // position
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(float), positions.data(), GL_STATIC_DRAW);
  // vertexAttribPointer(index, size, type, normalized, stride, pointer)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12 /* stride to next attribute */, (void*)0);
    glEnableVertexAttribArray(0);

    // color
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, colorIndices.size() * sizeof(int), colorIndices.data(), GL_STATIC_DRAW);
    // vertexAttribIPointer(index, size, type, stride, pointer)
    glVertexAttribIPointer(1, 1, GL_INT, 4 /* stride to next attribute */, (void*)0);  // <---- notice the attrib integer pointer function signature
    glEnableVertexAttribArray(1);

	// the VBO handles are stored in the VAO
	// and the specific VBO, that is VBO[0] and VBO[1] are tied to the location 0 and 1 of the vertex shader
    // location=0 is glVertexAttribPointer( -->0<--...
    // location=1 is glVertexAttribIPointer( -->1<--...
}

void TriangleMesh::draw() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertex_count);
}

TriangleMesh::~TriangleMesh() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(2, VBO.data());
}