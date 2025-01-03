#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "triangle_mesh.hpp"

TriangleMesh::TriangleMesh() {
    vertex_count = 6;

    std::vector<float> vertexCoordinates = {
         -1.0f, -1.0f, 0.0f,   // bottom left
		  1.0f, -1.0f, 0.0f,   // bottom right
		 -1.0f,  1.0f, 0.0f,   // top left
		  1.0f,  1.0f, 0.0f,   // top right
    };

    std::vector<int> colorIndices = {
		0, 1, 2
    };
	// 1st triangle: bottom left, bottom right, top left, 
    // 2nd triangle: top right, bottom right, top left
    std::vector<int> elementIndices = {
        //0, 1, 2, 2, 1, 3
        0, 1, 2, 3, 1, 2
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Vertex Buffer objects
    VBO.resize(2);
    glGenBuffers(2, VBO.data());

    // position
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, vertexCoordinates.size() * sizeof(float), vertexCoordinates.data(), GL_STATIC_DRAW);
  // vertexAttribPointer(index, size, type, normalized, stride, pointer)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12 /* stride to next attribute */, (void*)0);
    glEnableVertexAttribArray(0);

    // color
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, colorIndices.size() * sizeof(int), colorIndices.data(), GL_STATIC_DRAW);
    // vertexAttribIPointer(index, size, type, stride, pointer)
    glVertexAttribIPointer(1, 1, GL_INT, 4 /* stride to next attribute */, (void*)0);  // <---- notice the attrib integer pointer function signature
    glEnableVertexAttribArray(1);

    // element buffer
	glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementIndices.size() * sizeof(int), elementIndices.data(), GL_STATIC_DRAW);

	// the VBO handles are stored in the VAO
	// and the specific VBO, that is VBO[0] and VBO[1] are tied to the location 0 and 1 of the vertex shader
    // location=0 is glVertexAttribPointer( -->0<--...
    // location=1 is glVertexAttribIPointer( -->1<--...
}

void TriangleMesh::draw() {
    glBindVertexArray(VAO);
	//glDrawArrays(GL_TRIANGLES, 0, vertex_count);  // if you draw using glDrawArrays, you don't need to bind the EBO
	glDrawElements(GL_TRIANGLES, vertex_count, GL_UNSIGNED_INT, 0);
}

TriangleMesh::~TriangleMesh() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(2, VBO.data());
	glDeleteBuffers(1, &EBO);
}