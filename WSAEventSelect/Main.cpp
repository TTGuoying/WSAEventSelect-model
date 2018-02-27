#include "ClientBase.h"
#include <stdio.h>

class Client : public ClientBase
{
public:
	// 连接关闭
	virtual void OnConnectionClosed()
	{
		printf("   Close\n");
	}
	// 连接上发生错误
	virtual void OnConnectionError()
	{
		printf("   Error\n");
	}
	// 读操作完成
	virtual void OnRecvCompleted(BYTE* buffer, int len)
	{
		printf("recv[%d]:%s\n", len, (char*)buffer);
	}
	// 写操作完成
	virtual void OnSendCompleted()
	{
		printf("*Send success\n");
	}

};

int main()
{
	Client client;
	if (!client.Start("127.0.0.1", 10240))
	{
		printf("   start error\n");
	}

	int i = 0;
	while (true)
	{
		char buff[128];
		/*scanf_s("%s", &buff, 128);
		*/

		sprintf_s(buff, 128, "第%d条Msg", i++);
		Sleep(500);
		client.Send((BYTE*)buff, strlen(buff)+1);
	}
}