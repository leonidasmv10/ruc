#pragma once
#include <stdio.h>
#include <curl\curl.h>

namespace zar
{
	class http {
	public:

		static bool execute(const char* url, const char* out_file_name)
		{
			/*CURL* curl;
			FILE* fp;
			CURLcode res;
			curl = curl_easy_init();
			if (curl) {
				fp = fopen(out_file_name, "wb");
				curl_easy_setopt(curl, CURLOPT_URL, url);
				curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
				curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
				res = curl_easy_perform(curl);

				curl_easy_cleanup(curl);
				fclose(fp);
				return true;
			}
			return false;*/
			return true;
		}

	private:

		static size_t write_data(void* ptr, size_t size, size_t nmemb, FILE* stream) {
			size_t written = fwrite(ptr, size, nmemb, stream);
			return written;
		}

	};
}
