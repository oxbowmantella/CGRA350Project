#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>
//#include <string>

#include "opengl.hpp"
#include "imgui.h"

#include "cgra/matrix.hpp"
#include "cgra/wavefront.hpp"

#include "ex1.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"

static float scaler = 1;    //object scaler
static float xCHNG = 1; //change in mouseX
static float yCHNG = 1; //change in mouseY
static glm::vec3 rotation(0,0,0);
static glm::vec3 translation(0,0,0);

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
    
    // Create the cube mesh
    createCube();
    
}

void Application::createCube() {
    /************************************************************
     * 2. Create a Mesh                                         *
     *                                                          *
     * Add the remaining triangles for the cube                 *
     ************************************************************/

    // Use the correct number of rows for the full
    // cube.
    cgra::Matrix<double> vertices(36, 3);
    cgra::Matrix<unsigned int> triangles(12, 3);
    
    //first half of triangle
    vertices.setRow(0, {  1.0,  1.0,  1.0 });
    vertices.setRow(1, { -1.0, -1.0,  1.0 });
    vertices.setRow(2, {  1.0, -1.0,  1.0 });

	//second half of triangle
	vertices.setRow(3, { 1.0,  1.0,  1.0 });
	vertices.setRow(4, { -1.0,  1.0,  1.0 });
	vertices.setRow(5, { -1.0, -1.0,  1.0 });
    
    //right side triangle top
    vertices.setRow(6, {1.0, -1.0, 1.0});
    vertices.setRow(7, {1.0, 1.0, -1.0});
    vertices.setRow(8, {1.0, 1.0, 1.0});
    
    //right side triangle bottem
    vertices.setRow(9, {1.0, -1.0, 1.0});
    vertices.setRow(10, {1.0, -1.0, -1.0});
    vertices.setRow(11, {1.0, 1.0, -1.0});
    
    //left side triangle top
    vertices.setRow(12, {-1.0, -1.0, 1.0});
    vertices.setRow(13, {-1.0, 1.0, 1.0});
    vertices.setRow(14, {-1.0, 1.0, -1.0});
    
    //left side triangle bottem
    vertices.setRow(15, {-1.0, 1.0, -1.0});
    vertices.setRow(16, {-1.0, -1.0, -1.0});
    vertices.setRow(17, {-1.0, -1.0, 1.0});
  
    //back side triangle top
    vertices.setRow(18, {-1.0,-1.0,-1.0});
    vertices.setRow(19, {-1.0, 1.0,-1.0});
    vertices.setRow(20, { 1.0, 1.0,-1.0});
    
    //back side triangle bottem
    vertices.setRow(21, { 1.0, 1.0,-1.0});
    vertices.setRow(22, { 1.0,-1.0,-1.0});
    vertices.setRow(23, { -1.0,-1.0,-1.0});
    
    //top side triangle front
    vertices.setRow(24, {1.0, 1.0, 1.0});
    vertices.setRow(25, {1.0, 1.0, -1.0});
    vertices.setRow(26, {-1.0, 1.0, 1.0});
    
    //top side triangle back
    vertices.setRow(27, {1.0, 1.0, -1.0});
    vertices.setRow(28, {-1.0, 1.0, -1.0});
    vertices.setRow(29, {-1.0, 1.0, 1.0});
    
    //bottem side triangle front
    vertices.setRow(30, {1.0, -1.0, 1.0});
    vertices.setRow(31, {-1.0, -1.0, 1.0});
    vertices.setRow(32, {-1.0, -1.0, -1.0});
    
    //bottem side triangle back
    vertices.setRow(33, {1.0, -1.0, 1.0});
    vertices.setRow(34, {-1.0, -1.0, -1.0});
    vertices.setRow(35, {1.0, -1.0, -1.0});
    
    // Remember to make sure that the order of the vertices
    // is counter-clockwise when looking at the front of the
    // triangle.
    triangles.setRow(0, { 0, 1, 2});
    triangles.setRow(1, { 3, 4, 5});
    triangles.setRow(2, { 6, 7, 8});
    triangles.setRow(3, { 9, 10, 11});
    triangles.setRow(4, { 12, 13, 14});
    triangles.setRow(5, { 15, 16, 17});
    triangles.setRow(6, { 18, 19, 20});
    triangles.setRow(7, { 21, 22, 23});
    triangles.setRow(8, { 24, 25, 26});
    triangles.setRow(9, { 27, 28, 29});
    triangles.setRow(10, { 30, 31, 32});
    triangles.setRow(11, { 33, 34, 35});
    m_mesh.setData(vertices, triangles);
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

void Application::drawScene() {
    // Calculate the aspect ratio of the viewport;
    // width / height
    float aspectRatio = m_viewportSize.x / m_viewportSize.y;
    // Calculate the projection matrix with a field-of-view of 45 degrees
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);

    // Set the projection matrix
    m_program.setProjectionMatrix(projectionMatrix);

    glm::mat4 modelTransform(1.0f);
    
    
    modelTransform = glm::translate(modelTransform, m_translation);
    modelTransform = glm::scale(modelTransform, glm::vec3(m_scale));

    /************************************************************
     * 3. Manual Transforms                                     *
     *                                                          *
     * Use `m_translation`, `m_scale`, and `m_rotationMatrix`   *
     * to create the  `modelTransform` matrix.                  *
     * The following glm functions will be useful:              *
     *    `glm::translate`                                      *
     *    `glm::scale`                                          *
     ************************************************************/
    const float PI = 3.14159;
    modelTransform = glm::rotate(modelTransform, m_rotationMatrix[0][0] * PI / 180, {1, 0 ,0});
    modelTransform = glm::rotate(modelTransform, m_rotationMatrix[1][1] * PI / 180, {0, 1 ,0});
    modelTransform = glm::rotate(modelTransform, m_rotationMatrix[2][2] * PI / 180, {0, 0 ,1});
    m_program.setModelMatrix(modelTransform);
    
    // Draw the mesh
    m_mesh.draw();
}

void Application::doGUI() {
    ImGui::SetNextWindowSize(ImVec2(250, 250), ImGuiSetCond_FirstUseEver);
    ImGui::Begin("Shapes");

    /************************************************************
     *                                                          *
     * 2. Load an .obj file                                     *
     *                                                          *
     * Add an input for a filename.                             *
     *                                                          *
     ************************************************************
     *                                                          *
     * 3. Manual Transforms                                     *
     *                                                          *
     * Create inputs for controlling translation, scale and     *
     * rotation.                                                *
     *                                                          *
     ************************************************************
     *                                                          *
     * 5. Add a checkbox for rendering the object in wireframe  *
     *  mode.                                                   *
     ************************************************************/

    // Example for rotation, use glm to create a a rotation
    // matrix from this vector
    //static char data[128];
    static bool click = false;
    static char buf[255];

    if (ImGui::InputFloat3("Rotation", &rotation[0])) {
        // This block is executed if the input changes
        //glm::mat4 rotate = glm::eulerAngleXYZ(rotation.x, rotation.y, rotation.z);
        m_rotationMatrix = glm::mat3x3(
                                       rotation.x,0.0,0.0,
                                       0.0,rotation.y,0.0,
                                       0.0,0.0,rotation.z
                                       );
    }
    if (ImGui::InputFloat3("Translation", &translation[0])) {
        m_translation = glm::vec3(translation.x,translation.y,translation.z);
    }
    if (ImGui::InputFloat("Scale", &scaler)){
        //std::cout << scaler << "\n";
        m_scale = (scaler);
        
    }
    
    if (ImGui::Checkbox("Draw Wireframe", &click)){
        //std::cout << click <<"\n";
            m_mesh.setDrawWireframe(&click);
    }else if(click == false){   //disable wireframe mode
        m_mesh.setDrawWireframe(false);
    }
    
    if(ImGui::InputText(".obj File", buf, 255));

    if(ImGui::Button("Load File")){
        std::cout<< buf << "\n";
        //object load outs
        // /Users/siddharthmistry/Desktop/cgra251/a1/work/res/models/dragon.obj
        // /Users/siddharthmistry/Desktop/cgra251/a1/work/res/models/sphere.obj
        // /Users/siddharthmistry/Desktop/cgra251/a1/work/res/models/bunng.obj
        loadObj(buf);
    }
    if(ImGui::Button("Create Cude")){
        createCube();
    }
    
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
    /**********************************************************
     * 4. Interactive Transforms                              *
     *                                                        *
     * Change `translation`, `scale` and `rotation` based on  *
     * `mousePositionDelta`.                                  *
     **********************************************************/
    
    int last_mx = 0, last_my = 0, cur_mx = xpos, cur_my = ypos;
    // Make a vec2 with the current mouse position
    glm::vec2 currentMousePosition(xpos, ypos);
    // Get the difference from the previous mouse position
    glm::vec2 mousePositionDelta = currentMousePosition - m_mousePosition;
    
    if (m_mouseButtonDown[GLFW_MOUSE_BUTTON_LEFT]) {
		m_rotationMatrix = getRotation(m_viewportSize, m_mousePosition, currentMousePosition, m_rotationMatrix);
         
    } else if (m_mouseButtonDown[GLFW_MOUSE_BUTTON_MIDDLE]) {
        if(mousePositionDelta.x < 0){       //trans left
            //std::cout<<"left"<<"\n";
            xCHNG = xCHNG - mousePositionDelta.x/100;
            translation.x = translation.x + xCHNG;
            m_translation = glm::vec3(translation.x,translation.y,translation.z);
        }
        else if(mousePositionDelta.x > 0){  //trans right
            //std::cout<<"right"<<"\n";
            xCHNG = xCHNG - (mousePositionDelta.x/100);
            translation.x = translation.x - xCHNG;
            m_translation = glm::vec3(translation.x,translation.y,translation.z);
        }
        else if(mousePositionDelta.y > 0){  //trans up
            //std::cout<<"up"<<"\n";
            yCHNG = yCHNG - (mousePositionDelta.y/100);
            translation.y = translation.y + xCHNG;
            m_translation = glm::vec3(translation.x,translation.y,translation.z);
        }
        else if(mousePositionDelta.y < 0){  //trans down
            //std::cout<<"down"<<"\n";
            yCHNG = yCHNG - mousePositionDelta.y/100;
            translation.y = translation.y - xCHNG;
            m_translation = glm::vec3(translation.x,translation.y,translation.z);
        }
    } else if (m_mouseButtonDown[GLFW_MOUSE_BUTTON_RIGHT]) {
        //default 0, then at the mouse difference to the scale vector, or minus
        if(mousePositionDelta.y < 0){       //scale up
            //std::cout<<"up"<<"\n";
            scaler = scaler-mousePositionDelta.y/10;
            m_scale=(scaler);
        }
        else if(mousePositionDelta.y > 0){  //scale down
            //std::cout<<"down"<<"\n";
            scaler = scaler-(mousePositionDelta.y/10);
            m_scale=(scaler);
        }
        else if(mousePositionDelta.x > 0){  //scale up
            //std::cout<<"right"<<"\n";
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
		glm::vec2 halfSize = s / 2.0f;	//Reuse this value for a slight increase in effeciency
		glm::vec2 p0Arc = (p0 - (halfSize)) / (halfSize);
		glm::vec2 p1Arc = (p1 - (halfSize)) / (halfSize);

		//Begin moving the co-ords to 3d
		glm::vec3 v0;
		glm::vec3 v1 = glm::vec3(p1.x, p1.y, 0);
		//Check that the lengths of each point are actually on the arcball
		float length = glm::length(p0Arc);
		float z = 0;
		if (length > 1) {	//The vector is too long, normalise it and put it on the edge of the arcball
			v0 = glm::vec3(p0Arc.x / length, p0Arc.y / length, 0);	//TODO check this length function is right
		}
		else {	//The vector is viable, caculate it's Z co-ordinate, instead of defaulting to 0 as above
			z = std::sqrt(1 - (p0Arc.x * p0Arc.x) + (p0Arc.y * p0Arc.y));	//TODO I could be wrong about the brackets here
			v0 = glm::vec3(p0Arc.x, p0Arc.y, z);
		}
		std::cout << "Is z a number: " << z << " -- ";
		//Now do the same for p1Arc
		length = glm::length(p1Arc);
		z = 0;
		if (length > 1) {	//The vector is too long, normalise it and put it on the edge of the arcball
			v1 = glm::vec3(p1Arc.x / length, p1Arc.y / length, 0);
		}
		else {	//The vector is viable, caculate it's Z co-ordinate, instead of defaulting to 0 as above
			z = std::sqrt(1 - (p1Arc.x * p1Arc.x) + (p1Arc.y * p0Arc.y));
			v1 = glm::vec3(p1Arc.x, p1Arc.y, z);
		}
		std::cout << "Is z a number mk2: " << z << " -- ";
		//Now to work out the rotation matrix
		//Start by using the dot product of our two new 3d vectors to get the angle of rotation
		float angle = (std::pow(glm::cos(glm::dot(v0, v1)), -1));	//Note that the rotation will be in radians

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
