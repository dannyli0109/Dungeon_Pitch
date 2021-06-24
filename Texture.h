#pragma once
#include <string>
#include <iostream>
#include "Graphics.h"
#include <ft2build.h>
#include FT_FREETYPE_H

class Texture
{
public:
	Texture(std::string fileName);
	Texture(FT_Face face);
	~Texture();
	void Bind(int index);
	static void Unbind();
	GLuint GetId() { return id; }
private:
	GLuint id;
	bool loadedSuccessfully;
};

