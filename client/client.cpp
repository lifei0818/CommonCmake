#include <iostream>
#include <winsock2.h>
int main() {

	WSADATA wsadata;
	WSAStartup(MAKEWORD(2, 2), &wsadata);

	SOCKET Client;
	Client = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);


	sockaddr_in sockAddrIn;
	memset(&sockAddrIn, 0, sizeof(sockAddrIn));
	sockAddrIn.sin_family = AF_INET;
	sockAddrIn.sin_port = htons(9527);
	sockAddrIn.sin_addr.s_addr = inet_addr("127.0.0.1");



	//设置socket的选项
	int time_out = 2000;
	if (setsockopt(Client, SOL_SOCKET, SO_RCVTIMEO, (char*)&time_out, sizeof(time_out)) != 0) {
		return -1;
	}

	while (true) {
		char buf[100];
		int len = sizeof(sockAddrIn);
#if 1
		scanf("%s", buf);
		int sendRet = sendto(Client, buf, sizeof(buf), 0, (sockaddr*)&sockAddrIn, sizeof(sockAddrIn));
		if (sendRet == -1) {
			std::cout << WSAGetLastError() << std::endl;
			std::cout << "send failed" << std::endl;
			break;
		}
		else {
			std::cout << "send success" << std::endl;
		}
#endif
		int recvRet = recvfrom(Client, buf, sizeof(buf), 0, (sockaddr*)&sockAddrIn, &len);
		if (recvRet == -1) {
			continue;
		}
		else {
			std::cout << buf << std::endl;
		}
	}
	return 0;
}