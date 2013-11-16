#ifndef THREADPOOLSELFDEFINE_H
#define THREADPOOLSELFDEFINE_H
#include "string"
#include <afx.h>
using namespace std;
typedef  DWORD  ( WINAPI * JOBCALLBACKE)(LPVOID lpParam);
typedef struct tagJobInfo{	//�ص�����ָ�뼰����
	JOBCALLBACKE		jobcallback;
	unsigned char		*lpParam;
	unsigned int		length;
}JobInfo;

typedef enum tagJobPriority //�߳����ȼ�
{
	HIGH_PRIORITY,
	NORMAL_PRIORITY
}JobPriority;
typedef struct tagTest{		//���Դ��ݲ���
	int a;
	int b;
}TestStruct;

class MyMutex{
	HANDLE	m_out;
public:
	MyMutex(){
		m_out = CreateMutex(NULL,FALSE,NULL);
	}
	~MyMutex(){
		ReleaseMutex(m_out);
		m_out = NULL;	// û�йرգ���й©
	}
 void Lock(){ WaitForSingleObject(m_out, INFINITE); }
 void Unlock(){ ReleaseMutex(m_out); }
};
#endif	THREADPOOLSELFDEFINE_H
