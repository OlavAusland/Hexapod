#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/constants.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <iostream>

#include "core/shader.h"
#include "core/IK.h"

class Leg
{
public:
    glm::vec3 base;

    glm::vec3 femur;
    glm::vec3 tibia;
    float* vertices;
    

    Leg(glm::vec3 base, float l1, float l2)
    {
        this->base = base;
        this->femur = glm::vec3(l1, 0, 0);
        this->tibia = glm::vec3(l2, 0, 0);
        
        vertices = (float*)malloc(sizeof(float) * 8);
        vertices[0] = base.x; vertices[1] = base.y;
        vertices[2] = base.x + femur.x; vertices[3] = base.y + femur.y;
        vertices[4] = base.x + femur.x; vertices[5] = base.y + femur.y;
        vertices[6] = base.x + femur.x + tibia.x; vertices[7] = base.y + femur.y + tibia.y;
    }

    void Rotate(float z, float femur, float tibia)
    {
        glm::mat4 zRotMat(1.0f);
        glm::mat4 femurRotMat(1.0f);
        glm::mat4 tibiaRotMat(1.0f);
    
        //zRotMat = glm::rotate(zRotMat, z, glm::vec3(0, 1, 0));
        femurRotMat = glm::rotate(femurRotMat, femur, glm::vec3(0, 0, 1));
        tibiaRotMat = glm::rotate(tibiaRotMat, tibia, glm::vec3(0, 0, 1));
        
        
        glm::vec3 tmp_base = zRotMat * glm::vec4(this->base, 1.0f);
        glm::vec3 tmp_femur = femurRotMat * zRotMat * glm::vec4(this->femur, 1.0f);
        glm::vec3 tmp_tibia = tibiaRotMat * femurRotMat * zRotMat* glm::vec4(this->tibia, 1.0f);

        //this->femur = femurRotMat * glm::vec4(this->femur, 1.0f);
        //this->tibia = tibiaRotMat * glm::vec4(this->tibia, 1.0f);
        
        vertices[0] = base.x; vertices[1] = base.y;
        vertices[2] = base.x + tmp_femur.x; vertices[3] = base.y + tmp_femur.y;
        vertices[4] = base.x + tmp_femur.x; vertices[5] = base.y + tmp_femur.y;
        vertices[6] = base.x + tmp_femur.x + tmp_tibia.x; vertices[7] = base.y + tmp_femur.y + tmp_tibia.y;
    }
};

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

    float vertices[] = {
        0.0f,  0.0f,
        2.0f,  2.0f,
        2.0f,  2.0f,
        4.0f,  2.0f
    };
    Leg leg(glm::vec3(0.0, 0.0, 0.0), 10.0, 5.0);

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8,leg.vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
    
  
    Shader shader("../../res/shaders/basic.glsl");
    shader.Bind();

    // 3D
    //glm::mat4 proj = glm::ortho(-40.0f, 40.0f, -40.0f, 40.0f, -1.0f, 1.0f);
    glm::mat4 proj = glm::perspective(glm::radians(35.0f), 1.0f, 0.0f, 100.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -100));
    glm::mat4 mvp = proj * view;
    
    shader.SetUniformMat4f("u_MVP", mvp);
    
    float zRot = 0;
    float position[3]={0,0,0};
    int display_w = 0, display_h = 0;
    while(!glfwWindowShouldClose(window))
    {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
        

        {
            if(ImGui::DragFloat3("End Effector", position))
            {

                auto angles = CalculateInverseKinematic(position[0], position[1], position[2], 10, 5.0);
                std::cout << "(" << angles.theta_1 << ", " << angles.theta_2 << ", " << angles.theta_3 << ")\n";
                //leg.Rotate(0, angles.theta_2, angles.theta_3);
                leg.Rotate(angles.theta_1, angles.theta_2, angles.theta_3);
            }

            if(ImGui::DragFloat("Z Rotation", &zRot))
            {
                mvp = proj * glm::rotate(view, glm::radians(zRot), glm::vec3(0, 1, 0));
;
                shader.SetUniformMat4f("u_MVP", mvp);
            }
        }


        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8,leg.vertices, GL_STATIC_DRAW);

        // MAIN CODE
        //ImGui::Text("Application Average");
        
        glDrawArrays(GL_LINES, 0, 4);

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
