#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "glm/fwd.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/constants.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <cmath>
#include <iostream>

#include "core/shader.h"
#include "core/IK.h"
#include "core/hexapod.h"

#include <time.h>

glm::vec3 BezierCurve(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, float t)
{
    return pow((1 - t), 2.0f) * p0 + 2 * (1 - t) * t * p1 + pow(t, 2.0f) * p2;
}

float normalize(float value, float min, float max)
{
    return ((value - min) / (max - min));
}

float lerp(float start, float end, float value)
{
    return (start + (end - start) * value);
}

void walk(Hexapod& hexapod)
{
    static clock_t last_time = clock();
    static float timer = 0;
    timer += (float)(clock() - last_time) / CLOCKS_PER_SEC;
    
    static float height = 0;
    ImGui::DragFloat("Height", &height);
    ImGui::Text("%f", timer);
    
    hexapod.SetDirection({0, 0, 1});
    for(int i = 0; i < hexapod.legs.size(); i++)
    {

        Leg leg = hexapod.legs[i];
        float localTime =  timer + ((i % 2 == 0) ? 0.0f : 1.0f);
        glm::vec3 endEffector = (glm::normalize(leg.base) * 10.0f);

        if(localTime > 2.0f) { localTime -= 2; }
        
        if(localTime < 1.0)
        {
            endEffector += hexapod.GetDirection() * ( 10.0f / 2.0f) - hexapod.GetDirection() * (10.0f * localTime);
        }else if(localTime >= 1 && localTime <= 2)
        {
            endEffector = BezierCurve(endEffector - hexapod.GetDirection() * (10.0f / 2.0f),
                                        endEffector + glm::vec3(0, 5, 0),
                                        endEffector + hexapod.GetDirection() * (10.0f /2.0f),
                                        localTime - 1);
        }
        
        auto thetas = CalculateInverseKinematic(endEffector.x, endEffector.y + height, -endEffector.z, 10.0, 16.0);
        leg.Rotate(thetas.theta_1, thetas.theta_2, thetas.theta_3);

        if(timer > 2) { timer = 0; }
    }

    last_time = clock();
}

void better_walk_cycle(Hexapod& hexapod)
{
    static clock_t last_time = clock();
    static float timer = 0.0;
    timer += (float)(clock() - last_time) / CLOCKS_PER_SEC;

    static float height = 0;
    ImGui::DragFloat("Height", &height);
    ImGui::Text("%f", timer);

    hexapod.SetDirection({0, 0, 1});

    for(int i = 0; i < hexapod.legs.size(); i++)
    {
        Leg leg = hexapod.legs[i];
        float localTime = timer + ((i % 2 == 0) ? 0.0f : 1.0f);
        glm::vec3 endEffector = (glm::normalize(leg.base) * 10.0f);
        if(localTime > 2.0f) { localTime -= 2; }
        if(localTime < 1.0)
        {
            endEffector += hexapod.GetDirection() * (10.0f / 2.0f) - hexapod.GetDirection() * (10.0f * localTime * localTime);
        }else if(localTime >= 1 && localTime <= 2)
        {
            endEffector = BezierCurve(endEffector - hexapod.GetDirection() * (10.0f / 2.0f),
                                        endEffector + glm::vec3(0, 15, 0),
                                        endEffector + hexapod.GetDirection() * (10.0f / 2.0f),
                                        localTime - 1);
        }

        auto thetas = CalculateInverseKinematic(endEffector.x, endEffector.y + height, -endEffector.z, 10.0, 16.0);
        leg.Rotate(thetas.theta_1, thetas.theta_2, thetas.theta_3);

        if(timer > 2) {timer = 0;}
    }

    last_time = clock();
}

void improved_walk_cycle(Hexapod& hexapod)
{
    static clock_t last_time = clock();
    static float global_timer = 0.0;
    
    global_timer += (float)(clock() - last_time) / CLOCKS_PER_SEC;

    static float height = 17.0;

    ImGui::DragFloat("Height", &height);
    ImGui::Text("%f", global_timer);

    static float speed = 0.0;
    ImGui::DragFloat("Speed", &speed);
    
    hexapod.SetDirection({0, 0, 1});

    static float exponent = 2.0;
    ImGui::DragFloat("Exponent", &exponent);

    float total_time = 2.0 - (2.0 * std::min(speed, 1.0f));


    for(int i = 0; i < hexapod.legs.size(); i++)
    {
        Leg& leg = hexapod.legs[i];

        glm::vec3 end_effector = (glm::normalize(leg.base) * 10.0f);

        float local_time = global_timer + ((i % 2 == 0) ? (total_time / 2.0f) : 0.0f);
        
        glm::vec3 dir = hexapod.GetDirection();


        if(local_time >= total_time) { local_time -= total_time; }
        
        float step_size = 10.0;
        if(local_time < (total_time / 2.0))
        {
            end_effector += dir * (step_size / 2.0f) - dir * step_size * (pow(local_time, exponent) / (pow((total_time / 2), exponent)));

        }
        else
        {
          end_effector = BezierCurve(end_effector - dir * (step_size / 2.0f),
                                        end_effector + glm::vec3(0, 7, 0),
                                        end_effector + dir * (step_size / 2.0f),
                                        normalize(local_time, (total_time / 2.0), total_time));
        }
        auto thetas = CalculateInverseKinematic(end_effector.x, end_effector.y - height, -end_effector.z, 10.0, 16.0);
        leg.Rotate(thetas.theta_1, thetas.theta_2, thetas.theta_3);
    }

    if(global_timer >= total_time){global_timer = 0.0;}

    last_time = clock();
}


int main()
{
    GLFWwindow* window;

    if(!glfwInit())
        return -1;  

    window = glfwCreateWindow(960, 960, "Hello, World", NULL, NULL);

    if(!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if(glewInit() != GLEW_OK)
        std::cout << "Error!";

    std::cout << glGetString(GL_VERSION) << std::endl;
    
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
    ImGui::StyleColorsDark();

    Hexapod hexapod({0, 10, 0});
    hexapod.SetOrigo({0, 10, 0});
    hexapod.SetWalkCycle(Hexapod::WalkCycle::Default, better_walk_cycle);
    hexapod.SetWalkCycle(Hexapod::WalkCycle::Improved, improved_walk_cycle);

    Shader shader("../../res/shaders/basic.glsl");
    shader.Bind();

    // 3D
    //glm::mat4 proj = glm::ortho(-40.0f, 40.0f, -40.0f, 40.0f, -1.0f, 1.0f);
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), 1.0f, 0.0f, 100.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -100));
    glm::mat4 mvp = proj * view;
    
    shader.SetUniformMat4f("u_MVP", mvp);

    Line lines[20];

    for(int i = 0; i < 20; i += 2)
    {
        lines[i] = {{-100,0, (-50 + (10 * (i / 2.0)))},{100,0,-50 + (10 * (i / 2.0))}};
        lines[i+1] = {{(-50 + (10 * (i / 2.0))), 0, -100},{(-50 + (10 * (i / 2.0))), 0, 100}};
    }

    Shader gridShader("../../res/shaders/grid.glsl");

    
    float zoom = 0;
    float direction[3] = {0,0,1};
    float position[3]={16,10,0};
    float rotations[3] = {0,25,0};
    int display_w = 0, display_h = 0;
    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
        
        {
            ImGui::DragFloat("Z Rotation", rotations);
            ImGui::DragFloat("X Rotation", &rotations[1]);
            ImGui::DragFloat("Zoom", &zoom);
        }
        
        mvp = proj * glm::rotate(view, glm::radians(rotations[1]), glm::vec3(1, 0, 0));
        mvp = glm::rotate(mvp, glm::radians(rotations[0]), glm::vec3(0, 1, 0));

        hexapod.walkCycles[Hexapod::WalkCycle::Improved](hexapod);
        
        gridShader.SetUniformMat4f("u_MVP", mvp);
        gridShader.Bind();
        for(auto line : lines){line.Draw();}
        
        shader.SetUniformMat4f("u_MVP", mvp);
        shader.Bind();
        hexapod.Draw();

        // MAIN CODE

        ImGui::Render();
        glfwGetFramebufferSize(window, &display_w, &display_h);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
