#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>

#include "opengl.hpp"
#include "imgui.h"

#include "cgra/matrix.hpp"
#include "cgra/wavefront.hpp"

#include "ex1.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"

#include <iostream>
#include <vector>
#include "glm/ext.hpp"

const double PI=3.141592653589793238462643383279502884197;
static int devisions = 21;
static int cubeDevisions = 2;
static int r = 2;
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
    
    glm::vec3 rotation(1.0f, 1.0f, 0.0f);
    m_rotationMatrix = glm::rotate(glm::mat4(1.0f), 45.0f, glm::vec3(rotation[0], rotation[1], rotation[2]));
    
}


void Application::sphere_latlong() {
    
    /************************************************************
     *
     * Form triangles in order to generate a sphere primitive.
     * You need to specify discrete steps in both the elevation and azimuthal angles.
     * Let the number of divisions for each angle be integers specified in the ImGui input controls
     * for this primitive.
     *
     ************************************************************/
    int size_vert = devisions*(devisions+1);
    cgra::Matrix<double> vertices(size_vert*3, 3);
    cgra::Matrix<unsigned int> triangles(size_vert, 3);
    int m_SubDiv = 0;
    glm::vec3 center(0,0,0);
    
    int j = 0;
    unsigned int numOfRows = 0;
    std::vector<glm::vec3>spherePoints;
    spherePoints.clear();
    for (double phi = 0; phi < 2*PI; phi +=PI*2/devisions) {
        for(double theta = 0; theta < PI; theta+=PI*2/devisions){
            //std::cout << "we here" << std::endl;
            glm::vec3 point;
            point.x = r * cos(phi*2) * sin(theta * 0.2) + center.x;
            point.y = r * sin(phi*2) * sin(theta) + center.y;
            point.z = r            * cos(theta) + center.z;
            spherePoints.push_back(point);
            m_SubDiv++;
            //std::cout << "we ends" << m_SubDiv<< std::endl;
        }
    }
    
    for (unsigned int i = 0; i < vertices.numRows()/2-6; i+=6) {
        
        vertices.setRow(i, { spherePoints[j].x, spherePoints[j].y, spherePoints[j].z });
        vertices.setRow(i+1, { spherePoints[j+1+devisions/2].x, spherePoints[j+1+devisions/2].y, spherePoints[j+1+devisions/2].z });
        vertices.setRow(i+2, { spherePoints[j+devisions/2].x, spherePoints[j+devisions/2].y, spherePoints[j+devisions/2].z });
        
        vertices.setRow(i+3, { spherePoints[j].x , spherePoints[j].y , spherePoints[j].z });
        vertices.setRow(i+4, { spherePoints[j+1].x, spherePoints[j+1].y, spherePoints[j+1].z });
        vertices.setRow(i+5, { spherePoints[j+1+devisions/2].x , spherePoints[j+1+devisions/2].y , spherePoints[j+1+devisions/2].z });
        j++;
        
    }
    for(unsigned int i = 0; i< triangles.numRows()/2; i++){
        triangles.setRow(i, {numOfRows,numOfRows+1,numOfRows+2});
        numOfRows+=3;
        //triangles.setRow(i, {i+3,i+4,i+5});
    }
    m_mesh.setData(vertices, triangles);
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
            sphere_latlong();
        }
    }
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
