#include "zar.h"

int main()
{
	setlocale(LC_ALL, "es_ES");

	// ------------------- DATA -------------------
	zar::file_data* file = new zar::file_data();
	zar::server_data* server = new zar::server_data();
	zar::flag_data* flag = new zar::flag_data();
	// --------------------------------------------

	zar::empresa_dao* e_dao = zar::empresa_dao::instance();
	e_dao->update(file);
	return 0;
}
