#pragma once
#include <vector>
#include "glm/glm.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>
//#include <string>

#include "opengl.hpp"
#include "imgui.h"

#include "cgra/matrix.hpp"
#include "cgra/wavefront.hpp"
#include "cgra/mesh.hpp"
#include "cgra/shader.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"



class fruitModels {
public:
    cgra::Program m_program;
    
    cgra::Mesh m_bowl;
    void drawBowl();
    void Bowl();
};