#include "../config.h"

#include <string>
#include <thread>
#include <future>
#include <iostream>
#include <stdio.h>

#include <spdlog\spdlog.h>

#include "http.h"
#include "zip.h"

#include "file_data.h"
#include "server_data.h"
#include "flag_data.h"

#include "app.h"
#include "console.h"

using namespace std;

void console_loop(zar::file_data* file, zar::server_data* server, zar::flag_data* flag) {
	zar::Console::instance()->loop(file, server, flag);
}

void app_loop(zar::file_data* file, zar::server_data* server, zar::flag_data* flag) {
	zar::App::instance()->loop(file, server, flag);
}

int main()
{
	// ------------------- DATA ----------------
	zar::file_data* file = new zar::file_data();
	zar::server_data* server = new zar::server_data();
	zar::flag_data* flag = new zar::flag_data();
	// -----------------------------------------

	std::thread m_thread(app_loop, file, server, flag);
	std::future<void> m_async{};

	m_async = std::async(std::launch::async, console_loop, file, server, flag);

	if (m_async.valid())
	{
		m_async.get();
	}

	m_thread.join();

	spdlog::info("Finish");
	return 0;
}
