// ThreadPoolException.h: interface for the CThreadPoolException class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_THREADPOOLEXCEPTION_H__E03BD464_C749_4AC6_AF31_62FAF08F1CF5__INCLUDED_)
#define AFX_THREADPOOLEXCEPTION_H__E03BD464_C749_4AC6_AF31_62FAF08F1CF5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "string"
using namespace std;
class CThreadPoolException : public exception 
{
public:
	string GetErrorMessage();
	CThreadPoolException(string exceptionInfo);
	virtual ~CThreadPoolException();
private:
	string m_exceptionInfo;
};

#endif // !defined(AFX_THREADPOOLEXCEPTION_H__E03BD464_C749_4AC6_AF31_62FAF08F1CF5__INCLUDED_)
