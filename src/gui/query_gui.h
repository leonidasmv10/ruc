#pragma once

namespace zar
{
	class query_gui final : public i_gui
	{
	public:
		query_gui()
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
			begin("Query");
			{
				ImGui::Separator();
				ImGui::Text("--- QUERY ---");
				ImGui::Separator();

				static char ruc[100];

				ImGui::InputText("RUC", ruc, IM_ARRAYSIZE(ruc));
				ImGui::NewLine();

				static ImGuiTableFlags flags = ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_RowBg | ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable;

				if (ImGui::BeginTable("table1", 3, flags))
				{
					ImGui::TableSetupColumn("RAZON SOCIAL", ImGuiTableColumnFlags_WidthFixed);
					ImGui::TableSetupColumn("ESTADO CONTRIBUYENTE", ImGuiTableColumnFlags_WidthStretch);
					ImGui::TableSetupColumn("CONIDICION DOMICILIO", ImGuiTableColumnFlags_WidthStretch);
					ImGui::TableHeadersRow();
					for (int row = 0; row < 9; row++)
					{
						ImGui::TableNextRow(ImGuiTableColumnFlags_WidthFixed);
						for (int column = 0; column < 3; column++)
						{
							ImGui::TableSetColumnIndex(column);
							ImGui::Text("%s %d,%d", (column == 2) ? "Stretch" : "Fixed", column, row);
						}
					}
					ImGui::EndTable();
				}
				if (ImGui::BeginTable("table2", 6, flags))
				{
					ImGui::TableSetupColumn("UBIGEO", ImGuiTableColumnFlags_WidthFixed);
					ImGui::TableSetupColumn("BBB", ImGuiTableColumnFlags_WidthFixed);
					ImGui::TableSetupColumn("CCC", ImGuiTableColumnFlags_WidthFixed | ImGuiTableColumnFlags_DefaultHide);
					ImGui::TableSetupColumn("DDD", ImGuiTableColumnFlags_WidthStretch);
					ImGui::TableSetupColumn("EEE", ImGuiTableColumnFlags_WidthStretch);
					ImGui::TableSetupColumn("FFF", ImGuiTableColumnFlags_WidthStretch | ImGuiTableColumnFlags_DefaultHide);
					ImGui::TableHeadersRow();
					for (int row = 0; row < 5; row++)
					{
						ImGui::TableNextRow();
						for (int column = 0; column < 6; column++)
						{
							ImGui::TableSetColumnIndex(column);
							ImGui::Text("%s %d,%d", (column >= 3) ? "Stretch" : "Fixed", column, row);
						}
					}
					ImGui::EndTable();
				}









				if (ImGui::Button("PROCESS"))
				{
					flag->is_process_query = true;
				}
			}
			end();

		}

	private:

	};
}
