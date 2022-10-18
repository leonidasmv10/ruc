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
				if (flag->is_process)
				{
					flag->is_process = false;

					spdlog::info("download zip");

					if (zar::http::execute(file->url, file->out_filename))
					{
						spdlog::info("download {} success", file->url);
						spdlog::info("read zip");

						if (zar::zip::execute(file->out_filename, file->name, file->size, file->text_data))
						{
							spdlog::info("read {} success", file->name);
							zar::algorithms::split_iterator(file->text_data, file->ruc_map);
							mysql::instance()->connect(*server);
							empresa->insert(file->ruc_map);

							spdlog::info("insert empresas success!");

							
						}
					}
				}
			}

		}

	private:

		empresa_dao* empresa;

	};
}
