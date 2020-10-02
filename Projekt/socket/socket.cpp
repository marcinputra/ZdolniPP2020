#include <iostream>
// biblioteki pozwalające na przepływ informacji
#include <WS2tcpip.h>

#pragma comment (lib, "ws2_32.lib")
// Komentarz #pragma wskazuje konsolidatorowi, że potrzebny jest plik Ws2_32.lib

using namespace std;

void main() 
{

	// inicjowanie winsock
	WSADATA wsaData;
	WORD ver = MAKEWORD(2, 2);
	/*
		Parametr MAKEWORD (2,2) WSAStartup 
		wysyła żądanie wersji 2.2 Winsock 
		w systemie i ustawia przekazaną wersję
		jako najwyższą wersję obsługi gniazd 
		Windows, z której może korzystać 
		wywołujący.
	*/
	int wsOK = WSAStartup(ver, &wsaData);
	/*
		Funkcja WSAStartup jest wywoływana 
		w celu zainicjowania użycia WS2_32.dll
	*/
	if (wsOK != 0) {
		cout << "Nie moge zainicjowac winsock! Koniec\n";
		return; // koniec programu
	}

	// utworzenie socketu (gniazda)
	SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, 0);

	// sprawdzenie gniazda czy jest prawidłowe
	if (listenSocket == INVALID_SOCKET) {
		cout << "Bload gniazda (socket)\n";
		return;
	}
	// powiązanie (bind) gniazda z adresem IP i portem
	sockaddr_in gHadd;
	gHadd.sin_family = AF_INET;
	gHadd.sin_port = htons(54000); // Funkcja htons konwertuje u_short z hosta na kolejność bajtów sieci TCP / IP (czyli big-endian)
	gHadd.sin_addr.S_un.S_addr = INADDR_ANY; // mozliwe jest przez uzycie inet_pton
	
	bind(listenSocket, (sockaddr*)&gHadd, sizeof(gHadd));

	// nasłuchiwać na tym adresie IP i porcie pod kątem przychodzących żądań połączenia
	listen(listenSocket, SOMAXCONN); // Funkcja nasłuchiwania umieszcza gniazdo w stanie, w którym nasłuchuje połączenia przychodzącego.

	// czekanie na połączenie (akceptacja połączenie w gnieździe)
	sockaddr_in client;	// Struktura SOCKADDR_IN określa adres transportowy i port dla rodziny adresów AF_INET .
	int  clientSize = sizeof(client);
	SOCKET clientSocket = accept(listenSocket,(sockaddr*)&)




	// odbiernie i wysylanie danych na serwer
	// funkcje recv i send używane przez serwer

	// Gdy serwer zakończy odbieranie danych od klienta i wysyłanie danych z powrotem do klienta, odłącza się od klienta i zamyka gniazdo.

	// zamknięcie socketu (gniazda)

	// zamknięcie winsock



}
-------------------------------
#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

int __cdecl main(void)
{
	WSADATA wsaData;
	int iResult;

	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET ClientSocket = INVALID_SOCKET;

	struct addrinfo* result = NULL;
	struct addrinfo hints;

	int iSendResult;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the server address and port
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	// Create a SOCKET for connecting to server
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		printf("socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

	// Setup the TCP listening socket
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	freeaddrinfo(result);

	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	// Accept a client socket
	ClientSocket = accept(ListenSocket, NULL, NULL);
	if (ClientSocket == INVALID_SOCKET) {
		printf("accept failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	// No longer need server socket
	closesocket(ListenSocket);

	// Receive until the peer shuts down the connection
	do {

		iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0) {
			printf("Bytes received: %d\n", iResult);

			// Echo the buffer back to the sender
			iSendResult = send(ClientSocket, recvbuf, iResult, 0);
			if (iSendResult == SOCKET_ERROR) {
				printf("send failed with error: %d\n", WSAGetLastError());
				closesocket(ClientSocket);
				WSACleanup();
				return 1;
			}
			printf("Bytes sent: %d\n", iSendResult);
		}
		else if (iResult == 0)
			printf("Connection closing...\n");
		else {
			printf("recv failed with error: %d\n", WSAGetLastError());
			closesocket(ClientSocket);
			WSACleanup();
			return 1;
		}

	} while (iResult > 0);

	// shutdown the connection since we're done
	iResult = shutdown(ClientSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(ClientSocket);
		WSACleanup();
		return 1;
	}

	// cleanup
	closesocket(ClientSocket);
	WSACleanup();

	return 0;
}
