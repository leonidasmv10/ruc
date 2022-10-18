#pragma once

namespace zar
{
	typedef std::map<std::string, ruc_data> zar_map;
	struct file_data
	{
		char url[100] = "http://www2.sunat.gob.pe/padron_reducido_ruc.zip";
		char out_filename[30] = "ruc.zip";

		std::string name = "";
		std::string text_data = "";
		int size = 0;

		zar_map ruc_map = {};
	};

}
