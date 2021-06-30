#include "Player.h"

Player::Player(GLFWwindow* window, Camera* camera, float speed, Entity* boxCastH, Entity* boxCastV, float health, std::vector<AmmoStats> ammos) : Agent(health)
{
	this->window = window;
	this->speed = speed;
	this->camera = camera;
	this->boxCastH = boxCastH;
	this->boxCastV = boxCastV;
	this->ammos = ammos;
}

void Player::Update(float deltaTime)
{
	Agent::Update(deltaTime);
	InputManager* input = InputManager::GetInstance();

	SpriteAnimation* spriteAnimation = entity->GetComponent<SpriteAnimation>();
	bool moved = false;


	glm::vec2 mouseWorldPos = ScreenToWorldPos({ input->state.mouseX, input->state.mouseY }, camera, window);
	//std::cout << mouseWorldPos.x << ", " << mouseWorldPos.y << std::endl;

	glm::vec2 playerPos = entity->transform->GetPosition();

	//std::cout << playerPos.x << ", " << playerPos.y << std::endl;
	float angle = GetAngle({mouseWorldPos.x - playerPos.x, -(mouseWorldPos.y - playerPos.y)});
	std::string dirString = "s";
	std::string stateString = "idle";

	if (angle >= -22.5f && angle < 22.5f) dirString = "e";
	if (angle >= 22.5f && angle < 67.5f) dirString = "se";
	if (angle >= 67.5f && angle < 112.5f) dirString = "s";
	if (angle >= 112.5f && angle < 157.5f) dirString = "sw";
	if (angle >= 157.5f || angle < -157.5f) dirString = "w";
	if (angle >= -157.5f && angle < -112.5f) dirString = "nw";
	if (angle >= -112.5f && angle < -67.5f) dirString = "n";
	if (angle >= -67.5f && angle < -22.5f) dirString = "ne";

	glm::vec2 targetDir = { 0, 0 };

	if (glfwGetKey(window, GLFW_KEY_W))
	{
		moved = true;
		targetDir.y += 1;
	}

	if (glfwGetKey(window, GLFW_KEY_A))
	{
		moved = true;
		targetDir.x -= 1;
	}

	if (glfwGetKey(window, GLFW_KEY_S))
	{
		moved = true;
		targetDir.y -= 1;
	}

	if (glfwGetKey(window, GLFW_KEY_D))
	{
		moved = true;
		targetDir.x += 1;
	}

	if (moved)
	{
		stateString = "running";
	}

	spriteAnimation->SetState(stateString + "_" + dirString);

	float dirLength = glm::length(targetDir);
	RigidBody* rb = entity->GetComponent<RigidBody>();
	
	if (rb)
	{
		if (dirLength > 0)
		{
			targetDir /= dirLength;
			rb->SetVelocity(targetDir * speed);

		}
		else if (dirLength == 0)
		{
			rb->SetVelocity({ 0, 0 });
		}
	}

	glm::vec2 castAmount = targetDir * speed * deltaTime;
	boxCastH->transform->localTransform[3][0] = castAmount.x;
	boxCastV->transform->localTransform[3][1] = castAmount.y;

	glm::vec2 windowSize = camera->GetSize();
	float zoom = camera->GetZoom();
	float xMin = -windowSize.x / zoom / 2.0f;
	float xMax = windowSize.x / zoom / 2.0f;
	float yMin = -windowSize.y / zoom / 2.0f;
	float yMax = windowSize.y / zoom / 2.0f;
	Box* box = entity->GetComponent<Box>();
	float boxOffsetX = (box->xMax - box->xMin) / 2.0f;
	float boxOffsetY = (box->yMax - box->yMin) / 2.0f;

	if (playerPos.x - boxOffsetX < xMin) entity->transform->localTransform[3][0] = xMin + boxOffsetX;
	if (playerPos.x + boxOffsetX > xMax) entity->transform->localTransform[3][0] = xMax - boxOffsetX;
	if (playerPos.y - boxOffsetY < yMin) entity->transform->localTransform[3][1] = yMin + boxOffsetY;
	if (playerPos.y + boxOffsetY > yMax) entity->transform->localTransform[3][1] = yMax - boxOffsetY;


	if (input->previousState.mouseDown && input->state.mouseUp)
	{
		float rad = atan2((mouseWorldPos.y - playerPos.y), mouseWorldPos.x - playerPos.x ) - M_PI_2;
		glm::vec2 dir = { mouseWorldPos.x - playerPos.x, mouseWorldPos.y - playerPos.y };
		//glm::mat4 m(1.0f);
		//m = glm::rotate(m, float(M_PI_2), glm::vec3(0, 0, 1.0f));
		//m = glm::translate(m, glm::vec3(dir, 0));
		//dir = m[3];
		float l = glm::length(dir);
		if (l > 0)
		{
			dir /= l;
		}

		int bulletType = 1;
		Entity* bullet = AmmoFactory::GetInstance()->InitBullet(
			entity->transform->GetPosition(), rad, 
			PLAYER_BULLET_LAYER, WALL_LAYER | ENEMY_LAYER,
			this->ammos[bulletType]
		);

		Entity::entities.push_back(bullet);
	}
}
