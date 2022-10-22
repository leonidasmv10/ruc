#pragma once

namespace zar
{
	class console {
	public:

		static console* instance()
		{
			static console instance;
			return &instance;
		}

		void task(file_data*& file, server_data*& server, flag_data*& flag)
		{
			empresa = new empresa_dao();

			while (true)
			{
				if (flag->is_process_insert)
				{
					flag->is_process_insert = false;

					spdlog::warn("download zip");

					if (zar::http::execute(file->url, file->out_filename))
					{
						spdlog::info("download {} success", file->url);
						spdlog::warn("read zip");

						if (zar::zip::execute(file->out_filename, file->name, file->size, file->text_data))
						{
							spdlog::info("read {} success", file->name);
							spdlog::warn("iterator init");
							zar::algorithms::split_iterator(file->text_data, file->ruc_map);
							spdlog::info("iterator sucess");
							mysql::instance()->connect(*server);
							spdlog::warn("init insert process", file->name);
							//empresa->insert(file->ruc_map);
							spdlog::info("insert empresas success!");

						}
					}
				}

				else if (flag->is_process_update)
				{
					flag->is_process_update = false;

					spdlog::info("update");
					mysql::instance()->connect(*server);
					//empresa->update();
				}

				else if (flag->is_process_query)
				{
					flag->is_process_query = false;

					spdlog::info("query");
					mysql::instance()->connect(*server);
					empresa->get_data();
				}
			}

		}

	private:

		empresa_dao* empresa;

	};
}
