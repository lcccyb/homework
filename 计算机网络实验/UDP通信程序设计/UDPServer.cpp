#include "pch.h"
#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#pragma comment(lib,"ws2_32.lib")
#define WSVERS MAKEWORD(2,0)
#define _WINSOCK_DEPRECATED_NO_WARNINGS

//服务端
int main()
{
	printf("UDP服务器已启动(服务器默认端口号:9999)[By Janking]...\n");
	int port = 9999;
	printf("\n!警告! 我没有做异常处理，请不要乱输入!\n");
	WSADATA wsadata;
	//缓存收到的数据
	
	if (WSAStartup(WSVERS, &wsadata) != 0) {
		printf("WSAStartup failed!\n");
		return -1;
	}    //初始化

	printf_s("\n服务器正在初始化......\n\n");
	//建立一个UDP的socket
	SOCKET soc_server = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	SOCKADDR_IN addr;   //地址数据结构
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);//端口号为9999
	addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	bind(soc_server, (sockaddr*)&addr, sizeof(sockaddr));

	int len = sizeof(SOCKADDR);
	//mode select
	int mode = 0;
	printf("请输入数字决定接收数据模式(1:自动)(2:手动):\n");
	scanf("%d", &mode);
	//内存初始化
	SOCKADDR_IN client;
	memset(&client, 0, sizeof(addr));
	//手动模式
	if (mode != 1) {
		while (1) {
			printf("\n正在接收数据...\n");
			//接收
			char response[10000];
			int count = recvfrom(soc_server, response, strlen(response), 0, (SOCKADDR*)&client, &len);
			if (count >= 0) {
				response[count] = '\0';      //给字符数组加一个'\0'
				printf("*** 收到数据：%s\n", response);
				printf("------来自： IP:[%s] Port:[%d]\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
			}
			else {
				printf("ERROR: %d", WSAGetLastError());
				break;
			}
			//发送数据
			char message[100] = "helloworld";
			printf_s("\n输入要发送的数据：\n");
			scanf("%s", message);
			sendto(soc_server, message, strlen(message), 0, (sockaddr*)&client, len);
		}
	}
	//自动模式
	else{
		printf("\n等待接收数据...\n");
		while(1) {
			//接收
			char response[1000000];
			int count = recvfrom(soc_server, response, strlen(response), 0, (SOCKADDR*)&client, &len);
			if (count >= 0) {
				response[count + 2] = '\0';      //给字符数组加一个'\0'
				printf("收到数据：%s\n",response);
				printf("------来自： IP:[%s] Port:[%d]\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
			}
			else {
				printf("%d", WSAGetLastError());
				break;
			}
		}
	}
	printf("已退出服务器!\n");
	return 0;
}
