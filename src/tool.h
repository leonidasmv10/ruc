#pragma once
#include "libzippp.h"
#include <vector>

namespace zar
{
	class Tool {
	public:

		static void print(const std::string& data)
		{
			std::string::const_iterator itBegin = data.begin();
			std::string::const_iterator itEnd = data.end();

			for (std::string::const_iterator it = itBegin; it != itEnd; ++it)
			{
				std::cout << *it;
				if (*it == '\n')
				{
					std::cout << "\n";
					itBegin = it + 1;
					system("pause");
				}
			}

			//if (itBegin != itEnd)
		}

	private:


	};
}
