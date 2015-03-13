#pragma once
#include <fstream>
#include <vector>
#define GLM_FORCE_RADIANS
#include <glm\glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "Vertex.h"
using namespace std;
class Geometry
{
private:
	vector<Vertex> data;
public:
	Geometry();
	~Geometry();
	void loadScene(const char *fname);
};

