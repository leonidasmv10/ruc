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
			empresa = empresa_dao::instance();

			while (true)
			{
				if (flag->is_process_insert)
				{
					flag->is_process_insert = false;
					spdlog::info("insert init");
					//if (zar::http::execute(file->url, file->out_filename))
					{
						mysql::instance()->connect(*server);
						empresa->insert(file);
					}
					spdlog::info("insert success");
				}

				else if (flag->is_process_update)
				{
					flag->is_process_update = false;
					spdlog::info("update init");
					//if (zar::http::execute(file->url, file->out_filename))
					{
						mysql::instance()->connect(*server);
						empresa->update(file);
					}
					spdlog::info("update success");
				}

				else if (flag->is_process_query)
				{
					flag->is_process_query = false;
					spdlog::info("query");
				}
			}

		}

	private:

		empresa_dao* empresa;

	};
}
