﻿#pragma once

namespace zar
{
	struct ruc_data
	{
		char ruc[12];
		char razon_social[300];
		char estado_contribuyente[50];
		char condicion_domicilio[50];
		char ubigeo[50];
		char tipo_via[50];
		char nombre_via[50];
		char codigo_zona[50];
		char tipo_zona[50];
		char numero[50];
		char interior[50];
		char lote[50];
		char departamento[50];
		char manzana[50];
		char kilometro[50];

		ruc_data()
		{
			strcpy(ruc, "-");
			strcpy(razon_social, "-");
			strcpy(estado_contribuyente, "-");
			strcpy(condicion_domicilio, "-");
			strcpy(ubigeo, "-");
			strcpy(tipo_via, "-");
			strcpy(nombre_via, "-");
			strcpy(codigo_zona, "-");
			strcpy(tipo_zona, "-");
			strcpy(numero, "-");
			strcpy(interior, "-");
			strcpy(lote, "-");
			strcpy(departamento, "-");
			strcpy(manzana, "-");
			strcpy(kilometro, "-");
		}

		void debug()
		{
			strcpy(ruc, "10781991061");
			strcpy(razon_social, "YORDY LEONIDAS MORENO VÁSQUEZ");
			strcpy(estado_contribuyente, "ACTIVO");
			strcpy(condicion_domicilio, "HABIDO");
			strcpy(ubigeo, "-");
			strcpy(tipo_via, "-");
			strcpy(nombre_via, "-");
			strcpy(codigo_zona, "-");
			strcpy(tipo_zona, "-");
			strcpy(numero, "-");
			strcpy(interior, "-");
			strcpy(lote, "-");
			strcpy(departamento, "-");
			strcpy(manzana, "-");
			strcpy(kilometro, "-");
		}

		void print()
		{
			spdlog::info("{}", ruc);
			std::cout << "razon social: " << razon_social << "\n";
			std::cout << "estado contribuyente: " << estado_contribuyente << "\n";
			std::cout << "condicion_domicilio: " << condicion_domicilio << "\n";
			std::cout << "ubigeo: " << ubigeo << "\n";
			std::cout << "tipo_via: " << tipo_via << "\n";
			std::cout << "nombre_via: " << nombre_via << "\n";
			std::cout << "codigo_zona: " << codigo_zona << "\n";
			std::cout << "tipo_zona: " << tipo_zona << "\n";
			std::cout << "numero: " << numero << "\n";
			std::cout << "interior: " << interior << "\n";
			std::cout << "lote: " << lote << "\n";
			std::cout << "departamento: " << departamento << "\n";
			std::cout << "manzana: " << manzana << "\n";
			std::cout << "kilometro: " << kilometro << "\n";
		}
	};
}