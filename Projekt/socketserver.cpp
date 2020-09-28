#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")
#define APP_PORT "27015"
#define BUFLEN 512

using namespace std;

int sockmain()
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
	memset(&hints, 0, sizeof(hints));
	int addrResult = getaddrinfo("127.0.0.1", APP_PORT, &hints, &result);
	if (addrResult != 0)
	{
		cerr << "Nie mozna uzyskac adresu ip kod: " << addrResult << endl;
		WSACleanup();
		return addrResult;
	}
	ptr = result;
	SOCKET ListenSocket = INVALID_SOCKET;
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET)
	{
		cerr << "Blad tworzenia socketa" << endl;
		WSACleanup();
		return 1;
	}
	// Bind
	int bindResult;
	bindResult = bind(ListenSocket, result->ai_addr, (int)(result->ai_addrlen));
	if (bindResult == SOCKET_ERROR)
	{
		cerr << "Blad bindowania adresu ip" << endl;
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}
	// Put socket on listen mode
	if (listen(ListenSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	cout << "Oczekiwanie na polaczenie..." << endl;
	SOCKET ClientSocket;
	ClientSocket = accept(ListenSocket, nullptr, nullptr);
	if (ClientSocket == INVALID_SOCKET)
	{
		closesocket(ListenSocket);
		WSACleanup();
		cerr << "Blad podczas laczenia." << endl;
		return 1;
	}

	// Odbieranie danych od klienta
	char recvbuf[BUFLEN];
	do {
		int bytesRecieved = recv(ClientSocket, recvbuf, BUFLEN, 0);
		if (bytesRecieved > 0)
		{
			cout << "Otrzymano wiadomosc:" << endl;
			cout << recvbuf << endl;
		}
	} while (true);
	return 0;
}