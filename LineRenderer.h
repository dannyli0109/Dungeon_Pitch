#pragma once
#include "Graphics.h"
#include "ShaderProgram.h"

struct LineVertex
{
	glm::vec3 position;
	glm::vec4 color;
};

class LineRenderer
{
public:
	LineRenderer(ShaderProgram* shaderProgram, int batchSize);
	~LineRenderer();
	void Begin(glm::mat4 projectionMatrix);
	void End();
	void AddLine(glm::vec2 p1, glm::vec2 p2, glm::vec4 color);
	void AddCircle(glm::vec2 position, float radius, glm::vec4 color, int segments);
private:
	ShaderProgram* shaderProgram;
	int maxSize, vertexCount;
	std::vector<LineVertex> vertices;
	GLuint vbo;
	GLuint vao;
	glm::mat4 projectionMatrix;
};

