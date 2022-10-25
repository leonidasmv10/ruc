#include "zar.h"

int main()
{
	setlocale(LC_ALL, "es_ES");

	// ------------------- DATA -------------------
	zar::file_data* file = new zar::file_data();
	zar::server_data* server = new zar::server_data();
	// --------------------------------------------

	spdlog::info("update init");
	if (zar::http::execute(file->url, file->out_filename))
	{
		zar::mysql::instance()->connect(*server); 
		zar::empresa_dao* e_dao = zar::empresa_dao::instance();
		e_dao->update(file);
	}
	spdlog::info("update success");

	return 0;
}
