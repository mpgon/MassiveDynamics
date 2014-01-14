#include "ClientWS.h"
#include <string> 
#include <iostream> 
#include <stdlib.h>
#include <conio.h>

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
	else
		cout << "Autenticacao com sucesso!" << endl;
	
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
}