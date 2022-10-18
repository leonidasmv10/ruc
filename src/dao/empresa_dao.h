#pragma once
#include <mysql/jdbc.h>

namespace zar
{
	class empresa_dao {
	public:

		empresa_dao()
		{
			sql = mysql::instance();
		}

		std::string get_query_insert(const ruc_data& ruc)
		{
			return "(default, '" +
				std::string(ruc.ruc) + "', '" +
				std::string(ruc.razon_social) + "', '" +
				std::string(ruc.estado_contribuyente) + "', '" +
				std::string(ruc.condicion_domicilio) + "', '" +
				std::string(ruc.ubigeo) + "', '" +
				std::string(ruc.tipo_via) + "', '" +
				std::string(ruc.nombre_via) + "', '" +
				std::string(ruc.codigo_zona) + "', '" +
				std::string(ruc.tipo_zona) + "', '" +
				std::string(ruc.numero) + "', '" +
				std::string(ruc.interior) + "', '" +
				std::string(ruc.lote) + "', '" +
				std::string(ruc.departamento) + "', '" +
				std::string(ruc.manzana) + "', '" +
				std::string(ruc.kilometro) + "' )";
		}

		const std::string get_template_insert()
		{
			return "INSERT INTO empresas VALUES ";
		}

		void insert(const ruc_data& ruc)
		{
			const std::string query = get_template_insert() + get_query_insert(ruc) + ";";
			execute(query);
		}

		void insert(zar_map& map)
		{
			std::string query = get_template_insert();
			unsigned count = 1;
			for (zar_map::const_iterator it = map.cbegin(); it != map.cend(); ++it)
			{
				query += get_query_insert(it->second) + ",";
				if (count % 10 == 0)
				{
					query.back() = ';';
					execute(query);
					query = get_template_insert();
					std::this_thread::sleep_for(std::chrono::seconds(10));
				}
				count++;
			}

			{
				query.back() = ';';
				execute(query);
				query = get_template_insert();
			}
		}

	private:

		void execute(const std::string& query)
		{
			sql->open();
			sql->execute_query(query);
			sql->close();
		}

		mysql* sql;
	};
}
