#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.hpp"
#include "material.hpp"
#include "triangle_mesh.hpp"


int main()
try {
	GLFWwindow* window;

	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

	window = glfwCreateWindow(640, 480, "Domain Flow Scheduler and Mapper", NULL, NULL);
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
	int w, h;
	glfwGetFramebufferSize(window, &w, &h);
	glViewport(0, 0, w, h);

	TriangleMesh* triangle = new TriangleMesh();
	Material* material = new Material("../img/checker-pattern-horizontal.png");
	//Material* material = new Material("../img/checker-pattern-diagonal.jpg");
	//Material* material = new Material("../img/marika_matsumoto.jpg");
	Material* mask = new Material("../img/mask.jpg");

	unsigned int shader = make_shader(
		"../src/shaders/vertex.glsl",
		"../src/shaders/fragment.glsl"
	);

	// set the texture units
	glUseProgram(shader);
	glUniform1i(glGetUniformLocation(shader, "material"), 0);
	glUniform1i(glGetUniformLocation(shader, "mask"), 1);

	// enable alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	while (!glfwWindowShouldClose(window)) {

		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader);

		material->use(0);
		mask->use(1);
		triangle->draw();

		glfwSwapBuffers(window);

	}

	glDeleteProgram(shader);

	delete triangle;
	delete material;
	delete mask;

	glfwTerminate();

	return EXIT_SUCCESS;
}
catch(...) {
	std::cerr << "Caught unexpected exception" << std::endl;
}


#ifdef FIXED
unsigned int make_shader() {
	unsigned int vertexShaderModule = glCreateShader(GL_VERTEX_SHADER);
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec2 vertexPos;\n"
		"layout (location = 1) in vec3 vertexColor;\n"
		"out vec3 fragmentColor;\n"
		"void main() {\n"
		"   gl_Position = vec4(vertexPos, 0.0, 1.0);\n"
		"   fragmentColor = vertexColor;\n"
		"}\0";
	glShaderSource(vertexShaderModule, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShaderModule);
	int success;
	glGetShaderiv(vertexShaderModule, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(vertexShaderModule, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
#define FIRST
	unsigned int fragmentShaderModule = glCreateShader(GL_FRAGMENT_SHADER);
	const char* fragmentShaderSource =
#ifdef FIRST
		"#version 330 core\n"
		"in vec3 fragmentColor;\n";
	"out vec4 screenColor;\n"
		"void main() {\n"
		"   screenColor = vec4(fragmentColor, 1.0);\n";
	"}\0";
#else
		"#version 330 core\n"
		"out vec4 screenColor;\n"
		"void main() {\n"
		"   screenColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
		"}\0";
#endif
	glShaderSource(fragmentShaderModule, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShaderModule);
	glGetShaderiv(fragmentShaderModule, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(fragmentShaderModule, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	unsigned int shader = glCreateProgram();
	glAttachShader(shader, vertexShaderModule);
	glAttachShader(shader, fragmentShaderModule);
	glLinkProgram(shader);
	// check for linker errors
	glGetProgramiv(shader, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(shader, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	// clean up the shaders
	glDeleteShader(vertexShaderModule);
	glDeleteShader(fragmentShaderModule);

	return shader;
}
#endif
