#pragma once

#include <ctime>
#include <cstdlib>
#include "Graphics.h"
#include "GUI.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "Camera.h"
#include "Entity.h"
#include "Transform.h"
#include "SpriteContainer.h"
#include "SpriteAnimation.h"
#include "Font.h";
#include "UIButton.h"
#include "LineRenderer.h"
#include "InputManager.h"
#include "RigidBody.h"
#include "PhysicsScene.h"
#include "Box.h"
#include "Circle.h"
#include "Augment.h"
#include "Map.h"
#include "Player.h"
#include "Enemy.h"
#include "Ammo.h"

class ProgramManager
{
public:
    bool Init();
    void Run();
    void Destroy();
private:
    void RenderGUI();
    //bool InitWindow();
    //void InitResources();
    void InitEntities();
    void InitPlayer();
    void InitEnemy(glm::vec2 pos);
    void InitMap();
    void CreateMenu();
    void ReadAugments(std::string filename);
    void InitAugments();
    void ReRollAugments();
    void BuyAugmnt(int cost);
private:
    GLFWwindow* window;
    ResourceManager* resourceManager;
    InputManager* inputManager;

    ShaderProgram* spriteShader;
    ShaderProgram* textShader;
    ShaderProgram* lineShader;

    SpriteRenderer* spriteRenderer;
    LineRenderer* lineRenderer;

    PhysicsScene* physicsScene;

    Camera* camera;
    float time;
    float currentTime;
    float deltaTime;
    Font* font;
    UIButton* button;
    //Entity* player;

    Player* playerComponent;
    Entity* bullet;

    int gold = 999;
    std::vector<int> current;
    bool showMenu = false;
    int frames = 10;
    std::vector<AugmentStats> augments;
    std::vector<std::vector<int>> augmentRarities;
    std::vector<float> prices =
    {
        1, 2, 3, 5
    };
    std::vector<float> percentage =
    {
        0.4f, 0.3f, 0.2f, 0.1f
    };

    int augmentAmounts = 3;
    glm::vec2 mapPos = { 0, 0 };

    //std::vector<glm::vec3> bgColors = {
    //    {1, 1, 1},
    //    {1, 1, 1},
    //    {38 / 255.0f, 162 / 255.0f, 240 / 255.0f},
    //    {38 / 255.0f, 162 / 255.0f, 240 / 255.0f},
    //    {111 / 255.0f, 26 / 255.0f, 240 / 255.0f},
    //    {250 / 255.0f, 189 / 255.0f, 31 / 255.0f},

    //    {1, 1, 1},
    //    {1, 1, 1},
    //    {38 / 255.0f, 162 / 255.0f, 240 / 255.0f},
    //    {38 / 255.0f, 162 / 255.0f, 240 / 255.0f},
    //    {111 / 255.0f, 26 / 255.0f, 240 / 255.0f},
    //    {250 / 255.0f, 189 / 255.0f, 31 / 255.0f},

    //    {1, 1, 1},
    //    {1, 1, 1},
    //    {38 / 255.0f, 162 / 255.0f, 240 / 255.0f},
    //    {38 / 255.0f, 162 / 255.0f, 240 / 255.0f},
    //    {111 / 255.0f, 26 / 255.0f, 240 / 255.0f},
    //    {250 / 255.0f, 189 / 255.0f, 31 / 255.0f}
    //};

    //std::vector<std::string> relics = {
    //    "ArcherI",
    //    "ArcherII",
    //    "ArcherIII",
    //    "ArcherIV",
    //    "ArcherV",
    //    "ArcherVI",

    //    "SniperI",
    //    "SniperII",
    //    "SniperIII",
    //    "SniperIV",
    //    "SniperV",
    //    "SniperVI",

    //    "SummonerI",
    //    "SummonerII",
    //    "SummonerIII",
    //    "SummonerIV",
    //    "SummonerV",
    //    "SummonerVI"
    //};

    //std::vector<int> price = {
    //    1, 1, 2, 2, 3, 5,
    //    1, 1, 2, 2, 3, 5,
    //    1, 1, 2, 2, 3, 5
    //};
};

