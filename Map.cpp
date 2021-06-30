#include "Map.h"

Map::Map(Transform* transform, std::vector<std::string> layout) : Entity(transform)
{
	for (int j = 0; j < layout.size(); j++)
	{
		for (int i = 0; i < layout[j].size(); i++)
		{
			if (layout[j][i] == '#')
			{
				
				Entity* wall = new Entity(new Transform({i, j , 0}, 0, { 1, 1 }));
				wall->AddComponent(new RigidBody({ 0, 0 }, { 0, 0 }, 1));
				wall->AddComponent(new BoxRotated(
					{
						{-0.5f, 0.5f}, {0.5f, 0.5f}, {0.5f, -0.5f}, {-0.5f, -0.5f}
					},
					WALL_LAYER,
					PLAYER_BULLET_LAYER,
					{ 1, 0, 0, 1 }
				));

				AddChild(wall);
			}
		}
	}
}

void Map::DrawGUI()
{
	glm::vec2 pos = transform->GetPosition();
	ImGui::DragFloat2("mapPos", &pos.x, 0.01f);
	transform->localTransform[3][0] = pos.x;
	transform->localTransform[3][1] = pos.y;
}
