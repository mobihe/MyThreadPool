// ThreadMutex.h: interface for the CThreadMutex class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_THREADMUTEX_H__479B29D8_22A6_4EB5_A28B_C9B102CC199B__INCLUDED_)
#define AFX_THREADMUTEX_H__479B29D8_22A6_4EB5_A28B_C9B102CC199B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//#include "windows.h"
#include <afx.h>
class CThreadMutex
{
private:
	HANDLE	this_lock;
public:
	CThreadMutex(){ this_lock=CreateMutex(NULL,FALSE,NULL); }
	~CThreadMutex(){ ReleaseMutex(this_lock);this_lock = NULL;	}// 没有关闭，会泄漏  //pthread_mutex_destroy(&this_lock);
	void Lock(){ 	WaitForSingleObject(this_lock, INFINITE);; }
	void Unlock(){ ReleaseMutex(this_lock); }
    };
#endif // !defined(AFX_THREADMUTEX_H__479B29D8_22A6_4EB5_A28B_C9B102CC199B__INCLUDED_)
