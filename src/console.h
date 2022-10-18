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
			while (true)
			{
				if (flag->is_update)
				{
					spdlog::info("download zip");

					ruc_data test;
					test.debug();
					test.print();

					mysql::instance()->connect(*server);

					empresa_dao* empresa = new empresa_dao();
					empresa->insert(test);

					/*if (zar::http::execute(file->url, file->out_filename))
					{
						spdlog::info("download {} success", file->url);
						spdlog::info("read zip");

						if (zar::zip::execute(file->out_filename, file->name, file->size, file->text_data))
						{
							spdlog::info("read {} success", file->name);
							zar::tool::split_iterator(file->text_data, file->my_map);
						}
					}*/
					flag->is_update = false;
				}
			}

		}

	private:

	};
}
