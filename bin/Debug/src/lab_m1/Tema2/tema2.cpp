#include "lab_m1/Tema2/tema2.h"

#include <vector>
#include <string>
#include <iostream>
#include <cmath>

using namespace std;
using namespace m1;


/*
 *  To find out more about FrameStart, Update, FrameEnd
 *  and the order in which they are called, see world.cpp.
 */


Tema2::Tema2()
{
}


Tema2::~Tema2()
{
}


glm::vec3 Rotate(glm::vec3 point, float angle, glm::vec3 center) {
    glm::vec3 translatedPoint = point - center;
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::vec4 rotatedPoint = rotationMatrix * glm::vec4(translatedPoint, 1.0f);
    return glm::vec3(rotatedPoint) + center;
}


float random(glm::vec2 st) {
    return glm::fract(sin(glm::dot(st, glm::vec2(329.21318, 1930.33))) * 2008.54565123f);
}

// Func?ia pentru noise 2D
float noise(glm::vec2 st) {
    glm::vec2 i = glm::floor(st);
    glm::vec2 f = glm::fract(st);

    float a = random(i);
    float b = random(i + glm::vec2(1.0, 0.0));
    float c = random(i + glm::vec2(0.0, 1.0));
    float d = random(i + glm::vec2(1.0, 1.0));

    glm::vec2 u = f * f * (3.0f - 2.0f * f);

    return glm::mix(a, b, u.x) + (c - a) * u.y * (1.0f - u.x) + (d - b) * u.x * u.y;
}

void Tema2::Init()
{


    a = (rand() % 21) - 10;
    d = rand();
    b = (d % d);
    c = (rand() % 10) - 10;

    a1 = (rand() % 21) - 10;
    d1 = rand();
    b1 = d1 % d1;
    c1 = (rand() % 10) - 10;


    a2 = (rand() % 21) - 10;
    d2 = rand();
    b2 = d2 % d2;
    c2 = (rand() % 10) - 10;

    a4 = (rand() % 21) - 10;
    d4 = rand();
    b4 = (d4 % d4);
    c4 = (rand() % 10) - 10;

    a5 = (rand() % 21) - 10;
    d5 = rand();
    b5 = (d4 % d4);
    c5 = (rand() % 10) - 10;



    cout << a - 0.3f << " " << b << " " << c << endl;

    GetSceneCamera()->SetPosition(glm::vec3(0, 2.3f, 0.5f)); // Pozi?ia ini?ialã a camerei
    GetSceneCamera()->SetRotation(glm::vec3(0, 0, 0)); // Rotirea ini?ialã
    GetSceneCamera()->Update();

    {
        Mesh* mesh = new Mesh("box");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    // Create a simple cube
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(-0.05f, 0.0f, -0.05f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,0,0)), // 0
            VertexFormat(glm::vec3(0.05f, 0.0f, -0.05f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,0,0)),  // 1
            VertexFormat(glm::vec3(-0.05f, 0.0f, 0.05f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0,0,0)),  // 2
            VertexFormat(glm::vec3(0.05f, 0.0f, 0.05f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0,0,0)),   // 3
            VertexFormat(glm::vec3(-0.05f, 0.1f, -0.05f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0,0,0)), // 4
            VertexFormat(glm::vec3(0.05f, 0.1f, -0.05f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0,0,0)),  // 5
            VertexFormat(glm::vec3(-0.05f, 0.1f, 0.05f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0,0,0)),  // 6
            VertexFormat(glm::vec3(0.05f, 0.1f, 0.05f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,0,0))

        };

        vector<unsigned int> indices =
        {
            0, 1, 2,        1, 3, 2,
            2, 3, 7,        2, 7, 6,
            1, 7, 3,        1, 5, 7,
            6, 7, 4,        7, 5, 4,
            0, 4, 1,        1, 4, 5,
            2, 6, 4,        0, 2, 4,
        };

        CreateMesh("cube", vertices, indices);
    }

    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(-0.05f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,0,0)), // 0
            VertexFormat(glm::vec3(-0.05f, 0.0f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,1,0)),  // 1
            VertexFormat(glm::vec3(-0.05f, 2.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0,0,0)),  // 2
            VertexFormat(glm::vec3(-0.05f, 2.0f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,1,0)), // 3

            VertexFormat(glm::vec3(-0.05f, 2.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,0,0)), // 4
            VertexFormat(glm::vec3(-0.05f, 2.0f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,1,0)),  // 5
            VertexFormat(glm::vec3(2.05f, 2.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0,0,0)),  // 6
            VertexFormat(glm::vec3(2.05f, 2.0f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,1,0)), // 7

            VertexFormat(glm::vec3(2.05f, 2.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,0,0)), // 8
            VertexFormat(glm::vec3(2.05f, 2.0f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,1,0)),  // 9
            VertexFormat(glm::vec3(2.05f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0,0,0)),  // 10
            VertexFormat(glm::vec3(2.05f, 0.0f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,1,0)), // 11

            VertexFormat(glm::vec3(2.05f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,0,0)), // 12
            VertexFormat(glm::vec3(2.05f, 0.0f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,1,0)),  // 13
            VertexFormat(glm::vec3(-0.05f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0,0,0)),  // 14
            VertexFormat(glm::vec3(-0.05f, 0.0f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,1,0)), // 15

            VertexFormat(glm::vec3(0.25f, 0.2f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,0,0)), // 16
            VertexFormat(glm::vec3(0.25f, 0.2f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,1,0)),  // 17
            VertexFormat(glm::vec3(0.25f, 1.8f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0,0,0)),  // 18
            VertexFormat(glm::vec3(0.25f, 1.8f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,1,0)), // 19

            VertexFormat(glm::vec3(0.25f, 1.8f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,0,0)), // 20
            VertexFormat(glm::vec3(0.25f, 1.8f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,1,0)),  // 21
            VertexFormat(glm::vec3(1.75f, 1.8f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0,0,0)),  // 22
            VertexFormat(glm::vec3(1.75f, 1.8f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,1,0)), // 23

            VertexFormat(glm::vec3(1.75f, 1.8f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,0,0)), // 24
            VertexFormat(glm::vec3(1.75f, 1.8f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,1,0)),  // 25
            VertexFormat(glm::vec3(1.75f, 0.2f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0,0,0)),  // 26
            VertexFormat(glm::vec3(1.75f, 0.2f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,1,0)), // 27

            VertexFormat(glm::vec3(1.75f, 0.2f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,0,0)), // 28
            VertexFormat(glm::vec3(1.75f, 0.2f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,1,0)),  // 29
            VertexFormat(glm::vec3(0.25f, 0.2f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0,0,0)),  // 30
            VertexFormat(glm::vec3(0.25f, 0.2f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,1,0)), // 31


        };

        vector<unsigned int> indices =
        {
            0, 2, 3,
            0, 3, 1,

            4, 6, 7,
            4, 7, 5,

            8, 10, 11,
            8, 11, 9,

            12, 14, 15,
            12, 15, 13,

            16, 18, 19,
            16, 19, 17,

            20, 22, 23,
            20, 23, 21,

            24, 26, 27,
            24, 27, 25,

            28, 30, 31,
            28, 31, 29
        };

        CreateMesh("cube1", vertices, indices);
    }

    {
        vector<VertexFormat> vertices = {
            VertexFormat(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 0, 0)), // 0
            VertexFormat(glm::vec3(0.0f, 0.1f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 1, 0)),  // 1
            VertexFormat(glm::vec3(direction1, 0.1f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 0, 0)),  // 2
            VertexFormat(glm::vec3(direction1, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 1, 0)), // 3
        };

        vector<unsigned int> indices = {
            0, 1, 2,
            0, 2, 3,
        };

        CreateMesh("dreptunghi", vertices, indices);


        
    }


    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(-0.05f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 0
            VertexFormat(glm::vec3(-0.05f, 0.0f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)),  // 1
            VertexFormat(glm::vec3(-0.05f, 2.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 2
            VertexFormat(glm::vec3(-0.05f, 2.0f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 3

            VertexFormat(glm::vec3(-0.05f, 2.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 4
            VertexFormat(glm::vec3(-0.05f, 2.0f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)),  // 5
            VertexFormat(glm::vec3(2.05f, 2.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 6
            VertexFormat(glm::vec3(2.05f, 2.0f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 7

            VertexFormat(glm::vec3(2.05f, 2.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 8
            VertexFormat(glm::vec3(2.05f, 2.0f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)),  // 9
            VertexFormat(glm::vec3(2.05f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 10
            VertexFormat(glm::vec3(2.05f, 0.0f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 11

            VertexFormat(glm::vec3(2.05f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 12
            VertexFormat(glm::vec3(2.05f, 0.0f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)),  // 13
            VertexFormat(glm::vec3(-0.05f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 14
            VertexFormat(glm::vec3(-0.05f, 0.0f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 15

            VertexFormat(glm::vec3(0.25f, 0.2f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 16
            VertexFormat(glm::vec3(0.25f, 0.2f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)),  // 17
            VertexFormat(glm::vec3(0.25f, 1.8f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 18
            VertexFormat(glm::vec3(0.25f, 1.8f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 19

            VertexFormat(glm::vec3(0.25f, 1.8f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 20
            VertexFormat(glm::vec3(0.25f, 1.8f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)),  // 21
            VertexFormat(glm::vec3(1.75f, 1.8f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 22
            VertexFormat(glm::vec3(1.75f, 1.8f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 23

            VertexFormat(glm::vec3(1.75f, 1.8f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 24
            VertexFormat(glm::vec3(1.75f, 1.8f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)),  // 25
            VertexFormat(glm::vec3(1.75f, 0.2f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 26
            VertexFormat(glm::vec3(1.75f, 0.2f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 27

            VertexFormat(glm::vec3(1.75f, 0.2f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 28
            VertexFormat(glm::vec3(1.75f, 0.2f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)),  // 29
            VertexFormat(glm::vec3(0.25f, 0.2f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 30
            VertexFormat(glm::vec3(0.25f, 0.2f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 31


        };




        vector<unsigned int> indices =
        {
            0, 2, 3,
            0, 3, 1,

            4, 6, 7,
            4, 7, 5,

            8, 10, 11,
            8, 11, 9,

            12, 14, 15,
            12, 15, 13,

            16, 18, 19,
            16, 19, 17,

            20, 22, 23,
            20, 23, 21,

            24, 26, 27,
            24, 27, 25,

            28, 30, 31,
            28, 31, 29
        };

        CreateMesh("cube2", vertices, indices);
    }

    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(-0.05f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 0
            VertexFormat(glm::vec3(-0.05f, 0.0f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)),  // 1
            VertexFormat(glm::vec3(-0.05f, 2.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 2
            VertexFormat(glm::vec3(-0.05f, 2.0f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 3

            VertexFormat(glm::vec3(-0.05f, 2.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 4
            VertexFormat(glm::vec3(-0.05f, 2.0f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)),  // 5
            VertexFormat(glm::vec3(2.05f, 2.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 6
            VertexFormat(glm::vec3(2.05f, 2.0f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 7

            VertexFormat(glm::vec3(2.05f, 2.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 8
            VertexFormat(glm::vec3(2.05f, 2.0f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)),  // 9
            VertexFormat(glm::vec3(2.05f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 10
            VertexFormat(glm::vec3(2.05f, 0.0f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 11

            VertexFormat(glm::vec3(2.05f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 12
            VertexFormat(glm::vec3(2.05f, 0.0f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)),  // 13
            VertexFormat(glm::vec3(-0.05f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 14
            VertexFormat(glm::vec3(-0.05f, 0.0f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 15

            VertexFormat(glm::vec3(0.25f, 0.2f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 16
            VertexFormat(glm::vec3(0.25f, 0.2f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)),  // 17
            VertexFormat(glm::vec3(0.25f, 1.8f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 18
            VertexFormat(glm::vec3(0.25f, 1.8f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 19

            VertexFormat(glm::vec3(0.25f, 1.8f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 20
            VertexFormat(glm::vec3(0.25f, 1.8f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)),  // 21
            VertexFormat(glm::vec3(1.75f, 1.8f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 22
            VertexFormat(glm::vec3(1.75f, 1.8f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 23

            VertexFormat(glm::vec3(1.75f, 1.8f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 24
            VertexFormat(glm::vec3(1.75f, 1.8f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)),  // 25
            VertexFormat(glm::vec3(1.75f, 0.2f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 26
            VertexFormat(glm::vec3(1.75f, 0.2f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 27

            VertexFormat(glm::vec3(1.75f, 0.2f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 28
            VertexFormat(glm::vec3(1.75f, 0.2f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)),  // 29
            VertexFormat(glm::vec3(0.25f, 0.2f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 30
            VertexFormat(glm::vec3(0.25f, 0.2f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 31


        };

        vector<unsigned int> indices =
        {
            0, 2, 3,
            0, 3, 1,

            4, 6, 7,
            4, 7, 5,

            8, 10, 11,
            8, 11, 9,

            12, 14, 15,
            12, 15, 13,

            16, 18, 19,
            16, 19, 17,

            20, 22, 23,
            20, 23, 21,

            24, 26, 27,
            24, 27, 25,

            28, 30, 31,
            28, 31, 29
        };

        CreateMesh("cube3", vertices, indices);
    }


    {
        vector<VertexFormat> vertices = {
            // Fa?a din fa?ã
            VertexFormat(glm::vec3(-1.2f, 0.0f, -0.25f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,1,0)), // 0
            VertexFormat(glm::vec3(1.2f, 0.0f, -0.25f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,1,0)), // 1
            VertexFormat(glm::vec3(-1.2f, 0.0f,  0.25f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)), // 2
            VertexFormat(glm::vec3(1.2f, 0.0f,  0.25f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)), // 3

            // Fa?a din spate
            VertexFormat(glm::vec3(-1.2f, 1.0f, -0.25f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,1,0)), // 4
            VertexFormat(glm::vec3(1.2f, 1.0f,  -0.25f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,1,0)), // 5
            VertexFormat(glm::vec3(-1.2f, 1.0f,  0.25f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)), // 6
            VertexFormat(glm::vec3(1.2f, 1.0f,  0.25f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)), // 7
        };

        // Indicii pentru conectarea vârfurilor ?i formarea fe?elor paralelipipedului
        vector<unsigned int> indices = {
            // Fa?a din fa?ã
            0, 1, 2,  1, 3, 2,

            4, 6, 5,  5, 6, 7,

            0, 2, 4,  2, 6, 4,

            1, 5, 3,  3, 5, 7,

            2, 3, 6,  3, 7, 6,

            0, 4, 1,  1, 4, 5
        };

        // Crea?i paralelipipedul cu culoare neagrã
        CreateMesh("paralelipipedXOZ", vertices, indices);
    }



    {
        std::vector<VertexFormat> crossParalelipipedeVertices = {
            VertexFormat(glm::vec3(-0.5f, -0.05f, -0.05f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(0.5f, -0.05f, -0.05f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(-0.5f, -0.05f,  0.05f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(0.5f, -0.05f,  0.05f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(-0.5f,  0.05f, -0.05f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(0.5f,  0.05f, -0.05f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(-0.5f,  0.05f,  0.05f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(0.5f,  0.05f,  0.05f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1, 0, 0)),

            VertexFormat(glm::vec3(-0.05f, -0.05f, -0.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(0.05f, -0.05f, -0.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(-0.05f, -0.05f,  0.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(0.05f, -0.05f,  0.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(-0.05f,  0.05f, -0.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(0.05f,  0.05f, -0.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(-0.05f,  0.05f,  0.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(0.05f,  0.05f,  0.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1, 0, 0)),


            VertexFormat(glm::vec3(-0.5f, 0.05f, -0.05f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,0,0)),
            VertexFormat(glm::vec3(-0.4f, 0.05f, -0.05f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,0,0)),
            VertexFormat(glm::vec3(-0.5f, 0.05f, 0.05f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0,0,0)),
            VertexFormat(glm::vec3(-0.4f, 0.05f, 0.05f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0,0,0)),
            VertexFormat(glm::vec3(-0.5f, 0.15f, -0.05f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0,0,0)),
            VertexFormat(glm::vec3(-0.4f, 0.15f, -0.05f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0,0,0)),
            VertexFormat(glm::vec3(-0.5f, 0.15f, 0.05f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0,0,0)),
            VertexFormat(glm::vec3(-0.4f, 0.15f, 0.05f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,0,0)),

            VertexFormat(glm::vec3(0.5f, 0.05f, -0.05f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,0,0)),
            VertexFormat(glm::vec3(0.4f, 0.05f, -0.05f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,0,0)),
            VertexFormat(glm::vec3(0.5f, 0.05f, 0.05f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0,0,0)),
            VertexFormat(glm::vec3(0.4f, 0.05f, 0.05f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0,0,0)),
            VertexFormat(glm::vec3(0.5f, 0.15f, -0.05f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0,0,0)),
            VertexFormat(glm::vec3(0.4f, 0.15f, -0.05f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0,0,0)),
            VertexFormat(glm::vec3(0.5f, 0.15f, 0.05f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0,0,0)),
            VertexFormat(glm::vec3(0.4f, 0.15f, 0.05f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,0,0)),

            VertexFormat(glm::vec3(-0.05f, 0.05f, 0.4f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(0.05f,  0.05f, 0.4f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-0.05f, 0.05f,  0.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(0.05f,  0.05f,  0.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-0.05f,  0.15f, 0.4f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(0.05f,  0.15f,  0.4f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-0.05f,  0.15f,  0.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(0.05f,  0.15f,  0.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 0, 0)),

            VertexFormat(glm::vec3(-0.05f, 0.05f, -0.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(0.05f,  0.05f, -0.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-0.05f, 0.05f,  -0.4f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(0.05f,  0.05f,  -0.4f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-0.05f,  0.15f, -0.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(0.05f,  0.15f,  -0.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-0.05f,  0.15f,  -0.4f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(0.05f,  0.15f,  -0.4f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 0, 0)),

            VertexFormat(glm::vec3(-0.5f, 0.16f, -0.1f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 0
            VertexFormat(glm::vec3(-0.4f, 0.16f, -0.1f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)),  // 1
            VertexFormat(glm::vec3(-0.5f, 0.16f, 0.1f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 2
            VertexFormat(glm::vec3(-0.4f, 0.16f, 0.1f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),   // 3
            VertexFormat(glm::vec3(-0.5f, 0.16f, -0.1f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)), // 4
            VertexFormat(glm::vec3(-0.4f, 0.16f, -0.1f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 5
            VertexFormat(glm::vec3(-0.5f, 0.16f, 0.1f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 6
            VertexFormat(glm::vec3(-0.4f, 0.16f, 0.1f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)),   // 7

            VertexFormat(glm::vec3(0.5f, 0.16f, -0.1f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 0
            VertexFormat(glm::vec3(0.4f, 0.16f, -0.1f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)),  // 1
            VertexFormat(glm::vec3(0.5f, 0.16f, 0.1f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 2
            VertexFormat(glm::vec3(0.4f, 0.16f, 0.1f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),   // 3
            VertexFormat(glm::vec3(0.5f, 0.16f, -0.1f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)), // 4
            VertexFormat(glm::vec3(0.4f, 0.16f, -0.1f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 5
            VertexFormat(glm::vec3(0.5f, 0.16f, 0.1f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 6
            VertexFormat(glm::vec3(0.4f, 0.16f, 0.1f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)),   // 7

            //VertexFormat(Rotate(glm::vec3(0.05f, 0.16f, -0.5f), 0, glm::vec3(0, 0.16f, -0.4f)), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 0
            //VertexFormat(Rotate(glm::vec3(-0.05f, 0.16f, -0.5f), 0, glm::vec3(0, 0.16f, -0.4f)), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)),  // 1
            //VertexFormat(Rotate(glm::vec3(0.05f, 0.16f, -0.3f), 0, glm::vec3(0, 0.16f, -0.4f)), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 2
            //VertexFormat(Rotate(glm::vec3(-0.05f, 0.16f, -0.3f), 0, glm::vec3(0, 0.16f, -0.4f)), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),   // 3
            //VertexFormat(Rotate(glm::vec3(0.05f, 0.16f, -0.5f), 0, glm::vec3(0, 0.16f, -0.4f)), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)), // 4
            //VertexFormat(Rotate(glm::vec3(-0.05f, 0.16f, -0.5f), 0, glm::vec3(0, 0.16f, -0.4f)), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 5
            //VertexFormat(Rotate(glm::vec3(0.05f, 0.16f, -0.3f), 0, glm::vec3(0, 0.16f, -0.4f)), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 6
            //VertexFormat(Rotate(glm::vec3(-0.05f, 0.16f, -0.3f), 0, glm::vec3(0, 0.16f, -0.4f)), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)),   // 7


            VertexFormat(glm::vec3(0.05f, 0.16f, -0.5f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 0
            VertexFormat(glm::vec3(-0.05f, 0.16f, -0.5f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)),  // 1
            VertexFormat(glm::vec3(0.05f, 0.16f, -0.3f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 2
            VertexFormat(glm::vec3(-0.05f, 0.16f, -0.3f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),   // 3
            VertexFormat(glm::vec3(0.05f, 0.16f, -0.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)), // 4
            VertexFormat(glm::vec3(-0.05f, 0.16f, -0.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 5
            VertexFormat(glm::vec3(0.05f, 0.16f, -0.3f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 6
            VertexFormat(glm::vec3(-0.05f, 0.16f, -0.3f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)),   // 7

            VertexFormat(glm::vec3(-1.5f, 0.16f, -0.1f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 0
            VertexFormat(glm::vec3(-1.4f, 0.16f, -0.1f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)),  // 1
            VertexFormat(glm::vec3(-1.5f, 0.16f, 0.1f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 2
            VertexFormat(glm::vec3(-1.4f, 0.16f, 0.1f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),   // 3
            VertexFormat(glm::vec3(-1.5f, 0.16f, -0.1f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)), // 4
            VertexFormat(glm::vec3(-1.4f, 0.16f, -0.1f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 5
            VertexFormat(glm::vec3(-1.5f, 0.16f, 0.1f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 6
            VertexFormat(glm::vec3(-1.4f, 0.16f, 0.1f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)),   // 7
        };

        std::vector<unsigned int> crossParalelipipedeIndices = {
            0, 1, 2, 1, 3, 2,
            4, 6, 5, 5, 6, 7,
            0, 2, 4, 2, 6, 4,
            1, 5, 3, 3, 5, 7,
            2, 3, 6, 3, 7, 6,
            0, 4, 1, 1, 4, 5,

            8, 9, 10, 9, 11, 10,
            12, 14, 13, 13, 14, 15,
            8, 10, 12, 10, 14, 12,
            9, 13, 11, 11, 13, 15,
            10, 11, 14, 11, 15, 14,
            8, 12, 9, 9, 12, 13,

            16, 17, 18, 17, 19, 18,
            18, 19, 23, 18, 23, 22,
            17, 23, 19, 17, 21, 23,
            22, 23, 20, 23, 21, 20,
            16, 20, 17, 17, 20, 21,
            18, 22, 20, 16, 18, 20,

            24, 25, 26, 25, 27, 26,
            26, 27, 31, 26, 31, 30,
            25, 31, 27, 25, 29, 31,
            30, 31, 28, 31, 29, 28,
            24, 28, 25, 25, 28, 29,
            26, 30, 28, 24, 26, 28,

            32, 33, 34, 33, 35, 34,
            34, 35, 39, 34, 39, 38,
            33, 39, 35, 33, 37, 39,
            38, 39, 36, 39, 37, 36,
            32, 36, 33, 33, 36, 37,
            34, 38, 36, 32, 34, 36,

            40, 41, 42, 41, 43, 42,
            42, 43, 47, 42, 47, 46,
            41, 47, 43, 41, 45, 47,
            46, 47, 44, 47, 45, 44,
            40, 44, 41, 41, 44, 45,
            42, 46, 44, 40, 42, 44,

            48, 49, 50, 49, 51, 50,
            52, 54, 53, 53, 54, 55,
            48, 50, 52, 50, 54, 52,
            49, 53, 51, 51, 53, 55,
            50, 51, 54, 51, 55, 54,
            48, 52, 49, 49, 52, 53,

            56, 57, 58, 57, 59, 58,
            60, 62, 61, 61, 62, 63,
            56, 58, 60, 58, 62, 60,
            57, 61, 59, 59, 61, 63,
            58, 59, 62, 59, 63, 62,
            56, 60, 57, 57, 60, 61,

            64, 65, 66, 65, 67, 66,
            68, 70, 69, 69, 70, 71,
            64, 66, 68, 66, 70, 68,
            65, 69, 67, 67, 69, 71,
            66, 67, 70, 67, 71, 70,
            64, 68, 65, 65, 68, 69,

            72, 73, 74, 73, 75, 74,
            76, 78, 77, 77, 78, 79,
            72, 74, 76, 74, 78, 76,
            73, 77, 75, 75, 77, 79,
            74, 75, 78, 75, 79, 78,
            72, 76, 73, 73, 76, 77

        };

        CreateMesh("paralelipipede_cruce", crossParalelipipedeVertices, crossParalelipipedeIndices);
    }




    {
        Shader* shader = new Shader("LabShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab6", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "lab6", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    {
        int numSegments = 20;
        float radius = 0.3f;
        float height = 1.0f;

        std::vector<VertexFormat> vertices;
        std::vector<unsigned int> indices;

        for (int i = 0; i < numSegments; i++) {
            float angle = (2.0f * M_PI * i) / numSegments;
            float x = radius * cos(angle);
            float z = radius * sin(angle);
            vertices.emplace_back(glm::vec3(x, 0.0f, z), glm::vec3(0.6f, 0.4f, 0.2f), glm::vec3(0.6f, 0.4f, 0.2f)); // Maro
        }

        for (int i = 0; i < numSegments; i++) {
            float angle = (2.0f * M_PI * i) / numSegments;
            float x = radius * cos(angle);
            float z = radius * sin(angle);
            vertices.emplace_back(glm::vec3(x, height, z), glm::vec3(0.6f, 0.4f, 0.2f), glm::vec3(0.6f, 0.4f, 0.2f)); // Maro
        }

        int centerBottom = vertices.size();
        vertices.emplace_back(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.6f, 0.4f, 0.2f), glm::vec3(0.6f, 0.4f, 0.2f));
        int centerTop = vertices.size();
        vertices.emplace_back(glm::vec3(0.0f, height, 0.0f), glm::vec3(0.6f, 0.4f, 0.2f), glm::vec3(0.6f, 0.4f, 0.2f));

        for (int i = 0; i < numSegments; i++) {
            indices.push_back(centerBottom);
            indices.push_back(i);
            indices.push_back((i + 1) % numSegments);
        }

        for (int i = 0; i < numSegments; i++) {
            indices.push_back(centerTop);
            indices.push_back(numSegments + i);
            indices.push_back(numSegments + (i + 1) % numSegments);
        }

        for (int i = 0; i < numSegments; i++) {
            int next = (i + 1) % numSegments;
            indices.push_back(i);
            indices.push_back(numSegments + i);
            indices.push_back(next);

            indices.push_back(next);
            indices.push_back(numSegments + i);
            indices.push_back(numSegments + next);
        }

        CreateMesh("trunchi", vertices, indices);
    }

    {
        // Parametri pentru con
        int numSegments = 30; // Numãrul de segmente pentru bazã
        float radius = 0.5f;  // Raza bazei
        float height = 1.0f;  // Înãl?imea conului

        std::vector<VertexFormat> vertices;
        std::vector<unsigned int> indices;


        for (int i = 0; i < numSegments; i++) {
            float angle = (2.0f * M_PI * i) / numSegments;
            float x = radius * cos(angle);
            float z = radius * sin(angle);
            vertices.emplace_back(glm::vec3(x, 0.0f, z), glm::vec3(0.8f, 0.5f, 0.2f)); // Maro
        }

        // Centrul bazei
        int centerIndex = vertices.size();
        vertices.emplace_back(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.8f, 0.5f, 0.2f)); // Maro

        // Vârful conului
        int topIndex = vertices.size();
        vertices.emplace_back(glm::vec3(0.0f, height, 0.0f), glm::vec3(0.8f, 0.5f, 0.2f)); // Maro

        // Indici pentru baza conului (triunghiuri cu centrul bazei)
        for (int i = 0; i < numSegments; i++) {
            indices.push_back(centerIndex);
            indices.push_back(i);
            indices.push_back((i + 1) % numSegments);
        }

        // Indici pentru suprafa?a conului (triunghiuri între bazã ?i vârf)
        for (int i = 0; i < numSegments; i++) {
            indices.push_back(i);
            indices.push_back((i + 1) % numSegments);
            indices.push_back(topIndex);
        }

        // Crearea mesh-ului
        CreateMesh("con", vertices, indices);
    }

    {
        std::vector<VertexFormat> vertices;
        std::vector<unsigned int> indices;

        float size = 1.0f; // Dimensiunea fiecãrui pãtrat
        int rows = 27;
        int cols = 27;

        // Generãm vârfurile pentru fiecare patratel
        int vertexIndex = 0;
        for (int i = -rows + 1; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                // Col?urile pãtratului
                glm::vec3 bottomLeft(j * size, 0.0f, i * size);
                glm::vec3 bottomRight((j + 1) * size, 0.0f, i * size);
                glm::vec3 topLeft(j * size, 0.0f, (i + 1) * size);
                glm::vec3 topRight((j + 1) * size, 0.0f, (i + 1) * size);



                // Adãugãm vârfurile pentru acest pãtrat
                vertices.push_back(VertexFormat(bottomLeft, glm::vec3(0.0f), glm::vec3(1, 1, 0))); // V0
                vertices.push_back(VertexFormat(bottomRight, glm::vec3(0.0f), glm::vec3(1, 1, 0))); // V1
                vertices.push_back(VertexFormat(topLeft, glm::vec3(0.0f), glm::vec3(1, 1, 0))); // V2
                vertices.push_back(VertexFormat(topRight, glm::vec3(0.0f), glm::vec3(1, 1, 0))); // V3

                // Adãugãm indicii pentru cele douã triunghiuri care formeazã pãtratul
                indices.push_back(vertexIndex);     // V0
                indices.push_back(vertexIndex + 1); // V1
                indices.push_back(vertexIndex + 2); // V2

                indices.push_back(vertexIndex + 1); // V1
                indices.push_back(vertexIndex + 3); // V3
                indices.push_back(vertexIndex + 2); // V2

                vertexIndex += 4; // Incrementãm indexul pentru urmãtorul set de patru vârfuri
            }
        }

        for (int i = -rows + 1; i < rows; i++) {
            for (int j = 0; j > -cols; j--) {
                // Col?urile pãtratului
                glm::vec3 bottomLeft(j * size, 0.0f, i * size);
                glm::vec3 bottomRight((j + 1) * size, 0.0f, i * size);
                glm::vec3 topLeft(j * size, 0.0f, (i + 1) * size);
                glm::vec3 topRight((j + 1) * size, 0.0f, (i + 1) * size);



                // Adãugãm vârfurile pentru acest pãtrat
                vertices.push_back(VertexFormat(bottomLeft, glm::vec3(0.0f), glm::vec3(1, 1, 0))); // V0
                vertices.push_back(VertexFormat(bottomRight, glm::vec3(0.0f), glm::vec3(1, 1, 0))); // V1
                vertices.push_back(VertexFormat(topLeft, glm::vec3(0.0f), glm::vec3(1, 1, 0))); // V2
                vertices.push_back(VertexFormat(topRight, glm::vec3(0.0f), glm::vec3(1, 1, 0))); // V3

                // Adãugãm indicii pentru cele douã triunghiuri care formeazã pãtratul
                indices.push_back(vertexIndex);     // V0
                indices.push_back(vertexIndex + 1); // V1
                indices.push_back(vertexIndex + 2); // V2

                indices.push_back(vertexIndex + 1); // V1
                indices.push_back(vertexIndex + 3); // V3
                indices.push_back(vertexIndex + 2); // V2

                vertexIndex += 4; // Incrementãm indexul pentru urmãtorul set de patru vârfuri
            }
        }

        CreateMesh("terrain", vertices, indices);
    }


    {

        vector<VertexFormat> arrowVertices = {
           VertexFormat(glm::vec3(-0.2f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 0
           VertexFormat(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)),  // 1
           VertexFormat(glm::vec3(0.2f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 2
           VertexFormat(glm::vec3(-0.1f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),   // 3
           VertexFormat(glm::vec3(0.1f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)), // 4
           VertexFormat(glm::vec3(-0.1f, 2.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 5
           VertexFormat(glm::vec3(0.1f, 2.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 6
        };
        // Indices pentru a desena sãgeata folosind GL_TRIANGLES
        std::vector<unsigned int> arrowIndices = {
            // Corpul sãge?ii (dreptunghi)
            0, 1, 2,
            3, 4, 5,
            4, 6, 5

        };

        CreateMesh("arow", arrowVertices, arrowIndices);

    }



}


Mesh* Tema2::CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices)
{
    unsigned int VAO = 0;
    // Create the VAO and bind it
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Create the VBO and bind it
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Send vertices data into the VBO buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    // Create the IBO and bind it
    unsigned int IBO;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    // Send indices data into the IBO buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

    // Set vertex position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

    // Set vertex normal attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

    // Set texture coordinate attribute
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

    // Set vertex color attribute
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
    // ========================================================================

    // Unbind the VAO
    glBindVertexArray(0);

    // Check for OpenGL errors
    CheckOpenGLError();

    // Mesh information is saved into a Mesh object
    meshes[name] = new Mesh(name);
    meshes[name]->InitFromBuffer(VAO, static_cast<unsigned int>(indices.size()));
    meshes[name]->vertices = vertices;
    meshes[name]->indices = indices;
    return meshes[name];
}


void Tema2::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}



void Tema2::RenderScene() {



    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(a1, b1 + 0.8f, c1));
        RenderSimpleMesh(meshes["paralelipipedXOZ"], shaders["VertexNormal"], modelMatrix);

    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(a2, b2 + 0.5f, c2));
        RenderSimpleMesh(meshes["paralelipipedXOZ"], shaders["VertexNormal"], modelMatrix);

    }


    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(2, 2, -3));
        RenderSimpleMesh(meshes["cube1"], shaders["VertexNormal"], modelMatrix);

    }


    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-4, 3, -6));
        RenderSimpleMesh(meshes["cube2"], shaders["VertexNormal"], modelMatrix);

    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(dronePosition.x - 0.15f, dronePosition.y + 0.3f, dronePosition.z + 0.2f));
        RenderSimpleMesh(meshes["dreptunghi"], shaders["VertexNormal"], modelMatrix);

    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-4, 5, -10));
        RenderSimpleMesh(meshes["cube3"], shaders["VertexNormal"], modelMatrix);

    }


    if (ok2 == 1) {

        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-3, 8, -10));
        RenderSimpleMesh(meshes["arow"], shaders["VertexNormal"], modelMatrix);

    }
    else
        if (ok1 == 1) {

            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(-3, 6, -6));
            RenderSimpleMesh(meshes["arow"], shaders["VertexNormal"], modelMatrix);

        }
        else
            if (ok1 == 0) {
                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix = glm::translate(modelMatrix, glm::vec3(3, 5, -3));
                RenderSimpleMesh(meshes["arow"], shaders["VertexNormal"], modelMatrix);
            }


    {


        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, dronePosition);
        modelMatrix = glm::rotate(modelMatrix, glm::radians(pitch), glm::vec3(1, 0, 0));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(yaw), glm::vec3(0, 0, 1));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(roll), glm::vec3(0, 1, 0));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(angleX), glm::vec3(0, 0, 1));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(135.0f), glm::vec3(0, 1, 0));
        RenderSimpleMesh(meshes["paralelipipede_cruce"], shaders["VertexNormal"], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(a, b + 0.5f, c)); // Pozi?ia de start
        modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 1, 1));    // Scalare
        RenderSimpleMesh(meshes["trunchi"], shaders["VertexNormal"], modelMatrix);
    }
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(a, b + 1.5f, c)); // Pozi?ia conului
        modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 1, 1));    // Scalarea conului
        RenderSimpleMesh(meshes["con"], shaders["VertexNormal"], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(a, b + 2, c)); // Pozi?ia conului
        modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 1, 1));    // Scalarea conului
        RenderSimpleMesh(meshes["con"], shaders["VertexNormal"], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(a4, b4 + 0.5f, c4)); // Pozi?ia de start
        modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 1, 1));    // Scalare
        RenderSimpleMesh(meshes["trunchi"], shaders["VertexNormal"], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(a4, b4 + 1.5f, c4));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 1, 1));
        RenderSimpleMesh(meshes["con"], shaders["VertexNormal"], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(a4, b4 + 2, c4)); // Pozi?ia conului
        modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 1, 1));    // Scalarea conului
        RenderSimpleMesh(meshes["con"], shaders["VertexNormal"], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(a5, b5 + 0.5f, c5));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 1, 1));
        RenderSimpleMesh(meshes["trunchi"], shaders["VertexNormal"], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(a5, b5 + 1.5f, c5));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 1, 1));
        RenderSimpleMesh(meshes["con"], shaders["VertexNormal"], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(a5, b5 + 2, c5));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 1, 1));
        RenderSimpleMesh(meshes["con"], shaders["VertexNormal"], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, 0));
        modelMatrix = glm::rotate(modelMatrix, RADIANS(0.0f), glm::vec3(0, 1, 0));
        RenderMesh(meshes["terrain"], shaders["LabShader"], modelMatrix);
    }

    t = noise(glm::vec2(0, 0)) + 1.0f;


}


void Tema2::Update(float deltaTimeSeconds)
{

    glm::mat4 rotation = glm::mat4(1.0f);


    rotation = glm::rotate(rotation, glm::radians(pitch), glm::vec3(1.0f, 0.0f, 0.0f)); // Pitch
    rotation = glm::rotate(rotation, glm::radians(yaw), glm::vec3(0.0f, 0.0f, 1.0f));   // Yaw
    rotation = glm::rotate(rotation, glm::radians(roll), glm::vec3(0.0f, 1.0f, 0.0f));  // Roll

    glm::mat4 transform = glm::translate(glm::mat4(1.0f), dronePosition) * rotation;
    glm::vec3 cameraOffset = glm::vec3(0.0f, 0.3f, 0.5f); // Offset-ul camerei
    glm::vec3 cameraPosition = glm::vec3(transform * glm::vec4(cameraOffset, 1.0f));

    GetSceneCamera()->SetPosition(cameraPosition);
    GetSceneCamera()->SetRotation(glm::quat_cast(rotation)); // Quaternion din rota?ie
    GetSceneCamera()->Update();

    rotationAngle += deltaTimeSeconds * RADIANS(1600.0f);
    if (rotationAngle > 2 * M_PI) {
        rotationAngle -= 2 * M_PI;
    }

    if (direction1 > 0.0f) {
        direction1 -= deltaTimeSeconds * 0.005f;
    }


    {
        vector<VertexFormat> vertices = {
            VertexFormat(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 0, 0)), // 0
            VertexFormat(glm::vec3(0.0f, 0.1f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 1, 0)),  // 1
            VertexFormat(glm::vec3(direction1, 0.1f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 0, 0)),  // 2
            VertexFormat(glm::vec3(direction1, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 1, 0)), // 3
        };

        vector<unsigned int> indices = {
            0, 1, 2,
            0, 2, 3,
        };

        CreateMesh("dreptunghi", vertices, indices);



    }


    {
        std::vector<VertexFormat> crossParalelipipedeVertices = {
            // Paralelipipedul pe axa X (orientat pe axa X)
            // Fa?a de jos
            VertexFormat(glm::vec3(-0.5f, -0.05f, -0.05f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(0.5f, -0.05f, -0.05f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(-0.5f, -0.05f,  0.05f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(0.5f, -0.05f,  0.05f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1, 0, 0)),

            // Fa?a de sus
            VertexFormat(glm::vec3(-0.5f,  0.05f, -0.05f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(0.5f,  0.05f, -0.05f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(-0.5f,  0.05f,  0.05f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(0.5f,  0.05f,  0.05f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1, 0, 0)),

            // Paralelipipedul pe axa Z (orientat pe axa Z)
            // Fa?a de jos
            VertexFormat(glm::vec3(-0.05f, -0.05f, -0.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(0.05f, -0.05f, -0.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(-0.05f, -0.05f,  0.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(0.05f, -0.05f,  0.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1, 0, 0)),

            // Fa?a de sus
            VertexFormat(glm::vec3(-0.05f,  0.05f, -0.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(0.05f,  0.05f, -0.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(-0.05f,  0.05f,  0.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(0.05f,  0.05f,  0.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1, 0, 0)),


            VertexFormat(glm::vec3(-0.5f, 0.05f, -0.05f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,0,0)),
            VertexFormat(glm::vec3(-0.4f, 0.05f, -0.05f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,0,0)),
            VertexFormat(glm::vec3(-0.5f, 0.05f, 0.05f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0,0,0)),
            VertexFormat(glm::vec3(-0.4f, 0.05f, 0.05f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0,0,0)),
            VertexFormat(glm::vec3(-0.5f, 0.15f, -0.05f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0,0,0)),
            VertexFormat(glm::vec3(-0.4f, 0.15f, -0.05f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0,0,0)),
            VertexFormat(glm::vec3(-0.5f, 0.15f, 0.05f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0,0,0)),
            VertexFormat(glm::vec3(-0.4f, 0.15f, 0.05f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,0,0)),

            VertexFormat(glm::vec3(0.5f, 0.05f, -0.05f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,0,0)),
            VertexFormat(glm::vec3(0.4f, 0.05f, -0.05f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,0,0)),
            VertexFormat(glm::vec3(0.5f, 0.05f, 0.05f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0,0,0)),
            VertexFormat(glm::vec3(0.4f, 0.05f, 0.05f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0,0,0)),
            VertexFormat(glm::vec3(0.5f, 0.15f, -0.05f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0,0,0)),
            VertexFormat(glm::vec3(0.4f, 0.15f, -0.05f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0,0,0)),
            VertexFormat(glm::vec3(0.5f, 0.15f, 0.05f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0,0,0)),
            VertexFormat(glm::vec3(0.4f, 0.15f, 0.05f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,0,0)),

            VertexFormat(glm::vec3(-0.05f, 0.05f, 0.4f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(0.05f,  0.05f, 0.4f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-0.05f, 0.05f,  0.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(0.05f,  0.05f,  0.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-0.05f,  0.15f, 0.4f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(0.05f,  0.15f,  0.4f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-0.05f,  0.15f,  0.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(0.05f,  0.15f,  0.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 0, 0)),

            VertexFormat(glm::vec3(-0.05f, 0.05f, -0.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(0.05f,  0.05f, -0.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-0.05f, 0.05f,  -0.4f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(0.05f,  0.05f,  -0.4f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-0.05f,  0.15f, -0.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(0.05f,  0.15f,  -0.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-0.05f,  0.15f,  -0.4f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(0.05f,  0.15f,  -0.4f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 0, 0)),

            VertexFormat(Rotate(glm::vec3(-0.5f, 0.16f, -0.1f), rotationAngle, glm::vec3(-0.45f, 0.16f, 0.0f)), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 0
            VertexFormat(Rotate(glm::vec3(-0.4f, 0.16f, -0.1f), rotationAngle, glm::vec3(-0.45f, 0.16f, 0.0f)), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)),  // 1
            VertexFormat(Rotate(glm::vec3(-0.5f, 0.16f, 0.1f), rotationAngle, glm::vec3(-0.45f, 0.16f, 0.0f)), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 2
            VertexFormat(Rotate(glm::vec3(-0.4f, 0.16f, 0.1f), rotationAngle, glm::vec3(-0.45f, 0.16f, 0.0f)), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),   // 3
            VertexFormat(Rotate(glm::vec3(-0.5f, 0.16f, -0.1f), rotationAngle, glm::vec3(-0.45f, 0.16f, 0.0f)), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)), // 4
            VertexFormat(Rotate(glm::vec3(-0.4f, 0.16f, -0.1f), rotationAngle, glm::vec3(-0.45f, 0.16f, 0.0f)), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 5
            VertexFormat(Rotate(glm::vec3(-0.5f, 0.16f, 0.1f), rotationAngle, glm::vec3(-0.45f, 0.16f, 0.0f)), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 6
            VertexFormat(Rotate(glm::vec3(-0.4f, 0.16f, 0.1f), rotationAngle, glm::vec3(-0.45f, 0.16f, 0.0f)), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)),   // 7

            VertexFormat(Rotate(glm::vec3(0.5f, 0.16f, -0.1f), rotationAngle, glm::vec3(0.45f, 0.16f, 0.0f)), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 0
            VertexFormat(Rotate(glm::vec3(0.4f, 0.16f, -0.1f), rotationAngle, glm::vec3(0.45f, 0.16f, 0.0f)), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)),  // 1
            VertexFormat(Rotate(glm::vec3(0.5f, 0.16f, 0.1f), rotationAngle, glm::vec3(0.45f, 0.16f, 0.0f)), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 2
            VertexFormat(Rotate(glm::vec3(0.4f, 0.16f, 0.1f), rotationAngle, glm::vec3(0.45f, 0.16f, 0.0f)), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),   // 3
            VertexFormat(Rotate(glm::vec3(0.5f, 0.16f, -0.1f), rotationAngle, glm::vec3(0.45f, 0.16f, 0.0f)), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)), // 4
            VertexFormat(Rotate(glm::vec3(0.4f, 0.16f, -0.1f), rotationAngle, glm::vec3(0.45f, 0.16f, 0.0f)), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 5
            VertexFormat(Rotate(glm::vec3(0.5f, 0.16f, 0.1f), rotationAngle, glm::vec3(0.45f, 0.16f, 0.0f)), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 6
            VertexFormat(Rotate(glm::vec3(0.4f, 0.16f, 0.1f), rotationAngle, glm::vec3(0.45f, 0.16f, 0.0f)), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)),   // 7

            VertexFormat(Rotate(glm::vec3(0.05f, 0.16f, -0.5f), rotationAngle, glm::vec3(0, 0.16f, -0.4f)), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 0
            VertexFormat(Rotate(glm::vec3(-0.05f, 0.16f, -0.5f), rotationAngle, glm::vec3(0, 0.16f, -0.4f)), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)),  // 1
            VertexFormat(Rotate(glm::vec3(0.05f, 0.16f, -0.3f), rotationAngle, glm::vec3(0, 0.16f, -0.4f)), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 2
            VertexFormat(Rotate(glm::vec3(-0.05f, 0.16f, -0.3f), rotationAngle, glm::vec3(0, 0.16f, -0.4f)), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),   // 3
            VertexFormat(Rotate(glm::vec3(0.05f, 0.16f, -0.5f), rotationAngle, glm::vec3(0, 0.16f, -0.4f)), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)), // 4
            VertexFormat(Rotate(glm::vec3(-0.05f, 0.16f, -0.5f), rotationAngle, glm::vec3(0, 0.16f, -0.4f)), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 5
            VertexFormat(Rotate(glm::vec3(0.05f, 0.16f, -0.3f), rotationAngle, glm::vec3(0, 0.16f, -0.4f)), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 6
            VertexFormat(Rotate(glm::vec3(-0.05f, 0.16f, -0.3f), rotationAngle, glm::vec3(0, 0.16f, -0.4f)), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)),   // 7

            VertexFormat(Rotate(glm::vec3(0.05f, 0.16f, 0.5f), rotationAngle, glm::vec3(0, 0.16f, 0.4f)), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 0
            VertexFormat(Rotate(glm::vec3(-0.05f, 0.16f, 0.5f), rotationAngle, glm::vec3(0, 0.16f, 0.4f)), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)),  // 1
            VertexFormat(Rotate(glm::vec3(0.05f, 0.16f, 0.3f), rotationAngle, glm::vec3(0, 0.16f, 0.4f)), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 2
            VertexFormat(Rotate(glm::vec3(-0.05f, 0.16f, 0.3f), rotationAngle, glm::vec3(0, 0.16f, 0.4f)), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),   // 3
            VertexFormat(Rotate(glm::vec3(0.05f, 0.16f, 0.5f), rotationAngle, glm::vec3(0, 0.16f, 0.4f)), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)), // 4
            VertexFormat(Rotate(glm::vec3(-0.05f, 0.16f, 0.5f), rotationAngle, glm::vec3(0, 0.16f, 0.4f)), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 5
            VertexFormat(Rotate(glm::vec3(0.05f, 0.16f, 0.3f), rotationAngle, glm::vec3(0, 0.16f, 0.4f)), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 6
            VertexFormat(Rotate(glm::vec3(-0.05f, 0.16f, 0.3f), rotationAngle, glm::vec3(0, 0.16f, 0.4f)), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)),   // 7
        };

        std::vector<unsigned int> crossParalelipipedeIndices = {
            0, 1, 2, 1, 3, 2,
            4, 6, 5, 5, 6, 7,
            0, 2, 4, 2, 6, 4,
            1, 5, 3, 3, 5, 7,
            2, 3, 6, 3, 7, 6,
            0, 4, 1, 1, 4, 5,

            8, 9, 10, 9, 11, 10,
            12, 14, 13, 13, 14, 15,
            8, 10, 12, 10, 14, 12,
            9, 13, 11, 11, 13, 15,
            10, 11, 14, 11, 15, 14,
            8, 12, 9, 9, 12, 13,

            16, 17, 18, 17, 19, 18,
            18, 19, 23, 18, 23, 22,
            17, 23, 19, 17, 21, 23,
            22, 23, 20, 23, 21, 20,
            16, 20, 17, 17, 20, 21,
            18, 22, 20, 16, 18, 20,

            24, 25, 26, 25, 27, 26,
            26, 27, 31, 26, 31, 30,
            25, 31, 27, 25, 29, 31,
            30, 31, 28, 31, 29, 28,
            24, 28, 25, 25, 28, 29,
            26, 30, 28, 24, 26, 28,

            32, 33, 34, 33, 35, 34,
            34, 35, 39, 34, 39, 38,
            33, 39, 35, 33, 37, 39,
            38, 39, 36, 39, 37, 36,
            32, 36, 33, 33, 36, 37,
            34, 38, 36, 32, 34, 36,

            40, 41, 42, 41, 43, 42,
            42, 43, 47, 42, 47, 46,
            41, 47, 43, 41, 45, 47,
            46, 47, 44, 47, 45, 44,
            40, 44, 41, 41, 44, 45,
            42, 46, 44, 40, 42, 44,

            48, 49, 50, 49, 51, 50,
            52, 54, 53, 53, 54, 55,
            48, 50, 52, 50, 54, 52,
            49, 53, 51, 51, 53, 55,
            50, 51, 54, 51, 55, 54,
            48, 52, 49, 49, 52, 53,

            56, 57, 58, 57, 59, 58,
            60, 62, 61, 61, 62, 63,
            56, 58, 60, 58, 62, 60,
            57, 61, 59, 59, 61, 63,
            58, 59, 62, 59, 63, 62,
            56, 60, 57, 57, 60, 61,

            64, 65, 66, 65, 67, 66,
            68, 70, 69, 69, 70, 71,
            64, 66, 68, 66, 70, 68,
            65, 69, 67, 67, 69, 71,
            66, 67, 70, 67, 71, 70,
            64, 68, 65, 65, 68, 69,

            72, 73, 74, 73, 75, 74,
            76, 78, 77, 77, 78, 79,
            72, 74, 76, 74, 78, 76,
            73, 77, 75, 75, 77, 79,
            74, 75, 78, 75, 79, 78,
            72, 76, 73, 73, 76, 77



        };

        // Creãm mesh-ul pentru cruce
        CreateMesh("paralelipipede_cruce", crossParalelipipedeVertices, crossParalelipipedeIndices);
    }
    if ((!(window->KeyHold(GLFW_KEY_K))) && (!(window->KeyHold(GLFW_KEY_L)))) {

        if (angleX > 0.0f) {
            angleX -= 8.0f * deltaTimeSeconds;
        }

        if (angleX < 0.0f) {
            angleX += 8.0f * deltaTimeSeconds;
        }

    }



    if (ok1 == 1) {

        {

            vector<VertexFormat> vertices
            {
                VertexFormat(glm::vec3(-0.05f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 0
                VertexFormat(glm::vec3(-0.05f, 0.0f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)),  // 1
                VertexFormat(glm::vec3(-0.05f, 2.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 2
                VertexFormat(glm::vec3(-0.05f, 2.0f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 3

                VertexFormat(glm::vec3(-0.05f, 2.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 4
                VertexFormat(glm::vec3(-0.05f, 2.0f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)),  // 5
                VertexFormat(glm::vec3(2.05f, 2.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 6
                VertexFormat(glm::vec3(2.05f, 2.0f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 7

                VertexFormat(glm::vec3(2.05f, 2.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 8
                VertexFormat(glm::vec3(2.05f, 2.0f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)),  // 9
                VertexFormat(glm::vec3(2.05f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 10
                VertexFormat(glm::vec3(2.05f, 0.0f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 11

                VertexFormat(glm::vec3(2.05f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 12
                VertexFormat(glm::vec3(2.05f, 0.0f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)),  // 13
                VertexFormat(glm::vec3(-0.05f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 14
                VertexFormat(glm::vec3(-0.05f, 0.0f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 15

                VertexFormat(glm::vec3(0.25f, 0.2f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 16
                VertexFormat(glm::vec3(0.25f, 0.2f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)),  // 17
                VertexFormat(glm::vec3(0.25f, 1.8f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 18
                VertexFormat(glm::vec3(0.25f, 1.8f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 19

                VertexFormat(glm::vec3(0.25f, 1.8f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 20
                VertexFormat(glm::vec3(0.25f, 1.8f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)),  // 21
                VertexFormat(glm::vec3(1.75f, 1.8f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 22
                VertexFormat(glm::vec3(1.75f, 1.8f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 23

                VertexFormat(glm::vec3(1.75f, 1.8f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 24
                VertexFormat(glm::vec3(1.75f, 1.8f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)),  // 25
                VertexFormat(glm::vec3(1.75f, 0.2f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 26
                VertexFormat(glm::vec3(1.75f, 0.2f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 27

                VertexFormat(glm::vec3(1.75f, 0.2f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 28
                VertexFormat(glm::vec3(1.75f, 0.2f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)),  // 29
                VertexFormat(glm::vec3(0.25f, 0.2f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 30
                VertexFormat(glm::vec3(0.25f, 0.2f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 31


            };

            vector<unsigned int> indices =
            {
                0, 2, 3,
                0, 3, 1,

                4, 6, 7,
                4, 7, 5,

                8, 10, 11,
                8, 11, 9,

                12, 14, 15,
                12, 15, 13,

                16, 18, 19,
                16, 19, 17,

                20, 22, 23,
                20, 23, 21,

                24, 26, 27,
                24, 27, 25,

                28, 30, 31,
                28, 31, 29
            };

            CreateMesh("cube1", vertices, indices);
        }

        {

            vector<VertexFormat> vertices
            {
                VertexFormat(glm::vec3(-0.05f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,0,0)), // 0
                VertexFormat(glm::vec3(-0.05f, 0.0f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,1,0)),  // 1
                VertexFormat(glm::vec3(-0.05f, 2.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0,0,0)),  // 2
                VertexFormat(glm::vec3(-0.05f, 2.0f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,1,0)), // 3

                VertexFormat(glm::vec3(-0.05f, 2.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,0,0)), // 4
                VertexFormat(glm::vec3(-0.05f, 2.0f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,1,0)),  // 5
                VertexFormat(glm::vec3(2.05f, 2.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0,0,0)),  // 6
                VertexFormat(glm::vec3(2.05f, 2.0f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,1,0)), // 7

                VertexFormat(glm::vec3(2.05f, 2.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,0,0)), // 8
                VertexFormat(glm::vec3(2.05f, 2.0f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,1,0)),  // 9
                VertexFormat(glm::vec3(2.05f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0,0,0)),  // 10
                VertexFormat(glm::vec3(2.05f, 0.0f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,1,0)), // 11

                VertexFormat(glm::vec3(2.05f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,0,0)), // 12
                VertexFormat(glm::vec3(2.05f, 0.0f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,1,0)),  // 13
                VertexFormat(glm::vec3(-0.05f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0,0,0)),  // 14
                VertexFormat(glm::vec3(-0.05f, 0.0f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,1,0)), // 15

                VertexFormat(glm::vec3(0.25f, 0.2f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,0,0)), // 16
                VertexFormat(glm::vec3(0.25f, 0.2f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,1,0)),  // 17
                VertexFormat(glm::vec3(0.25f, 1.8f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0,0,0)),  // 18
                VertexFormat(glm::vec3(0.25f, 1.8f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,1,0)), // 19

                VertexFormat(glm::vec3(0.25f, 1.8f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,0,0)), // 20
                VertexFormat(glm::vec3(0.25f, 1.8f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,1,0)),  // 21
                VertexFormat(glm::vec3(1.75f, 1.8f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0,0,0)),  // 22
                VertexFormat(glm::vec3(1.75f, 1.8f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,1,0)), // 23

                VertexFormat(glm::vec3(1.75f, 1.8f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,0,0)), // 24
                VertexFormat(glm::vec3(1.75f, 1.8f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,1,0)),  // 25
                VertexFormat(glm::vec3(1.75f, 0.2f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0,0,0)),  // 26
                VertexFormat(glm::vec3(1.75f, 0.2f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,1,0)), // 27

                VertexFormat(glm::vec3(1.75f, 0.2f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,0,0)), // 28
                VertexFormat(glm::vec3(1.75f, 0.2f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,1,0)),  // 29
                VertexFormat(glm::vec3(0.25f, 0.2f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0,0,0)),  // 30
                VertexFormat(glm::vec3(0.25f, 0.2f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,1,0)), // 31


            };

            vector<unsigned int> indices =
            {
                0, 2, 3,
                0, 3, 1,

                4, 6, 7,
                4, 7, 5,

                8, 10, 11,
                8, 11, 9,

                12, 14, 15,
                12, 15, 13,

                16, 18, 19,
                16, 19, 17,

                20, 22, 23,
                20, 23, 21,

                24, 26, 27,
                24, 27, 25,

                28, 30, 31,
                28, 31, 29
            };

            CreateMesh("cube2", vertices, indices);



        }

        if (ok2 == 1) {

            {
                vector<VertexFormat> vertices
                {
                    VertexFormat(glm::vec3(-0.05f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 0
                    VertexFormat(glm::vec3(-0.05f, 0.0f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)),  // 1
                    VertexFormat(glm::vec3(-0.05f, 2.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 2
                    VertexFormat(glm::vec3(-0.05f, 2.0f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 3

                    VertexFormat(glm::vec3(-0.05f, 2.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 4
                    VertexFormat(glm::vec3(-0.05f, 2.0f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)),  // 5
                    VertexFormat(glm::vec3(2.05f, 2.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 6
                    VertexFormat(glm::vec3(2.05f, 2.0f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 7

                    VertexFormat(glm::vec3(2.05f, 2.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 8
                    VertexFormat(glm::vec3(2.05f, 2.0f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)),  // 9
                    VertexFormat(glm::vec3(2.05f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 10
                    VertexFormat(glm::vec3(2.05f, 0.0f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 11

                    VertexFormat(glm::vec3(2.05f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 12
                    VertexFormat(glm::vec3(2.05f, 0.0f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)),  // 13
                    VertexFormat(glm::vec3(-0.05f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 14
                    VertexFormat(glm::vec3(-0.05f, 0.0f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 15

                    VertexFormat(glm::vec3(0.25f, 0.2f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 16
                    VertexFormat(glm::vec3(0.25f, 0.2f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)),  // 17
                    VertexFormat(glm::vec3(0.25f, 1.8f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 18
                    VertexFormat(glm::vec3(0.25f, 1.8f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 19

                    VertexFormat(glm::vec3(0.25f, 1.8f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 20
                    VertexFormat(glm::vec3(0.25f, 1.8f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)),  // 21
                    VertexFormat(glm::vec3(1.75f, 1.8f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 22
                    VertexFormat(glm::vec3(1.75f, 1.8f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 23

                    VertexFormat(glm::vec3(1.75f, 1.8f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 24
                    VertexFormat(glm::vec3(1.75f, 1.8f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)),  // 25
                    VertexFormat(glm::vec3(1.75f, 0.2f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 26
                    VertexFormat(glm::vec3(1.75f, 0.2f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 27

                    VertexFormat(glm::vec3(1.75f, 0.2f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 28
                    VertexFormat(glm::vec3(1.75f, 0.2f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)),  // 29
                    VertexFormat(glm::vec3(0.25f, 0.2f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1,0,0)),  // 30
                    VertexFormat(glm::vec3(0.25f, 0.2f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(1,0,0)), // 31


                };

                vector<unsigned int> indices =
                {
                    0, 2, 3,
                    0, 3, 1,

                    4, 6, 7,
                    4, 7, 5,

                    8, 10, 11,
                    8, 11, 9,

                    12, 14, 15,
                    12, 15, 13,

                    16, 18, 19,
                    16, 19, 17,

                    20, 22, 23,
                    20, 23, 21,

                    24, 26, 27,
                    24, 27, 25,

                    28, 30, 31,
                    28, 31, 29
                };

                CreateMesh("cube2", vertices, indices);


            }

            {

                vector<VertexFormat> vertices
                {
                    VertexFormat(glm::vec3(-0.05f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,0,0)), // 0
                    VertexFormat(glm::vec3(-0.05f, 0.0f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,1,0)),  // 1
                    VertexFormat(glm::vec3(-0.05f, 2.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0,0,0)),  // 2
                    VertexFormat(glm::vec3(-0.05f, 2.0f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,1,0)), // 3

                    VertexFormat(glm::vec3(-0.05f, 2.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,0,0)), // 4
                    VertexFormat(glm::vec3(-0.05f, 2.0f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,1,0)),  // 5
                    VertexFormat(glm::vec3(2.05f, 2.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0,0,0)),  // 6
                    VertexFormat(glm::vec3(2.05f, 2.0f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,1,0)), // 7

                    VertexFormat(glm::vec3(2.05f, 2.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,0,0)), // 8
                    VertexFormat(glm::vec3(2.05f, 2.0f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,1,0)),  // 9
                    VertexFormat(glm::vec3(2.05f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0,0,0)),  // 10
                    VertexFormat(glm::vec3(2.05f, 0.0f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,1,0)), // 11

                    VertexFormat(glm::vec3(2.05f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,0,0)), // 12
                    VertexFormat(glm::vec3(2.05f, 0.0f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,1,0)),  // 13
                    VertexFormat(glm::vec3(-0.05f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0,0,0)),  // 14
                    VertexFormat(glm::vec3(-0.05f, 0.0f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,1,0)), // 15

                    VertexFormat(glm::vec3(0.25f, 0.2f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,0,0)), // 16
                    VertexFormat(glm::vec3(0.25f, 0.2f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,1,0)),  // 17
                    VertexFormat(glm::vec3(0.25f, 1.8f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0,0,0)),  // 18
                    VertexFormat(glm::vec3(0.25f, 1.8f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,1,0)), // 19

                    VertexFormat(glm::vec3(0.25f, 1.8f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,0,0)), // 20
                    VertexFormat(glm::vec3(0.25f, 1.8f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,1,0)),  // 21
                    VertexFormat(glm::vec3(1.75f, 1.8f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0,0,0)),  // 22
                    VertexFormat(glm::vec3(1.75f, 1.8f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,1,0)), // 23

                    VertexFormat(glm::vec3(1.75f, 1.8f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,0,0)), // 24
                    VertexFormat(glm::vec3(1.75f, 1.8f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,1,0)),  // 25
                    VertexFormat(glm::vec3(1.75f, 0.2f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0,0,0)),  // 26
                    VertexFormat(glm::vec3(1.75f, 0.2f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,1,0)), // 27

                    VertexFormat(glm::vec3(1.75f, 0.2f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,0,0)), // 28
                    VertexFormat(glm::vec3(1.75f, 0.2f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,1,0)),  // 29
                    VertexFormat(glm::vec3(0.25f, 0.2f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0,0,0)),  // 30
                    VertexFormat(glm::vec3(0.25f, 0.2f, 0.2f), glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3(0,1,0)), // 31


                };

                vector<unsigned int> indices =
                {
                    0, 2, 3,
                    0, 3, 1,

                    4, 6, 7,
                    4, 7, 5,

                    8, 10, 11,
                    8, 11, 9,

                    12, 14, 15,
                    12, 15, 13,

                    16, 18, 19,
                    16, 19, 17,

                    20, 22, 23,
                    20, 23, 21,

                    24, 26, 27,
                    24, 27, 25,

                    28, 30, 31,
                    28, 31, 29
                };

                CreateMesh("cube3", vertices, indices);
            }
        }

    }

    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);

    RenderScene();
    DrawCoordinateSystem();

}


void Tema2::FrameEnd()
{
    DrawCoordinateSystem();
}


void Tema2::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    glUniformMatrix4fv(glGetUniformLocation(shader->program, "Model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));

    glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
    glUniformMatrix4fv(glGetUniformLocation(shader->program, "View"), 1, GL_FALSE, glm::value_ptr(viewMatrix));

    glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
    glUniformMatrix4fv(glGetUniformLocation(shader->program, "Projection"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));



    int color11Location = glGetUniformLocation(shader->program, "color11");


    glUniform1f(glGetUniformLocation(shader->program, "color11"), 0.23f);
    glUniform1f(glGetUniformLocation(shader->program, "color21"), 0.45f);
    glUniform1f(glGetUniformLocation(shader->program, "color31"), 0.25f);


    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see input_controller.h.
 */


void Tema2::OnInputUpdate(float deltaTime, int mods)
{

    float speed = 2.0f;



    if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {

        if (window->KeyHold(GLFW_KEY_N)) {


            if ((dronePosition.x >= a1 - 1.2f && dronePosition.x <= a1 + 1.2f) && (dronePosition.y >= b1 + 0.8f && dronePosition.y <= b1 + 1.8f) && (dronePosition.z <= c1 + 0.60f))
                ok = 0;
            else
                if ((dronePosition.x >= a2 - 1.2f && dronePosition.x <= a2 + 1.2f) && (dronePosition.y >= b2 + 0.8f && dronePosition.y <= b2 + 1.8f) && (dronePosition.z <= c2 + 0.60f))
                    ok = 0;
                else
                    if ((dronePosition.x >= a - 0.3f && dronePosition.x <= a + 0.6f) && dronePosition.z <= c + 0.7f && (dronePosition.y >= b + 0.5f && dronePosition.y <= b + 2.2f))
                        ok = 0;
                    else
                        if ((dronePosition.x >= a4 - 0.3f && dronePosition.x <= a4 + 0.6f) && dronePosition.z <= c4 + 0.7f && (dronePosition.y >= b4 + 0.5f && dronePosition.y <= b4 + 2.2f))
                            ok = 0;
                        else
                            if ((dronePosition.x >= a5 - 0.3f && dronePosition.x <= a5 + 0.6f) && dronePosition.z <= c5 + 0.7f && (dronePosition.y >= b5 + 0.5f && dronePosition.y <= b5 + 2.2f))
                                ok = 0;
                            else
                                if (dronePosition.z <= -2 && (((dronePosition.x >= 1.95f && dronePosition.x <= 2.25f) || (dronePosition.x >= 3.75f && dronePosition.x <= 4.05f) && dronePosition.y >= 2 && dronePosition.y <= 4) || (dronePosition.x >= 1.95f && dronePosition.x <= 4.05f && ((dronePosition.y >= 2.0f && dronePosition.y <= 2.2f) || (dronePosition.y >= 3.8f && dronePosition.y <= 4.0f)))))
                                    ok = 0;
                                else
                                    if (dronePosition.z <= -5 && (((dronePosition.x >= -4.05f && dronePosition.x <= -3.75f) || (dronePosition.x >= -2.25f && dronePosition.x <= -1.95f) && dronePosition.y >= 3 && dronePosition.y <= 5) || (dronePosition.x >= -4.05f && dronePosition.x <= -1.95f && ((dronePosition.y >= 3.0f && dronePosition.y <= 3.2f) || (dronePosition.y >= 4.8f && dronePosition.y <= 5.0f)))))
                                        ok = 0;
                                    else
                                        if (dronePosition.z <= -9 && (((dronePosition.x >= -4.05f && dronePosition.x <= -3.75f) || (dronePosition.x >= -2.25f && dronePosition.x <= -1.95f) && dronePosition.y >= 3 && dronePosition.y <= 5) || (dronePosition.x >= -4.05f && dronePosition.x <= -1.95f && ((dronePosition.y >= 5.0f && dronePosition.y <= 5.2f) || (dronePosition.y >= 6.8f && dronePosition.y <= 7.0f)))))
                                            ok = 0;
                                        else
                                            ok = 1;

            if (dronePosition.z >= -4 && dronePosition.z <= -3.1f && (dronePosition.x >= 2.25f && dronePosition.x <= 3.75f) && (dronePosition.y >= 2.2f && dronePosition.y <= 3.8f) && aux > dronePosition.z) {
                ok1 = 1;
            }

            if (dronePosition.z <= -6.1f && (dronePosition.x >= -3.75f && dronePosition.x <= -2.25f) && (dronePosition.y >= 3.2f && dronePosition.y <= 4.8f) && aux > dronePosition.z) {
                ok2 = 1;
            }

            //&& (((dronePosition.x < 0.7f) || (dronePosition.x > 1.6f)) || (dronePosition.z > -4.0f)) && ((dronePosition.z == -3) && ((dronePosition.x < 1.95f) || (dronePosition.x > 4.05f)))) { // Mi?care în sus
            if (ok == 1) {
                aux = dronePosition.z;
                dronePosition.z -= speed * deltaTime;

            }
        }
        if (window->KeyHold(GLFW_KEY_M)) {
            aux = dronePosition.z;
            dronePosition.z += speed * deltaTime;
            nr = 1;
        }
        if (window->KeyHold(GLFW_KEY_LEFT)) { // Mi?care la stânga
            dronePosition.x -= speed * deltaTime;
            nr = 1;
        }
        if (window->KeyHold(GLFW_KEY_RIGHT)) { // Mi?care la dreapta
            dronePosition.x += speed * deltaTime;
            nr = 1;
        }

        if (window->KeyHold(GLFW_KEY_DOWN)) {
            if (dronePosition.y > t) {
                dronePosition.y -= speed * deltaTime;
                nr = 1;
            }
        }

        if (window->KeyHold(GLFW_KEY_UP)) {
            dronePosition.y += speed * deltaTime;
            nr = 1;
        }

        if (window->KeyHold(GLFW_KEY_K)) {
            if (angleX < 15.0f) {
                angleX += 1.0f;
            }
        }


        if (window->KeyHold(GLFW_KEY_L)) {
            if (angleX > -15.0f) {
                angleX -= 1.0f;
            }
        }


        if (window->KeyHold(GLFW_KEY_1)) {
            pitch += 120 * deltaTime;
        }

        if (window->KeyHold(GLFW_KEY_2)) {
            pitch -= 120 * deltaTime;
        }
        if (window->KeyHold(GLFW_KEY_3)) {
            yaw += 120 * deltaTime;
        }
        if (window->KeyHold(GLFW_KEY_4)) {
            yaw -= 120 * deltaTime;
        }
        if (window->KeyHold(GLFW_KEY_5)) {
            roll += 120 * deltaTime;
        }

        if (window->KeyHold(GLFW_KEY_6)) {
            roll -= 120 * deltaTime;
        }

        if (window->KeyHold(GLFW_KEY_7)) {
            thrustMagnitude += 0.01f;
            velocity += thrustDirection * thrustMagnitude * deltaTime;
            dronePosition += velocity * deltaTime;
        }

        if (window->KeyHold(GLFW_KEY_8)) {
            thrustMagnitude += 0.01f;
            velocity += thrustDirection * thrustMagnitude * deltaTime;
            dronePosition -= velocity * deltaTime;
        }
        if (!(window->KeyHold(GLFW_KEY_7))) {
            thrustDirection = glm::vec3(0, 1, 0);
            //thrustMagnitude = 1.0f;
            velocity = glm::vec3(0, 0, 0);
        }
    }



}


void Tema2::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema2::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema2::OnWindowResize(int width, int height)
{
}