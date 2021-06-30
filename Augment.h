#pragma once
#include <string>
#include "SpriteRenderer.h"
#include "Font.h"
#include "InputManager.h"
#include <functional>
	//    {1, 1, 1},
	//    {1, 1, 1},
	//    {38 / 255.0f, 162 / 255.0f, 240 / 255.0f},
	//    {38 / 255.0f, 162 / 255.0f, 240 / 255.0f},
	//    {111 / 255.0f, 26 / 255.0f, 240 / 255.0f},
	//    {250 / 255.0f, 189 / 255.0f, 31 / 255.0f},

struct AugmentStats
{
	int id;
	std::string name;
	std::vector<std::vector<std::string>> descriptions;
	int rarity;
	std::vector<int> synergies;
	std::function<void(int cost)> onClick;

	std::vector<glm::vec3> bgColors =
	{
		{1, 1, 1},
		{59 / 255.0f, 163 / 255.0f, 177 / 255.0f},
		{160 / 255.0f, 107 / 255.0f, 181 / 255.0f},
		{250 / 255.0f, 190 / 255.0f, 80 / 255.0f}
	};

	std::vector<int> cost =
	{
		1, 2, 3, 5
	};

	std::vector<std::string> synergyText = 
	{
		"Sniper",
		"Spray",
		"Explosive"
	};

	std::vector<glm::vec3> synergyColor =
	{
		{ 255 / 255.0f, 0 / 255.0f, 179 / 255.0f },
		{ 0 / 255.0f, 255 / 255.0f, 0 / 255.0f },
		{ 177 / 255.0f, 59 / 255.0f, 59 / 255.0f }
	};


	virtual void Draw(GLFWwindow* window, SpriteRenderer* spriteRenderer, Font* font, glm::vec2 position, glm::vec2 size, float fontSize);
};


class Augment
{
public:
	Augment(AugmentStats stats) : level(0)
	{
		this->id = stats.id;
		this->rarity = stats.rarity;
		this->name = stats.name;
		this->descriptions = descriptions;
	}
	virtual void Update(float deltaTime) = 0;
	virtual void Draw(SpriteRenderer* spriteRenderer) = 0;
public:
	int level;
	int id;
	int rarity;
	std::string name;
	std::vector<std::string> descriptions;
};
