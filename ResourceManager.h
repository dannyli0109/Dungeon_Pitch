#pragma once
#include <vector>
#include "Texture.h"

enum class TextureKey
{
	white,
	running_s_start = 1,
	running_n_start = int(running_s_start + 60),
	running_e_start = int(running_n_start + 60),
	running_se_start = int(running_e_start + 60),
	running_sw_start = int(running_se_start + 60),
	running_ne_start = int(running_sw_start + 60),
	running_nw_start = int(running_ne_start + 60),
	idle_s_start = int(running_nw_start + 60),
	idle_n_start = int(idle_s_start + 60),
	idle_e_start = int(idle_n_start + 60),
	idle_se_start = int(idle_e_start + 60),
	idle_sw_start = int(idle_se_start + 60),
	idle_ne_start = int(idle_sw_start + 60),
	idle_nw_start = int(idle_ne_start + 60)
};


class ResourceManager
{
public:
	static ResourceManager* GetInstance();
	static ResourceManager* CreateInstance();
	void AddTexture(Texture* texture);
	Texture* GetTexture(int index);
	void Destroy();
private:
	ResourceManager() {};
	~ResourceManager() {};
	static ResourceManager* instance;
	std::vector<Texture*> textures;
};

