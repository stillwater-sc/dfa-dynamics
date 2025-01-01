#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


int main()
try {
	GLFWwindow* window;

	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	window = glfwCreateWindow(640, 480, "Domain Flow Schedular and Mapper", NULL, NULL);
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glClearColor(0.25f, 0.25f, 0.25f, 1.0f);

	while (!glfwWindowShouldClose(window)) {

		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);

	}

	glfwTerminate();

	return EXIT_SUCCESS;
}
catch(...) {
	std::cerr << "Caught unexpected exception" << std::endl;
}
