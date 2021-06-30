#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include "ResourceManager.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Camera.h"


std::string LoadFileAsString(std::string filename);
float MapVal(float val, float v1min, float v1max, float v2min, float v2max);
void LoadAnimationFrames(std::string folder, int count);
float GetAngle(glm::vec2 v);
glm::vec2 ScreenToWorldPos(glm::vec2 screenPos, Camera* camera, GLFWwindow* window);
int Random(int min, int max);
std::vector<std::pair<std::string, std::vector<int>>> read_csv(std::string filename);
std::vector<std::string> Split(const std::string& s, std::string delimiter);