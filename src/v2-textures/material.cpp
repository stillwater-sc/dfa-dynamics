#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include "material.hpp"

Material::Material(const char* filename) {
	int width, height, nrChannels;
	unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, STBI_rgb_alpha);
	if (data == NULL) {
		std::cerr << "Failed to load texture " << filename << std::endl;
		return;
	}
	else {
		std::cout << "Loaded texture " << filename << " with width " << width << " and height " << height << " nrChannels " << nrChannels << '\n';
	}

	// make the texture
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// upload the texture
	glTexImage2D(GL_TEXTURE_2D, 
		0 /* MIPMAP level */, 
		GL_RGBA, 
		width, height, 
		0 /* border color = black */, 
		GL_RGBA, GL_UNSIGNED_BYTE, data);

	// once uploaded, we can get rid of the data
	stbi_image_free(data);

	// configure the texture sampler
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);  // when shrinking no interpolation
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  // when magnifying linear interpolation
}

Material::~Material() {
	glDeleteTextures(1, &texture);
}

void Material::use(int textureUnit) {
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(GL_TEXTURE_2D, texture);
}