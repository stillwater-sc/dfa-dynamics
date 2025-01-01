
class TriangleMesh {
public:
	TriangleMesh();
	void draw();
	~TriangleMesh();

private:

	unsigned int VBO;  // VBO - Vertex Buffer Object
	unsigned int VAO;  // VAO - Vertex Array Object
	unsigned int vertex_count;
};