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

		std::string get_file_insert(const ruc_data& ruc)
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

		const std::string get_template_insert()
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
			//stmt = con->createStatement();
			//res = stmt->executeQuery("SELECT 'Hello World!' AS _message");
			//while (res->next()) {
			//	cout << "\t... MySQL replies: ";
			//	/* Access column data by alias or column name */
			//	cout << res->getString("_message") << endl;
			//	cout << "\t... MySQL says it again: ";
			//	/* Access column data by numeric offset, 1 is the first column */
			//	cout << res->getString(1) << endl;
			//}

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

		void insert(zar_map& map)
		{
			std::string query = get_template_insert();

			/*std::ofstream registers;
			registers.open("registers.txt");*/

			unsigned count = 1;

			for (zar_map::const_iterator it = map.cbegin(); it != map.cend(); ++it)
			{
				query += get_query_insert(it->second) + ",";
				/*std::cout << query;
				system("pause");*/

				if (count >= 1000)
				{
					query.back() = ';';
					execute(query);
					//registers << data_file;

					spdlog::info("created {} dates sucess", 1000);
					std::this_thread::sleep_for(std::chrono::seconds(1));

					query = get_template_insert();
					count = 0;
				}
				count++;
			}

			{
				query.back() = ';';
				execute(query);
			}

			//registers.close();
			//remove(localFileTxtTmp);
			rename("ruc.zip", "ruc_last.zip");

		}

		void update()
		{
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
						spdlog::info("ruc: {}", it->first);
						zar_map::iterator c_it = ruc_last_map.find(it->first);
						if (c_it != ruc_last_map.end())
						{
							if (c_it->second != it->second)
							{
								spdlog::warn("------------------------");
								spdlog::warn("actulizar empresa");
								spdlog::warn("EMPRESA 1");
								c_it->second.print();
								spdlog::warn("EMPRESA 2");
								it->second.print();
								spdlog::warn("------------------------");
							}
						}
						else
						{
							spdlog::warn("nueva empresa");
							it->second.print();
						}

					}
				}
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
