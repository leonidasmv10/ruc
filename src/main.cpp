#include "zar.h"

void console_loop(zar::file_data* file, zar::server_data* server, zar::flag_data* flag) {
	zar::console::instance()->task(file, server, flag);
}

void app_loop(zar::file_data* file, zar::server_data* server, zar::flag_data* flag) {
	zar::app::instance()->task(file, server, flag);
}

int main()
{
	setlocale(LC_ALL, "es_ES");

	// ------------------- DATA -------------------
	zar::file_data* file = new zar::file_data();
	zar::server_data* server = new zar::server_data();
	zar::flag_data* flag = new zar::flag_data();
	// --------------------------------------------

	std::thread m_thread(app_loop, file, server, flag);
	std::future<void> m_async = std::async(std::launch::async, console_loop, file, server, flag);

	if (m_async.valid())
	{
		m_async.get();
	}

	m_thread.join();
	return 0;
}
