#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")
#define APP_PORT "21370"

using namespace std;

int main()
{
	WSADATA wsaData;
	int wsResult;
	wsResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (wsResult != 0)
	{
		cout << "Nie mozna uruchomic WinSock kod: " << wsResult << endl;
		return wsResult;
	}
	// Create socket
	// Get ip
	struct addrinfo* result = NULL, * ptr = NULL, hints;
	int addrResult = getaddrinfo(NULL, APP_PORT, &hints, &result);
	if (addrResult != 0)
	{
		cerr << "Nie mozna uzyskac adresu ip" << endl;
		WSACleanup();
		return addrResult;
	}
	ptr = result;
	SOCKET ListenSocket = INVALID_SOCKET;
	ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ListenSocket == INVALID_SOCKET)
	{
		cerr << "Blad tworzenia socketa" << endl;
		WSACleanup();
		return 1;
	}
	// Bind
	
	return 0;
}