#pragma once

namespace zar
{
	class setting_gui final : public i_gui
	{
	public:
		setting_gui()
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

			begin("Setting");
			{
				ImGui::Separator();
				ImGui::Text("--- SETTING ---");
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

				ImGui::InputText("url", server->url, IM_ARRAYSIZE(server->url));
				ImGui::InputText("user", server->user, IM_ARRAYSIZE(server->user));
				ImGui::InputText("password", server->pass, IM_ARRAYSIZE(server->pass));
				ImGui::InputText("db", server->db, IM_ARRAYSIZE(server->db));
				ImGui::Separator();

				ImGui::NewLine();
				if (ImGui::Button("CREATE TABLE"))
				{
					mysql::instance()->connect(*server);
					empresa_dao::instance()->create_table();
					spdlog::info("CREATE TABLE SUCCESS");
				}

				ImGui::SameLine();

				if (ImGui::Button("DROP TABLE"))
				{
					mysql::instance()->connect(*server);
					empresa_dao::instance()->drop_table();
					spdlog::info("DROP TABLE SUCCESS");
				}

			}
			end();

		}

	private:

	};
}
