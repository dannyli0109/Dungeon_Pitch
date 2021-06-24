#pragma once
#include <vector>

#include "ShaderProgram.h"
#include "Texture.h"	
#include "Camera.h"
#include "ResourceManager.h"
//#include "Graphics.h"

struct SpriteVertex
{
	glm::vec3 position;
	glm::vec2 uv;
	glm::vec4 color;
	glm::vec2 tiling;
	float textureIndex;
};

class SpriteRenderer
{
public:
	SpriteRenderer(ShaderProgram* shaderProgram, int batchSize);
	~SpriteRenderer();
	void Begin(glm::mat4 projectionMatrix);
	void End();
	void AddSprite(glm::mat4 transform, Texture* texture, glm::vec4 tint, glm::vec2 tiling, bool flipped);
	void AddSprite(glm::mat4 transform, glm::vec4 color);

private:
	ShaderProgram* shaderProgram;
	GLuint vertexBuffer, indexBuffer, vao;
	glm::mat4 projectionMatrix;
	int maxIndices, maxVertices, maxTextures, indexCount, vertexCount, textureCount;
	std::vector<SpriteVertex> vertices;
	std::vector<Texture*> textures;
	glm::vec4 quadPositions[4] = {
		{-0.5f, 0.5f, 0, 1.0f},
		{0.5f, 0.5f, 0, 1.0f},
		{-0.5f, -0.5f, 0, 1.0f},
		{0.5f, -0.5f, 0, 1.0f}
	};

	glm::vec2 quadUvs[4] = {
		{0, 0},
		{1, 0},
		{0, 1},
		{1, 1}
	};
};

