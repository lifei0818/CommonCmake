#include <iostream>
#include <winsock2.h>
int main() {
	//�첽�׽��ֵ���������
	WSADATA wsadata;
	//��һ�������ǰ汾�ţ��ڶ�����WSADATA�ṹ������ĵ�ֵַ
	WSAStartup(MAKEWORD(2, 2), &wsadata);

	SOCKET ServerSocket;
	//����һ��socket
	//��һ�����������ַ������ָ���²����·Э�飬AF_INET��ʾʹ��IPV4
	//�ڶ����������׽ӿ����ͣ�SOCK_DGRAM (���ݱ��׽���)һ������UDP
	//���飺https://blog.csdn.net/qing666888/article/details/50419875
	//������������ʾЭ��
	//�����������Ͷ���������������ʹ����C++Ԥ�趨�ĺ꣨û��ϵͳѧ��C++��˵���������½⣩
	ServerSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);


	//������һ�������ַ��sockaddr_in��һ���ṹ��1
	sockaddr_in sockAddrIn;
	memset(&sockAddrIn, 0, sizeof(sockAddrIn));
	//ָ�����ַ
	sockAddrIn.sin_family = AF_INET;
	//htons��Host to Network Short �����ͱ����������ֽ�˳��ת��������ֽ�˳��
	sockAddrIn.sin_port = htons(9527);
	//INADDR_ANY��һ���꣬��ʾ����
	sockAddrIn.sin_addr.s_addr = inet_addr("127.0.0.1");


	//��������socket���ַ�󶨣�����ֵΪ0��ʾ�ɹ���-1��ʾʧ��
	int ret = bind(ServerSocket, (sockaddr*)&sockAddrIn, sizeof(sockAddrIn));
	if (ret == SOCKET_ERROR) {
		std::cout << "bind failed" << std::endl;
		return -1;
	}


	while (true) {
		char buf[100] = {0};
		int len=sizeof(sockAddrIn);

		//��ʼ������Ϣ
		//��һ���������׽���
		//�ڶ���������������
		//��������������������С
		//���ĸ����������ò�����ʽ

		//����������������ָ�룬�ں����౻�޸ģ��������к󣬷ֱ�õ���Ӧ��ֵ
		//��������������յ��ĵ�ַ
		//���������������յ�����Ϣʵ�ʳ���
		int recvRet = recvfrom(ServerSocket, buf, sizeof(buf), 0, (sockaddr*)&sockAddrIn, &len);
		//-1��ʾ����ʧ��
		if (recvRet == -1) {
			Sleep(1000);
			std::cout<<"recieve failed"<<std::endl;
			std::cout << WSAGetLastError() << std::endl;
			continue;
		}

		//��Сд��ĸת��Ϊ��д
		for (int i = 0; i < len; i++) {
			if (buf[i] >= 'a'&&buf[i] <= 'z') {
				buf[i] = 'A' + buf[i] - 'a';
			}
		}
		//�����������ָ��Ҫ���͵�Ŀ��ip�Ͷ˿ں�
		//����������������������ĳ���
		int sendRet = sendto(ServerSocket, buf, sizeof(buf), 0, (sockaddr*)&sockAddrIn, sizeof(sockAddrIn));
		if (sendRet == -1) {
			std::cout << "send failed" << std::endl;
			break;
		}
		else {
			std::cout << "send success" << std::endl;
		}
	}

	return 0;
}
