#pragma once
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


static float scaler = 1;    //object scaler
static float xCHNG = 1; //change in mouseX
static float yCHNG = 1; //change in mouseY
static glm::vec3 rotation(0,0,0);
static glm::vec3 translation(0,0,0);
bool toSphere = false;
fruitModels m_fruits = *new fruitModels();
void Application::init() {
    // Load the shader program
    // The use of CGRA_SRCDIR "/path/to/shader" is so you don't
    // have to run the program from a specific folder.
    if(m_fruits.enable_textures == true){
        m_program = cgra::Program::load_program(
                                                CGRA_SRCDIR "/res/shaders/texture.vs.glsl",
                                                CGRA_SRCDIR "/res/shaders/texture.fs.glsl");
    }
    if(m_fruits.enable_textures == false){
        m_program = cgra::Program::load_program(
                                                CGRA_SRCDIR "/res/shaders/simple.vs.glsl",
                                                CGRA_SRCDIR "/res/shaders/simple.fs.glsl");
    }
    
    
    glm::mat4 viewMatrix(1);
    viewMatrix[3] = glm::vec4(0, 0, -10, 1);
    m_program.setViewMatrix(viewMatrix);
    
}

void Application::drawScene() {
    // Calculate the aspect ratio of the viewport;
    // width / height
    float aspectRatio = m_viewportSize.x / m_viewportSize.y;
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
    
    // Set the projection matrix
    m_program.setProjectionMatrix(projectionMatrix);
    
    glm::mat4 modelTransform(1.0f);
    
    
    modelTransform = glm::translate(modelTransform, m_translation);
    modelTransform = glm::scale(modelTransform, glm::vec3(m_scale));
    
    const float PI = 3.14159;
    modelTransform = glm::rotate(modelTransform, m_rotationMatrix[0][0] * PI / 180, {1, 0 ,0});
    modelTransform = glm::rotate(modelTransform, m_rotationMatrix[1][1] * PI / 180, {0, 1 ,0});
    modelTransform = glm::rotate(modelTransform, m_rotationMatrix[2][2] * PI / 180, {0, 0 ,1});
    m_program.setModelMatrix(modelTransform);
    
    m_mesh.draw();
    
    // Draw the mesh
    //Fruit testing
    m_fruits.Bowl(0,0,-3,90,180,0);
    m_fruits.drawBowl();
    m_fruits.Orange(0,0,0,-90,180,0);
    m_fruits.drawOrange();
    m_fruits.Strawberry(2,0,0,-90,180,0);
    m_fruits.drawStrawberry();
    m_fruits.Tomato(-2,0,0,-90,180,0);
    m_fruits.drawTomato();
    m_fruits.Apple(4,0,0,-90,180,0);
    m_fruits.drawApple();

    //DrawPlane();
}

void Application::doGUI() {
    ImGui::SetNextWindowSize(ImVec2(250, 250), ImGuiSetCond_FirstUseEver);
    ImGui::Begin("Shapes");
    static bool click = false;
    static bool click2 = false;
    static char buf[255];
    
    if (ImGui::InputFloat3("Rotation", &rotation[0])) {
        m_rotationMatrix = glm::mat3x3(
                                       rotation.x,0.0,0.0,
                                       0.0,rotation.y,0.0,
                                       0.0,0.0,rotation.z
                                       );
    }
    if (ImGui::Checkbox("Draw Wireframe", &click)){
        m_fruits.m_AppleTopper.setDrawWireframe(&click);
        m_fruits.m_apple.setDrawWireframe(&click);
        m_fruits.m_orangeTopper.setDrawWireframe(&click);
        m_fruits.m_orange.setDrawWireframe(&click);
        m_fruits.m_TomatorTopper.setDrawWireframe(&click);
        m_fruits.m_tomato.setDrawWireframe(&click);
        m_fruits.m_StrawTopper.setDrawWireframe(&click);
        m_fruits.m_strawberry.setDrawWireframe(&click);
        m_fruits.m_bowl.setDrawWireframe(&click);
        m_fruits.enable_textures = false;
        click2 = false;
        init();
    }else if(click == false){   //disable wireframe mode
        m_fruits.m_AppleTopper.setDrawWireframe(false);
        m_fruits.m_apple.setDrawWireframe(false);
        m_fruits.m_orangeTopper.setDrawWireframe(false);
        m_fruits.m_orange.setDrawWireframe(false);
        m_fruits.m_TomatorTopper.setDrawWireframe(false);
        m_fruits.m_tomato.setDrawWireframe(false);
        m_fruits.m_StrawTopper.setDrawWireframe(false);
        m_fruits.m_strawberry.setDrawWireframe(false);
        m_fruits.m_bowl.setDrawWireframe(false);
        init();
    }
    
    if (ImGui::Checkbox("Enable Textures", &click2)){
        m_fruits.enable_textures = true;
        click = false;
        init();
    }else if(click2 == false){   //disable wireframe mode
        m_fruits.enable_textures = false;
        init();
    }
    
    if (ImGui::InputInt("Mesh divisions", &m_fruits.devisions)) {}
    ImGui::TextWrapped("To see the change in mesh resolution, disable the textures in order to see the change in resolution real time");
    ImGui::Spacing();
    ImGui::TextWrapped("Click and drag to rotate around, along with scroll to zoom in");
    ImGui::End();
}
void Application::DrawPlane(){
    cgra::Matrix<double> vertices(18, 3);
    cgra::Matrix<unsigned int> triangles(18, 3);
    vertices.setRow(0, {-5.0, -1.0, -5.0});
    vertices.setRow(1, {-5.0, -1.0, 5.0});
    vertices.setRow(2, {5.0, -1.0, 5.0});
    vertices.setRow(3, {5.0, -1.0, -5.0});
    vertices.setRow(4, {-5.0, -1.0, -5.0});
    vertices.setRow(5, {5.0, -1.0, 5.0});
    triangles.setRow(0, { 0, 1, 2});
    triangles.setRow(1, { 3, 4, 5});

    m_mesh.setData(vertices, triangles);
}

//---------------------------------------------------------------Input Handlers--------------------------------------------------------------------//
void Application::onMouseButton(int button, int action, int) {
    if (button >=0 && button < 3) {
        // Set the 'down' state for the appropriate mouse button
        m_mouseButtonDown[button] = action == GLFW_PRESS;
    }
}
void Application::loadObj(const char *filename) {
    cgra::Wavefront obj;
    // Wrap the loading in a try..catch block
    try {
        obj = cgra::Wavefront::load(filename);
    } catch (std::exception e) {
        std::cerr << "Couldn't load file: '" << filename << "' " << e.what() << std::endl;
        return;
    }
    
    /************************************************************
     * 2. Create a Mesh                                         *
     *                                                          *
     * Use the data in `obj` to create appropriately-sized      *
     * vertex and index matrices and fill them with data.       *
     *                                                          *
     * Assume that all the faces in the file are triangles.     *
     ************************************************************/
    
    // Replace these with appropriate values
    //100000 works too
    unsigned int numVertices  = obj.m_positions.size();
    unsigned int numTriangles = obj.m_faces.size();
    
    cgra::Matrix<double> vertices(numVertices, 3);
    cgra::Matrix<unsigned int> triangles(numTriangles, 3);
    
    for (size_t i = 0; i < obj.m_positions.size(); i++) {
        // Add each position to the vertices matrix
        std::cout << "vertices" << i << std::endl;
        vertices.setRow(i,{obj.m_positions[i][0],obj.m_positions[i][1],obj.m_positions[i][2]});
    }
    
    for (size_t i = 0; i < obj.m_faces.size(); i++) {
        // Add each triangle's indices to the triangles matrix
        // Remember that Wavefront files use indices that start at 1
        std::vector<cgra::Wavefront::Vertex> m_vertices = obj.m_faces[i].m_vertices;
        triangles.setRow(i,{m_vertices[0].m_p-1,m_vertices[1].m_p - 1,m_vertices[2].m_p - 1});
    }
    
    m_mesh.setData(vertices, triangles);
}
void Application::onCursorPos(double xpos, double ypos) {
    
    int last_mx = 0, last_my = 0, cur_mx = xpos, cur_my = ypos;
    // Make a vec2 with the current mouse position
    glm::vec2 currentMousePosition(xpos, ypos);
    // Get the difference from the previous mouse position
    glm::vec2 mousePositionDelta = currentMousePosition - m_mousePosition;
    
    if (m_mouseButtonDown[GLFW_MOUSE_BUTTON_LEFT]) {
        rotation = glm::vec3(rotation.x + mousePositionDelta.x,rotation.y + mousePositionDelta.y, rotation.z);
        m_rotationMatrix = glm::mat3x3(
                                       rotation.y,0.0,0.0,
                                       0.0,rotation.x ,0.0,
                                       0.0,0.0,rotation.z
                                       );
    } else if (m_mouseButtonDown[GLFW_MOUSE_BUTTON_MIDDLE]) {
        if(mousePositionDelta.x < 0){       //trans left
            xCHNG = xCHNG - mousePositionDelta.x/100;
            translation.x = translation.x + xCHNG;
            m_translation = glm::vec3(translation.x,translation.y,translation.z);
        }
        else if(mousePositionDelta.x > 0){  //trans right
            xCHNG = xCHNG - (mousePositionDelta.x/100);
            translation.x = translation.x - xCHNG;
            m_translation = glm::vec3(translation.x,translation.y,translation.z);
        }
        else if(mousePositionDelta.y > 0){  //trans up
            yCHNG = yCHNG - (mousePositionDelta.y/100);
            translation.y = translation.y + xCHNG;
            m_translation = glm::vec3(translation.x,translation.y,translation.z);
        }
        else if(mousePositionDelta.y < 0){  //trans down
            yCHNG = yCHNG - mousePositionDelta.y/100;
            translation.y = translation.y - xCHNG;
            m_translation = glm::vec3(translation.x,translation.y,translation.z);
        }
    } else if (m_mouseButtonDown[GLFW_MOUSE_BUTTON_RIGHT]) {
        //default 0, then at the mouse difference to the scale vector, or minus
        if(mousePositionDelta.y < 0){       //scale up
            scaler = scaler-mousePositionDelta.y/10;
            m_scale=(scaler);
        }
        else if(mousePositionDelta.y > 0){  //scale down
            scaler = scaler-(mousePositionDelta.y/10);
            m_scale=(scaler);
        }
        else if(mousePositionDelta.x > 0){  //scale up
            scaler = scaler + (mousePositionDelta.x/10);
            m_scale=(scaler);
        }
        else if(mousePositionDelta.x < 0){  //scale down
            //std::cout<<"left"<<"\n";
            scaler = scaler+ mousePositionDelta.x/10;
            m_scale=(scaler);
        }
        
    }
    // Update the mouse position to the current one
    m_mousePosition = currentMousePosition;
}
glm::mat4 Application::getRotation(glm::vec2 s, glm::vec2 p0, glm::vec2 p1, glm::mat4 m_rotationMatrix) {
    //Convert p0 and p1 from "normal" 2d screen space, into "arcball' space, still in 2d for now.
    glm::vec2 halfSize = s / 2.0f;    //Reuse this value for a slight increase in effeciency
    glm::vec2 p0Arc = (p0 - (halfSize)) / (halfSize);
    glm::vec2 p1Arc = (p1 - (halfSize)) / (halfSize);
    
    //Begin moving the co-ords to 3d
    glm::vec3 v0;
    glm::vec3 v1 = glm::vec3(p1.x, p1.y, 0);
    //Check that the lengths of each point are actually on the arcball
    float length = glm::length(p0Arc);
    float z = 0;
    if (length > 1) {    //The vector is too long, normalise it and put it on the edge of the arcball
        v0 = glm::vec3(p0Arc.x / length, p0Arc.y / length, 0);    //TODO check this length function is right
    }
    else {    //The vector is viable, caculate it's Z co-ordinate, instead of defaulting to 0 as above
        z = std::sqrt(1 - (p0Arc.x * p0Arc.x) + (p0Arc.y * p0Arc.y));    //TODO I could be wrong about the brackets here
        v0 = glm::vec3(p0Arc.x, p0Arc.y, z);
    }
    std::cout << "Is z a number: " << z << " -- ";
    //Now do the same for p1Arc
    length = glm::length(p1Arc);
    z = 0;
    if (length > 1) {    //The vector is too long, normalise it and put it on the edge of the arcball
        v1 = glm::vec3(p1Arc.x / length, p1Arc.y / length, 0);
    }
    else {    //The vector is viable, caculate it's Z co-ordinate, instead of defaulting to 0 as above
        z = std::sqrt(1 - (p1Arc.x * p1Arc.x) + (p1Arc.y * p0Arc.y));
        v1 = glm::vec3(p1Arc.x, p1Arc.y, z);
    }
    std::cout << "Is z a number mk2: " << z << " -- ";
    //Now to work out the rotation matrix
    //Start by using the dot product of our two new 3d vectors to get the angle of rotation
    float angle = (std::pow(glm::cos(glm::dot(v0, v1)), -1));    //Note that the rotation will be in radians
    
    //Now work out which axis the rotation is acting on. Do this using the cross product
    glm::vec3 axis = glm::cross(v0, v1);
    //To ensure that parrallel vectors do not break out code, we check that the cross product is greater than 0 before continuing
    if (glm::length(axis) <= 0) { return m_rotationMatrix; }
    
    angle = angle / 10;
    //Finally, create the rotation matrix
    std::cout << "angle: " << glm::degrees(angle) << ", axis length: " << glm::length(axis) << std::endl;
    return glm::rotate(m_rotationMatrix, angle, axis);
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
