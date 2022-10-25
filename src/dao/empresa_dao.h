#pragma once
#include <mysql/jdbc.h>

namespace zar
{
	class empresa_dao {
	public:

		static empresa_dao* instance()
		{
			static empresa_dao instance;
			return &instance;
		}

		empresa_dao()
		{
			sql = mysql::instance();
		}

		std::string get_query_insert(const ruc_data& ruc)
		{
			return "(default,'" +
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

		const std::string get_template_delete_table()
		{
			return "DROP TABLE IF EXISTS empresas;";
		}

		const std::string get_template_table()
		{
			return
				"CREATE TABLE empresas (" +
				std::string("id int(11) NOT NULL PRIMARY KEY AUTO_INCREMENT, ") +
				"ruc varchar(11) NOT NULL," +
				"razon_social varchar(500) NOT NULL," +
				"estado_contribuyente varchar(50) NOT NULL," +
				"condicion_domicilio varchar(50) NOT NULL," +
				"ubigeo varchar(50) NOT NULL," +
				"tipo_via varchar(50) NOT NULL," +
				"nombre_via varchar(50) NOT NULL," +
				"codigo_zona varchar(50) NOT NULL," +
				"tipo_zona varchar(50) NOT NULL," +
				"numero varchar(50) NOT NULL," +
				"interior varchar(50) NOT NULL," +
				"lote varchar(50) NOT NULL," +
				"departamento varchar(50) NOT NULL," +
				"manzana varchar(50) NOT NULL," +
				"kilometro varchar(50) NOT NULL" +
				") ENGINE = InnoDB DEFAULT CHARSET = latin1; ";
		}

		void insert(const ruc_data& ruc)
		{
			const std::string query = get_template_insert() + get_query_insert(ruc) + ";";
			execute(query);
		}

		void insert(file_data*& file)
		{
			unsigned c = 0;
			unsigned n_partition = 1000;

			if (zar::zip::execute(file->out_filename, file->name, file->size, file->text_data))
			{
				zar::empresa_dao* e_dao = new zar::empresa_dao();
				std::string data = file->text_data;

				std::string query = e_dao->get_template_insert();
				int type = 1;

				spdlog::info("read {} success", file->name);
				spdlog::warn("iterator init");

				std::string::iterator it_begin = data.begin() + 188;
				const std::string::const_iterator it_end = data.end();

				zar::ruc_data new_ruc;
				std::string r_data = "";

				bool is_one_quote = false;
				bool is_two_quote = false;

				for (std::string::iterator it = it_begin; it != it_end; ++it)
				{
					if (*it == '|' && *(it + 1) != '|')
					{
						r_data = std::string(it_begin, it);
						if (is_one_quote) {
							zar::algorithms::fixed_one_quote(r_data);
							is_one_quote = false;
						}
						else if (is_two_quote) {
							zar::algorithms::fixed_two_quote(r_data);
							is_two_quote = false;
						}

						zar::algorithms::set_type(new_ruc, r_data, type);
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
					else if (*it == 92)
					{
						*it = '/';
					}
					else if (*it == '\n')
					{
						query += e_dao->get_query_insert(new_ruc) + ",";
						c++;

						if (c >= n_partition)
						{
							c = 0;
							query.back() = ';';

							sql->open();
							sql->execute_query(query);
							sql->close();

							query.clear();
							query = e_dao->get_template_insert();
						}

						it_begin = it + 1;
						type = 1;
					}
				}

				rename(file->out_filename, file->out_filename_last);

				query += e_dao->get_query_insert(new_ruc) + ",";
				query.back() = ';';

				sql->open();
				sql->execute_query(query);
				sql->close();

				query.clear();

				spdlog::info("finish");
			}
		}

		ruc_data query(const std::string& ruc)
		{
			std::string query = "SELECT * FROM empresas WHERE ruc=\"" + ruc + "\"";
			std::unique_ptr<sql::ResultSet> res(execute_query(query));

			if (res == nullptr) return {};

			ruc_data data;
			res->afterLast();

			while (res->previous())
			{
				strcpy(data.ruc, res->getString(2).c_str());
				strcpy(data.razon_social, res->getString(3).c_str());
				strcpy(data.estado_contribuyente, res->getString(4).c_str());
				strcpy(data.condicion_domicilio, res->getString(5).c_str());
				strcpy(data.ubigeo, res->getString(6).c_str());
				strcpy(data.tipo_via, res->getString(8).c_str());
				strcpy(data.nombre_via, res->getString(8).c_str());
				strcpy(data.codigo_zona, res->getString(9).c_str());
				strcpy(data.tipo_zona, res->getString(10).c_str());
				strcpy(data.numero, res->getString(11).c_str());
				strcpy(data.interior, res->getString(12).c_str());
				strcpy(data.lote, res->getString(13).c_str());
				strcpy(data.departamento, res->getString(14).c_str());
				strcpy(data.manzana, res->getString(15).c_str());
				strcpy(data.kilometro, res->getString(16).c_str());
			}
			return data;
		}

		void create_table()
		{
			execute(get_template_table());
		}

		void drop_table()
		{
			execute(get_template_delete_table());
		}

		int get_count()
		{
			std::string query = "SELECT COUNT(id) AS c FROM empresas;";
			std::unique_ptr<sql::ResultSet> res(execute_query(query));

			if (res == nullptr) return 0;
			int c = 0;

			res->afterLast();
			while (res->previous())
			{
				c = res->getInt("c");
			}
			return c;
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
