#pragma once
#include "libzippp.h"
#include <vector>

namespace zar
{
	class tool {
	public:

		static void print(const std::string& data)
		{
			std::string::const_iterator it_begin = data.begin();
			const std::string::const_iterator it_end = data.end();

			for (std::string::const_iterator it = it_begin; it != it_end; ++it)
			{
				std::cout << *it;
				if (*it == '\n')
				{
					std::cout << "\n";
					it_begin = it + 1;
					system("pause");
				}
			}

			//if (itBegin != itEnd)
		}

		static void split_iterator(const std::string& data, zar::zar_map& my_map)
		{
			std::string::const_iterator it_begin = data.begin() + 188;
			const std::string::const_iterator it_end = data.end();

			int type = 1;
			ruc_data new_ruc;

			for (std::string::const_iterator it = it_begin; it != it_end; ++it)
			{
				std::cout << *it;

				if (*it == '|')
				{
					set_type(new_ruc, std::string(it_begin, it), type);
					it_begin = it + 1;
				}

				if (*it == '\n')
				{
					std::cout << "\n";
					it_begin = it + 1;
					type = 1;
					new_ruc.print();
					new_ruc = ruc_data();
					system("pause");
				}
			}

			if (it_begin != it_end)
			{
				//std::string(it_begin, it_end);
				new_ruc.print();
			}
		}

		static void set_type(ruc_data& ruc, const std::string& data, int& type)
		{
			switch (type)
			{
			case 1:
				strcpy(ruc.ruc, data.c_str());
				break;
			case 2:
				strcpy(ruc.razon_social, data.c_str());
				break;
			case 3:
				strcpy(ruc.estado_contribuyente, data.c_str());
				break;
			case 4:
				strcpy(ruc.condicion_domicilio, data.c_str());
				break;
			case 5:
				strcpy(ruc.ubigeo, data.c_str());
				break;
			case 6:
				strcpy(ruc.tipo_via, data.c_str());
				break;
			case 7:
				strcpy(ruc.nombre_via, data.c_str());
				break;
			case 8:
				strcpy(ruc.codigo_zona, data.c_str());
				break;
			case 9:
				strcpy(ruc.tipo_zona, data.c_str());
				break;
			case 10:
				strcpy(ruc.numero, data.c_str());
				break;
			case 11:
				strcpy(ruc.interior, data.c_str());
				break;
			case 12:
				strcpy(ruc.lote, data.c_str());
				break;
			case 13:
				strcpy(ruc.departamento, data.c_str());
				break;
			case 14:
				strcpy(ruc.manzana, data.c_str());
				break;
			case 15:
				strcpy(ruc.kilometro, data.c_str());
				break;
			default:
				break;
			}
			type++;
		}

	private:


	};
}
