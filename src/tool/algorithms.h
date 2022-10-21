﻿#pragma once
#include "libzippp.h"
#include <vector>

namespace zar
{
	class algorithms {
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

			std::string r_data = "";
			bool is_ascii = false;

			for (std::string::const_iterator it = it_begin; it != it_end; ++it)
			{
				if (*it == '|')
				{
					r_data = std::string(it_begin, it);
					if (is_ascii) {
						fixed_ascci(r_data);
						is_ascii = false;
					}

					set_type(new_ruc, r_data, type);
					it_begin = it + 1;
				}
				else if (*it == 39)
				{
					is_ascii = true;
				}
				else if (*it == '\n')
				{
					it_begin = it + 1;
					type = 1;
					//my_map[std::string(new_ruc.ruc)] = new_ruc;
					my_map.insert(std::pair<std::string, ruc_data>(std::string(new_ruc.ruc), new_ruc));

					/*if (std::string(new_ruc.ruc) == "20508088826")
					{
						spdlog::warn("F1");
						new_ruc.print();
					}

					if (std::string(my_map[new_ruc.ruc].ruc) == "20508088826")
					{
						spdlog::warn("F2");
						new_ruc.print();
					}*/
				}
			}

			set_type(new_ruc, std::string(it_begin, it_end), type);
			my_map[new_ruc.ruc] = new_ruc;

			/*system("pause");
			for (auto m_it = my_map.begin(); m_it != my_map.end(); ++m_it)
				spdlog::info("{}", m_it->second.ruc);

			spdlog::info("map size: {}", my_map.size() - 1);*/

		}

		static void fixed_ascci(std::string& data)
		{
			unsigned i = 1;
			unsigned size = data.size();

			for (; i < size; i++)
			{
				if (data[i] == 39 && data[i] != data[i - 1]) {
					data.insert(i, "'");
				}
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
