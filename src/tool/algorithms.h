#pragma once
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

		static std::string get_file_insert(const ruc_data& ruc)
		{
			return
				std::string(ruc.ruc) + "|" +
				std::string(ruc.razon_social) + "|" +
				std::string(ruc.estado_contribuyente) + "|" +
				std::string(ruc.condicion_domicilio) + "|" +
				std::string(ruc.ubigeo) + "|" +
				std::string(ruc.tipo_via) + "|" +
				std::string(ruc.nombre_via) + "|" +
				std::string(ruc.codigo_zona) + "|" +
				std::string(ruc.tipo_zona) + "|" +
				std::string(ruc.numero) + "|" +
				std::string(ruc.interior) + "|" +
				std::string(ruc.lote) + "|" +
				std::string(ruc.departamento) + "|" +
				std::string(ruc.manzana) + "|" +
				std::string(ruc.kilometro) + "|";
		}


		static void split_iterator(const std::string& data, zar::zar_map& my_map)
		{
			std::string::const_iterator it_begin = data.begin() + 188;
			const std::string::const_iterator it_end = data.end();

			int type = 1;
			ruc_data new_ruc;

			std::string r_data = "";
			bool is_one_quote = false;
			bool is_two_quote = false;

			for (std::string::const_iterator it = it_begin; it != it_end; ++it)
			{
				if (*it == '|')
				{
					r_data = std::string(it_begin, it);
					if (is_one_quote) {
						fixed_one_quote(r_data);
						is_one_quote = false;
					}
					else if (is_two_quote) {
						fixed_two_quote(r_data);
						is_two_quote = false;
					}

					set_type(new_ruc, r_data, type);
					it_begin = it + 1;
				}
				else if (*it == 39)
				{
					is_one_quote = true;
				}
				else if (*it == 34)
				{
					is_two_quote = true;
				}
				else if (*it == '\n')
				{
					it_begin = it + 1;
					type = 1;
					my_map.insert(std::pair<std::string, ruc_data>(std::string(new_ruc.ruc), new_ruc));
				}
			}

			set_type(new_ruc, std::string(it_begin, it_end), type);
			my_map[new_ruc.ruc] = new_ruc;

		}

		static void fixed_one_quote(std::string& data)
		{
			unsigned size = data.size();
			int c = 0;
			std::vector<int> list_pos;

			for (unsigned i = 0; i < size; i++)
			{
				if (data[i] == 39) {
					c++;
					list_pos.push_back(i + c);
				}
			}

			for (const int& i : list_pos)
			{
				data.insert(i, "'");
			}
		}

		static void fixed_two_quote(std::string& data)
		{
			unsigned size = data.size();
			int c = 0;

			std::vector<int> list_pos;

			for (unsigned i = 0; i < size; i++)
			{
				if (data[i] == 34) {

					list_pos.push_back(i + c);
					c++;
				}
			}

			for (const int& i : list_pos)
			{
				data.insert(i, "\\");
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
