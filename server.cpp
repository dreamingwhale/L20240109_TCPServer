#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>

using namespace std;

#pragma comment(lib, "ws2_32")

#pragma pack(push, 1)

typedef struct _Data
{
	int FirstNumber;
	int SecondNumber;
	char Operator;
} Data;
#pragma pack(pop)

int main()
{
	srand((u_int)(time(nullptr)));

	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET ListenSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	struct sockaddr_in ListenSockAddr;
	memset(&ListenSockAddr, 0, sizeof(ListenSockAddr));
	ListenSockAddr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &(ListenSockAddr.sin_addr.s_addr));
	ListenSockAddr.sin_port = htons(5001);

	bind(ListenSocket, (struct sockaddr*)&ListenSockAddr, sizeof(ListenSockAddr));

	listen(ListenSocket, 5);

	struct sockaddr_in ClinetSockAddr;
	memset(&ClinetSockAddr, 0, sizeof(ClinetSockAddr));
	int ClientSockAddrLength = sizeof(ClinetSockAddr);
	SOCKET ClientSocket = accept(ListenSocket, (struct sockaddr*)&ClinetSockAddr, &ClientSockAddrLength);

	while (true)
	{
		//char Message[9] = { 0, };

		Data Packet;
		// 0 ~ 9999
		Packet.FirstNumber = (rand() % 20000) - 10000;
		// 1 ~ 9999
		Packet.SecondNumber = (rand() % 20000) - 10000;
		Packet.SecondNumber == 0 ? 1 : Packet.SecondNumber;
		////[0][0][0][0][][][][][]
		//memcpy(&Message[0], &FirstNumber, sizeof(int));
		////[0][0][0][0][1][1][1][1][]
		//memcpy(&Message[4], &SecondNumber, sizeof(int));
		////[0][0][0][0][1][1][1][1][2]
		Packet.Operator = rand() % 5;

		send(ClientSocket, (char*)&Packet, (u_int)sizeof(Packet), 0);

		char Buffer[1024] = { 0, };
		int RecvByte = recv(ClientSocket, Buffer, 1024, 0);
		if (RecvByte <= 0)
		{
			break;
		}

		long long Result = 0;
		memcpy(&Result, Buffer, sizeof(Result));
		cout << Result << endl;
	}

	closesocket(ClientSocket);
	closesocket(ListenSocket);

	WSACleanup();

	return 0;
}