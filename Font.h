#pragma once
#include <iostream>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "Graphics.h"
#include <unordered_map>
#include "ShaderProgram.h"
#include "Texture.h"

struct Character
{
	Texture* texture;
	glm::ivec2 size;
	glm::ivec2 bearing;
	unsigned int advance;
};

class Font
{
public:
	Font(ShaderProgram* shader, std::string filePath);
	ShaderProgram* GetShader() { return shader; }
	~Font();
	void Draw(std::string text, float x, float y, float scale, glm::vec3 color);
	float MeasureWidth(std::string text, float scale);
private:
	std::unordered_map<char, Character> characters;
	ShaderProgram* shader;
	GLuint vbo, vao;
	int size;
};

