#include "../config.h"

#include "libzippp.h"

#include <iostream>
#include <fstream>
#include <string>


#include <chrono>
#include <ctime> 
#include <thread>

//#include <mysql/jdbc.h>

#include <vector>
#include <unordered_map>



using namespace libzippp;
using namespace std;

#include <iostream>
#include <fstream>
#include <string>

#include <chrono>
#include <ctime> 
#include <thread>

#include <mysql/jdbc.h>

#include <vector>
#include <unordered_map>

#include <stdio.h>
#include <curl/curl.h>
/* For older cURL versions you will also need
#include <curl/types.h>
#include <curl/easy.h>
*/
#include <string>

size_t write_data(void* ptr, size_t size, size_t nmemb, FILE* stream) {
	size_t written = fwrite(ptr, size, nmemb, stream);
	return written;
}



std::vector<std::string> split_iterator(const std::string& str)
{
	std::vector<std::string> resultado;

	std::string::const_iterator itBegin = str.begin();
	std::string::const_iterator itEnd = str.end();

	int numItems = 1;
	for (std::string::const_iterator it = itBegin; it != itEnd; ++it)
		numItems += *it == '|';

	resultado.reserve(numItems);

	for (std::string::const_iterator it = itBegin; it != itEnd; ++it)
	{
		if (*it == '|')
		{
			resultado.push_back(std::string(itBegin, it));
			itBegin = it + 1;
		}
	}

	if (itBegin != itEnd)
		resultado.push_back(std::string(itBegin, itEnd));

	return resultado;
}

std::string find_ruc(const std::string& str)
{

	std::string::const_iterator itBegin = str.begin();
	std::string::const_iterator itEnd = str.end();

	for (std::string::const_iterator it = itBegin; it != itEnd; ++it)
	{
		if (*it == '|')
		{
			return std::string(itBegin, it);

		}
	}
	return "";
}

std::string formatInsert(std::string& texto)
{
	std::string text = "";

	for (int i = 0; i < texto.size(); i++)
	{
		if ((texto[i] > -1 || texto[i] < 256 || isalpha(texto[i]) || isdigit(texto[i]) || texto[i] == '|' || texto[i] == '-' || texto[i] == ' ') && texto[i] != 39)
		{
			text += texto[i];
		}
	}

	std::vector<std::string> datos = split_iterator(text);

	return "(default, '" + datos[0] + "', '" + datos[1] + "', '" + datos[2] + "', '" + datos[3] + "', '" + datos[4] + "', '" + datos[5] + "', '" + datos[6] + "', '" + datos[7] + "', '" + datos[8] + "', '" + datos[9] + "', '" + datos[10] + "', '" + datos[11] + "', '" + datos[12] + "', '" + datos[13] + "', '" + datos[14] + "' ),";
}

std::string formatUpdate(std::string& texto)
{
	std::vector<std::string> datos = split_iterator(texto);
	return "UPDATE empresas SET razonsocial='" + datos[1] + "',estadocontribuyente='" + datos[2] + "',condicionDomicilio='" + datos[3] + "',ubigeo='" + datos[4] + "',tipovia='" + datos[5] + "',nombrevia='" + datos[6] + "',codigozona='" + datos[7] + "',tipozona='" + datos[8] + "',numero='" + datos[9] + "',interior='" + datos[10] + "',lote='" + datos[11] + "',departamento='" + datos[12] + "',manzana='" + datos[13] + "',kilometro='" + datos[14] + "' WHERE ruc='" + datos[0] + "';\n";
}

std::string formatDelete(std::string& ruc)
{
	return "ruc='" + ruc + "' or ";
}

int main(int argc, const char* argv[])
{

	//setlocale(LC_ALL, "spanish"); 
	setlocale(LC_ALL, "es_ES");



	//const char* localFilePath = "padron_reducido_ruc.zip";
	const char* localFileTxt = "ruc.txt";
	//const char* localFileTxtTmp = "ruc_temp.txt";
	//const char* urlPath = "http://www2.sunat.gob.pe/padron_reducido_ruc.zip";

	const char* url = (argc > 1 ? argv[1] : ZAR_URL);
	const std::string user(argc >= 3 ? argv[2] : ZAR_USER);
	const std::string pass(argc >= 4 ? argv[3] : ZAR_PASS);
	const std::string database(argc >= 5 ? argv[4] : ZAR_DB);

	std::ofstream registrosTXT;
	std::ofstream modificadosTXT;

	registrosTXT.open("registrados.txt");
	registrosTXT << "RUC|NOMBRE O RAZON SOCIAL|ESTADO DEL CONTRIBUYENTE|CONDICION DE DOMICILIO|UBIGEO|TIPO DE VIA|NOMBRE DE VIA|CODIGO DE ZONA|TIPO DE ZONA|NUMERO|INTERIOR|LOTE|DEPARTAMENTO|MANZANA|KILOMETRO|\n";

	modificadosTXT.open("modificados.txt");
	modificadosTXT << "RUC|NOMBRE O RAZON SOCIAL|ESTADO DEL CONTRIBUYENTE|CONDICION DE DOMICILIO|UBIGEO|TIPO DE VIA|NOMBRE DE VIA|CODIGO DE ZONA|TIPO DE ZONA|NUMERO|INTERIOR|LOTE|DEPARTAMENTO|MANZANA|KILOMETRO|\n";

	//if (obtenerZip(localFilePath, urlPath))
	//{
	//	std::cout << "Zip instalado\n";
	//}

	//if (descomprimirZip(localFilePath))
	//{
	//	std::cout << "Zip descomprimido\n";
	//}

	std::ifstream archivo;
	std::string texto;

	try
	{

		sql::mysql::MySQL_Driver* driver;
		sql::Connection* con;
		sql::ConnectOptionsMap connection_properties;

		connection_properties[OPT_HOSTNAME] = url;
		connection_properties[OPT_USERNAME] = user;
		connection_properties[OPT_PASSWORD] = pass;
		connection_properties[OPT_PORT] = 3306;
		connection_properties[OPT_SCHEMA] = database;
		connection_properties["OPT_SSL_MODE"] = sql::SSL_MODE_DISABLED;
		connection_properties[OPT_RECONNECT] = true;

		driver = sql::mysql::get_driver_instance();
		driver->threadInit();


		archivo.open(localFileTxt, std::ios::in);

		while (!archivo.eof())
		{
			getline(archivo, texto);
			break;
		}

		unsigned int i;

		std::string queryInsertar = "INSERT INTO empresas VALUES ";
		std::list<std::string> listaQueryInsertar;



		std::string query = queryInsertar;
		std::string n_ruc = "59|LEONÉÓ VÁSQUEZ|-|-|-|-|-|-|-|-|-|-|-|-|-|";

		//while (!archivo.eof())
		//{
		//	getline(archivo, texto);
		//	query += formatInsert(texto);
		//	//break;
		//}

		query += formatInsert(n_ruc);

		query.back() = ';';


		std::cout << query;

		con = driver->connect(connection_properties);

		std::unique_ptr<sql::PreparedStatement> pstmtModificar(con->prepareStatement(query));
		pstmtModificar->execute();
		std::cout << "Insertando DB\n";


		con->close();
		delete con;



		archivo.close();
		driver->threadEnd();
	}
	catch (sql::SQLException& e)
	{
		std::ofstream error;
		error.open("error.txt");

		error << "# ERR: SQLException in " << __FILE__ << "\n";
		error << "(" << "EXAMPLE_FUNCTION" << ") on line " << __LINE__ << "\n";

		error << "# ERR: " << e.what() << "\n";
		error << " (MySQL error code: " << e.getErrorCode() << "\n";
		error << ", SQLState: " << e.getSQLState() << " )" << "\n";

		return EXIT_FAILURE;
	}

	//rename(localFileTxt, localFileTxtTmp);

	CURL* curl;
	FILE* fp;
	CURLcode res;
	char* url_ruc = "http://www2.sunat.gob.pe/padron_reducido_ruc.zip";
	char outfilename[FILENAME_MAX] = "ruc.zip";
	curl = curl_easy_init();
	if (curl) {
		fp = fopen(outfilename, "wb");
		curl_easy_setopt(curl, CURLOPT_URL, url_ruc);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
		res = curl_easy_perform(curl);
		/* always cleanup */
		curl_easy_cleanup(curl);
		fclose(fp);
	}


	libzippp::ZipArchive zf("ruc.zip");
	zf.open(ZipArchive::ReadOnly);

	vector<ZipEntry> entries = zf.getEntries();
	vector<ZipEntry>::iterator it;
	for (it = entries.begin(); it != entries.end(); ++it) {
		ZipEntry entry = *it;
		string name = entry.getName();
		int size = entry.getSize();

		//the length of binaryData will be size
		void* binaryData = entry.readAsBinary();

		//the length of textData will be size
		string textData = entry.readAsText();

		cout << textData;
		//...
	}

	zf.close();

	return 0;


}


