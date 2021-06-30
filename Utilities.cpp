#include "Utilities.h"

std::string LoadFileAsString(std::string filename)
{
	std::stringstream fileSoFar;
	std::ifstream file(filename);

	if (file.is_open())
	{
		while (!file.eof())
		{
			std::string thisLine;
			std::getline(file, thisLine);
			fileSoFar << thisLine << std::endl;
		}
		return fileSoFar.str();
	}
	else
	{
		std::cout << "Error loading file: " << filename << std::endl;
		return "";
	}
}

float MapVal(float val, float v1min, float v1max, float v2min, float v2max)
{
	return ((val - v1min) * (v2max - v2min)) / (v1max - v1min) + v2min;
}

void LoadAnimationFrames(std::string folder, int count)
{
	ResourceManager* resourceManager = ResourceManager::GetInstance();
	for (int i = 0; i < count; i++)
	{
		std::string path;
		path += folder;
		path += "\\";
		path += "frame";
		path += std::to_string(i);
		path += ".png";
		resourceManager->AddTexture(new Texture(path));
	}
}

float GetAngle(glm::vec2 v)
{
	return atan2(v.y, v.x) * 180.0f / M_PI;
}

glm::vec2 ScreenToWorldPos(glm::vec2 screenPos, Camera* camera, GLFWwindow* window)
{
	glm::mat4 deprojection = glm::inverse(camera->GetProjection());

	int width, height;
	glfwGetWindowSize(window, &width, &height);

	glm::vec2 ndcPos;
	ndcPos.x = (screenPos.x / width) * 2.0f - 1.0f;
	ndcPos.y = -((screenPos.y / height) * 2.0f - 1.0f);

	glm::vec4 worldPos = deprojection * glm::vec4(ndcPos, 0, 1);
	return worldPos;
}

int Random(int min, int max)
{
	return rand() % (max - min + 1) + min;
}

std::vector<std::pair<std::string, std::vector<int>>> read_csv(std::string filename) {
    // Reads a CSV file into a vector of <string, vector<int>> pairs where
    // each pair represents <column name, column values>

    // Create a vector of <string, int vector> pairs to store the result
    std::vector<std::pair<std::string, std::vector<int>>> result;

    // Create an input filestream
    std::ifstream myFile(filename);

    // Make sure the file is open
    if (!myFile.is_open()) throw std::runtime_error("Could not open file");

    // Helper vars
    std::string line, colname;
    int val;

    // Read the column names
    if (myFile.good())
    {
        // Extract the first line in the file
        std::getline(myFile, line);

        // Create a stringstream from line
        std::stringstream ss(line);

        // Extract each column name
        while (std::getline(ss, colname, ',')) {

            // Initialize and add <colname, int vector> pairs to result
            result.push_back({ colname, std::vector<int> {} });
        }
    }

    // Read data, line by line
    while (std::getline(myFile, line))
    {
        // Create a stringstream of the current line
        std::stringstream ss(line);

        // Keep track of the current column index
        int colIdx = 0;

        // Extract each integer
        while (ss >> val) {

            // Add the current integer to the 'colIdx' column's values vector
            result.at(colIdx).second.push_back(val);

            // If the next token is a comma, ignore it and move on
            if (ss.peek() == ',') ss.ignore();

            // Increment the column index
            colIdx++;
        }
    }

    // Close file
    myFile.close();

    return result;
}


std::vector<std::string> Split(const std::string& s, std::string delimiter)
{
	std::vector<std::string> res;
	auto start = 0U;
	auto end = s.find(delimiter);
	while (end != std::string::npos)
	{
		res.push_back(s.substr(start, end - start));
		start = end + delimiter.length();
		end = s.find(delimiter, start);
	}
	res.push_back(s.substr(start, end));

	return res;
}