// TestClass.cpp: implementation of the TestClass class.
//
//////////////////////////////////////////////////////////////////////

#include "TestClass.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
void  TestClass::good(){//回调函数测试
	
	MYDEBUG::OUTPUT("good 1 !!!!");
	Sleep(400);
}
DWORD TestClass::testjob(LPVOID lp){//回调函数测试
	if (NULL != lp)
	{
		TestClass *temptest = (TestClass *)lp;
		if (NULL !=temptest)
		{
			MYDEBUG::OUTPUT("TestClass::testjob");
		}
		
		temptest = NULL;
	}
	return 0;
}
int gtempi = 0;
DWORD TestClass::testjob2(LPVOID lp){//回调函数测试
	if (!lp)
	{
		MYDEBUG::OUTPUT("NUll");
	}
	TestStruct *temptest= (TestStruct*)lp;
	MYDEBUG::OUTPUT("%d,%d",temptest->a,temptest->b);
	temptest = NULL;
	while(true){
		gtempi++;
		if (10 == gtempi)
		{
			break;
		}
	}
	return 0;
}
void TestClass::test(){//测试函数接口
	
	manage= new CThreadManage(1);		//产生线程池
	Sleep(3000);
	for( int i=0;i<20;i++)
	{ 
		TestStruct temptest;
		temptest.a=i+1;
		temptest.b=-(i+1);
		try
		{
			manage->AddJob((JOBCALLBACKE)testjob2,&temptest,sizeof(temptest),NORMAL_PRIORITY);
		}
		catch (CThreadPoolException e)
		{
			cout<<e.GetErrorMessage()<<endl;break;
		}
	Sleep(10);
	}
	Sleep(6*1000);
	manage->TerminateAll();
	}