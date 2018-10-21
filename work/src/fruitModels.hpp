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
    void specifyTexture1();
    void specifyTexture2();
    void specifyTexture3();
    void specifyTexture4();
    //--------------
    cgra::Mesh m_bowl;
    float bowl_scaler = 0.3;
    void drawBowl();
    void Bowl(float InTranX, float InTranY, float InTranZ, float InRotX, float InRotY, float InRotZ);
    
    //--------------
    cgra::Mesh m_orange;
    float orange_scaler = 0.5;
    void drawOrange();
    void Orange(float InTranX, float InTranY, float InTranZ, float InRotX, float InRotY, float InRotZ);
    
    cgra::Mesh m_orangeTopper;
    void drawOrangeTopper();
    void createOrangeTopper(double x, double y, double z,float ROTx, float ROTy, float ROTz);
    
    //--------------
    cgra::Mesh m_strawberry;
    float strawberry_scaler = 1;
    void drawStrawberry();
    void Strawberry(float InTranX, float InTranY, float InTranZ, float InRotX, float InRotY, float InRotZ);
    
    cgra::Mesh m_StrawTopper;
    void drawStrawTopper();
    void createStrawTopper(double x, double y, double z,float ROTx, float ROTy, float ROTz);
    
    //--------------
    cgra::Mesh m_tomato;
    float tomato_scaler = 1.5;
    void drawTomato();
    void Tomato(float InTranX, float InTranY, float InTranZ, float InRotX, float InRotY, float InRotZ);
    
    cgra::Mesh m_TomatorTopper;
    void drawTomatoTopper();
    void createTomatoTopper(double x, double y, double z,float ROTx, float ROTy, float ROTz);
    
    //--------------
    cgra::Mesh m_apple;
    float apple_scaler = 2;
    void drawApple();
    void Apple(float InTranX, float InTranY, float InTranZ, float InRotX, float InRotY, float InRotZ);
    
    cgra::Mesh m_AppleTopper;
    void drawAppleTopper();
    void createAppleTopper(double x, double y, double z,float ROTx, float ROTy, float ROTz);
};
