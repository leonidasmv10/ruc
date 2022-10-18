#pragma once
#include "libzippp.h"
#include <vector>

namespace zar
{
	class zip {
	public:

		static bool execute(const char* zip, std::string& name, int& size, std::string& text_data)
		{
			bool flag = false;

			libzippp::ZipArchive zf(zip);
			zf.open(libzippp::ZipArchive::ReadOnly);

			std::vector<libzippp::ZipEntry> entries = zf.getEntries();
			std::vector<libzippp::ZipEntry>::iterator it;
			for (it = entries.begin(); it != entries.end(); ++it) {
				libzippp::ZipEntry entry = *it;
				name = entry.getName();
				size = entry.getSize();

				text_data = entry.readAsText();
				flag = true;
				break;
			}

			zf.close();
			return flag;
		}

	private:


	};
}
