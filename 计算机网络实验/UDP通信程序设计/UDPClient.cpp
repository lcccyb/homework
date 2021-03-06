#include "pch.h"
#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#pragma comment(lib,"ws2_32.lib")
#define WSVERS MAKEWORD(2,0)
//客户端
int main()
{
	printf("UDP客户端已启动(服务器默认端口号:9999)[By Janking]...\n");
	WSADATA wsadata;
	int port = 9999;
	char ip[20];
	printf("\n!警告! 我没有做异常处理，请不要乱输入!\n");
	printf("\n!警告! 自动接收模式下最后一位可能为乱码，不用担心!\n");
	printf("\n请输入服务器ip地址(输入1默认为:127.0.0.1):\n");
	scanf("%s", ip);
	if (ip[0] == '1' && ip[1] == '\0')
		strcpy(ip, "127.0.0.1");
	printf("服务器默认端口号: 9999\n");

	//缓存收到的数据
	char response[100000];
	if (WSAStartup(WSVERS, &wsadata) != 0) {
		printf("WSAStartup failed!\n");
		return -1;
	}    //初始化

	printf_s("\n客户端正在初始化......\n\n");
	SOCKET soc_client = socket(AF_INET, SOCK_DGRAM, 0);
	SOCKADDR_IN addr_server;   //服务器的地址数据结构
	addr_server.sin_family = AF_INET;
	addr_server.sin_port = htons(port);//端口号
	addr_server.sin_addr.S_un.S_addr = inet_addr(ip);   //127.0.0.1为本电脑IP地址
	
	//临时变量
	int len = sizeof(SOCKADDR_IN);
	//mode select
	int mode = 0;
	printf("请输入数字决定发送数据模式(1:自动)(2:手动):\n");
	scanf("%d", &mode);
	//手动模式
	if (mode != 1) {
		while (1) {
			char message[100] = "helloworld";
			printf_s("\n输入要发送的数据：\n");
			scanf("%s", message);
			//发送数据
			sendto(soc_client, message, strlen(message), 0, (SOCKADDR*)&addr_server, sizeof(SOCKADDR));
			printf("\n正在接收数据...\n");
			int count = recvfrom(soc_client, response, strlen(response), 0, (SOCKADDR*)&addr_server, &len);
			if (count >= 0) {
				response[count] = '\0';      //给字符数组加一个'\0'
				printf("*** 收到数据：%s\n", response);
				printf("------来自： IP:[%s] Port:[%d]\n", inet_ntoa(addr_server.sin_addr), ntohs(addr_server.sin_port));
			}
			else {
				printf("ERROR: %d", WSAGetLastError());
				break;
			}
		}
	}
	//自动模式
	else {
		for(int i = 0; i < 100;i++) {
			char message[15] = "Message No.";
			char num[5];
			itoa(i, num, 10);
			strcat(message, num);
			//发送数据
			sendto(soc_client, message, strlen(message), 0, (SOCKADDR*)&addr_server, sizeof(SOCKADDR));
			printf("已发送数据: %s\n",message);
			Sleep(10);
		}
	}

	//关闭连接
	closesocket(soc_client);
	WSACleanup();
	printf("已退出客户端!\n");
	return 0;
}
