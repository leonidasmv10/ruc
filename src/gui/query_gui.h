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
				static ruc_data data;

				ImGui::Separator();
				ImGui::Text("--- QUERY ---");
				ImGui::Separator();

				static char ruc[12] = "10781991061";

				ImGui::InputText("RUC", ruc, IM_ARRAYSIZE(ruc));
				ImGui::SameLine();

				if (ImGui::Button("FIND"))
				{
					flag->is_process_query = true;
					mysql::instance()->connect(*server);
					data = empresa_dao::instance()->query(ruc);
					data.print();
				}

				ImGui::NewLine();

				static ImGuiTableFlags flags = ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_RowBg | ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable;

				if (ImGui::BeginTable("table1", 14, flags))
				{
					ImGui::TableSetupColumn("RAZON SOCIAL", ImGuiTableColumnFlags_WidthFixed);
					ImGui::TableSetupColumn("ESTADO CONTRIBUYENTE", ImGuiTableColumnFlags_WidthStretch);
					ImGui::TableSetupColumn("CONDICION DOMICILIO", ImGuiTableColumnFlags_WidthStretch);
					ImGui::TableSetupColumn("UBIGEO", ImGuiTableColumnFlags_WidthStretch);
					ImGui::TableSetupColumn("TIPO VIA", ImGuiTableColumnFlags_WidthStretch);
					ImGui::TableSetupColumn("NOMBRE VIA", ImGuiTableColumnFlags_WidthStretch);
					ImGui::TableSetupColumn("CODIGO ZONA", ImGuiTableColumnFlags_WidthStretch);
					ImGui::TableSetupColumn("TIPO ZONA", ImGuiTableColumnFlags_WidthStretch);
					ImGui::TableSetupColumn("NUMERO", ImGuiTableColumnFlags_WidthStretch);
					ImGui::TableSetupColumn("INTERIOR", ImGuiTableColumnFlags_WidthStretch);
					ImGui::TableSetupColumn("LOTE", ImGuiTableColumnFlags_WidthStretch);
					ImGui::TableSetupColumn("DEPARTAMENTO", ImGuiTableColumnFlags_WidthStretch);
					ImGui::TableSetupColumn("MANZANA", ImGuiTableColumnFlags_WidthStretch);
					ImGui::TableSetupColumn("KILOMETRO", ImGuiTableColumnFlags_WidthStretch);
					ImGui::TableHeadersRow();

					for (int row = 0; row < 1; row++)
					{
						ImGui::TableNextRow(ImGuiTableColumnFlags_WidthFixed);

						ImGui::TableSetColumnIndex(0);
						ImGui::Text("%s", data.razon_social);

						ImGui::TableSetColumnIndex(1);
						ImGui::Text("%s", data.estado_contribuyente);

						ImGui::TableSetColumnIndex(2);
						ImGui::Text("%s", data.condicion_domicilio);

						ImGui::TableSetColumnIndex(3);
						ImGui::Text("%s", data.ubigeo);

						ImGui::TableSetColumnIndex(4);
						ImGui::Text("%s", data.tipo_via);

						ImGui::TableSetColumnIndex(5);
						ImGui::Text("%s", data.nombre_via);

						ImGui::TableSetColumnIndex(6);
						ImGui::Text("%s", data.codigo_zona);

						ImGui::TableSetColumnIndex(7);
						ImGui::Text("%s", data.tipo_zona);

						ImGui::TableSetColumnIndex(8);
						ImGui::Text("%s", data.numero);

						ImGui::TableSetColumnIndex(9);
						ImGui::Text("%s", data.interior);

						ImGui::TableSetColumnIndex(10);
						ImGui::Text("%s", data.lote);

						ImGui::TableSetColumnIndex(11);
						ImGui::Text("%s", data.departamento);

						ImGui::TableSetColumnIndex(12);
						ImGui::Text("%s", data.manzana);

						ImGui::TableSetColumnIndex(13);
						ImGui::Text("%s", data.kilometro);


					}
					ImGui::EndTable();
				}

				/*if (ImGui::BeginTable("table2", 6, flags))
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
				}*/










			}
			end();

		}

	private:

	};
}
