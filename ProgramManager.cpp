#include "ProgramManager.h"

bool ProgramManager::Init()
{

    //Initialise GLFW, make sure it works. Put an error message here if you like.
    if (!glfwInit())
        return false;

    //Set resolution here, and give your window a different title.
    window = glfwCreateWindow(1280, 720, "Test Bed", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate(); //Again, you can put a real error message here.
        return false;
    }

    //This tells GLFW that the window we created is the one we should render to.
    glfwMakeContextCurrent(window);


    //Tell GLAD to load all its OpenGL functions.
    if (!gladLoadGL())
        return false;

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    srand(std::time(0));

    glViewport(0, 0, 1280, 720);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwSwapInterval(1);

    spriteShader = new ShaderProgram("Quad.vert", "Quad.frag");
    textShader = new ShaderProgram("Text.vert", "Text.frag");
    lineShader = new ShaderProgram("Line.vert", "Line.frag");


    resourceManager = ResourceManager::CreateInstance();
    inputManager = InputManager::CreateInstance();
    physicsScene = PhysicsScene::CreateInstance();

    font = new Font(textShader, "fonts/Bitter/BitterPro-Black.ttf");
    resourceManager->AddTexture(new Texture("white.png"));
    resourceManager->AddTexture(new Texture("dungeon.png"));
    LoadAnimationFrames("player_walking_s", frames);
    LoadAnimationFrames("player_walking_n", frames);
    LoadAnimationFrames("player_walking_e", frames);
    LoadAnimationFrames("player_walking_se", frames);
    LoadAnimationFrames("player_walking_sw", frames);
    LoadAnimationFrames("player_walking_ne", frames);
    LoadAnimationFrames("player_walking_nw", frames);
    LoadAnimationFrames("player_idle_s", frames);
    LoadAnimationFrames("player_idle_n", frames);
    LoadAnimationFrames("player_idle_e", frames);
    LoadAnimationFrames("player_idle_se", frames);
    LoadAnimationFrames("player_idle_sw", frames);
    LoadAnimationFrames("player_idle_ne", frames);
    LoadAnimationFrames("player_idle_nw", frames);
    //ReadAugments("Augments - Augments.csv");

    camera = new Camera({ 0, 0 }, { 1280, 720 }, 96);
    InitAugments();
    InitEntities();


    spriteRenderer = new SpriteRenderer(spriteShader, 512);
    lineRenderer = new LineRenderer(lineShader, 512);
    button = UIButton::CreateInstance(window, font);
    //glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    time = glfwGetTime();
    //current.resize(3);

    //for (int i = 0; i < 3; i++)
    //{
    //    int index = Random(0, relics.size() - 1);
    //    current[i] = index;
    //}
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        ProgramManager* programManager = (ProgramManager*)glfwGetWindowUserPointer(window);


        if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
        {
            programManager->showMenu = !programManager->showMenu;
        }

        if (key == GLFW_KEY_R && action == GLFW_PRESS)
        {
            programManager->ReRollAugments();
            programManager->gold -= 2;
        }
    });

    return true;
}

void ProgramManager::Run()
{
    while (!glfwWindowShouldClose(window))
    {
        currentTime = glfwGetTime();
        deltaTime = currentTime - time;
        time = currentTime;
        //Tell GLFW to check if anything is going on with input, etc.
        glfwPollEvents();
        inputManager->Update(window);

        //std::cout << Entity::entities.size() << std::endl;

        //Clear the screen – eventually do rendering code here.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (!showMenu)
        {
            for (int i = 0; i < Entity::entities.size(); i++)
            {
                Entity::entities[i]->Update(deltaTime);
            }

            physicsScene->CheckForCollisions();
            physicsScene->Update(deltaTime);
        }

        glm::mat4 projection = camera->GetProjection();
        spriteRenderer->Begin(projection);
        //player->Draw(spriteRenderer);
        for (Entity* entity : Entity::entities)
        {
            entity->Draw(spriteRenderer);
        }

        for (Entity* entity : Entity::entities)
        {
            entity->DrawOverlay(spriteRenderer, font);
        }

        spriteRenderer->End();

        lineRenderer->Begin(projection);
        physicsScene->Draw(lineRenderer);
        lineRenderer->End();

        for (int i = 0; i < physicsScene->physicalObjects.size(); i++)
        {
            if (physicsScene->physicalObjects[i]->GetEntity()->removing)
            {
                physicsScene->physicalObjects.erase(physicsScene->physicalObjects.begin() + i);
                i--;
            }
        }

        for (int i = 0; i < Entity::entities.size(); i++)
        {
            if (Entity::entities[i]->removing)
            {
                delete Entity::entities[i];
                Entity::entities.erase(Entity::entities.begin() + i);
                i--;
            }
        }

        if (showMenu)
        {
            CreateMenu();
        }
        //RenderGUI();
        //Swapping the buffers – this means this frame is over.
        glfwSwapBuffers(window);
    }
}

void ProgramManager::Destroy()
{
    glfwTerminate();
    // Cleanup GUI related
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void ProgramManager::RenderGUI()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    // Make window dockable
    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

    // begin imgui window
    ImGui::Begin("Imgui window");
    //// draw ui element in between
    //Box* box = player->GetComponent<Box>();

    //ImGui::DragFloat("minX", &box->xMin);
    //ImGui::DragFloat("maxX", &box->xMax);
    //ImGui::DragFloat("minY", &box->yMin);
    //ImGui::DragFloat("maxY", &box->yMax);
    //ImGui::DragFloat("maxY", &box->yMax);
    //Circle* circle = bullet->GetComponent<Circle>();
    //ImGui::DragFloat("radius", &circle->radius);
    
    for (int i = 0; i < Entity::entities.size(); i++)
    {
        Entity::entities[i]->DrawGUI();
    }



    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    ImGui::EndFrame();
}

void ProgramManager::InitEntities()
{
    InitMap();
    InitPlayer();
    for (int i = 0; i < 5; i++)
    {
        InitEnemy({ -2.6 + 0.5 * i, 2 });
    }
}

void ProgramManager::InitPlayer()
{
    Entity* boxCastH = new Entity(new Transform({ 0, 0, 0 }, 0, { 1, 1 }));
    boxCastH->AddComponent(new RigidBody({ 0, 0 }, { 0, 0 }, 1.0f));
    boxCastH->AddComponent(new Box(-0.16, 0.16, -0.25, 0.43, PLAYER_DETECT_WALL_H_LAYER, WALL_LAYER, { 0, 0, 1, 1 }));


    Entity* boxCastV = new Entity(new Transform({ 0, 0, 0 }, 0, { 1, 1 }));
    boxCastV->AddComponent(new RigidBody({ 0, 0 }, { 0, 0 }, 1.0f));
    boxCastV->AddComponent(new Box(-0.16, 0.16, -0.25, 0.43, PLAYER_DETECT_WALL_V_LAYER, WALL_LAYER, { 0, 0, 1, 1 }));


    Entity* player = new Entity(new Transform({ 0, 0, 0 }, 0, { 1, 1 }));

    player->AddChild(boxCastH);
    player->AddChild(boxCastV);
    {
        AmmoStats bulletStats = {};
        bulletStats.speed = 7.0f;
        bulletStats.type = AmmoType::Bullet;
        bulletStats.damage = 2.0f;
        bulletStats.size = 1.0f;
        bulletStats.critChance = 0.0f;
        bulletStats.travelTime = 2.0f;
        bulletStats.count = 1;
        bulletStats.baseSize = { 0.1f, 0.25f };

        AmmoStats rocketStats = {};
        rocketStats.speed = 5.0f;
        rocketStats.type = AmmoType::Rocket;
        rocketStats.damage = 1.0f;
        rocketStats.size = 1.0f;
        rocketStats.critChance = 0.0f;
        rocketStats.travelTime = 2.0f;
        rocketStats.count = 1;
        rocketStats.baseSize = { 0.2f, 0.4f };
        rocketStats.rocket.explodeDamage = 5.0f;
        rocketStats.rocket.explodeLayer = PLAYER_BULLET_LAYER;
        rocketStats.rocket.explodeMask = ENEMY_LAYER | WALL_LAYER;
        rocketStats.rocket.explodeRadius = 1.0f;

        playerComponent = new Player(window, camera, 3.0f, boxCastH, boxCastV, 20.0f, { bulletStats, rocketStats });
        player->AddComponent(playerComponent);
    }

    player->AddComponent(new RigidBody({ 0, 0 }, { 0, 0 }, 1.0f));
    player->AddComponent(new Box(-0.16, 0.16, -0.25, 0.43, PLAYER_LAYER, WALL_LAYER | ENEMY_LAYER | ENEMY_BULLET_LAYER, {1, 0, 0, 1}));

    {
        Sprite playerSprite = {};
        playerSprite.texture = resourceManager->GetTexture(int(TextureKey::running_s_start));
        playerSprite.tint = { 1.0f, 1.0f, 1.0f, 1.0f };
        playerSprite.tiling = { 1.0f, 1.0f };
        playerSprite.flipped = false;
        player->AddComponent(new SpriteContainer(playerSprite));
    }

    {
        std::unordered_map<std::string, Animation> animations;
        {
            Animation animation;
            animation.frameCount = frames;
            animation.duration = 1.0f;
            for (int i = 0; i < animation.frameCount; i++)
            {
                animation.textures.push_back(resourceManager->GetTexture(int(TextureKey::running_s_start) + i));
            }
            animations["running_s"] = animation;
        }

        {
            Animation animation;
            animation.frameCount = frames;
            animation.duration = 1.0f;
            for (int i = 0; i < animation.frameCount; i++)
            {
                animation.textures.push_back(resourceManager->GetTexture(int(TextureKey::running_n_start) + i));
            }
            animations["running_n"] = animation;
        }

        {
            Animation animation;
            animation.frameCount = frames;
            animation.duration = 1.0f;
            for (int i = 0; i < animation.frameCount; i++)
            {
                animation.textures.push_back(resourceManager->GetTexture(int(TextureKey::running_e_start) + i));
            }
            animations["running_e"] = animation;
        }

        {
            Animation animation;
            animation.frameCount = frames;
            animation.duration = 1.0f;
            animation.flipped = true;
            for (int i = 0; i < animation.frameCount; i++)
            {
                animation.textures.push_back(resourceManager->GetTexture(int(TextureKey::running_e_start) + i));
            }
            animations["running_w"] = animation;
        }

        {
            Animation animation;
            animation.frameCount = frames;
            animation.duration = 1.0f;
            for (int i = 0; i < animation.frameCount; i++)
            {
                animation.textures.push_back(resourceManager->GetTexture(int(TextureKey::running_se_start) + i));
            }
            animations["running_se"] = animation;
        }

        {
            Animation animation;
            animation.frameCount = frames;
            animation.duration = 1.0f;
            for (int i = 0; i < animation.frameCount; i++)
            {
                animation.textures.push_back(resourceManager->GetTexture(int(TextureKey::running_sw_start) + i));
            }
            animations["running_sw"] = animation;
        }

        {
            Animation animation;
            animation.frameCount = frames;
            animation.duration = 1.0f;
            for (int i = 0; i < animation.frameCount; i++)
            {
                animation.textures.push_back(resourceManager->GetTexture(int(TextureKey::running_ne_start) + i));
            }
            animations["running_ne"] = animation;
        }

        {
            Animation animation;
            animation.frameCount = frames;
            animation.duration = 1.0f;
            for (int i = 0; i < animation.frameCount; i++)
            {
                animation.textures.push_back(resourceManager->GetTexture(int(TextureKey::running_nw_start) + i));
            }
            animations["running_nw"] = animation;
        }

        {
            Animation animation;
            animation.frameCount = frames;
            animation.duration = 3.0f;
            for (int i = 0; i < animation.frameCount; i++)
            {
                animation.textures.push_back(resourceManager->GetTexture(int(TextureKey::idle_s_start) + i));
            }
            animations["idle_s"] = animation;
        }

        {
            Animation animation;
            animation.frameCount = frames;
            animation.duration = 3.0f;
            for (int i = 0; i < animation.frameCount; i++)
            {
                animation.textures.push_back(resourceManager->GetTexture(int(TextureKey::idle_n_start) + i));
            }
            animations["idle_n"] = animation;
        }

        {
            Animation animation;
            animation.frameCount = frames;
            animation.duration = 3.0f;
            for (int i = 0; i < animation.frameCount; i++)
            {
                animation.textures.push_back(resourceManager->GetTexture(int(TextureKey::idle_e_start) + i));
            }
            animations["idle_e"] = animation;
        }

        {
            Animation animation;
            animation.frameCount = frames;
            animation.duration = 3.0f;
            animation.flipped = true;
            for (int i = 0; i < animation.frameCount; i++)
            {
                animation.textures.push_back(resourceManager->GetTexture(int(TextureKey::idle_e_start) + i));
            }
            animations["idle_w"] = animation;
        }

        {
            Animation animation;
            animation.frameCount = frames;
            animation.duration = 3.0f;
            for (int i = 0; i < animation.frameCount; i++)
            {
                animation.textures.push_back(resourceManager->GetTexture(int(TextureKey::idle_se_start) + i));
            }
            animations["idle_se"] = animation;
        }

        {
            Animation animation;
            animation.frameCount = frames;
            animation.duration = 3.0f;
            for (int i = 0; i < animation.frameCount; i++)
            {
                animation.textures.push_back(resourceManager->GetTexture(int(TextureKey::idle_sw_start) + i));
            }
            animations["idle_sw"] = animation;
        }

        {
            Animation animation;
            animation.frameCount = frames;
            animation.duration = 3.0f;
            for (int i = 0; i < animation.frameCount; i++)
            {
                animation.textures.push_back(resourceManager->GetTexture(int(TextureKey::idle_ne_start) + i));
            }
            animations["idle_ne"] = animation;
        }

        {
            Animation animation;
            animation.frameCount = frames;
            animation.duration = 3.0f;
            for (int i = 0; i < animation.frameCount; i++)
            {
                animation.textures.push_back(resourceManager->GetTexture(int(TextureKey::idle_nw_start) + i));
            }
            animations["idle_nw"] = animation;
        }

        player->AddComponent(new SpriteAnimation(animations, "idle_se"));
    }
    Entity::entities.push_back(player);

}

void ProgramManager::InitEnemy(glm::vec2 pos)
{
    Entity* enemy = new Entity(new Transform(glm::vec3(pos, 0), 0, { 1, 1 }));
    int idelFrames = 10;


    enemy->AddComponent(new RigidBody({ 0, 0 }, { 0, 0 }, 1.0f));
    enemy->AddComponent(new Box(-0.16, 0.16, -0.25, 0.43, ENEMY_LAYER, WALL_LAYER | PLAYER_LAYER | PLAYER_BULLET_LAYER, { 1, 0, 0, 1 }));
    
    {
        AmmoStats stats = {};
        stats.speed = 5.0f;
        stats.type = AmmoType::Bullet;
        stats.damage = 1.0f;
        stats.size = 1.0f;
        stats.critChance = 0.0f;
        stats.travelTime = 2.0f;
        stats.count = 1;
        stats.baseSize = { 0.1f, 0.25f };


        enemy->AddComponent(new Enemy(playerComponent, 5, 20, {stats}));
    }
    
    glm::vec4 tint = { 0.5, 0.5, 0.5, 1 };

    {
        Sprite enemySprite = {};
        enemySprite.texture = resourceManager->GetTexture(int(TextureKey::running_s_start));
        enemySprite.tint = tint;
        enemySprite.tiling = { 1.0f, 1.0f };
        enemySprite.flipped = false;

        enemy->AddComponent(new SpriteContainer(enemySprite));
    }

    {
        std::unordered_map<std::string, Animation> animations;
        {
            Animation animation;
            animation.frameCount = frames;
            animation.duration = 1.0f;
            animation.tint = tint;
            for (int i = 0; i < animation.frameCount; i++)
            {
                animation.textures.push_back(resourceManager->GetTexture(int(TextureKey::running_s_start) + i));
            }
            animations["running_s"] = animation;
        }

        {
            Animation animation;
            animation.frameCount = frames;
            animation.duration = 1.0f;
            animation.tint = tint;
            for (int i = 0; i < animation.frameCount; i++)
            {
                animation.textures.push_back(resourceManager->GetTexture(int(TextureKey::running_n_start) + i));
            }
            animations["running_n"] = animation;
        }

        {
            Animation animation;
            animation.frameCount = frames;
            animation.duration = 1.0f;
            animation.tint = tint;
            for (int i = 0; i < animation.frameCount; i++)
            {
                animation.textures.push_back(resourceManager->GetTexture(int(TextureKey::running_e_start) + i));
            }
            animations["running_e"] = animation;
        }

        {
            Animation animation;
            animation.frameCount = frames;
            animation.duration = 1.0f;
            animation.flipped = true;
            animation.tint = tint;
            for (int i = 0; i < animation.frameCount; i++)
            {
                animation.textures.push_back(resourceManager->GetTexture(int(TextureKey::running_e_start) + i));
            }
            animations["running_w"] = animation;
        }

        {
            Animation animation;
            animation.frameCount = frames;
            animation.duration = 1.0f;
            animation.tint = tint;
            for (int i = 0; i < animation.frameCount; i++)
            {
                animation.textures.push_back(resourceManager->GetTexture(int(TextureKey::running_se_start) + i));
            }
            animations["running_se"] = animation;
        }

        {
            Animation animation;
            animation.frameCount = frames;
            animation.duration = 1.0f;
            animation.tint = tint;
            for (int i = 0; i < animation.frameCount; i++)
            {
                animation.textures.push_back(resourceManager->GetTexture(int(TextureKey::running_sw_start) + i));
            }
            animations["running_sw"] = animation;
        }

        {
            Animation animation;
            animation.frameCount = frames;
            animation.duration = 1.0f;
            animation.tint = tint;
            for (int i = 0; i < animation.frameCount; i++)
            {
                animation.textures.push_back(resourceManager->GetTexture(int(TextureKey::running_ne_start) + i));
            }
            animations["running_ne"] = animation;
        }

        {
            Animation animation;
            animation.frameCount = frames;
            animation.duration = 1.0f;
            animation.tint = tint;
            for (int i = 0; i < animation.frameCount; i++)
            {
                animation.textures.push_back(resourceManager->GetTexture(int(TextureKey::running_nw_start) + i));
            }
            animations["running_nw"] = animation;
        }

        {
            Animation animation;
            animation.frameCount = idelFrames;
            animation.duration = 3.0f;
            animation.tint = tint;
            for (int i = 0; i < animation.frameCount; i++)
            {
                animation.textures.push_back(resourceManager->GetTexture(int(TextureKey::idle_s_start) + i));
            }
            animations["idle_s"] = animation;
        }

        {
            Animation animation;
            animation.frameCount = idelFrames;
            animation.duration = 3.0f;
            animation.tint = tint;
            for (int i = 0; i < animation.frameCount; i++)
            {
                animation.textures.push_back(resourceManager->GetTexture(int(TextureKey::idle_n_start) + i));
            }
            animations["idle_n"] = animation;
        }

        {
            Animation animation;
            animation.frameCount = idelFrames;
            animation.duration = 3.0f;
            animation.tint = tint;
            for (int i = 0; i < animation.frameCount; i++)
            {
                animation.textures.push_back(resourceManager->GetTexture(int(TextureKey::idle_e_start) + i));
            }
            animations["idle_e"] = animation;
        }

        {
            Animation animation;
            animation.frameCount = idelFrames;
            animation.duration = 3.0f;
            animation.flipped = true;
            animation.tint = tint;
            for (int i = 0; i < animation.frameCount; i++)
            {
                animation.textures.push_back(resourceManager->GetTexture(int(TextureKey::idle_e_start) + i));
            }
            animations["idle_w"] = animation;
        }

        {
            Animation animation;
            animation.frameCount = idelFrames;
            animation.duration = 3.0f;
            animation.tint = tint;
            for (int i = 0; i < animation.frameCount; i++)
            {
                animation.textures.push_back(resourceManager->GetTexture(int(TextureKey::idle_se_start) + i));
            }
            animations["idle_se"] = animation;
        }

        {
            Animation animation;
            animation.frameCount = idelFrames;
            animation.duration = 3.0f;
            animation.tint = tint;
            for (int i = 0; i < animation.frameCount; i++)
            {
                animation.textures.push_back(resourceManager->GetTexture(int(TextureKey::idle_sw_start) + i));
            }
            animations["idle_sw"] = animation;
        }

        {
            Animation animation;
            animation.frameCount = idelFrames;
            animation.duration = 3.0f;
            animation.tint = tint;
            for (int i = 0; i < animation.frameCount; i++)
            {
                animation.textures.push_back(resourceManager->GetTexture(int(TextureKey::idle_ne_start) + i));
            }
            animations["idle_ne"] = animation;
        }

        {
            Animation animation;
            animation.frameCount = idelFrames;
            animation.duration = 3.0f;
            animation.tint = tint;
            for (int i = 0; i < animation.frameCount; i++)
            {
                animation.textures.push_back(resourceManager->GetTexture(int(TextureKey::idle_nw_start) + i));
            }
            animations["idle_nw"] = animation;
        }

        enemy->AddComponent(new SpriteAnimation(animations, "idle_se"));
    }

    Entity::entities.push_back(enemy);
}

void ProgramManager::InitMap()
{
    Entity* map = new Entity(
        new Transform(glm::vec3(0, 0, 0), 0, { 10.0f, 10.0f })
    );
    //map->AddComponent(new SpriteContainer())

    {
        Sprite dungeonSprite = {};
        dungeonSprite.texture = resourceManager->GetTexture(int(TextureKey::dungeon));
        dungeonSprite.tint = { 1.0f, 1.0f, 1.0f, 1.0f };
        dungeonSprite.tiling = { 1.0f, 1.0f };
        dungeonSprite.flipped = false;

        map->AddComponent(new SpriteContainer(dungeonSprite));
    }
    Entity::entities.push_back(map);

    {
        Entity* wall = new Entity(new Transform({ 0, 0, 0 }, 0, { 1.0f, 1.0f }));
        wall->AddComponent(new RigidBody({ 0, 0 }, { 0, 0 }, FLT_MAX));
        wall->AddComponent(new BoxRotated(
            {
                {-3.06f, 3.13f}, {3.11f, 3.11f}, {3.2f, 2.56f}, {-3.21f, 2.56f}
            },
            WALL_LAYER,
            PLAYER_BULLET_LAYER | ENEMY_BULLET_LAYER | PLAYER_LAYER | PLAYER_DETECT_WALL_H_LAYER | PLAYER_DETECT_WALL_V_LAYER,
            { 1, 0, 0, 1 }
        ));
        Entity::entities.push_back(wall);
    }

    {
        Entity* wall = new Entity(new Transform({ 0, 0, 0 }, 0, { 1.0f, 1.0f }));
        wall->AddComponent(new RigidBody({ 0, 0 }, { 0, 0 }, FLT_MAX));
        wall->AddComponent(new BoxRotated(
            {
                { -4.17f, -3.2f}, {4.17f, -3.2f}, {4.25f, -3.63f}, {-4.26f, -3.63f }
            },
            WALL_LAYER,
            PLAYER_BULLET_LAYER | ENEMY_BULLET_LAYER | PLAYER_LAYER | PLAYER_DETECT_WALL_H_LAYER | PLAYER_DETECT_WALL_V_LAYER,
            { 1, 0, 0, 1 }
        ));
        Entity::entities.push_back(wall);
    }

    {
        Entity* wall = new Entity(new Transform({ 0, 0, 0 }, 0, { 1.0f, 1.0f }));
        wall->AddComponent(new RigidBody({ 0, 0 }, { 0, 0 }, FLT_MAX));
        wall->AddComponent(new BoxRotated(
            {
                {-3.44f, 3.13f}, {-3.09f, 3.13f}, {-4.26f, -3.64f}, {-4.71f, -3.61f}
            },
            WALL_LAYER,
            PLAYER_BULLET_LAYER | ENEMY_BULLET_LAYER | PLAYER_LAYER | PLAYER_DETECT_WALL_H_LAYER | PLAYER_DETECT_WALL_V_LAYER,
            { 1, 0, 0, 1 }
        ));
        Entity::entities.push_back(wall);
    }

    {
        Entity* wall = new Entity(new Transform({ 0, 0, 0 }, 0, { 1.0f, 1.0f }));
        wall->AddComponent(new RigidBody({ 0, 0 }, { 0, 0 }, FLT_MAX));
        wall->AddComponent(new BoxRotated(
            {
                { 3.1f, 3.1f }, { 3.43f, 3.15f }, { 4.71f, -3.52f }, { 4.25f, -3.64f }
            },
            WALL_LAYER,
            PLAYER_BULLET_LAYER | ENEMY_BULLET_LAYER | PLAYER_LAYER | PLAYER_DETECT_WALL_H_LAYER | PLAYER_DETECT_WALL_V_LAYER,
            { 1, 0, 0, 1 }
        ));
        Entity::entities.push_back(wall);
    }
}

void ProgramManager::CreateMenu()
{
    glm::vec2 size = camera->GetSize();

    float padding = 50;
    float width = 350;
    float height = 400;
    int amounts = 3;
    float fullButtonWidth = width * amounts + padding * (amounts - 1);

    for (int i = 0; i < amounts; i++)
    {
        float xPosition = (size.x - fullButtonWidth) / 2.0f;
        xPosition += i * (width + padding);

        augments[current[i]].Draw(window, spriteRenderer, font, { xPosition, size.y / 2.0f - height / 2.0f }, { width, height }, 16.0f);
        //std::string str = augments[current[i]].name;
        //button->Draw(spriteRenderer, { xPosition, size.y / 2.0f - height / 2.0f }, { width, height }, { 1.0f, 1.0f, 1.0f }, str, 16.0f, { 0, 0, 0 });
    }

    std::string goldText = "$: " +  std::to_string(playerComponent->gold);
    button->Draw(spriteRenderer, { 640 - width / 2.0f, 720 - 16 }, { width, 16 }, { 0, 0, 0 }, goldText, 16.0f, { 1, 1, 1 });

    
}

void ProgramManager::ReadAugments(std::string filename)
{
    //std::stringstream fileSoFar;
    //std::ifstream file(filename);
    //int row = 0;
    //if (file.is_open())
    //{
    //    while (!file.eof())
    //    {
    //        std::string thisLine;
    //        std::getline(file, thisLine);
    //        if (row != 0)
    //        {
    //            Augment augment = {};
    //            std::vector<std::string> cols = Split(thisLine, ",");
    //            augment.name = cols[1];
    //            augment.description = cols[2];
    //            int rarity;
    //            std::istringstream rarityStream(cols[3]);
    //            rarityStream >> rarity;
    //            augment.rarity = rarity;
    //            augments.push_back(augment);
    //        }
    //        
    //        row++;
    //    }
    //}
    //else
    //{
    //    std::cout << "Error loading file: " << filename << std::endl;
    //}

    //file.close();
}

void ProgramManager::InitAugments()
{

    /*
        sinper	
        sinper	
        sinper	explosive
        sinper	spray
        spray	explosive
        explosive	
        spray	
    */
    augmentRarities.resize(4);
    {
        AugmentStats stats;
        stats.id = 0;
        stats.name = "Laser Sight";
        stats.descriptions = {
            {
                "10% Damage",
                "You get a red laser sight to improve your aim"
            },
            {
                "20% Damage",
                "You get a red laser sight to improve your aim"
            },
            {
                "40% Damage",
                "You get a red laser sight to improve your aim"
            }
        };
        stats.rarity = 0;
        stats.synergies = { 0 };
        stats.onClick = [this](int cost)
        {
            BuyAugmnt(cost);
        };
        augments.push_back(stats);
        augmentRarities[stats.rarity].push_back(stats.id);
    }

    {
        AugmentStats stats;
        stats.id = 1;
        stats.name = "Organic brand bullets";
        stats.descriptions = {
            {
                "2% Crit Rate",
                "Gain a bullet each time you crit"
            },
            {
                "6% Crit Rate",
                "Gain a bullet each time you crit"
            },
            {
                "18% Crit Rate",
                "Gain a bullet each time you crit"
            }
        };
        stats.rarity = 1;
        stats.synergies = { 0 };
        stats.onClick = [this](int cost)
        {
            BuyAugmnt(cost);
        };
        augments.push_back(stats);
        augmentRarities[stats.rarity].push_back(stats.id);
    }

    {
        AugmentStats stats;
        stats.id = 2;
        stats.name = "Extra strength gun powder";
        stats.descriptions = {
            {
                "3% Crit Rate",
                "Crits make an explosive on hit"
            },
            {
                "9% Crit Rate",
                "Crits make an explosive on hit"
            },
            {
                "27% Crit Rate",
                "Crits make an explosive on hit"
            }
        };
        stats.rarity = 2;
        stats.synergies = { 0, 2 };
        stats.onClick = [this](int cost)
        {
            BuyAugmnt(cost);
        };
        augments.push_back(stats);
        augmentRarities[stats.rarity].push_back(stats.id);
    }

    {
        AugmentStats stats;
        stats.id = 3;
        stats.name = "Multi barrel";
        stats.descriptions = {
            {
                "Shoot 2 additional bullets"
            },
            {
                "Shoot 4 additional bullets"
            },
            {
                "Shoot 8 additional bullets"
            }
        };
        stats.rarity = 3;
        stats.synergies = { 0, 1 };
        stats.onClick = [this](int cost)
        {
            BuyAugmnt(cost);
        };
        augments.push_back(stats);
        augmentRarities[stats.rarity].push_back(stats.id);
    }

    {
        AugmentStats stats;
        stats.id = 4;
        stats.name = "Defective nanobot";
        stats.descriptions = {
            {
                "10% explode damage",
                "Enemy explode on death"
            },
            {
                "20% explode damage",
                "Enemy explode on death"
            },
            {
                "40% explode damage",
                "Enemy explode on death"
            }
        };
        stats.rarity = 2;
        stats.synergies = { 1, 2 };
        stats.onClick = [this](int cost)
        {
            BuyAugmnt(cost);
        };
        augments.push_back(stats);
        augmentRarities[stats.rarity].push_back(stats.id);
    }

    {
        AugmentStats stats;
        stats.id = 5;
        stats.name = "Rocket fuel";
        stats.descriptions = {
            { "10% explode range" },
            { "20% explode range" },
            { "40% explode range" }
        };
        stats.rarity = 0;
        stats.synergies = { 2 };
        stats.onClick = [this](int cost)
        {
            BuyAugmnt(cost);
        };
        augments.push_back(stats);
        augmentRarities[stats.rarity].push_back(stats.id);
    }

    {
        AugmentStats stats;
        stats.id = 6;
        stats.name = "Fat bullets";
        stats.descriptions = {
            { "10% bullet size" },
            { "20% bullet size" },
            { "40% bullet size" }
        };
        stats.rarity = 1;
        stats.synergies = { 1 };
        stats.onClick = [this](int cost)
        {
            BuyAugmnt(cost);
        };
        augments.push_back(stats);
        augmentRarities[stats.rarity].push_back(stats.id);
    }

    ReRollAugments();
}

void ProgramManager::ReRollAugments()
{
    current.resize(augmentAmounts);


    for (int i = 0; i < current.size(); i++)
    {
        float randNum = rand() / double(RAND_MAX);
        int rarity;
        if (randNum < 0.4f)
        {
            rarity = 0;
        }
        else if (randNum < 0.7f)
        {
            rarity = 1;
        }
        else if (randNum < 0.9f)
        {
            rarity = 2;
        }
        else
        {
            rarity = 3;
        }

        std::vector<int> augmentIndices = augmentRarities[rarity];
        int randIndex = Random(0, augmentIndices.size() - 1);
        int augmentIndex = augmentIndices[randIndex];
        current[i] = augmentIndex;
    }
}

void ProgramManager::BuyAugmnt(int cost)
{
    if (playerComponent->gold >= cost)
    {
        playerComponent->gold -= cost;
        ReRollAugments();
    }
}


