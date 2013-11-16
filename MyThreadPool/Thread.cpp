// Thread.cpp: implementation of the CThread class.
//
//////////////////////////////////////////////////////////////////////

#include "Thread.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CThread::CThread()
{
	m_ThreadHandle = NULL;
}

CThread::~CThread()
{
	//���ﱾ����Ҫ���߳̽��йرգ���ȫ��Ϊ�˱����������Ϊ��������CWorkerThread�е�Terminate�������Ѿ��������̹߳ر���
	if (m_ThreadHandle != NULL)
	{
		int ret;
		ret = ::WaitForSingleObject(m_ThreadHandle,100);//ʱ�䲻��̫�̣���������̵߳�ʱ��ᱻ��ס
		if (WAIT_OBJECT_0 != ret)
		{
			DWORD dwExitCode;
			GetExitCodeThread(m_ThreadHandle,&dwExitCode);
			if (STILL_ACTIVE ==dwExitCode)
			{
				TerminateThread(m_ThreadHandle,dwExitCode);
				::CloseHandle(m_ThreadHandle);
			}
		}
		m_ThreadHandle = NULL;
	}
}
DWORD CThread::_ThreadFunction(LPVOID lpParam) 
{
    CThread* t = (CThread*) lpParam;
	t->Run();
	return 0xCC44;
}

HANDLE CThread::Start(CThread* cthread)
{
    
	m_ThreadHandle = CreateThread(NULL, 0, _ThreadFunction, (LPVOID)cthread, 0, &m_ThreadIDReal);
//    printf("CThread::CThread|thread has been created, id is:%lu\n",GetThreadID());
    return m_ThreadHandle;
    
}

BOOL CThread::ThreadRun(LPVOID lpParam)
{
	CThread* t = (CThread*) lpParam;
	
	return FALSE;
}

DWORD CThread::GetThreadIdReal()
{
return m_ThreadIDReal;
}
