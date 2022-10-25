#include "zar.h"

int main()
{
	setlocale(LC_ALL, "es_ES");

	// ------------------- DATA -------------------
	zar::file_data* file = new zar::file_data();
	zar::server_data* server = new zar::server_data();
	// --------------------------------------------

	spdlog::info("insert init");
	if (zar::http::execute(file->url, file->out_filename))
	{
		zar::mysql::instance()->connect(*server);
		zar::empresa_dao* e_dao = zar::empresa_dao::instance();

		e_dao->create_table();
		e_dao->insert(file);
	}
	spdlog::info("insert success");
	
	return 0;
}
