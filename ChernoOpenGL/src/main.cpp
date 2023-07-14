#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


int main() {
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(960, 540, "Hello World", nullptr, nullptr);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);


    if (glewInit() != GLEW_OK) {
        std::cout << "Unable to initialize GLEW\n";
        return -1;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    {
        float positions[] = {
                100.0f, 100.0f, 0.0f, 0.0f,   // 0
                200.0f, 100.0f, 1.0f, 0.0f,     // 1
                200.0f, 200.0f, 1.0f, 1.0f,   // 2
                100.0f, 200.0f, 0.0f, 1.0f // 3
        };
        //索引缓冲区
        unsigned int indices[] = {
                0, 1, 2,
                2, 3, 0
        };

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        VertexArray va;
        VertexBuffer vb(positions, sizeof(positions));
        VertexBufferLayout layout;
        layout.Push<float>(2); //3 floats per position
        layout.Push<float>(2); //3 floats per position
        va.AddBuffer(vb, layout);

        IndexBuffer ib(indices, 6);

        //创建正交矩阵
        glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
        // 创建一个平移矩阵
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0));

        Shader shader("res/shaders/Basic.shader");
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);


        Texture texture("res/textures/ChernoLogo.png");
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0);


        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        shader.Unbind();

        Renderer renderer;

        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.FontGlobalScale = 2.5f;

        const char *glsl_version = "#version 150";
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(glsl_version);

        ImGui::StyleColorsDark();


        glm::vec3 translation(200, 200, 0);

        float r = 0.0f;
        float increment = 0.05f;
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window)) {

            renderer.Clear();

            // Start the Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            glm::mat4 model = glm::translate(glm::mat4(1.0f),translation);
            glm::mat4 mvp = proj * view * model;



            shader.Bind();
            shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
            shader.SetUniformMat4f("u_MVP", mvp);

            //顶点数组。索引缓冲区。着色器
            renderer.Draw(va, ib, shader);

            if (r > 1.0f) {
                increment = -0.05f;
            } else if (r < 0.0f) {
                increment = 0.05f;
            }

            r += increment;


            {


                ImGui::SliderFloat3("translation", &translation.x, 0.0f, 960.0f);


                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            }


            ImGui::Render();

            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}