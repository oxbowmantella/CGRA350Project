
// glm
//#include <gtc/constants.hpp>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"

// project
#include "light.hpp"
#include "ex1.hpp"
#include "ray.hpp"
#include "fruitModels.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include "opengl.hpp"
#include "imgui.h"
#include "cgra/matrix.hpp"
#include "cgra/wavefront.hpp"

bool DirectionalLight::occluded(Scene *scene, const glm::vec3 &point) const {
	//-------------------------------------------------------------
	// [Assignment 4] :
	// Determine whether the given point is being occluded from
	// this directional light by an object in the scene.
	// Remember that directional lights are "infinitely" far away
	// so any object in the way would cause an occlusion.
	//-------------------------------------------------------------

	// YOUR CODE GOES HERE
	// ...
    Ray reverseDirection = Ray(point, -m_direction);
    //for(std::shared_ptr<SceneObject>object : scene->objects()){
        RayIntersection intersect = scene->intersect(reverseDirection);
        if(intersect.m_valid){
            return true;
        }
    //}
	return false;
}


glm::vec3 DirectionalLight::incidentDirection(const glm::vec3 &) const {
	return m_direction;
}


glm::vec3 DirectionalLight::irradiance(const glm::vec3 &) const {
	return m_irradiance;
}


bool PointLight::occluded(Scene *scene, const glm::vec3 &point) const {
	//-------------------------------------------------------------
	// [Assignment 4] :
	// Determine whether the given point is being occluded from
	// this directional light by an object in the scene.
	// Remember that point lights are somewhere in the scene and
	// an occulsion has to occur somewhere between the light and 
	// the given point.
	//-------------------------------------------------------------

	// YOUR CODE GOES HERE
	// ...
    Ray reverseDirection = Ray(point,m_position-point);
    RayIntersection intersect = scene->intersect(reverseDirection);
    if (intersect.m_valid) {
        glm::vec3 LightToObject = point - m_position;
        glm::vec3 LightToCollision = intersect.m_position - m_position;
        
        float dot = glm::dot(LightToObject, LightToCollision);
        return dot >= 0;
    }
    return false;
}

glm::vec3 PointLight::incidentDirection(const glm::vec3 &point) const {
	//-------------------------------------------------------------
	// [Assignment 4] :
	// Return the direction of the incoming light (light to point)
	//-------------------------------------------------------------

	// YOUR CODE GOES HERE
	// ...
    glm::vec3 dir = point - m_position;
    return dir;
	//return glm::vec3(0);
    
}


glm::vec3 PointLight::irradiance(const glm::vec3 &point) const {
	//-------------------------------------------------------------
	// [Assignment 4] :
	// Return the total irradiance on the given point.
	// This requires you to convert the flux of the light into
	// irradiance by dividing it by the surface of the sphere
	// it illuminates. Remember that the surface area increases
	// as the sphere gets bigger, ie. the point is further away.
	//-------------------------------------------------------------

	// YOUR CODE GOES HERE
	// ...
    float dist = glm::distance(point, m_position);
    return m_flux / (4 * glm::pi<float>() * dist * dist);
    //return glm::vec3(0);
}

