#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>

#include "opengl.hpp"
#include "imgui.h"

#include "cgra/matrix.hpp"
#include "cgra/wavefront.hpp"

#include "ex1.hpp"
#include "fruitModels.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"

#include <iostream>
#include <vector>
#include "glm/ext.hpp"


bool toSphere = false;
void Application::init() {
    // Load the shader program
    // The use of CGRA_SRCDIR "/path/to/shader" is so you don't
    // have to run the program from a specific folder.
    m_program = cgra::Program::load_program(
                                            CGRA_SRCDIR "/res/shaders/simple.vs.glsl",
                                            CGRA_SRCDIR "/res/shaders/simple.fs.glsl");
    
    // Create a view matrix that positions the camera
    // 10 units behind the object
    glm::mat4 viewMatrix(1);
    viewMatrix[3] = glm::vec4(0, 0, -10, 1);
    m_program.setViewMatrix(viewMatrix);
    
    /*
    glm::vec3 rotation(1.0f, 1.0f, 0.0f);
    m_rotationMatrix = glm::rotate(glm::mat4(1.0f), 45.0f, glm::vec3(rotation[0], rotation[1], rotation[2]));
    */
}


void Application::drawScene() {
    // Calculate the aspect ratio of the viewport;
    // width / height
    float aspectRatio = m_viewportSize.x / m_viewportSize.y;
    // Calculate the projection matrix with a field-of-view of 45 degrees
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
    
    // Set the projection matrix
    m_program.setProjectionMatrix(projectionMatrix);
    glm::mat4 modelTransform = m_rotationMatrix * glm::mat4(1.0f);
    
    /************************************************************
     *                                                          *
     * Use `m_translation`, `m_scale`, and `m_rotationMatrix`   *
     * to create the  `modelTransform` matrix.                  *
     * The following glm functions will be useful:              *
     *    `glm::translate`                                      *
     *    `glm::scale`                                          *
     ************************************************************/
    
    m_program.setModelMatrix(modelTransform);
    
    // Draw the mesh
    m_mesh.draw();
    
    fruitModels m_fruits = *new fruitModels();
    m_fruits.Bowl();
    m_fruits.drawBowl();
}

void Application::doGUI() {
    ImGui::SetNextWindowSize(ImVec2(450, 450), ImGuiSetCond_FirstUseEver);
    ImGui::Begin("Shapes");
    static bool click = false;
    static bool click2 = false;
    static bool sphere_draw;
    // Example for rotation, use glm to create a a rotation
    // matrix from this vector
    static glm::vec3 rotation(1.0f, 1.0f, 0.0f);
    if (ImGui::InputFloat3("Rotation", &rotation[0])) {
        // This block is executed if the input changes
        m_rotationMatrix = glm::rotate(glm::mat4(1.0f), 45.0f, glm::vec3(rotation[0], rotation[1], rotation[2]));
    }
    
    /*
    if (ImGui::InputInt("Number of divisions", &devisions)) {
        // This block is executed if the input changes
        //devisions = devisions + 3;
        if(sphere_draw == true){
            sphere_latlong();
        }
        //sphere_from_cube();
        
    }
    if (ImGui::Checkbox("Draw Wireframe", &click)){
        //std::cout << click <<"\n";
        m_mesh.setDrawWireframe(&click);
    }else if(click == false){   //disable wireframe mode
        m_mesh.setDrawWireframe(false);
    }
    
    if (ImGui::Checkbox("Use sphere_latlong", &sphere_draw)) {
        // This block is executed if the input changes
        if(sphere_draw == true){
     
            
        }
    }*/
    ImGui::Separator();
   
    ImGui::End();
    
}


// Input Handlers

void Application::onMouseButton(int button, int action, int) {
    if (button >=0 && button < 3) {
        // Set the 'down' state for the appropriate mouse button
        m_mouseButtonDown[button] = action == GLFW_PRESS;
    }
}

void Application::onCursorPos(double xpos, double ypos) {
    
    // Make a vec2 with the current mouse position
    glm::vec2 currentMousePosition(xpos, ypos);
    
    // Get the difference from the previous mouse position
    glm::vec2 mousePositionDelta = currentMousePosition - m_mousePosition;
    
    if (m_mouseButtonDown[GLFW_MOUSE_BUTTON_LEFT]) {
        
    } else if (m_mouseButtonDown[GLFW_MOUSE_BUTTON_MIDDLE]) {
        
    } else if (m_mouseButtonDown[GLFW_MOUSE_BUTTON_RIGHT]) {
        
    }
    
    // Update the mouse position to the current one
    m_mousePosition = currentMousePosition;
}

void Application::onKey(int key, int scancode, int action, int mods) {
    // `(void)foo` suppresses unused variable warnings
    (void)key;
    (void)scancode;
    (void)action;
    (void)mods;
}

void Application::onScroll(double xoffset, double yoffset) {
    // `(void)foo` suppresses unused variable warnings
    (void)xoffset;
    (void)yoffset;
}
