#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string>
#include <sys/stat.h>
#include <sys/types.h>
//网络通信需要包含的头文件，需要  的库
#include<winSOck2.h>
#pragma comment(lib,"WS2_32.lib")
#define PRINTF(str) printf("%s\n",str);
void server_file(int client, const char* filename);
void error_die(const char* str) {
	perror(str);
	exit(1);
}

int get_line(int sock, char* buff, int size) {
	char c = 0;
	int idx = 0;
	while (idx<size-1 && c!='\n') {
		int n = recv(sock, &c,1,0);
		if (n > 0) {
			if (c == '\r') {
				n = recv(sock, &c, 1, MSG_PEEK);
				if (n > 0 && c == '\n') {
					recv(sock, &c, 1, 0);
				} 
				else {
					c = '\n'; 
				}
			}
			buff[idx++] = c;
		}
		else {
			c = '\n';
		}
	}
	buff[idx] = 0;
	return idx;
}


int startup(unsigned short *port) {//实现网络初始化
	 // 1.网络通信的初始化
	WSADATA date;
	int ret = WSAStartup(MAKEWORD(1, 1), &date);
	if (ret) {
		error_die("WSAStartup");
	}

	int server_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (server_socket == -1) {
		// 打印错误提示
		error_die("套接字");
	}

	//设置端口可复用
	int opt = 1;
	ret = setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR,(const char*) &opt,sizeof(opt));
	
	if (ret==-1) {
		error_die("setsockopt");
	}
	//配置服务器端网络地址
	struct sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(*port); 
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	//绑定套接字
	int A_ret = bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));
	if (A_ret < 0) {
		error_die("bind");
	}
	//动态分配端口
	int namelen = sizeof(server_addr);
	if (*port == 0) {
		if (getsockname(server_socket, (struct sockaddr*)&server_addr,
			&namelen) < 0) {
			error_die("getsockname");
		}
		*port = server_addr.sin_port;
	}

	if (listen(server_socket, 5) < 0) {
		error_die("listen");
	}
	return server_socket;
}

void not_found(int client) {
	char path[1024] = "htdocs/404.html";
	server_file(client, path);
	//......to do
}

void headers(int client) {
	char buff[1024];

	strcpy(buff, "HTTP/1.0 200 OK\r\n");
	send(client, buff, strlen(buff), 0);

	strcpy(buff, "Server:liniHttpd/0.1\r\n");
	send(client, buff, strlen(buff), 0);

	strcpy(buff, "Content-type:text/html \n");
	send(client, buff, strlen(buff), 0);

	strcpy(buff, "\r\n");
	send(client, buff, strlen(buff), 0);
}


void cat(int client, FILE* resoure) {
	char buff[4096];
	int count = 0;
	while (1) {
		int ret = fread(buff, sizeof(char), sizeof(buff), resoure);
		if (ret <= 0) {
			break;
		}
		send(client, buff, ret, 0);
		count += ret;
	}
	printf("const=%d\n", count);

}

void server_file(int client, const char* filename) {
	int number = 1;
	char buff[1024];
	while (number > 0 && strcmp(buff, "\n")) {
		number = get_line(client, buff, sizeof(buff));
		PRINTF(buff);
	}
	FILE* resource = NULL;
	if (strcmp(filename, "htdocs/index.html") == 0) {
		resource = fopen(filename, "r");
	}
	else {
		resource = fopen(filename, "rb");
	}
	 
	if (resource == NULL) {
		not_found(client);
	}
	else {
		headers(client);
		 
		cat(client, resource);

		printf("发送完毕");
	}
	fclose(resource);
	
	//......to do
}

DWORD WINAPI accept_request(LPVOID arg) {
	char buff[1024];

	int client = (SOCKET)arg;

	int num = get_line(client, buff, sizeof(buff));
	printf("buff = %s \n", buff);
	char method[255];
	int idx=0,j=0;
	while (!isspace(buff[j]) && idx < sizeof(method) - 1) {
		method[idx++] = buff[j++];
	}
	method[idx] = 0;//字符串截止符
	PRINTF(method);
	if (_stricmp(method, "GET") && _stricmp(method, "POST")) {
		return 0;
	}

	char url[255];
	while (isspace(buff[j]) && j < sizeof(buff)) {
		j++;
	}
	idx = 0;
	while (!isspace(buff[j]) && idx < sizeof(url) - 1 && j < sizeof(buff)) {
		url[idx++] = buff[j++];
	}
	url[idx] = 0;
	PRINTF(url);
	char path[512]="";
	sprintf(path,"htdocs%s", url);
	if (path[strlen(path) - 1] == '/') {
		strcat(path,"index.html");
	}
 	PRINTF(path);
	struct stat status;
	if (stat(path, &status) == -1) {
		int num=1;
		/*while (num > 0 && strcmp(buff, "\n")) {
			num = get_line(client, buff, sizeof(buff));
		}*/
		not_found(client); 
	}
	else {
		if ((status.st_mode & S_IFMT) == S_IFDIR){
			strcat(path, "/index.html");
		}
		server_file(client, path);
		 
	}
	closesocket(client);
	return 0;
}

int main(void) {
	unsigned short port = 8099;
	int server_sock = startup(&port);
	printf("httpd服务已经启动，正在监听 %d 端口\n", port);


	

	while (1) {
		struct sockaddr_in client_addr;
		int client_addr_len = sizeof(client_addr);

		int client_sock = accept(server_sock, (struct sockaddr*)&client_addr,
			&client_addr_len);
		if (client_sock == -1) {
			error_die("accept");
		}

		DWORD threadid = 0;
		CreateThread(0, 0, accept_request, (void*)client_sock, 0, &threadid);
	}
	
	closesocket(server_sock);


	return 0;
}





























