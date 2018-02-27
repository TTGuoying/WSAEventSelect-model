#include "ClientBase.h"
#include <stdio.h>

class Client : public ClientBase
{
public:
	// ���ӹر�
	virtual void OnConnectionClosed()
	{
		printf("   Close\n");
	}
	// �����Ϸ�������
	virtual void OnConnectionError()
	{
		printf("   Error\n");
	}
	// ���������
	virtual void OnRecvCompleted(BYTE* buffer, int len)
	{
		printf("recv[%d]:%s\n", len, (char*)buffer);
	}
	// д�������
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

		sprintf_s(buff, 128, "��%d��Msg", i++);
		Sleep(500);
		client.Send((BYTE*)buff, strlen(buff)+1);
	}
}