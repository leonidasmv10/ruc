#pragma once
#include <mysql/jdbc.h>

namespace zar
{
	class mysql {
	public:

		static mysql* instance()
		{
			static mysql instance;
			return &instance;
		}

		void connect(const server_data& data)
		{
			try
			{
				connection_properties[OPT_HOSTNAME] = data.url;
				connection_properties[OPT_USERNAME] = data.user;
				connection_properties[OPT_PASSWORD] = data.pass;
				connection_properties[OPT_PORT] = 3306;
				connection_properties[OPT_SCHEMA] = data.db;
				connection_properties["OPT_SSL_MODE"] = sql::SSL_MODE_DISABLED;
				connection_properties[OPT_RECONNECT] = true;

				driver = sql::mysql::get_driver_instance();
			}
			catch (sql::SQLException& e)
			{
				spdlog::error("# ERR: SQLException in {}", __FILE__);
				spdlog::error("({}) on line {}", __FUNCTION__, __LINE__);
				spdlog::error("# ERR: {}", e.what());
				spdlog::error(" (MySQL error code: {}, SQLState: {})", e.getErrorCode(), e.getSQLState());
			}
		}

		void open()
		{
			try
			{
				driver->threadInit();
				connection = driver->connect(connection_properties);
			}
			catch (sql::SQLException& e)
			{
				spdlog::error("# ERR: SQLException in {}", __FILE__);
				spdlog::error("({}) on line {}", __FUNCTION__, __LINE__);
				spdlog::error("# ERR: {}", e.what());
				spdlog::error(" (MySQL error code: {}, SQLState: {})", e.getErrorCode(), e.getSQLState());
			}
		}

		void close()
		{
			try
			{
				driver->threadEnd();
				connection->close();
				delete connection;
				connection = nullptr;
			}
			catch (sql::SQLException& e)
			{
				spdlog::error("# ERR: SQLException in {}", __FILE__);
				spdlog::error("({}) on line {}", __FUNCTION__, __LINE__);
				spdlog::error("# ERR: {}", e.what());
				spdlog::error(" (MySQL error code: {}, SQLState: {})", e.getErrorCode(), e.getSQLState());
			}
		}

		void execute(const std::string& query)
		{
			try
			{
				std::unique_ptr<sql::PreparedStatement> pstmt(connection->prepareStatement(query));
				pstmt->execute();
			}
			catch (sql::SQLException& e)
			{
				spdlog::error("# ERR: SQLException in {}", __FILE__);
				spdlog::error("({}) on line {}", __FUNCTION__, __LINE__);
				spdlog::error("# ERR: {}", e.what());
				spdlog::error(" (MySQL error code: {}, SQLState: {})", e.getErrorCode(), e.getSQLState());
			}
		}

		sql::ResultSet* execute_query(const std::string& query)
		{
			try
			{
				std::unique_ptr<sql::PreparedStatement> pstmt(connection->prepareStatement(query));
				return pstmt->executeQuery();
			}
			catch (sql::SQLException& e)
			{
				spdlog::error("# ERR: SQLException in {}", __FILE__);
				spdlog::error("({}) on line {}", __FUNCTION__, __LINE__);
				spdlog::error("# ERR: {}", e.what());
				spdlog::error(" (MySQL error code: {}, SQLState: {})", e.getErrorCode(), e.getSQLState());
			}
		}

	private:

		sql::mysql::MySQL_Driver* driver;
		sql::Connection* connection;
		sql::ConnectOptionsMap connection_properties;
	};
}
