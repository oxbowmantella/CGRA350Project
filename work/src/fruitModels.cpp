#pragma once
#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>

#include "opengl.hpp"
#include "imgui.h"

#include "cgra/matrix.hpp"
#include "cgra/wavefront.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "fruitModels.hpp"
//test parameters
double a = 1;
double b = 5/2;

const double PI=3.141592653589793238462643383279502884197;
static int devisions = 28;
static int cubeDevisions = 2;
static int r = 2;
//------------------------------------------Fruit Bowl------------------------------------------//
void fruitModels::drawBowl(){m_bowl.draw();}
void fruitModels::Bowl() {
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
            point.x = r * cos(phi*2) * sin(theta * 0.8) + center.x;
            point.y = r * sin(phi*2) * sin(theta) + center.y;
            point.z = r            * sin(theta) + center.z;
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
    m_bowl.setData(vertices, triangles);
}
//------------------------------------------StrawBerry------------------------------------------//
void fruitModels::drawStrawberry(){m_strawberry.draw();}
void fruitModels::Strawberry() {
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
            point.x = r * cos(phi*2) * sin(theta * 0.8) + center.x;
            point.y = r * sin(phi*2) * sin(theta * 0.6) + center.y;
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
    m_strawberry.setData(vertices, triangles);
}
//------------------------------------------Tomato------------------------------------------//
void fruitModels::drawTomato(){m_tomato.draw();}
void fruitModels::Tomato() {
    int size_vert = devisions*(devisions+1);
    cgra::Matrix<double> vertices(size_vert*3, 3);
    cgra::Matrix<unsigned int> triangles(size_vert, 3);
    int m_SubDiv = 0;
    glm::vec3 center(0,0,0);
    int j = 0;
    unsigned int numOfRows = 0;
    std::vector<glm::vec3>spherePoints;
    spherePoints.clear();
    for (double phi = 0; phi < PI *2; phi +=PI*2/devisions) {
        for(double theta = 0; theta < PI; theta+=PI*2/devisions){
            //std::cout << "we here" << std::endl;
            glm::vec3 point;
            point.x = r * cos(phi*2) * sin(theta * 0.89) + center.x;
            point.y = r * sin(phi*2) * sin(theta) + center.y;
            point.z = r            * cos(theta)/1.2 + center.z;
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
    
    m_tomato.setData(vertices, triangles);
    
    createTopper(center.x,center.y,center.z - 0.4 , 0,-90,90);
    drawTopper();
}

//------------------------------------------Topper------------------------------------------//
void fruitModels::drawTopper(){m_topper.draw();}
void fruitModels::createTopper(double x, double y, double z,float ROTx, float ROTy, float ROTz){
    glm::mat4 modelTransform(1.0f);

    modelTransform = glm::rotate(modelTransform, glm::radians(ROTx), {1, 0 ,0});
    modelTransform = glm::rotate(modelTransform, glm::radians(ROTy), {0, 1 ,0});
    modelTransform = glm::rotate(modelTransform, glm::radians(ROTz), {0, 0 ,1});
    
    static char filename[255] = CGRA_SRCDIR "/res/models/topper.obj";
    cgra::Wavefront cylinderObj;
    try {
        cylinderObj = cgra::Wavefront::load(filename);
    } catch (std::exception e) {
        std::cerr << "Couldn't load file: '" << filename << "' " << e.what() << std::endl;
        return;
    }
    unsigned int numVertices  = cylinderObj.m_positions.size();
    unsigned int numTriangles = cylinderObj.m_faces.size();
    
    cgra::Matrix<double> vertices(numVertices, 3);
    cgra::Matrix<unsigned int> triangles(numTriangles, 3);
    glm::vec3 vmax(cylinderObj.m_positions[0][0],cylinderObj.m_positions[0][1],cylinderObj.m_positions[0][2]);
    glm::vec3 vmin(cylinderObj.m_positions[0][0],cylinderObj.m_positions[0][1],cylinderObj.m_positions[0][2]);
    
    for (size_t i = 0; i < cylinderObj.m_positions.size(); i++) {
        // Add each position to the vertices matrix
        //std::cout << "vertices" << i << std::endl;
        glm::mat4 model = modelTransform;
        glm::mat4 mvp = glm::mat4(1.0f)* model;
        glm::vec4 vertex(cylinderObj.m_positions[i][0],cylinderObj.m_positions[i][1],cylinderObj.m_positions[i][2], 1.0f);
        vertex = mvp * vertex;
        vertices.setRow(i,{vertex[0]+x,vertex[1]+y,vertex[2]+z});
        glm::vec3 v(cylinderObj.m_positions[i][0],cylinderObj.m_positions[i][1],cylinderObj.m_positions[i][2]);
        vmax = glm::max(vmax, v);
        vmin = glm::min(vmin, v);
    }
    for (size_t i = 0; i < cylinderObj.m_faces.size(); i++) {
        std::vector<cgra::Wavefront::Vertex> m_vertices = cylinderObj.m_faces[i].m_vertices;
        triangles.setRow(i,{m_vertices[0].m_p-1,m_vertices[1].m_p - 1,m_vertices[2].m_p - 1});
    }
    m_topper.setData(vertices, triangles);

}
