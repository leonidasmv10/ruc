//
//#include "../config.h"
//
//#include "libzippp.h"
//
//#include <iostream>
//#include <fstream>
//#include <string>
//
//
//#include <chrono>
//#include <ctime> 
//#include <thread>
//
////#include <mysql/jdbc.h>
//
//#include <vector>
//#include <unordered_map>
//
//
//#define DEFAULT_URI "127.0.0.1"
//#define EXAMPLE_USER "root"
//#define EXAMPLE_PASS ""
//#define EXAMPLE_DB "bflexpe"
//
//bool obtenerZip(const char* localFilePath, const char* url)
//{
//
//	//CkHttp http;
//	/*bool success = http.Download(url, localFilePath);
//	if (success != true) {
//		std::cout << http.lastErrorText() << "\r\n";
//		return false;
//	}*/
//	return true;
//}
//
//bool descomprimirZip(const char* localFilePath, const char* path = "")
//{
//	//CkZip zip;
//
//	//bool success = zip.OpenZip(localFilePath);
//	//if (success != true) {
//	//	std::cout << zip.lastErrorText() << "\r\n";
//	//	return false;
//	//}
//
//	////zip.put_DecryptPassword("myPassword");
//
//	//int unzipCount = zip.Unzip(path);
//	//if (unzipCount < 0) {
//	//	std::cout << zip.lastErrorText() << "\r\n";
//	//}
//	return true;
//}
//
//using namespace libzippp;
//using namespace std;
//
//int main(int argc, const char* argv[])
//{
//
//	libzippp::ZipArchive zf("padron_reducido_ruc.zip");
//	zf.open(ZipArchive::ReadOnly);
//
//	vector<ZipEntry> entries = zf.getEntries();
//	vector<ZipEntry>::iterator it;
//	for (it = entries.begin(); it != entries.end(); ++it) {
//		ZipEntry entry = *it;
//		string name = entry.getName();
//		int size = entry.getSize();
//
//		//the length of binaryData will be size
//		void* binaryData = entry.readAsBinary();
//
//		//the length of textData will be size
//		string textData = entry.readAsText();
//
//		cout << textData;
//		//...
//	}
//
//	zf.close();
//
//	return 0;
//
//}
//
//

//
//#include <stdio.h>
//#include <curl/curl.h>
///* For older cURL versions you will also need
//#include <curl/types.h>
//#include <curl/easy.h>
//*/
//#include <string>
//
//
//
//size_t write_data(void* ptr, size_t size, size_t nmemb, FILE* stream) {
//    size_t written = fwrite(ptr, size, nmemb, stream);
//    return written;
//}
//
//int main(void) {
//
//
//
//    CURL* curl;
//    FILE* fp;
//    CURLcode res;
//    char* url = "http://www2.sunat.gob.pe/padron_reducido_ruc.zip";
//    char outfilename[FILENAME_MAX] = "bbb.zip";
//    curl = curl_easy_init();
//    if (curl) {
//        fp = fopen(outfilename, "wb");
//        curl_easy_setopt(curl, CURLOPT_URL, url);
//        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
//        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
//        res = curl_easy_perform(curl);
//        /* always cleanup */
//        curl_easy_cleanup(curl);
//        fclose(fp);
//    }
//    return 0;
//}

#include <iostream>

#define DEFAULT_URI "127.0.0.1"
#define EXAMPLE_USER "root"
#define EXAMPLE_PASS ""
#define EXAMPLE_DB "bflexpe"
#include <mysql/jdbc.h>


int main(int argc, const char* argv[])
{
	sql::mysql::MySQL_Driver* driver;
	sql::Connection* con;
	sql::ConnectOptionsMap connection_properties;

	const char* url = (argc > 1 ? argv[1] : DEFAULT_URI);
	const std::string user(argc >= 3 ? argv[2] : EXAMPLE_USER);
	const std::string pass(argc >= 4 ? argv[3] : EXAMPLE_PASS);
	const std::string database(argc >= 5 ? argv[4] : EXAMPLE_DB);

	connection_properties[OPT_HOSTNAME] = url;
	connection_properties[OPT_USERNAME] = user;
	connection_properties[OPT_PASSWORD] = pass;
	connection_properties[OPT_PORT] = 3306;
	connection_properties[OPT_SCHEMA] = database;
	connection_properties["OPT_SSL_MODE"] = sql::SSL_MODE_DISABLED;
	connection_properties[OPT_RECONNECT] = true;

	driver = sql::mysql::get_driver_instance();
	driver->threadInit();
}