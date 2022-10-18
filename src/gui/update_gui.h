#pragma once

namespace zar
{
	class update_gui final : public i_gui
	{
	public:
		update_gui()
			= default;

		void start() override
		{
			i_gui::start();
		}

		void update() override
		{
			i_gui::update();
		}

		void render(file_data*& file, server_data*& server, flag_data*& flag) override
		{
			i_gui::render(file, server, flag);
			begin("Update");
			{
				ImGui::Separator();
				ImGui::Text("--- ACTUALIZAR ---");
				ImGui::Separator();
				

			}
			end();
		}

	private:

	};
}
