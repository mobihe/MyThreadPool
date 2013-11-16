// WorkerThread.h: interface for the CWorkerThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WORKERTHREAD_H__C8D54DF2_9493_45F3_8548_ADD046AAEBB1__INCLUDED_)
#define AFX_WORKERTHREAD_H__C8D54DF2_9493_45F3_8548_ADD046AAEBB1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Thread.h"
#include "ThreadPool.h"
//#include "windows.h"

#include "ThreadPoolSelfDefine.h"
#include "ThreadMutex.h"
#define  DELETEPARAMSPACE(ptr)  if(ptr){ delete ptr; ptr = NULL;}
class CThreadPool;
class CWorkerThread  :public CThread
{
public:
	BOOL Terminate();
	CWorkerThread();
	virtual ~CWorkerThread();

	void Run();
	BOOL SetJob(JobInfo tempJobInfo);
	JOBCALLBACKE GetCallBackFuntionlp(void){return m_callBackFunction;}
	void SetThreadPool(CThreadPool * thrpool);
	CThreadPool *GetThreadPool(void){return m_ThreadPool;}
private:
	CThreadPool				*m_ThreadPool;
	JOBCALLBACKE			m_callBackFunction;
	LPVOID 					m_callBackParam;
	unsigned char			*m_callBackParamchar;
	CThreadMutex			m_functionAndParamMutex;
	CThreadMutex			m_threadRunFlagMutex;
	BOOL					m_threadRunFlag;
};

#endif // !defined(AFX_WORKERTHREAD_H__C8D54DF2_9493_45F3_8548_ADD046AAEBB1__INCLUDED_)
