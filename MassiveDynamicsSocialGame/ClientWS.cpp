#include "ClientWS.h"
#include <string>#include <iostream>#include <stdlib.h>
#include "grafos.h"

#include <conio.h>

#include <vector>

using namespace std;

bool login()
{
	HRESULT hr = ERROR_SUCCESS;
	WS_ERROR* error = NULL;
	WS_HEAP* heap = NULL;
	WS_SERVICE_PROXY* proxy = NULL;

	WS_ENDPOINT_ADDRESS address = {};

	WS_STRING url = WS_STRING_VALUE(L"http://172.31.101.112/MassiveDynamicsWService.svc");

	address.url = url;

	hr = WsCreateHeap(2048, 512, NULL, 0, &heap, error);
	WS_HTTP_BINDING_TEMPLATE templ = {};
	hr = BasicHttpBinding_IMassiveDynamicsWService_CreateServiceProxy(&templ, NULL, 0, &proxy, error);
	hr = WsOpenServiceProxy(proxy, &address, NULL, error);



	string username = "";
	string password = "";
	cout << "Introduza Username: ";
	cin >> username;
	const char HIDING_CHARACTER = '*';

	char ch;
	const char ENTER = 13;

	cout << endl << "Introduza Password: ";

	while ((ch = _getch()) != ENTER)
	{
		password += ch;
		std::cout << '*';
	}

	cout << endl;

	wstring u(username.begin(), username.end());
	const WCHAR * user = u.c_str();

	wstring p(password.begin(), password.end());
	const WCHAR * pass = p.c_str();

	BOOL  result;

	hr = BasicHttpBinding_IMassiveDynamicsWService_authenticate(proxy, (WCHAR*)user, (WCHAR*)pass, &result, heap, NULL, 0, NULL, error);

	if (!result)
		cout << "Username ou password invalidos!" << endl;
	else{
		nomeInicial = username;
		cout << "Autenticacao com sucesso!" << endl;
	}
	
	system("pause");

	if (proxy)
	{
		WsCloseServiceProxy(proxy, NULL, NULL);
		WsFreeServiceProxy(proxy);
	}

	if (heap)
	{
		WsFreeHeap(heap);
	}

	if (error)
	{
		WsFreeError(error);
	}

	return result;
}std::vector<std::string> explode(const string& str, const char& ch) {
	string next;
	vector<string> result;

	// For each character in the string
	for (string::const_iterator it = str.begin(); it != str.end(); it++) {
		// If we've hit the terminal character
		if (*it == ch) {
			// If we have some characters accumulated
			if (!next.empty()) {
				// Add them to the result vector
				result.push_back(next);
				next.clear();
			}
		}
		else {
			// Accumulate the next character into the sequence
			next += *it;
		}
	}
	if (!next.empty())
		result.push_back(next);
	return result;
}void criaNos(){	HRESULT hr = ERROR_SUCCESS;
	WS_ERROR* error = NULL;
	WS_HEAP* heap = NULL;
	WS_SERVICE_PROXY* proxy = NULL;

	WS_ENDPOINT_ADDRESS address = {};

	WS_STRING url = WS_STRING_VALUE(L"http://172.31.101.112/MassiveDynamicsWService.svc");

	address.url = url;

	hr = WsCreateHeap(2048, 512, NULL, 0, &heap, error);
	WS_HTTP_BINDING_TEMPLATE templ = {};
	hr = BasicHttpBinding_IMassiveDynamicsWService_CreateServiceProxy(&templ, NULL, 0, &proxy, error);
	hr = WsOpenServiceProxy(proxy, &address, NULL, error);


	WCHAR * result;
	hr = BasicHttpBinding_IMassiveDynamicsWService_getUsers(proxy, &result, heap, NULL, 0, NULL, error);


	int size = wcslen(result);
	char *lista_res = (char *)malloc(size);
	char DefChar = ' ';
	WideCharToMultiByte(CP_ACP, 0, result, -1, lista_res, size * 2, &DefChar, NULL);


	std::vector<std::string> r = explode(lista_res, ';');


	int nos_qtd = 0;
	for (size_t i = 0; i < r.size(); i++) {
		if (i==0){
			numNos = atoi(r[0].c_str());
		}
		else {
			nos[nos_qtd].setNome(r[i]);
			if (nos[i-1].getNome()==nomeInicial){
				noInicial = i - 1;
			}
			i++;
			nos_qtd++;
		}

	}



	if (proxy)
	{
		WsCloseServiceProxy(proxy, NULL, NULL);
		WsFreeServiceProxy(proxy);
	}

	if (heap)
	{
		WsFreeHeap(heap);
	}

	if (error)
	{
		WsFreeError(error);
	}}void criaArcos(){	HRESULT hr = ERROR_SUCCESS;
	WS_ERROR* error = NULL;
	WS_HEAP* heap = NULL;
	WS_SERVICE_PROXY* proxy = NULL;

	WS_ENDPOINT_ADDRESS address = {};

	WS_STRING url = WS_STRING_VALUE(L"http://172.31.101.112/MassiveDynamicsWService.svc");

	address.url = url;

	hr = WsCreateHeap(2048, 512, NULL, 0, &heap, error);
	WS_HTTP_BINDING_TEMPLATE templ = {};
	hr = BasicHttpBinding_IMassiveDynamicsWService_CreateServiceProxy(&templ, NULL, 0, &proxy, error);
	hr = WsOpenServiceProxy(proxy, &address, NULL, error);


	WCHAR * result2;
	hr = BasicHttpBinding_IMassiveDynamicsWService_getRelacoes(proxy, &result2, heap, NULL, 0, NULL, error);

	

	int size2 = wcslen(result2);
	char *lista_res2 = (char *)malloc(size2);
	char DefChar2= ' ';
	WideCharToMultiByte(CP_ACP, 0, result2, -1, lista_res2, size2 * 2, &DefChar2, NULL);


	std::vector<std::string> r2 = explode(lista_res2, ';');


	int n_arco = 0;
	int lenth = r2.size();
	int i = 0;
	int n = 0;
	for (i = 0; i < lenth; i = i + 2){
		for (n = 0; n < numNos; n++){
			if (nos[n].getNome() == r2[i]){
				arcos[n_arco].noi = n;
			}
			if (nos[n].getNome() == r2[i + 1]){
				arcos[n_arco].nof = n;
			}
		}
			
		
		arcos[n_arco].largura = 1;
		n_arco++;
	}

	 
	
	numArcos = n_arco;

	/*for (int i = 0; i < numNos; i++){
		cout << "nos[" << i << "] nome = " << nos[i].getNome() << endl;
	}
	for (int i = 0; i < numArcos; i++){
		cout << "arco["<<i<<"] noi = "<<arcos[i].noi << endl;
		cout << "arco[" << i << "] nof = " << arcos[i].nof << endl;
	}

	system("pause");*/
	if (proxy)
	{
		WsCloseServiceProxy(proxy, NULL, NULL);
		WsFreeServiceProxy(proxy);
	}

	if (heap)
	{
		WsFreeHeap(heap);
	}

	if (error)
	{
		WsFreeError(error);
	}}