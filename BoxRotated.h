#pragma once
#include "Shape.h"
#include "Entity.h"
#include "Transform.h"
#include "GUI.h"
class BoxRotated :
    public Shape
{
public:
	BoxRotated(std::vector<glm::vec2> points, int layer, int mask, glm::vec4 color);

	std::vector<glm::vec2> GetPoints();
	glm::vec2 GetCenter();

#pragma region Overrdie
	virtual void Update(float deltaTime) override {};
	virtual void Draw(SpriteRenderer* spriteRenderer) override {};
	virtual void DrawShape(LineRenderer* lineRenderer) override;
	virtual bool ContainPoint(glm::vec2 point) override;
	virtual void DrawGUI() override
	{
		//if (layer == WALL_LAYER)
		//{
		///*	std::string label = "Shape Pos###" + std::to_string(entity->id);
		//	ImGui::DragFloat3(label.c_str(), &entity->transform->localTransform[3].x, 0.01f);*/

		//	//glm::vec2 scale = { entity->transform->localTransform[0][0], entity->transform->localTransform[1][1] };
		//	//std::string sacleLabel = "Shape Scale###" + std::to_string(entity->id);
		//	//ImGui::DragFloat2(sacleLabel.c_str(), &scale.x, 0.01f);
		//	//entity->transform->Scale(scale);

		//	for (int i = 0; i < points.size(); i++)
		//	{
		//		std::string label = "Shape Pos###" + std::to_string(entity->id) + std::to_string(i);
		//		ImGui::DragFloat2(label.c_str(), &points[i].x, 0.01f);
		//	}
		//	ImGui::Spacing();
		//}
	}
#pragma endregion
private:
	std::vector<glm::vec2> points;
};

