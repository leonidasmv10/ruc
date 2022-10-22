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

		std::string get_query_delete(const std::string& ruc)
		{
			return "ruc='" + ruc + "'";
		}

		const std::string get_template_insert()
		{
			return "INSERT INTO empresas VALUES ";
		}

		const std::string get_template_delete()
		{
			return "DELETE FROM empresas WHERE ";
		}

		const std::string get_template_update()
		{
			return "INSERT INTO empresas VALUES ";
		}

		void insert(const ruc_data& ruc)
		{
			const std::string query = get_template_insert() + get_query_insert(ruc) + ";";
			execute(query);
		}

		void get_data()
		{
			std::string ruc = "20450799026";

			std::string query = "SELECT * FROM empresas WHERE ruc=\"" + ruc + "\"";
			std::unique_ptr<sql::ResultSet> res(execute_query(query));

			//ruc_data ruc;
			res->afterLast();

			while (res->previous())
			{
				std::cout << "\t... ID: " << res->getInt("id") << std::endl;
				std::cout << "\t... RUC: " << res->getString(1) << std::endl;
				std::cout << "\t... RAZON SOCIAL: " << res->getString(2) << std::endl;
				std::cout << "\t... ESTADO CONTRIBUYENTE: " << res->getString(3) << std::endl;
				std::cout << "\t... CONDICION DOMICILIO: " << res->getString(4) << std::endl;
			}

			//	stmt = con->createStatement();
			//	stmt->execute("DROP TABLE IF EXISTS test");
			//	stmt->execute("CREATE TABLE test(id INT)");
			//	delete stmt;

			//	/* '?' is the supported placeholder syntax */
			//	pstmt = con->prepareStatement("INSERT INTO test(id) VALUES (?)");
			//	for (int i = 1; i <= 10; i++) {
			//		pstmt->setInt(1, i);
			//		pstmt->executeUpdate();
			//	}
			//	delete pstmt;

			//	/* Select in ascending order */
			//	pstmt = con->prepareStatement("SELECT id FROM test ORDER BY id ASC");
			//	res = pstmt->executeQuery();

			//	/* Fetch in reverse = descending order! */
			//	res->afterLast();
			//	while (res->previous())
			//		cout << "\t... MySQL counts: " << res->getInt("id") << endl;
			//	delete res;

			//	delete pstmt;
			//	delete con;
			//}
		}

		void update()
		{
			std::string query_insert = get_template_insert();
			std::string query_delete = get_template_delete();

			std::string name = "", data = "";
			int size = 0;

			zar_map ruc_map;
			zar_map ruc_last_map;

			if (zip::execute("ruc_last.zip", name, size, data))
			{
				algorithms::split_iterator(data, ruc_last_map);
				if (zip::execute("ruc.zip", name, size, data))
				{
					algorithms::split_iterator(data, ruc_map);
					for (zar_map::iterator it = ruc_map.begin(); it != ruc_map.end(); ++it)
					{
						//spdlog::info("ruc: {}", it->first);
						zar_map::iterator c_it = ruc_last_map.find(it->first);
						if (c_it != ruc_last_map.end())
						{
							if (c_it->second != it->second)
							{
								query_delete += get_query_delete(c_it->first) + " or ";
								query_insert += get_query_insert(it->second) + ",";

								spdlog::warn("old company");
								c_it->second.print();
								spdlog::warn("updated company");
								it->second.print();
							}
						}
						else
						{
							spdlog::warn("nueva empresa");
							query_insert += get_query_insert(it->second) + ",";
							it->second.print();
						}
					}

				}
			}

			query_delete.pop_back();
			query_delete.pop_back();
			query_delete.pop_back();

			query_delete.back() = ';';
			query_insert.back() = ';';

			std::cout << query_insert << "\n";
			std::cout << query_delete << "\n";

			execute(query_delete);
			execute(query_insert);
		}

	private:

		void execute(const std::string& query)
		{
			sql->open();
			sql->execute(query);
			sql->close();
		}

		sql::ResultSet* execute_query(const std::string& query)
		{
			sql->open();
			sql::ResultSet* res = sql->execute_query(query);
			sql->close();
			return res;
		}

		mysql* sql;
	};
}
