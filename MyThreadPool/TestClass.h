// TestClass.h: interface for the TestClass class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTCLASS_H__6BBFF91F_368C_4553_B671_1F938C3D77EB__INCLUDED_)
#define AFX_TESTCLASS_H__6BBFF91F_368C_4553_B671_1F938C3D77EB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "iostream"
#include "ThreadManage.h"
#include "ThreadPoolSelfDefine.h"
using namespace std;

class TestClass{
public: 
	int a;
	void  good();
	void good2(){cout<<"good2 !"<<endl;}
	static DWORD  WINAPI testjob(LPVOID lp);
	static DWORD  WINAPI testjob2(LPVOID lp);
	void test();
	TestClass(){
	}
private:
	CThreadManage* manage;
};
#endif // !defined(AFX_TESTCLASS_H__6BBFF91F_368C_4553_B671_1F938C3D77EB__INCLUDED_)
