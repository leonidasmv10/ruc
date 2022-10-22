//#include "zar.h"
//
//void console_loop(zar::file_data* file, zar::server_data* server, zar::flag_data* flag) {
//	zar::console::instance()->task(file, server, flag);
//}
//
//void app_loop(zar::file_data* file, zar::server_data* server, zar::flag_data* flag) {
//	zar::app::instance()->task(file, server, flag);
//}
//
//int main()
//{
//	setlocale(LC_ALL, "es_ES");
//
//	// ------------------- DATA -------------------
//	zar::file_data* file = new zar::file_data();
//	zar::server_data* server = new zar::server_data();
//	zar::flag_data* flag = new zar::flag_data();
//	// --------------------------------------------
//
//	std::thread m_thread(app_loop, file, server, flag);
//	std::future<void> m_async = std::async(std::launch::async, console_loop, file, server, flag);
//
//	if (m_async.valid())
//	{
//		m_async.get();
//	}
//
//	m_thread.join();
//	return 0;
//}

#include "zar.h"

int main()
{
	setlocale(LC_ALL, "es_ES");

	// ------------------- DATA -------------------
	zar::file_data* file = new zar::file_data();
	zar::server_data* server = new zar::server_data();
	zar::flag_data* flag = new zar::flag_data();
	// --------------------------------------------

	spdlog::info("welcome");

	if (zar::http::execute(file->url, file->out_filename))
	{
		spdlog::info("download {} success", file->url);
		spdlog::warn("read zip");

		if (zar::zip::execute(file->out_filename, file->name, file->size, file->text_data))
		{
			zar::mysql* sql = zar::mysql::instance();
			int type = 1;

			sql->connect(*server);
			sql->open();

			zar::empresa_dao* e_dao = new zar::empresa_dao();
			std::string data = file->text_data;

			spdlog::info("read {} success", file->name);
			spdlog::warn("iterator init");

			std::string::iterator it_begin = data.begin() + 188;
			const std::string::iterator it_end = data.end();

			zar::ruc_data new_ruc;
			std::string r_data = "";

			bool is_one_quote = false;
			bool is_two_quote = false;

			for (std::string::iterator it = it_begin; it != it_end; ++it)
			{

				if (*it == '|')
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
				/*else if (*it == 'Ñ')
				{
					*it = 165;
				}*/
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
					const std::string query = e_dao->get_template_insert() + e_dao->get_query_insert(new_ruc) + ";";
					sql->execute_query(query);
					it_begin = it + 1;
					type = 1;
				}
			}
			sql->close();
			spdlog::info("finish");
		}

		return 0;
	}
}