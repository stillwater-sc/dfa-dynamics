#pragma once

class Material {
public:
    Material(const char* filename);
    ~Material();

    void use(int textureUnit);

private:
    unsigned int texture;
    unsigned int shader;
};