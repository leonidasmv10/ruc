#include "../config.h"

#include <string>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <spdlog\spdlog.h>
#include "libzippp.h"

#include <fstream>
#include <chrono>
#include <ctime> 
#include <thread>
#include <vector>
#include <unordered_map>

#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime> 
#include <thread>
#include <mysql/jdbc.h>
#include <vector>
#include <unordered_map>
#include <stdio.h>
#include <curl/curl.h>
#include <future>

using namespace libzippp;
using namespace std;

GLFWwindow* window;
bool is_zip = false;

void DockSpace();

size_t write_data(void* ptr, size_t size, size_t nmemb, FILE* stream) {
	size_t written = fwrite(ptr, size, nmemb, stream);
	return written;
}


void download_zip();

void loop();

std::thread hilo_1(loop);
//std::thread hilo_2(download_zip);

std::thread::id main_thread_id = std::this_thread::get_id();

int main()
{
	if (main_thread_id == std::this_thread::get_id())
		std::cout << "This is the main thread.\n";
	else
		std::cout << "This is not the main thread.\n";

	std::future<void> fut{};
	if (true)  // 0 just for testing; your condition would come here
	{
		fut = std::async(std::launch::async, download_zip);
	}

	if (fut.valid())
	{
		fut.get();
		spdlog::error("Termina sync");

	}

	hilo_1.join();
	//hilo_2.join();
	spdlog::info("LOSE");

	return 0;
}

void DockSpace()
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

void download_zip()
{
	while (true)
	{
		if (is_zip)
		{
			spdlog::info("init download");
			CURL* curl;
			FILE* fp;
			CURLcode res;
			char* url_ruc = "http://www2.sunat.gob.pe/padron_reducido_ruc.zip";
			char outfilename[FILENAME_MAX] = "ruc.zip";
			curl = curl_easy_init();
			if (curl) {
				fp = fopen(outfilename, "wb");
				curl_easy_setopt(curl, CURLOPT_URL, url_ruc);
				curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
				curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
				res = curl_easy_perform(curl);
				/* always cleanup */
				curl_easy_cleanup(curl);
				fclose(fp);
				spdlog::info("{} dowload succes", url_ruc);
			}
			is_zip = false;
			break;
		}
	}

}

void loop()
{
	spdlog::info("Loop");

	if (glfwInit() == GL_FALSE) return;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(800, 600, "Programa", NULL, NULL);
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

	while (!glfwWindowShouldClose(window))
	{

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		DockSpace();


		ImGui::Begin("Data");
		{
			if (ImGui::Button("Descargar zip"))
			{
				is_zip = true;

			}
		}
		ImGui::End();



		ImGui::ShowDemoWindow();

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



//#include <iostream>  // cout
//#include <future>  // async
//#include <thread>
//
//void f() { for (auto i{ 0 }; i < 10000; ++i) std::cout << "a\n"; }
//void g() { for (auto i{ 0 }; i < 10000; ++i) std::cout << "b\n"; }
//
//int main()
//{
//    std::future<void> fut{};
//    if (true)  // 0 just for testing; your condition would come here
//    {
//        fut = std::async(std::launch::async, f);
//    }
//    std::thread t_g(g);
//    t_g.join();
//    if (fut.valid())
//    {
//        fut.get();
//        std::cout << "async";
//    }
//}
