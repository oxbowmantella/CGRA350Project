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

#include "cgra/stb_image.h"
#include "ex1.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"
//test parameter
double a = 1;
double b = 5/2;
//--------------
const double PI=3.141592653589793238462643383279502884197;
static int devisions = 28;
static int r = 2;

//------------------------------------------Fruit Bowl------------------------------------------//
void fruitModels::drawBowl(){m_bowl.draw();}
void fruitModels::Bowl(float InTranX, float InTranY, float InTranZ, float InRotX, float InRotY, float InRotZ) {
    int size_vert = devisions*(devisions+1);
    cgra::Matrix<double> vertices(size_vert*3, 3);
    cgra::Matrix<unsigned int> triangles(size_vert, 3);
    int m_SubDiv = 0;
    glm::vec3 center(0,0,0);
    
    glm::mat4 modelTransform(1.0f);
    modelTransform = glm::scale(modelTransform, glm::vec3(bowl_scaler));
    modelTransform = glm::rotate(modelTransform, glm::radians(InRotX), {1, 0 ,0});
    modelTransform = glm::rotate(modelTransform, glm::radians(InRotY), {0, 1 ,0});
    modelTransform = glm::rotate(modelTransform, glm::radians(InRotZ), {0, 0 ,1});
    
    int j = 0;
    unsigned int numOfRows = 0;
    std::vector<glm::vec3>spherePoints;
    spherePoints.clear();
    for (double phi = 0; phi < 2*PI; phi +=PI*2/devisions) {
        for(double theta = 0; theta < PI; theta+=PI*2/devisions){
            glm::vec3 point;
            point.x = r * cos(phi*2) * sin(theta * 0.8) + center.x;
            point.y = r * sin(phi*2) * sin(theta) + center.y;
            point.z = r            * sin(theta) + center.z;
            spherePoints.push_back(point);
            m_SubDiv++;
        }
    }
    for (unsigned int i = 0; i < vertices.numRows()/2-6; i+=6) {
        glm::mat4 model = modelTransform;
        glm::mat4 mvp = glm::mat4(1.0f)* model;
        
        glm::vec4 vertex_1(spherePoints[j].x, spherePoints[j].y, spherePoints[j].z, 1.0f);
        vertex_1 = mvp * vertex_1;
        vertices.setRow(i, { vertex_1[0]+InTranX, vertex_1[1]+InTranY, vertex_1[2]+InTranZ});
        
        glm::vec4 vertex_2(spherePoints[j+1+devisions/2].x, spherePoints[j+1+devisions/2].y, spherePoints[j+1+devisions/2].z , 1.0f);
        vertex_2 = mvp * vertex_2;
        vertices.setRow(i+1, { vertex_2[0]+InTranX, vertex_2[1]+InTranY, vertex_2[2]+InTranZ});
        
        glm::vec4 vertex_3(spherePoints[j+devisions/2].x, spherePoints[j+devisions/2].y, spherePoints[j+devisions/2].z , 1.0f);
        vertex_3 = mvp * vertex_3;
        vertices.setRow(i+2, { vertex_3[0]+InTranX, vertex_3[1]+InTranY, vertex_3[2]+InTranZ});
        
        glm::vec4 vertex_4(spherePoints[j].x , spherePoints[j].y , spherePoints[j].z , 1.0f);
        vertex_4 = mvp * vertex_4;
        vertices.setRow(i+3, { vertex_4[0]+InTranX, vertex_4[1]+InTranY, vertex_4[2]+InTranZ});
        
        glm::vec4 vertex_5(spherePoints[j+1].x, spherePoints[j+1].y, spherePoints[j+1].z, 1.0f);
        vertex_5 = mvp * vertex_5;
        vertices.setRow(i+4, { vertex_5[0]+InTranX, vertex_5[1]+InTranY, vertex_5[2]+InTranZ});
        
        glm::vec4 vertex_6(spherePoints[j+1+devisions/2].x , spherePoints[j+1+devisions/2].y , spherePoints[j+1+devisions/2].z , 1.0f);
        vertex_6 = mvp * vertex_6;
        vertices.setRow(i+5, { vertex_6[0]+InTranX, vertex_6[1]+InTranY, vertex_6[2]+InTranZ});
        
        j++;
    }
    for(unsigned int i = 0; i< triangles.numRows()/2; i++){
        triangles.setRow(i, {numOfRows,numOfRows+1,numOfRows+2});
        numOfRows+=3;
    }
    m_bowl.setData(vertices, triangles);
}

//------------------------------------------Orange------------------------------------------//
void fruitModels::drawOrange(){m_orange.draw();}
void fruitModels::Orange(float InTranX, float InTranY, float InTranZ, float InRotX, float InRotY, float InRotZ) {
    int size_vert = devisions*(devisions+1);
    cgra::Matrix<double> vertices(size_vert*3, 3);
    cgra::Matrix<unsigned int> triangles(size_vert, 3);
    int m_SubDiv = 0;
    glm::vec3 center(0,0,0);
    
    glm::mat4 modelTransform(1.0f);
    modelTransform = glm::scale(modelTransform, glm::vec3(orange_scaler));
    modelTransform = glm::rotate(modelTransform, glm::radians(InRotX), {1, 0 ,0});
    modelTransform = glm::rotate(modelTransform, glm::radians(InRotY), {0, 1 ,0});
    modelTransform = glm::rotate(modelTransform, glm::radians(InRotZ), {0, 0 ,1});
    
    int j = 0;
    unsigned int numOfRows = 0;
    std::vector<glm::vec3>spherePoints;
    spherePoints.clear();
    for (double phi = 0; phi < 2*PI; phi +=PI*2/devisions) {
        for(double theta = 0; theta < PI; theta+=PI*2/devisions){
            glm::vec3 point;
            point.x = r * cos(phi*2) * sin(theta) + center.x;
            point.y = r * sin(phi*2) * sin(theta) + center.y;
            point.z = r            * cos(theta) + center.z;
            spherePoints.push_back(point);
            m_SubDiv++;
        }
    }
    
    for (unsigned int i = 0; i < vertices.numRows()/2-6; i+=6) {
        glm::mat4 model = modelTransform;
        glm::mat4 mvp = glm::mat4(1.0f)* model;
        
        glm::vec4 vertex_1(spherePoints[j].x, spherePoints[j].y, spherePoints[j].z, 1.0f);
        vertex_1 = mvp * vertex_1;
        vertices.setRow(i, { vertex_1[0]+InTranX, vertex_1[1]+InTranY, vertex_1[2]+InTranZ});
        
        glm::vec4 vertex_2(spherePoints[j+1+devisions/2].x, spherePoints[j+1+devisions/2].y, spherePoints[j+1+devisions/2].z , 1.0f);
        vertex_2 = mvp * vertex_2;
        vertices.setRow(i+1, { vertex_2[0]+InTranX, vertex_2[1]+InTranY, vertex_2[2]+InTranZ});
        
        glm::vec4 vertex_3(spherePoints[j+devisions/2].x, spherePoints[j+devisions/2].y, spherePoints[j+devisions/2].z , 1.0f);
        vertex_3 = mvp * vertex_3;
        vertices.setRow(i+2, { vertex_3[0]+InTranX, vertex_3[1]+InTranY, vertex_3[2]+InTranZ});
        
        glm::vec4 vertex_4(spherePoints[j].x , spherePoints[j].y , spherePoints[j].z , 1.0f);
        vertex_4 = mvp * vertex_4;
        vertices.setRow(i+3, { vertex_4[0]+InTranX, vertex_4[1]+InTranY, vertex_4[2]+InTranZ});
        
        glm::vec4 vertex_5(spherePoints[j+1].x, spherePoints[j+1].y, spherePoints[j+1].z, 1.0f);
        vertex_5 = mvp * vertex_5;
        vertices.setRow(i+4, { vertex_5[0]+InTranX, vertex_5[1]+InTranY, vertex_5[2]+InTranZ});
        
        glm::vec4 vertex_6(spherePoints[j+1+devisions/2].x , spherePoints[j+1+devisions/2].y , spherePoints[j+1+devisions/2].z , 1.0f);
        vertex_6 = mvp * vertex_6;
        vertices.setRow(i+5, { vertex_6[0]+InTranX, vertex_6[1]+InTranY, vertex_6[2]+InTranZ});
        
        j++;
    }
    for(unsigned int i = 0; i< triangles.numRows()/2; i++){
        triangles.setRow(i, {numOfRows,numOfRows+1,numOfRows+2});
        numOfRows+=3;
    }
    m_orange.setData(vertices, triangles);
    specifyTexture1();
    createOrangeTopper(center.x+InTranX,center.y+InTranY,center.z+InTranZ, InRotX+90, InRotY+270,InRotX+90);
    drawOrangeTopper();
    
}

//------------------------------------------Topper(Orange)------------------------------------------//
void fruitModels::drawOrangeTopper(){m_orangeTopper.draw();}
void fruitModels::createOrangeTopper(double x, double y, double z,float ROTx, float ROTy, float ROTz){
    glm::mat4 modelTransform(1.0f);
    
    modelTransform = glm::scale(modelTransform, glm::vec3(orange_scaler));
    modelTransform = glm::rotate(modelTransform, glm::radians(ROTx), {1, 0 ,0});
    modelTransform = glm::rotate(modelTransform, glm::radians(ROTy), {0, 1 ,0});
    modelTransform = glm::rotate(modelTransform, glm::radians(ROTz), {0, 0 ,1});
    
    static char filename[255] = CGRA_SRCDIR "/res/models/OrangeTopper.obj";
    cgra::Wavefront orangeObj;
    try {
        orangeObj = cgra::Wavefront::load(filename);
    } catch (std::exception e) {
        std::cerr << "Couldn't load file: '" << filename << "' " << e.what() << std::endl;
        return;
    }
    unsigned int numVertices  = orangeObj.m_positions.size();
    unsigned int numTriangles = orangeObj.m_faces.size();
    
    cgra::Matrix<double> vertices(numVertices, 3);
    cgra::Matrix<unsigned int> triangles(numTriangles, 3);
    glm::vec3 vmax(orangeObj.m_positions[0][0],orangeObj.m_positions[0][1],orangeObj.m_positions[0][2]);
    glm::vec3 vmin(orangeObj.m_positions[0][0],orangeObj.m_positions[0][1],orangeObj.m_positions[0][2]);
    
    for (size_t i = 0; i < orangeObj.m_positions.size(); i++) {
        
        glm::mat4 model = modelTransform;
        glm::mat4 mvp = glm::mat4(1.0f)* model;
        glm::vec4 vertex(orangeObj.m_positions[i][0],orangeObj.m_positions[i][1],orangeObj.m_positions[i][2], 1.0f);
        vertex = mvp * vertex;
        vertices.setRow(i,{vertex[0]+x,vertex[1]+y,vertex[2]+z});
        glm::vec3 v(orangeObj.m_positions[i][0],orangeObj.m_positions[i][1],orangeObj.m_positions[i][2]);
        vmax = glm::max(vmax, v);
        vmin = glm::min(vmin, v);
    }
    for (size_t i = 0; i < orangeObj.m_faces.size(); i++) {
        std::vector<cgra::Wavefront::Vertex> m_vertices = orangeObj.m_faces[i].m_vertices;
        triangles.setRow(i,{m_vertices[0].m_p-1,m_vertices[1].m_p - 1,m_vertices[2].m_p - 1});
    }
    m_orangeTopper.setData(vertices, triangles);
    
}

//------------------------------------------StrawBerry------------------------------------------//
void fruitModels::drawStrawberry(){m_strawberry.draw();}
void fruitModels::Strawberry(float InTranX, float InTranY, float InTranZ, float InRotX, float InRotY, float InRotZ) {
    int size_vert = devisions*(devisions+1);
    cgra::Matrix<double> vertices(size_vert*3, 3);
    cgra::Matrix<unsigned int> triangles(size_vert, 3);
    int m_SubDiv = 0;
    glm::vec3 center(0,0,0);
    
    glm::mat4 modelTransform(1.0f);
    
    modelTransform = glm::scale(modelTransform, glm::vec3(strawberry_scaler));
    modelTransform = glm::rotate(modelTransform, glm::radians(InRotX), {1, 0 ,0});
    modelTransform = glm::rotate(modelTransform, glm::radians(InRotY), {0, 1 ,0});
    modelTransform = glm::rotate(modelTransform, glm::radians(InRotZ), {0, 0 ,1});
    
    int j = 0;
    unsigned int numOfRows = 0;
    std::vector<glm::vec3>spherePoints;
    spherePoints.clear();
    for (double phi = 0; phi < 2*PI; phi +=PI*2/devisions) {
        for(double theta = 0; theta < PI; theta+=PI*2/devisions){
            glm::vec3 point;
            point.x = r * cos(phi*2) * sin(theta * 0.8) + center.x;
            point.y = r * sin(phi*2) * sin(theta * 0.6) + center.y;
            point.z = r            * cos(theta) + center.z;
            spherePoints.push_back(point);
            m_SubDiv++;
        }
    }
    for (unsigned int i = 0; i < vertices.numRows()/2-6; i+=6) {
        glm::mat4 model = modelTransform;
        glm::mat4 mvp = glm::mat4(1.0f)* model;
        
        glm::vec4 vertex_1(spherePoints[j].x, spherePoints[j].y, spherePoints[j].z, 1.0f);
        vertex_1 = mvp * vertex_1;
        vertices.setRow(i, { vertex_1[0]+InTranX, vertex_1[1]+InTranY, vertex_1[2]+InTranZ});
        
        glm::vec4 vertex_2(spherePoints[j+1+devisions/2].x, spherePoints[j+1+devisions/2].y, spherePoints[j+1+devisions/2].z , 1.0f);
        vertex_2 = mvp * vertex_2;
        vertices.setRow(i+1, { vertex_2[0]+InTranX, vertex_2[1]+InTranY, vertex_2[2]+InTranZ});
        
        glm::vec4 vertex_3(spherePoints[j+devisions/2].x, spherePoints[j+devisions/2].y, spherePoints[j+devisions/2].z , 1.0f);
        vertex_3 = mvp * vertex_3;
        vertices.setRow(i+2, { vertex_3[0]+InTranX, vertex_3[1]+InTranY, vertex_3[2]+InTranZ});
        
        glm::vec4 vertex_4(spherePoints[j].x , spherePoints[j].y , spherePoints[j].z , 1.0f);
        vertex_4 = mvp * vertex_4;
        vertices.setRow(i+3, { vertex_4[0]+InTranX, vertex_4[1]+InTranY, vertex_4[2]+InTranZ});
        
        glm::vec4 vertex_5(spherePoints[j+1].x, spherePoints[j+1].y, spherePoints[j+1].z, 1.0f);
        vertex_5 = mvp * vertex_5;
        vertices.setRow(i+4, { vertex_5[0]+InTranX, vertex_5[1]+InTranY, vertex_5[2]+InTranZ});
        
        glm::vec4 vertex_6(spherePoints[j+1+devisions/2].x , spherePoints[j+1+devisions/2].y , spherePoints[j+1+devisions/2].z , 1.0f);
        vertex_6 = mvp * vertex_6;
        vertices.setRow(i+5, { vertex_6[0]+InTranX, vertex_6[1]+InTranY, vertex_6[2]+InTranZ});
        
        j++;
    }
    for(unsigned int i = 0; i< triangles.numRows()/2; i++){
        triangles.setRow(i, {numOfRows,numOfRows+1,numOfRows+2});
        numOfRows+=3;
    }
    m_strawberry.setData(vertices, triangles);
    
    createStrawTopper(center.x+InTranX,center.y+InTranY,center.z+InTranZ, InRotX+90, InRotY+270,InRotX+90);
    drawStrawTopper();
    specifyTexture2();
}

//------------------------------------------Topper(Strawberry)------------------------------------------//
void fruitModels::drawStrawTopper(){m_StrawTopper.draw();}
void fruitModels::createStrawTopper(double x, double y, double z,float ROTx, float ROTy, float ROTz){
    glm::mat4 modelTransform(1.0f);
    
    modelTransform = glm::scale(modelTransform, glm::vec3(strawberry_scaler));
    modelTransform = glm::rotate(modelTransform, glm::radians(ROTx), {1, 0 ,0});
    modelTransform = glm::rotate(modelTransform, glm::radians(ROTy), {0, 1 ,0});
    modelTransform = glm::rotate(modelTransform, glm::radians(ROTz), {0, 0 ,1});
    
    static char filename[255] = CGRA_SRCDIR "/res/models/StrawberryTopper.obj";
    cgra::Wavefront strawberryObj;
    try {
        strawberryObj = cgra::Wavefront::load(filename);
    } catch (std::exception e) {
        std::cerr << "Couldn't load file: '" << filename << "' " << e.what() << std::endl;
        return;
    }
    unsigned int numVertices  = strawberryObj.m_positions.size();
    unsigned int numTriangles = strawberryObj.m_faces.size();
    
    cgra::Matrix<double> vertices(numVertices, 3);
    cgra::Matrix<unsigned int> triangles(numTriangles, 3);
    glm::vec3 vmax(strawberryObj.m_positions[0][0],strawberryObj.m_positions[0][1],strawberryObj.m_positions[0][2]);
    glm::vec3 vmin(strawberryObj.m_positions[0][0],strawberryObj.m_positions[0][1],strawberryObj.m_positions[0][2]);
    
    for (size_t i = 0; i < strawberryObj.m_positions.size(); i++) {
        glm::mat4 model = modelTransform;
        glm::mat4 mvp = glm::mat4(1.0f)* model;
        glm::vec4 vertex(strawberryObj.m_positions[i][0],strawberryObj.m_positions[i][1],strawberryObj.m_positions[i][2], 1.0f);
        vertex = mvp * vertex;
        vertices.setRow(i,{vertex[0]+x,vertex[1]+y,vertex[2]+z});
        glm::vec3 v(strawberryObj.m_positions[i][0],strawberryObj.m_positions[i][1],strawberryObj.m_positions[i][2]);
        vmax = glm::max(vmax, v);
        vmin = glm::min(vmin, v);
    }
    for (size_t i = 0; i < strawberryObj.m_faces.size(); i++) {
        std::vector<cgra::Wavefront::Vertex> m_vertices = strawberryObj.m_faces[i].m_vertices;
        triangles.setRow(i,{m_vertices[0].m_p-1,m_vertices[1].m_p - 1,m_vertices[2].m_p - 1});
    }
    m_StrawTopper.setData(vertices, triangles);
    
}

//------------------------------------------Tomato------------------------------------------//
void fruitModels::drawTomato(){m_tomato.draw();}
void fruitModels::Tomato(float InTranX, float InTranY, float InTranZ, float InRotX, float InRotY, float InRotZ) {
    //rotation matrix
    glm::mat4 modelTransform(1.0f);
    
    modelTransform = glm::scale(modelTransform, glm::vec3(tomato_scaler));
    modelTransform = glm::rotate(modelTransform, glm::radians(InRotX), {1, 0 ,0});
    modelTransform = glm::rotate(modelTransform, glm::radians(InRotY), {0, 1 ,0});
    modelTransform = glm::rotate(modelTransform, glm::radians(InRotZ), {0, 0 ,1});
    
    int size_vert = devisions*(devisions+1);
    cgra::Matrix<double> vertices(size_vert*3, 3);
    cgra::Matrix<unsigned int> triangles(size_vert, 3);
    int m_SubDiv = 0;
    glm::vec3 center(0,0,0);
    int j = 0;
    unsigned int numOfRows = 0;
    std::vector<glm::vec3>spherePoints;
    cgra::Wavefront tomatoObj;
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
        glm::mat4 model = modelTransform;
        glm::mat4 mvp = glm::mat4(1.0f)* model;
        
        glm::vec4 vertex_1(spherePoints[j].x, spherePoints[j].y, spherePoints[j].z, 1.0f);
        vertex_1 = mvp * vertex_1;
        vertices.setRow(i, { vertex_1[0]+InTranX, vertex_1[1]+InTranY, vertex_1[2]+InTranZ});
        
        glm::vec4 vertex_2(spherePoints[j+1+devisions/2].x, spherePoints[j+1+devisions/2].y, spherePoints[j+1+devisions/2].z , 1.0f);
        vertex_2 = mvp * vertex_2;
        vertices.setRow(i+1, { vertex_2[0]+InTranX, vertex_2[1]+InTranY, vertex_2[2]+InTranZ});
        
        glm::vec4 vertex_3(spherePoints[j+devisions/2].x, spherePoints[j+devisions/2].y, spherePoints[j+devisions/2].z , 1.0f);
        vertex_3 = mvp * vertex_3;
        vertices.setRow(i+2, { vertex_3[0]+InTranX, vertex_3[1]+InTranY, vertex_3[2]+InTranZ});
        
        glm::vec4 vertex_4(spherePoints[j].x , spherePoints[j].y , spherePoints[j].z , 1.0f);
        vertex_4 = mvp * vertex_4;
        vertices.setRow(i+3, { vertex_4[0]+InTranX, vertex_4[1]+InTranY, vertex_4[2]+InTranZ});
        
        glm::vec4 vertex_5(spherePoints[j+1].x, spherePoints[j+1].y, spherePoints[j+1].z, 1.0f);
        vertex_5 = mvp * vertex_5;
        vertices.setRow(i+4, { vertex_5[0]+InTranX, vertex_5[1]+InTranY, vertex_5[2]+InTranZ});
        
        glm::vec4 vertex_6(spherePoints[j+1+devisions/2].x , spherePoints[j+1+devisions/2].y , spherePoints[j+1+devisions/2].z , 1.0f);
        vertex_6 = mvp * vertex_6;
        vertices.setRow(i+5, { vertex_6[0]+InTranX, vertex_6[1]+InTranY, vertex_6[2]+InTranZ});
        
        j++;
    }
    for(unsigned int i = 0; i< triangles.numRows()/2; i++){
        triangles.setRow(i, {numOfRows,numOfRows+1,numOfRows+2});
        numOfRows+=3;
    }
    
    m_tomato.setData(vertices, triangles);
    
    createTomatoTopper(center.x+InTranX,center.y+InTranY,center.z+InTranZ, InRotX+90, InRotY+270,InRotX+90);
    drawTomatoTopper();
    specifyTexture3();
}

//------------------------------------------Topper(Tomato)------------------------------------------//
void fruitModels::drawTomatoTopper(){m_TomatorTopper.draw();}
void fruitModels::createTomatoTopper(double x, double y, double z,float ROTx, float ROTy, float ROTz){
    glm::mat4 modelTransform(1.0f);

    modelTransform = glm::scale(modelTransform, glm::vec3(tomato_scaler));
    modelTransform = glm::rotate(modelTransform, glm::radians(ROTx), {1, 0 ,0});
    modelTransform = glm::rotate(modelTransform, glm::radians(ROTy), {0, 1 ,0});
    modelTransform = glm::rotate(modelTransform, glm::radians(ROTz), {0, 0 ,1});
    
    static char filename[255] = CGRA_SRCDIR "/res/models/TomatoTopper.obj";
    cgra::Wavefront tomatoObj;
    try {
        tomatoObj = cgra::Wavefront::load(filename);
    } catch (std::exception e) {
        std::cerr << "Couldn't load file: '" << filename << "' " << e.what() << std::endl;
        return;
    }
    unsigned int numVertices  = tomatoObj.m_positions.size();
    unsigned int numTriangles = tomatoObj.m_faces.size();
    
    cgra::Matrix<double> vertices(numVertices, 3);
    cgra::Matrix<unsigned int> triangles(numTriangles, 3);
    glm::vec3 vmax(tomatoObj.m_positions[0][0],tomatoObj.m_positions[0][1],tomatoObj.m_positions[0][2]);
    glm::vec3 vmin(tomatoObj.m_positions[0][0],tomatoObj.m_positions[0][1],tomatoObj.m_positions[0][2]);
    
    for (size_t i = 0; i < tomatoObj.m_positions.size(); i++) {

        glm::mat4 model = modelTransform;
        glm::mat4 mvp = glm::mat4(1.0f)* model;
        glm::vec4 vertex(tomatoObj.m_positions[i][0],tomatoObj.m_positions[i][1],tomatoObj.m_positions[i][2], 1.0f);
        vertex = mvp * vertex;
        vertices.setRow(i,{vertex[0]+x,vertex[1]+y,vertex[2]+z});
        glm::vec3 v(tomatoObj.m_positions[i][0],tomatoObj.m_positions[i][1],tomatoObj.m_positions[i][2]);
        vmax = glm::max(vmax, v);
        vmin = glm::min(vmin, v);
    }
    for (size_t i = 0; i < tomatoObj.m_faces.size(); i++) {
        std::vector<cgra::Wavefront::Vertex> m_vertices = tomatoObj.m_faces[i].m_vertices;
        triangles.setRow(i,{m_vertices[0].m_p-1,m_vertices[1].m_p - 1,m_vertices[2].m_p - 1});
    }
    m_TomatorTopper.setData(vertices, triangles);

}

//------------------------------------------Apple------------------------------------------//
void fruitModels::drawApple(){m_apple.draw();}
void fruitModels::Apple(float InTranX, float InTranY, float InTranZ, float InRotX, float InRotY, float InRotZ) {
    int size_vert = devisions*(devisions+1);
    cgra::Matrix<double> vertices(size_vert*3, 3);
    cgra::Matrix<unsigned int> triangles(size_vert, 3);
    int m_SubDiv = 0;
    glm::vec3 center(0,0,0);
    
    glm::mat4 modelTransform(1.0f);
    
    modelTransform = glm::scale(modelTransform, glm::vec3(apple_scaler));
    modelTransform = glm::rotate(modelTransform, glm::radians(InRotX), {1, 0 ,0});
    modelTransform = glm::rotate(modelTransform, glm::radians(InRotY), {0, 1 ,0});
    modelTransform = glm::rotate(modelTransform, glm::radians(InRotZ), {0, 0 ,1});

    
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
            point.z = r            * cos(theta)/0.9 + center.z;
            //std::cout << "z" << point.z<< std::endl;
            spherePoints.push_back(point);
            m_SubDiv++;
            //std::cout << "we ends" << m_SubDiv<< std::endl;
        }
    }
    for (unsigned int i = 0; i < vertices.numRows()/2-6; i+=6) {
        glm::mat4 model = modelTransform;
        glm::mat4 mvp = glm::mat4(1.0f)* model;
        
        glm::vec4 vertex_1(spherePoints[j].x, spherePoints[j].y, spherePoints[j].z, 1.0f);
        vertex_1 = mvp * vertex_1;
        vertices.setRow(i, { vertex_1[0]+InTranX, vertex_1[1]+InTranY, vertex_1[2]+InTranZ});
        
        glm::vec4 vertex_2(spherePoints[j+1+devisions/2].x, spherePoints[j+1+devisions/2].y, spherePoints[j+1+devisions/2].z , 1.0f);
        vertex_2 = mvp * vertex_2;
        vertices.setRow(i+1, { vertex_2[0]+InTranX, vertex_2[1]+InTranY, vertex_2[2]+InTranZ});
        
        glm::vec4 vertex_3(spherePoints[j+devisions/2].x, spherePoints[j+devisions/2].y, spherePoints[j+devisions/2].z , 1.0f);
        vertex_3 = mvp * vertex_3;
        vertices.setRow(i+2, { vertex_3[0]+InTranX, vertex_3[1]+InTranY, vertex_3[2]+InTranZ});
        
        glm::vec4 vertex_4(spherePoints[j].x , spherePoints[j].y , spherePoints[j].z , 1.0f);
        vertex_4 = mvp * vertex_4;
        vertices.setRow(i+3, { vertex_4[0]+InTranX, vertex_4[1]+InTranY, vertex_4[2]+InTranZ});
        
        glm::vec4 vertex_5(spherePoints[j+1].x, spherePoints[j+1].y, spherePoints[j+1].z, 1.0f);
        vertex_5 = mvp * vertex_5;
        vertices.setRow(i+4, { vertex_5[0]+InTranX, vertex_5[1]+InTranY, vertex_5[2]+InTranZ});
        
        glm::vec4 vertex_6(spherePoints[j+1+devisions/2].x , spherePoints[j+1+devisions/2].y , spherePoints[j+1+devisions/2].z , 1.0f);
        vertex_6 = mvp * vertex_6;
        vertices.setRow(i+5, { vertex_6[0]+InTranX, vertex_6[1]+InTranY, vertex_6[2]+InTranZ});
        
        j++;
    }
    for(unsigned int i = 0; i< triangles.numRows()/2; i++){
        triangles.setRow(i, {numOfRows,numOfRows+1,numOfRows+2});
        numOfRows+=3;
    }
    m_apple.setData(vertices, triangles);
    
    createAppleTopper(center.x+InTranX,center.y+InTranY,center.z+InTranZ, InRotX+90, InRotY+270,InRotX+90);
    drawAppleTopper();
    specifyTexture4();
}

//------------------------------------------Topper(Apple)------------------------------------------//
void fruitModels::drawAppleTopper(){m_AppleTopper.draw();}
void fruitModels::createAppleTopper(double x, double y, double z,float ROTx, float ROTy, float ROTz){
    glm::mat4 modelTransform(1.0f);
    
    modelTransform = glm::scale(modelTransform, glm::vec3(apple_scaler));
    modelTransform = glm::rotate(modelTransform, glm::radians(ROTx), {1, 0 ,0});
    modelTransform = glm::rotate(modelTransform, glm::radians(ROTy), {0, 1 ,0});
    modelTransform = glm::rotate(modelTransform, glm::radians(ROTz), {0, 0 ,1});
    
    static char filename[255] = CGRA_SRCDIR "/res/models/appleTopper.obj";
    cgra::Wavefront appleObj;
    try {
        appleObj = cgra::Wavefront::load(filename);
    } catch (std::exception e) {
        std::cerr << "Couldn't load file: '" << filename << "' " << e.what() << std::endl;
        return;
    }
    unsigned int numVertices  = appleObj.m_positions.size();
    unsigned int numTriangles = appleObj.m_faces.size();
    
    cgra::Matrix<double> vertices(numVertices, 3);
    cgra::Matrix<unsigned int> triangles(numTriangles, 3);
    glm::vec3 vmax(appleObj.m_positions[0][0],appleObj.m_positions[0][1],appleObj.m_positions[0][2]);
    glm::vec3 vmin(appleObj.m_positions[0][0],appleObj.m_positions[0][1],appleObj.m_positions[0][2]);
    
    for (size_t i = 0; i < appleObj.m_positions.size(); i++) {
        
        glm::mat4 model = modelTransform;
        glm::mat4 mvp = glm::mat4(1.0f)* model;
        glm::vec4 vertex(appleObj.m_positions[i][0],appleObj.m_positions[i][1],appleObj.m_positions[i][2], 1.0f);
        vertex = mvp * vertex;
        vertices.setRow(i,{vertex[0]+x,vertex[1]+y,vertex[2]+z});
        glm::vec3 v(appleObj.m_positions[i][0],appleObj.m_positions[i][1],appleObj.m_positions[i][2]);
        vmax = glm::max(vmax, v);
        vmin = glm::min(vmin, v);
    }
    for (size_t i = 0; i < appleObj.m_faces.size(); i++) {
        std::vector<cgra::Wavefront::Vertex> m_vertices = appleObj.m_faces[i].m_vertices;
        triangles.setRow(i,{m_vertices[0].m_p-1,m_vertices[1].m_p - 1,m_vertices[2].m_p - 1});
    }
    m_AppleTopper.setData(vertices, triangles);
    
}

//------------------------------------------TetureSetters------------------------------------------//
void fruitModels::specifyTexture1() {
    
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    int width, height, nrChannels;
    unsigned char *data = stbi_load(CGRA_SRCDIR "/res/textures/normalMap.png", &width, &height, &nrChannels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
}
void fruitModels::specifyTexture2() {
    
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    int width, height, nrChannels;
    unsigned char *data = stbi_load(CGRA_SRCDIR "/res/textures/Texture.png", &width, &height, &nrChannels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
}
void fruitModels::specifyTexture3() {
    
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    int width, height, nrChannels;
    unsigned char *data = stbi_load(CGRA_SRCDIR "/res/textures/normalMap.png", &width, &height, &nrChannels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
}
void fruitModels::specifyTexture4() {
    
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    int width, height, nrChannels;
    unsigned char *data = stbi_load(CGRA_SRCDIR "/res/textures/Texture.png", &width, &height, &nrChannels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
}
