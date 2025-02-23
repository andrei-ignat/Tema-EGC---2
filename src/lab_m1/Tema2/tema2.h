#pragma once

#include <vector>

#include "components/simple_scene.h"


namespace m1
{
    class Tema2 : public gfxc::SimpleScene
    {
    public:
        struct ViewportArea
        {
            ViewportArea() : x(0), y(0), width(1), height(1) {}
            ViewportArea(int x, int y, int width, int height)
                : x(x), y(y), width(width), height(height) {}
            int x;
            int y;
            int width;
            int height;
        };
        Tema2();
        ~Tema2();

        void Init() override;

        Mesh* CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices);

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;
        void RenderScene();

        void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix);

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        glm::vec3 dronePosition = glm::vec3(0, 2, 0);
        glm::vec3 initialPos = glm::vec3(0, 1, 0);
        glm::vec3 dronePosition1 = glm::vec3(0.30f, 1.10f, -0.30f);
        glm::vec3 dronePosition2 = glm::vec3(0.30f, 1.10f, 0.30f);
        glm::vec3 dronePosition3 = glm::vec3(-0.30f, 1.10f, 0.30f);
        glm::vec3 dronePosition4 = glm::vec3(-0.33f, 1.10f, -0.32f);
        float rotationAngle = 0.0f;

        float pitch = 0.0f;
        float roll = 0.0f;
        float yaw = 0.0f;
        glm::vec3 thrustDirection = glm::vec3(0, 1, 0);  // Direc?ia de propulsie pe axa Y
        float thrustMagnitude = 1.0f;
        glm::vec3 velocity = glm::vec3(0, 0, 0);
        float angleX = 0.0f;
        float angleY = 0.0f;
        float angleZ = 0.0f;
        int ok = 1;
        int ok1 = 0;
        int ok2 = 0;
        float aux;
        float angle;

        float direction1 = 0.3f;
        glm::vec3 direction;

        int a, b, c;
        int d;
        int a1, b1, c1;
        int d1;
        int a2, b2, c2;
        int d2;

        int a4, b4, c4, d4;
        int a5, b5, c5, d5;


        glm::vec3 dronePositionmove = glm::vec3(-0.30f, 1.22f, -0.32f);
        glm::vec3 dronePositionmove1 = glm::vec3(-0.30f, 1.22f, 0.36f);
        glm::vec3 dronePositionmove2 = glm::vec3(0.30f, 1.22f, 0.36f);
        glm::vec3 dronePositionmove3 = glm::vec3(0.30f, 1.22f, -0.32f);
        float t;
        glm::vec3 color_low = glm::vec3(0.0f, 1.0f, 0.0f);  // Verde pentru altitudini joase
        glm::vec3 color_high = glm::vec3(1.0f, 0.0f, 0.0f); // Albastru pentru altitudini mari
        ViewportArea miniViewportArea;
        int nr = 1;


    };
}   // namespace m1
