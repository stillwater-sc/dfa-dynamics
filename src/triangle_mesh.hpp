#include <vector>

class TriangleMesh {
public:
	TriangleMesh();
	~TriangleMesh();

	void draw();

private:
	unsigned int vertex_count;

	// VAO - Vertex Array Object
	unsigned int VAO;  
	
	// VBO - Vertex Buffer Objects
	std::vector<unsigned int> VBO;
};