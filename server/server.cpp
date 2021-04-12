#include <iostream>
#include <winsock2.h>
int main() {
	//异步套接字的启动命令
	WSADATA wsadata;
	//第一个参数是版本号，第二个是WSADATA结构体变量的地址值
	WSAStartup(MAKEWORD(2, 2), &wsadata);

	SOCKET ServerSocket;
	//创建一个socket
	//第一个参数是族地址，用于指定下层的网路协议，AF_INET表示使用IPV4
	//第二个参数是套接口类型，SOCK_DGRAM (数据报套接字)一般用于UDP
	//详情：https://blog.csdn.net/qing666888/article/details/50419875
	//第三个参数表示协议
	//三个参数类型都是正整数，这里使用了C++预设定的宏（没有系统学过C++，说法有误请谅解）
	ServerSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);


	//定义了一个网络地址，sockaddr_in是一个结构体1
	sockaddr_in sockAddrIn;
	memset(&sockAddrIn, 0, sizeof(sockAddrIn));
	//指定族地址
	sockAddrIn.sin_family = AF_INET;
	//htons：Host to Network Short 将整型变量从主机字节顺序转变成网络字节顺序
	sockAddrIn.sin_port = htons(9527);
	//INADDR_ANY是一个宏，表示本机
	sockAddrIn.sin_addr.s_addr = inet_addr("127.0.0.1");


	//将创建的socket与地址绑定，返回值为0表示成功，-1表示失败
	int ret = bind(ServerSocket, (sockaddr*)&sockAddrIn, sizeof(sockAddrIn));
	if (ret == SOCKET_ERROR) {
		std::cout << "bind failed" << std::endl;
		return -1;
	}


	while (true) {
		char buf[100] = {0};
		int len=sizeof(sockAddrIn);

		//开始接收信息
		//第一个参数：套接字
		//第二个参数：缓冲区
		//第三个参数：缓冲区大小
		//第四个参数：调用操作方式

		//第五六个参数传递指针，在函数类被修改，函数运行后，分别得到相应的值
		//第五个参数：接收到的地址
		//第六个参数：接收到的信息实际长度
		int recvRet = recvfrom(ServerSocket, buf, sizeof(buf), 0, (sockaddr*)&sockAddrIn, &len);
		//-1表示接收失败
		if (recvRet == -1) {
			Sleep(1000);
			std::cout<<"recieve failed"<<std::endl;
			std::cout << WSAGetLastError() << std::endl;
			continue;
		}

		//将小写字母转换为大写
		for (int i = 0; i < len; i++) {
			if (buf[i] >= 'a'&&buf[i] <= 'z') {
				buf[i] = 'A' + buf[i] - 'a';
			}
		}
		//第五个参数：指定要发送的目标ip和端口号
		//第六个参数：第五个参数的长度
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
