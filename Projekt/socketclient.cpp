#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

using namespace std;

#define DEFAULT_PORT "20175"

int main()
{
	const char* sendbuf = "Testowa wiadomosc!";
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
	struct addrinfo* result = NULL,
		* ptr = NULL,
		hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	int iResult;
	iResult = getaddrinfo("192.168.1.184", DEFAULT_PORT, &hints, &result);
	ptr = result;
	SOCKET ConnectSocket = INVALID_SOCKET;
	ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
	iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);

	if (ConnectSocket == INVALID_SOCKET) {
		cerr << "Nie mozna polaczyc sie z serwerem! Kod: " << iResult << endl;
		WSACleanup();
		return 1;
	}

	iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
	if (iResult == SOCKET_ERROR) {
		cerr << "Nie udalo sie wyslac wiadomosci! Kod: " << WSAGetLastError() << endl;
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}

	cout << "Przeslano " << iResult << " bajtow" << endl;

}