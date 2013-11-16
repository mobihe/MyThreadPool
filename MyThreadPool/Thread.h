// Thread.h: interface for the CThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_THREAD_H__BD42FD4E_DD13_4E6C_8FB9_3E9F7022B999__INCLUDED_)
#define AFX_THREAD_H__BD42FD4E_DD13_4E6C_8FB9_3E9F7022B999__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "cstring"
#include "iostream"
//#include "windows.h"
#include <afx.h>
class CThread  
{

private:
	int			m_ErrCode;
	char*		m_ThreadName;
protected:
	void		SetErrcode(int errcode){m_ErrCode = errcode;}
	static DWORD WINAPI _ThreadFunction(LPVOID lpParam);
	HANDLE		m_ThreadHandle;
public:
	DWORD GetThreadIdReal();
	BOOL ThreadRun(LPVOID lpParam);
	CThread();
	virtual ~CThread();
	virtual void	Run()=0;
	HANDLE			Start(CThread* cthread);
	int				GetLastError(void){return m_ErrCode;}
	void			SetThreadName(char* thrname){strcpy(m_ThreadName,thrname);}
	char*			GetThreadName(void){return m_ThreadName;}
	HANDLE	GetThreadHandle(void){return m_ThreadHandle;}
	DWORD			m_ThreadIDReal;
};

#endif // !defined(AFX_THREAD_H__BD42FD4E_DD13_4E6C_8FB9_3E9F7022B999__INCLUDED_)
