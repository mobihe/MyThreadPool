// WorkerThread.cpp: implementation of the CWorkerThread class.
//
//////////////////////////////////////////////////////////////////////

#include "WorkerThread.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWorkerThread::CWorkerThread()
{
//	m_Job = NULL;
   // m_JobData = NULL;
   // m_ThreadPool = NULL;
	m_ThreadPool = NULL;
	m_callBackFunction = NULL;
	m_callBackParam = NULL;
	m_callBackParamchar = NULL;
	m_threadRunFlag = TRUE;
}

CWorkerThread::~CWorkerThread()
{

}
void CWorkerThread::Run()
{
	BOOL tempThreadFlag = TRUE;
    while(tempThreadFlag)
    {
		m_functionAndParamMutex.Lock();
		if ((NULL != m_callBackFunction))
		{
		LPVOID tempParam=(LPVOID)m_callBackParamchar;
		try{
			MYDEBUG::OUTPUT("��ǰ�����߳�:%d",m_ThreadIDReal);
		(*m_callBackFunction)(tempParam);		//���ûص�����m_callBackParamchar
		
		}catch(...){
		//	m_functionAndParamMutex.Unlock();
			MYDEBUG::OUTPUT("Process Job error !");
		}
		if (NULL !=tempParam)
		{
			delete []m_callBackParamchar;
		}
		
		m_callBackFunction = NULL;
		m_callBackParamchar = NULL;
        m_ThreadPool->MoveToIdleList(this);
		}
		m_functionAndParamMutex.Unlock();
		
		m_threadRunFlagMutex.Lock();
		tempThreadFlag = m_threadRunFlag;
		m_threadRunFlagMutex.Unlock();
		if (tempThreadFlag)
		{	
			SuspendThread(m_ThreadHandle);
		}
    }
		MYDEBUG::OUTPUT("�߳�:%d �˳�",m_ThreadIDReal);
}

BOOL CWorkerThread::SetJob(JobInfo tempJobInfo)
{
	m_functionAndParamMutex.Lock();
    m_callBackFunction = tempJobInfo.jobcallback;
	if (NULL != tempJobInfo.lpParam)
	{
			try
			{
				m_callBackParamchar = new unsigned char [tempJobInfo.length+1];
			}catch (bad_alloc & e)
			{
				cout<<e.what()<<endl;
				cout<<("CWorkerThread::SetJob ��������ʱ����ռ�ʧ�� !")<<endl;
				return FALSE;
			}
		memcpy(m_callBackParamchar,tempJobInfo.lpParam,tempJobInfo.length);	
		m_callBackParamchar[tempJobInfo.length]='\0';
	}
	m_functionAndParamMutex.Unlock();
    return TRUE;
}

void CWorkerThread::SetThreadPool(CThreadPool* thrpool)
{
    m_ThreadPool = thrpool;
}

BOOL CWorkerThread::Terminate()
{
	m_threadRunFlagMutex.Lock();
	m_threadRunFlag = FALSE;
	m_threadRunFlagMutex.Unlock();
	ResumeThread(m_ThreadHandle);
	int ret;
	ret = ::WaitForSingleObject(m_ThreadHandle,1000);//ʱ�䲻��̫�̣���������̵߳�ʱ��ᱻ��ס
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
	return TRUE;
}

//DEL string CWorkerThread::GetFunctionName()
//DEL {
//DEL  string tempstr;
//DEL  unsigned char * ptemp = (unsigned char *)(m_callBackFunction);
//DEL  for (int i =0 ;i < 4;++i)
//DEL  {
//DEL 	 tempstr += (char)(*ptemp);
//DEL 	// ++ptemp;
//DEL  }
//DEL  return tempstr;
//DEL }
