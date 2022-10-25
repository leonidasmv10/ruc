﻿#include "zar.h"

int main()
{
	setlocale(LC_ALL, "es_ES");

	// ------------------- DATA -------------------
	zar::file_data* file = new zar::file_data();
	zar::server_data* server = new zar::server_data();
	zar::flag_data* flag = new zar::flag_data();
	// --------------------------------------------

	spdlog::info("welcome");
	spdlog::warn("download file");

	if (zar::http::execute(file->url, file->out_filename))
	{
		spdlog::info("download {} success", file->url);
		spdlog::warn("read zip");

		if (zar::zip::execute(file->out_filename, file->name, file->size, file->text_data))
		{
			zar::mysql* sql = zar::mysql::instance();
			sql->connect(*server);

			zar::empresa_dao* e_dao = new zar::empresa_dao();
			std::string data = file->text_data;

			std::string query = e_dao->get_template_insert();
			e_dao->create_table();

			int type = 1;
			unsigned c = 0;

			unsigned line = 0;
			unsigned n_partition = 1000;

			spdlog::info("read {} success", file->name);
			spdlog::warn("iterator init");

			std::string::iterator it_begin = data.begin() + 188;
			const std::string::const_iterator it_end = data.end();

			zar::ruc_data new_ruc;
			std::string r_data = "";

			bool is_one_quote = false;
			bool is_two_quote = false;

			for (std::string::iterator it = it_begin; it != it_end; ++it)
			{
				if (*it == '|' && *(it + 1) != '|')
				{
					r_data = std::string(it_begin, it);
					if (is_one_quote) {
						zar::algorithms::fixed_one_quote(r_data);
						is_one_quote = false;
					}
					else if (is_two_quote) {
						zar::algorithms::fixed_two_quote(r_data);
						is_two_quote = false;
					}

					zar::algorithms::set_type(new_ruc, r_data, type);
					it_begin = it + 1;
				}
				else if (*it == 92)
				{
					*it = '/';
				}
				else if (*it == 39)
				{
					is_one_quote = true;
				}
				else if (*it == 34)
				{
					is_two_quote = true;
				}
				else if (*it == '\n')
				{
					query += e_dao->get_query_insert(new_ruc) + ",";
					c++;

					if (c >= n_partition)
					{
						c = 0;
						query.back() = ';';

						sql->open();
						sql->execute_query(query);
						sql->close();

						query.clear();
						query = e_dao->get_template_insert();
					}

					it_begin = it + 1;
					type = 1;
				}
			}

			query += e_dao->get_query_insert(new_ruc) + ",";
			query.back() = ';';

			sql->open();
			sql->execute_query(query);
			sql->close();

			query.clear();

			spdlog::info("finish");
			rename(file->out_filename, file->out_filename_last);
		}

	}
	return 0;
}
