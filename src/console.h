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

		void loop(file_data*& file, server_data*& server, flag_data*& flag)
		{
			while (true)
			{
				if (flag->is_update)
				{
					spdlog::info("Download zip");

					if (zar::Http::execute(file->url, file->out_filename))
					{
						spdlog::info("Download {} success", file->url);
						spdlog::info("Read zip");

						if (zar::Zip::execute(file->out_filename, file->name, file->size, file->text_data))
						{
							spdlog::info("Read {} success", file->name);
						}
					}
					flag->is_update = false;
				}
			}

		}

	private:

		

	};
}
