#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_stdlib.h"

namespace zar
{
    class i_gui
    {
    public:
        virtual ~i_gui() = default;
        i_gui() = default;

        virtual void start()
        {
        }

        virtual void update()
        {
        }

        virtual void render(file_data*& file, server_data*& server, flag_data*& flag)
        {
        }
        
    protected:
        void begin(const char* title, const ImGuiWindowFlags flags = 0)
        {
            ImGui::Begin(title, NULL, flags);
        }
        
        void end()
        {
            ImGui::End();
        }
    };
}
