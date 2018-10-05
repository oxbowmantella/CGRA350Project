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
glm::vec2 P0 (0.0,0.0);
glm::vec2 P1 (0.0,1.0);
glm::vec2 P2 (1.0,1.0);
glm::vec2 P3 (1.0,0.0);
float t = 0.0;
static float screendist = 7;

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
    for (double phi = 0; phi < 2*PI; phi +=PI*2/devisions) {
        for(double theta = 0; theta < PI; theta+=PI*2/devisions){
            
            if(t < 1){
                t = t+0.01;
            }else{
                t = 0;
            }
            //std::cout << "we here" << std::endl;
            glm::vec3 point;
            point.x = r * cos(phi*2) * sin(theta * 0.8) + center.x;
            point.y = r * sin(phi*2) * sin(theta) + center.y;
            point.z =                cos(theta) + center.z;
            spherePoints.push_back(point);
            m_SubDiv++;
            //std::cout <<t<< std::endl;
            //t = t+0.01;
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
}
