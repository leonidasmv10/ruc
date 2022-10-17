#pragma once

namespace zar
{
	class Console {
	public:

		static Console* instance()
		{
			static Console instance;
			return &instance;
		}

		void task(file_data*& file, server_data*& server, flag_data*& flag)
		{
			while (true)
			{
				if (flag->is_update)
				{
					spdlog::info("download zip");

					if (zar::Http::execute(file->url, file->out_filename))
					{
						spdlog::info("download {} success", file->url);
						spdlog::info("read zip");

						if (zar::Zip::execute(file->out_filename, file->name, file->size, file->text_data))
						{
							spdlog::info("read {} success", file->name);
							zar::Tool::print(file->text_data);
						}
					}
					flag->is_update = false;
				}
			}

		}

	private:



	};
}
