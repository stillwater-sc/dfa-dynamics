#version 330 core

in vec3 fragmentColor;
in vec2 fragmentTextureCoord;

out vec4 screenColor;

uniform sampler2D material;  // texture unit 0
uniform sampler2D mask;      // texture unit 1

void main() {
    // just color without a texture
	//screenColor = vec4(fragmentColor, 1.0);
	
	// drawing a texture
	//screenColor = texture(material, fragmentTextureCoord);
	
	// with a mask
	vec3 baseColor = texture(material, fragmentTextureCoord).rgb;
	float alpha = texture(mask, fragmentTextureCoord).r;
	screenColor = vec4(baseColor, alpha);

}