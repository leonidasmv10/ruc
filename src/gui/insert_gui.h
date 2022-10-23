#pragma once

namespace zar
{
	class insert_gui final : public i_gui
	{
	public:
		insert_gui()
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

			begin("Insert");
			{
				ImGui::Separator();
				ImGui::Text("--- INSERT ---");
				ImGui::Separator();

			

				if (ImGui::Button("PROCESS"))
				{
					flag->is_process_insert = true;
				}
			}
			end();

		}

	private:

	};
}
