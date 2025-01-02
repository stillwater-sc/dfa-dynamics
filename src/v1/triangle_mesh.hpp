
class TriangleMesh {
public:
	TriangleMesh();
	~TriangleMesh();

	void draw();

private:
	unsigned int vertex_count;
	unsigned int VBO;  // VBO - Vertex Buffer Object
	unsigned int VAO;  // VAO - Vertex Array Object

};