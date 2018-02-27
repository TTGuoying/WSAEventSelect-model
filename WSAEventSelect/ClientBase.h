#pragma once
#include "stdafx.h"
#include <WinSock2.h>
#include <Windows.h>

// �ͷ�ָ��ĺ�
#define RELEASE(x)			{if(x != NULL) {delete x; x = NULL;}}
// �ͷž���ĺ�
#define RELEASE_HANDLE(x)	{if(x != NULL && x != INVALID_HANDLE_VALUE) { CloseHandle(x); x = INVALID_HANDLE_VALUE; }}
// �ͷ�Socket�ĺ�
#define RELEASE_SOCKET(x)	{if(x != INVALID_SOCKET) { closesocket(x); x = INVALID_SOCKET; }}

class ClientBase
{
public:
	ClientBase();
	~ClientBase();

	// ����ͨ��
	BOOL Start(const char *IPAddress, USHORT port);	
	// �ر�ͨ��
	BOOL Stop();	
	// ��������
	BOOL Send(const BYTE* buffer, int len);	
	// �Ƿ�������
	BOOL HasStarted();	

	// �¼�֪ͨ����(���������ش��庯��)
	// ���ӹر�
	virtual void OnConnectionClosed() = 0;
	// �����Ϸ�������
	virtual void OnConnectionError() = 0;
	// ���������
	virtual void OnRecvCompleted(BYTE* buffer, int len) = 0;
	// д�������
	virtual void OnSendCompleted() = 0;

private:
	// �����̺߳���
	static DWORD WINAPI RecvThreadProc(LPVOID lpParam); 
	// socket�Ƿ���
	BOOL IsSocketAlive(SOCKET sock);
	SOCKET clientSock;
	WSAEVENT socketEvent;
	HANDLE stopEvent;
	HANDLE thread;
};

