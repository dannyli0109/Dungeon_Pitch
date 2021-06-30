#include "LineRenderer.h"

LineRenderer::LineRenderer(ShaderProgram* shaderProgram, int batchSize)
{
	this->shaderProgram = shaderProgram;
	this->maxSize = batchSize;
    vertices.resize(maxSize);
    // Gen buffer
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);

    // Bind vao and vertex buffer
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, maxSize * sizeof(LineVertex), nullptr, GL_DYNAMIC_DRAW);

    // Set vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(LineVertex), (const void*)offsetof(LineVertex, LineVertex::position));
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(LineVertex), (const void*)offsetof(LineVertex, LineVertex::color));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // Unbind
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

LineRenderer::~LineRenderer()
{
}

void LineRenderer::Begin(glm::mat4 projectionMatrix)
{
    this->projectionMatrix = projectionMatrix;
    vertexCount = 0;
    shaderProgram->SetUniform("u_ProjectionMatrix", projectionMatrix);
}

void LineRenderer::End()
{
    if (vertexCount == 0) return;
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertexCount * sizeof(LineVertex), vertices.data());
    glBindVertexArray(vao);
    glDrawArrays(GL_LINES, 0, vertexCount);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void LineRenderer::AddLine(glm::vec2 p1, glm::vec2 p2, glm::vec4 color)
{
    if (vertexCount >= maxSize)
    {
        End();
        Begin(projectionMatrix);
    }
    vertices[vertexCount++] = { glm::vec3(p1, 0), color };
    vertices[vertexCount++] = { glm::vec3(p2, 0), color };
}

void LineRenderer::AddCircle(glm::vec2 position, float radius, glm::vec4 color, int segments)
{
    float cosAngle = cos(2 * 3.14159f / segments);
    float sinAngle = sin(2 * 3.14159f / segments);

    glm::mat2 rotMat = { {cosAngle, -sinAngle}, {sinAngle, cosAngle} };
    glm::vec2 plotPoint(0, radius);

    for (int i = 0; i <= segments; i++)
    {
        glm::vec2 p1 = position + plotPoint;
        plotPoint = rotMat * plotPoint;
        glm::vec2 p2 = position + plotPoint;
        AddLine(p1, p2, color);
    }
}
