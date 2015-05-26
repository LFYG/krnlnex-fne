#ifndef _SHARE_HPP
#define _SHARE_HPP

#include "elib_h\elib.h"


#define LIB_SUPPORT_OS		(_LIB_OS  (__OS_WIN))
#define DT_SUPPORT_OS		(_DT_OS   (__OS_WIN))
#define CMD_SUPPORT_OS		(_CMD_OS  (__OS_WIN))
#define PROP_SUPPORT_OS		(_PROP_OS (__OS_WIN))
#define EVENT_SUPPORT_OS	(_EVENT_OS(__OS_WIN))


///////////////////////////////////////////////////////////////////////////////
// ͨ�ú���
//
// GetIntByIndex()/SetIntByIndex()/GetPointerByIndex(): 
// ȡ/��������������������ĳ�Աֵ,�Ѳ���, ����ֵ>=0

#define _private  /*���Ϊ˽��*/

#ifdef __cplusplus
extern "C" {
#if 0
}
#endif
#endif
//-----------------------------------------------------------------------------




//!!! ���º�����������������֮��Աȫ��ΪINT����(��ͬ��ռ��4���ֽ�)
//index: 0..

_private void* _GetPointerByIndex(void *pBase, int index)
{
	return (void*) ((INT)pBase + index * sizeof(INT));
}

_private INT _GetIntByIndex(void *pBase, INT index)
{
	return *((INT*)_GetPointerByIndex(pBase,index));
}

_private void _SetIntByIndex(void *pBase, INT index, INT value)
{
	*((INT*)_GetPointerByIndex(pBase,index)) = value;
}


INT GetIntByIndex(PMDATA_INF pArgInf, INT index)
{
	return _GetIntByIndex(pArgInf->m_pCompoundData,index);
}

void SetIntByIndex(PMDATA_INF pArgInf, INT index, INT value)
{
	_SetIntByIndex(pArgInf->m_pCompoundData,index,value);
}

void* GetPointerByIndex(PMDATA_INF pArgInf, INT index)
{
	return _GetPointerByIndex(pArgInf->m_pCompoundData,index);
}

//��ȡȫ����ֵ
#define GlobalDataCount 	1024	//������������Ӵ���ֵ
_private DWORD g_GlobalDatas[GlobalDataCount];
void ClearGlobalDatas(void)
{
	memset(g_GlobalDatas, NULL, sizeof(DWORD)*GlobalDataCount);
}
void SetGlobalData(int index, void* p)
{
	if(index<0 || index>=GlobalDataCount) return;
	g_GlobalDatas[index] = (DWORD)p;
}
void* GetGlobalData(int index)
{
	if(index<0 || index>=GlobalDataCount) return NULL;
	return (void*)g_GlobalDatas[index];
}

typedef enum
{
	fi_OutputDebugInfo=0, fi_Assert, fi_TimeToText, fi_dir,
}
FuncIndex;

typedef struct 
{
	char* pFuncName;
	FuncIndex iFuncIndex;
}FuncNameIndex;

static FuncNameIndex g_FuncsNameIndex[] =
{
	{"��������ı�", fi_OutputDebugInfo},
	{"���", fi_Assert},
	{"ʱ�䵽�ı�", fi_TimeToText},
	/*{"Ѱ���ļ�", fi_dir},*/ //�˺���û��ִ�д���!!!???
};

void SetKrnlnFuncAddr(FuncIndex index, void* pFuncAddr)
{
	SetGlobalData((int)index, pFuncAddr);
}
PFN_EXECUTE_CMD GetKrnlnFuncAddr(FuncIndex index)
{
	return (PFN_EXECUTE_CMD) GetGlobalData((int)index);
}

//���ú��Ŀ��е�����
BOOL CallKrnlnFunc(FuncIndex index, PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	PFN_EXECUTE_CMD pFunc = GetKrnlnFuncAddr(index);
	if(pFunc)
	{
		pFunc(pRetData, nArgCount, pArgInf);
		return TRUE;
	}
	return FALSE;
}

//���׺��Ŀ���ȡ������Ҫ�ĺ�����ַ
#define FreeLibraryAddReturn() {::FreeLibrary(hModule); return;}
void Get_Krnln_Functions_Address()
{
	HMODULE hModule = ::LoadLibrary("krnln.fne");
	if(hModule==NULL)
	{
		hModule = ::LoadLibrary("krnln.fnr");
		if(hModule == NULL) return;
	}

	try{
	//-------------------------------------------------------------------------
	PFN_GET_LIB_INFO pfn_GetNewInfo = 
		(PFN_GET_LIB_INFO)::GetProcAddress(hModule, "GetNewInf");
	if(pfn_GetNewInfo==NULL) FreeLibraryAddReturn();
	
	PLIB_INFO pLibInfo = pfn_GetNewInfo();
	if(pLibInfo==NULL) FreeLibraryAddReturn();

	int nCmdCount = pLibInfo->m_nCmdCount;
	PCMD_INFO pCmdsInfo = pLibInfo->m_pBeginCmdInfo;
	PFN_EXECUTE_CMD* pCmdsFun = pLibInfo->m_pCmdsFunc;

	int nNeededFuncCount = sizeof(g_FuncsNameIndex) / sizeof(g_FuncsNameIndex[0]);
	for(int i=0; i<nCmdCount; i++)
	{
		PCMD_INFO pCmdInfo = &(pCmdsInfo[i]);
		if(pCmdInfo==NULL) continue;
		if(pCmdInfo->m_szName==NULL) continue;
		if(strlen(pCmdInfo->m_szName)<=0) continue;
		if(pCmdInfo->m_wState & CT_IS_HIDED == 0) continue;
		//TRACE("%s \n", pCmdInfo->m_szName);

		for(int j=0; j<nNeededFuncCount; j++)
		{
			if(g_FuncsNameIndex[j].pFuncName == NULL) continue;
			if(strcmp(pCmdInfo->m_szName, g_FuncsNameIndex[j].pFuncName)==0)
			{
				//ASSERT(pCmdsFun[i]); //ȷʵ��һЩ�����ִ�е�ַΪNULL, ��"Ѱ���ļ�" (������:�������,��������,���������).
				SetKrnlnFuncAddr(g_FuncsNameIndex[j].iFuncIndex, (void*)pCmdsFun[i]);
				break;
			}
		}
	}
	//-------------------------------------------------------------------------
	}catch(...){ ASSERT(FALSE); return; }
	FreeLibraryAddReturn();
}





//-----------------------------------------------------------------------------
#ifdef __cplusplus
}
#endif


class CFreqMem
{
private:
	unsigned char* m_pdata;
	size_t m_datalen, m_bufferlen;
public:
	CFreqMem()
	{
		m_pdata = NULL; m_datalen = m_bufferlen = 0;
	}
	void* GetPtr()
	{
		return (m_datalen == 0 ? NULL : m_pdata);
	}
	void AddDWord(DWORD dw)
	{
		AppendData(&dw, sizeof(dw));
	}
	void AppendData(void* pdata, size_t size)
	{
		if(m_bufferlen - m_datalen < size)
		{
			if(m_pdata == NULL)
			{
				m_bufferlen = 128;
				m_pdata = (unsigned char*) malloc(m_bufferlen);
				//assert(m_datalen == 0);
			}
			while(m_bufferlen - m_datalen < size)
			{
				m_bufferlen *= 2;
			};
			m_pdata = (unsigned char*) realloc(m_pdata, m_bufferlen);
		}
		memcpy(m_pdata + m_datalen, pdata, size);
		m_datalen += size;
	}
};



#endif //_SHARE_HPP