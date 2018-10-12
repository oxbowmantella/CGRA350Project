
#pragma once

// glm
//#include <glm.hpp>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"


// Simple ray class with origin and direction
class Ray {
public:
	glm::vec3 origin;
	glm::vec3 direction;

	Ray() { }
	Ray(const glm::vec3 &o, const glm::vec3 &d) : origin(o), direction(d) { }
};
