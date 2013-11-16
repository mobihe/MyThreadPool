// ThreadManage.h: interface for the CThreadManage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_THREADMANAGE_H__FDAF5F58_DC44_4393_8F4A_64D7997D232C__INCLUDED_)
#define AFX_THREADMANAGE_H__FDAF5F58_DC44_4393_8F4A_64D7997D232C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ThreadPool.h"
#pragma warning (disable:4786)
#include "vector"
#include "ThreadPoolSelfDefine.h"
#include "ThreadPoolException.h"
#define  DELETEPARAMSPACE(ptr)  if(ptr){  delete ptr; ptr = NULL;}
#define	 DEBUGCOUT
extern MYDEBUG debug;
class CJobListMutex
{
	   private:
		   HANDLE	joblist_lock;
	   public:
		   CJobListMutex(){ joblist_lock=CreateMutex(NULL,FALSE,NULL); }
		   ~CJobListMutex(){ 
			   ReleaseMutex(joblist_lock);
			   joblist_lock = NULL;
		   }// û�йرգ���й© 
		   void Lock(){ WaitForSingleObject(joblist_lock, INFINITE); }
		   void Unlock(){ ReleaseMutex(joblist_lock); }
};

class CThreadManage  
{
	  
public:
	BOOL GetJob(JobInfo * lpjob);
	BOOL AddJob( JOBCALLBACKE callbackfunction,LPVOID lpParam,int Paramsize ,JobPriority jobPriority) throw (string);
	CThreadManage();
	virtual ~CThreadManage();
	CThreadManage(int num);
	void	TerminateAll(void);
	CThreadPool *GetThreadPool(void){return m_Pool;}
private:
	CThreadPool				*m_Pool;					//�̳߳�ָ��
	int						m_NumOfThread;				//��ʼ�̳߳��߳���

	CJobListMutex			m_JobMapLock;				//��joblist���л���
	vector<JobInfo>			m_JobList;					//�������

	BOOL					m_threadRunFlag;			//�ַ��߳����п��Ʊ���
	CJobListMutex			m_threadRunFlagMutex;		//��m_threadRunFlag�ķ��ʽ��л���
	
	HANDLE					m_dispenseThreadhandle;		//�ַ��߳̾��
	static DWORD WINAPI _DispenseJobThread(LPVOID lpParam);
};

#endif // !defined(AFX_THREADMANAGE_H__FDAF5F58_DC44_4393_8F4A_64D7997D232C__INCLUDED_)
