#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_stdlib.h"

namespace zar
{
	class app {
	public:

		static app* instance()
		{
			static app instance;
			return &instance;
		}

		void task(file_data*& file, server_data*& server, flag_data*& flag)
		{
			spdlog::info("welcome");
			init();

			while (!glfwWindowShouldClose(window))
			{
				ImGui_ImplOpenGL3_NewFrame();
				ImGui_ImplGlfw_NewFrame();
				ImGui::NewFrame();

				glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT);

				dock_space();

				ImGui::Begin("Insert");
				{
					ImGui::Separator();
					ImGui::Text("--- INSERTAR ---");
					ImGui::Separator();
					ImGui::Text("FILE");
					ImGui::Separator();
					//ImGui::NewLine();

					ImGui::Text("link: %s", file->url);
					ImGui::Text("name: %s", file->name.c_str());
					ImGui::Text("size: %i kb", file->size);
					ImGui::Separator();

					ImGui::Text("SERVER");
					ImGui::Separator();
					//ImGui::NewLine();

					ImGui::InputText("url", server->url, IM_ARRAYSIZE(server->url));
					ImGui::InputText("user", server->user, IM_ARRAYSIZE(server->user));
					ImGui::InputText("password", server->pass, IM_ARRAYSIZE(server->pass));
					ImGui::InputText("db", server->db, IM_ARRAYSIZE(server->db));
					ImGui::Separator();

					if (ImGui::Button("PROCESS"))
					{
						flag->is_update = true;
					}
				}
				ImGui::End();
				ImGui::Begin("Update");
				{
					ImGui::Separator();
					ImGui::Text("--- ACTUALIZAR ---");
					ImGui::Separator();
				}
				ImGui::End();

				ImGui::Begin("Query");
				{
					ImGui::Separator();
					ImGui::Text("--- CONSULTAR ---");
					ImGui::Separator();
				}
				ImGui::End();

				//ImGui::ShowDemoWindow();

				ImGui::Render();
				ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

				ImGuiIO& io = ImGui::GetIO(); (void)io;

				if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
				{
					GLFWwindow* backup_current_context = glfwGetCurrentContext();
					ImGui::UpdatePlatformWindows();
					ImGui::RenderPlatformWindowsDefault();
					glfwMakeContextCurrent(backup_current_context);
				}

				glfwSwapBuffers(window);
				glfwPollEvents();
			}

		}

	private:

		void init()
		{
			if (glfwInit() == GL_FALSE) return;

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			window = glfwCreateWindow(800, 600, "RUC", NULL, NULL);

			if (!window) return;
			glfwMakeContextCurrent(window);

			if (GLenum err = glewInit()) return;
			const char* glsl_version = "#version 330";

			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO(); (void)io;

			io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
			io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
			io.ConfigFlags |= ImGuiWindowFlags_AlwaysHorizontalScrollbar;

			ImGui::StyleColorsDark();

			ImGuiStyle& style = ImGui::GetStyle();
			if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				style.WindowRounding = 0.0f;
				style.Colors[ImGuiCol_WindowBg].w = 1.0f;
			}

			ImGuiWindowFlags window_flags = 0;
			ImGui_ImplGlfw_InitForOpenGL(window, true);
			ImGui_ImplOpenGL3_Init(glsl_version);
		}

		void dock_space()
		{
			static bool opt_fullscreen = true;
			static bool opt_padding = false;
			static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

			ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
			if (opt_fullscreen)
			{
				ImGuiViewport* viewport = ImGui::GetMainViewport();
				ImGui::SetNextWindowPos(viewport->WorkPos);
				ImGui::SetNextWindowSize(viewport->WorkSize);
				ImGui::SetNextWindowViewport(viewport->ID);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
				window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
				window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
			}
			else
			{
				dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
			}

			if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
				window_flags |= ImGuiWindowFlags_NoBackground;

			if (!opt_padding)
				ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
			ImGui::Begin("DockSpace Demo", NULL, window_flags);
			if (!opt_padding)
				ImGui::PopStyleVar();

			if (opt_fullscreen)
				ImGui::PopStyleVar(2);

			// DockSpace
			ImGuiIO& io = ImGui::GetIO();
			if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
			{
				ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
				ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
			}
			else
			{
				ImGuiIO& io = ImGui::GetIO();
				ImGui::Text("ERROR: Docking is not enabled! See Demo > Configuration.");
				ImGui::Text("Set io.ConfigFlags |= ImGuiConfigFlags_DockingEnable in your code, or ");
				ImGui::SameLine(0.0f, 0.0f);
				if (ImGui::SmallButton("click here"))
					io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
			}

			if (ImGui::BeginMenuBar())
			{
				if (ImGui::BeginMenu("Options"))
				{
					//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
					ImGui::MenuItem("Padding", NULL, &opt_padding);
					//ImGui::Separator();
					ImGui::EndMenu();
				}

				ImGui::EndMenuBar();
			}
			ImGui::End();
		}

		GLFWwindow* window;

	};
}
