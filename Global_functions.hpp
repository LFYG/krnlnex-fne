#ifndef GLOBAL_FUNCTION_HPP
#define GLOBAL_FUNCTION_HPP

#include "share.hpp"
#include <math.h>

#ifndef __E_STATIC_LIB

///////////////////////////////////////////////////////////////////////////////
// �������
#define Global_All_functions \
	KRNLNEX_CMD (fn_Global_Trace),\
	KRNLNEX_CMD (fn_Global_Verify),\
	KRNLNEX_CMD (fn_Global_EnumerateFiles),\
	KRNLNEX_CMD (fn_Global_EnumerateDirs),\
	KRNLNEX_CMD (fn_Global_CallFunction),\
	KRNLNEX_CMD (fn_Global_Wait),\
	KRNLNEX_CMD (fn_Global_DelayCallFunction),\
	KRNLNEX_CMD (fn_Global_GetVarAddr),\
	KRNLNEX_NULL_CMD_2,\
	KRNLNEX_NULL_CMD_10,\


///////////////////////////////////////////////////////////////////////////////
// ���������Ϣ

#define Global_All_CmdInfo \
	Global_Trace_CmdInfo,\
	Global_Verify_CmdInfo,\
	Global_EnumerateFiles_CmdInfo,\
	Global_EnumerateDirs_CmdInfo,\
	Global_CallFunction_CmdInfo,\
	Global_Wait_CmdInfo,\
	Global_DelayCallFunction_CmdInfo,\
	Global_GetVarAddr_CmdInfo,\
	MASK_CMD_INFO_2,\
	MASK_CMD_INFO_10,\

#endif


///////////////////////////////////////////////////////////////////////////////
// ȫ������֮������ʵ�� (ͬһ�������Ĳ�������Ϣ��ʵ�ִ������һ�𣬱��ڲ��Ҽ��ο�)

//-----------------------------------------------------------------------------
// ������������Ϣ��ʵ�ִ���

#ifndef __E_STATIC_LIB

ARG_INFO Global_Trace_ArgInfo[] =
{
	{
/*name*/	_WT("�����ֵ"),
/*explain*/	_WT("���ڷǡ��ı��͡����������Զ�ת��Ϊ�ı����������ɽ�������������ͣ��������������Լ��Զ����������͡�"),
/*bmp inx*/	0,
/*bmp num*/	0,
/*type*/	_SDT_ALL,
/*default*/	0,
/*state*/	AS_DEFAULT_VALUE_IS_EMPTY|AS_RECEIVE_ALL_TYPE_DATA,
	},
};

#define Global_Trace_CmdInfo \
	{\
/*ccname*/	_WT("�������"),\
/*egname*/	_WT("Trace"),\
/*explain*/	_WT("�����������Ժ��Ŀ��еġ���������ı�()����������������һ�е����ı���"\
	"������ɽ���������ͨ����(�����������)���������顣"\
	"�롰��������ı�()����ͬ������������в������ݽ����Ϊһ���ı���������֮���ԡ� | �������"\
	"�����ȱ�������������ԣ�����Ч������������ĺ����ȡ�"\
	"�������ѵϿ˵����飬�������ֽڼ��������ʽ�����硰�ֽڼ�:n{13,10}��������nΪ�ֽڼ����ȡ�"\
	"���⣬������Ը������ݵ������ʽ����Ϊ�Ѻã������鱻���Ϊ���硰����:3,2{...}�������С�3,2����ʾ������Ϊ3��2�У�{}֮��Ϊʵ���������ݡ�"),\
/*category*/17,\
/*state*/	CT_IS_HIDED|CMD_SUPPORT_OS|CT_ALLOW_APPEND_NEW_ARG|CT_DISABLED_IN_RELEASE,\
/*ret*/		_SDT_NULL,\
/*reserved*/0,\
/*level*/	LVL_SIMPLE,\
/*bmp inx*/	0,\
/*bmp num*/	0,\
/*ArgCount*/sizeof(Global_Trace_ArgInfo) / sizeof(Global_Trace_ArgInfo[0]),\
/*arg lp*/	Global_Trace_ArgInfo,\
	}

#endif

void Trace_DoWithParam(XString* pStr, PMDATA_INF pParam)
{
	switch(pParam->m_dtDataType) 
	{
	case SDT_INT:
		XString_AddTextF(pStr, "%d | ", pParam->m_int); break;
	case SDT_SHORT: 
		XString_AddTextF(pStr, "%d | ", (short)pParam->m_int); break;
	case SDT_BYTE:
		 XString_AddTextF(pStr, "%d | ", (byte)pParam->m_int); break;
	case SDT_INT64:
		XString_AddTextF(pStr, "%I64d | ", pParam->m_int64); break;
	case SDT_FLOAT: 
		XString_AddTextF(pStr, "%f | ", pParam->m_float); break;
	case SDT_DOUBLE:
		XString_AddTextF(pStr, "%f | ", pParam->m_double); break;
	case SDT_BOOL:
		XString_AddTextF(pStr, "%s | ", pParam->m_bool?"��":"��"); break;
	case SDT_TEXT: //ǰ��Ӱ��˫����
	{
		char* pText = pParam->m_pText;
		if(pText==NULL || strlen(pText)<=0)
		{
			XString_AddText(pStr, "���� | "); 
		}
		else
		{
			//XString_AddTextF(pStr, "�ı�:%d", strlen(pText));
			XString_AddText(pStr, "��");
			XString_AddText(pStr, pText);
			XString_AddText(pStr, "�� | ");
		}
		break;
	}
	case SDT_BIN:
	{
		if(pParam->m_pBin == NULL) //! �ֽڼ�Ϊ�յ����һ��Ҫ��������ָ�����Խ��!
		{
			XString_AddText(pStr, "�ֽڼ�:0{} | ");
			break;
		}
		int bytes = _GetIntByIndex(pParam->m_pBin, 1);
		LPBYTE pBin = (LPBYTE)_GetPointerByIndex(pParam->m_pBin, 2);
		//�������ѵϿ˵����飬�����˶��ֽڼ��������ʽ�����硰�ֽڼ�:2{13,10}��
		XString_AddTextF(pStr, "�ֽڼ�:%d", bytes);
		XString_AddText(pStr, "{");
		for(int i=0; i<bytes; i++)
		{
			XString_AddTextF(pStr, i==bytes-1?"%d":"%d,", (BYTE)*(pBin+i));
			/*
			if(i > 50) //��ֹ����ı�̫������������ʾ��ȫ!
			{	
				XString_AddText(pStr, "..."); break;
			}
			*/
		}
			
		XString_AddText(pStr, "} | ");
		//XString_AddText(pStr, "(bin) | "); break;
		break;
	}
	case SDT_DATE_TIME:
	{	
		//���á����ڵ��ı�()������ת��
		MDATA_INF RetData, ArgInf[2];
		ArgInf[0].m_dtDataType = SDT_DATE_TIME;
		ArgInf[0].m_date = pParam->m_date;
		ArgInf[1].m_dtDataType = SDT_INT;
		ArgInf[1].m_int = 1; //1��#ȫ��ת���� 2��#���ڲ��֣� 3��#ʱ�䲿�֡�
		CallKrnlnFunc(fi_TimeToText, &RetData, 1, ArgInf);
		XString_AddText(pStr, "[");
		XString_AddText(pStr, RetData.m_pText);
		XString_AddText(pStr, "] | ");
		MFree(RetData.m_pText); //!
		break;
	}
	case SDT_SUB_PTR:
		XString_AddTextF(pStr, "(�ӳ����ַ:%d) | ", pParam->m_dwSubCodeAdr); break;
	case _SDT_NULL:
		XString_AddText(pStr, "(��) | "); break;
	default: XString_AddText(pStr, "(?δ֪?) | "); break;
	}
}
void Trace_DoWithParam_Array(XString* pStr, PMDATA_INF pParam)
{
	int nDimension = _GetIntByIndex(pParam->m_pAryData, 0); //ά��
	int nElementCount = 1;
	int i=0;
	XString_AddText(pStr, "����:");
	
	for(i=0; i<nDimension; i++)
	{
		XString_AddTextF(pStr, "%s%d", i==0 ? "" : "*",
						_GetIntByIndex(pParam->m_pAryData, i+1));
		nElementCount *= _GetIntByIndex(pParam->m_pAryData, i+1);
	}
	XString_AddText(pStr, "{");
	
	//pָ������������ʼ��
	LPBYTE p = (LPBYTE)_GetPointerByIndex(pParam->m_pAryData, nDimension+1);
	char s[5]; strcpy(s, ",");
	for(i=0; i<nElementCount; i++)
	{
		if(i == nElementCount-1) strcpy(s, "");
		switch(pParam->m_dtDataType) 
		{
		case SDT_INT: 
			XString_AddTextF(pStr, "%d%s", *(INT*)p,s); p+=sizeof(INT); break;
		case SDT_SHORT: 
			XString_AddTextF(pStr, "%d%s", *(SHORT*)p,s); p+=sizeof(SHORT); break;
		case SDT_BYTE:
			XString_AddTextF(pStr, "%d%s", *(BYTE*)p,s); p+=sizeof(BYTE); break;
		case SDT_INT64:
			XString_AddTextF(pStr, "%I64d%s", *(INT64*)p,s); p+=sizeof(INT64); break;
		case SDT_FLOAT: 
			XString_AddTextF(pStr, "%f%s", *(FLOAT*)p,s); p+=sizeof(FLOAT); break;
		case SDT_DOUBLE:
			XString_AddTextF(pStr, "%f%s", *(DOUBLE*)p,s); p+=sizeof(DOUBLE); break;
		case SDT_BOOL:
			XString_AddTextF(pStr, "%s%s", (*(BOOL*)p)==TRUE?"��":"��",s); p+=sizeof(BOOL); break;
		case SDT_TEXT:
		{
			char* pText = (char*) (*(DWORD*)p);
			p += sizeof(DWORD);
			XString_AddText(pStr, "��");
			if(pText!=NULL && strlen(pText)>0)
			{
				XString_AddText(pStr, pText);
			}
			XString_AddText(pStr, "��");
			XString_AddTextF(pStr, "%s", s);
			break;
		}
		case SDT_BIN:
		{
			if((*(DWORD*)p) == 0) //! �ֽڼ�Ϊ�յ����һ��Ҫ��������ָ�����Խ��!
			{
				XString_AddTextF(pStr, "�ֽڼ�:0{}%s", s);
				p += sizeof(DWORD);
				break;
			}
			int bytes = _GetIntByIndex((void*)(*(DWORD*)p), 1);
			LPBYTE pBin = (LPBYTE)_GetPointerByIndex((void*)(*(DWORD*)p), 2);
			p += sizeof(DWORD);
			//�������ѵϿ˵����飬�����˶��ֽڼ��������ʽ�����硰�ֽڼ�:2�ֽ�{13,10}��
			XString_AddTextF(pStr, "�ֽڼ�:%d", bytes);
			XString_AddText(pStr, "{");
			for(int j=0; j<bytes; j++)
			{
				XString_AddTextF(pStr, j==bytes-1?"%d":"%d,", (BYTE)*(pBin+j));
			}
			XString_AddTextF(pStr, "}%s", s);
			break;
		}
		case SDT_DATE_TIME: 
		{	
			//���á����ڵ��ı�()������ת��
			MDATA_INF RetData, ArgInf[2];
			ArgInf[0].m_dtDataType = SDT_DATE_TIME;
			ArgInf[0].m_date = *(DATE*)p;  p+=sizeof(DATE);
			ArgInf[1].m_dtDataType = SDT_INT;
			ArgInf[1].m_int = 1; //1��#ȫ��ת���� 2��#���ڲ��֣� 3��#ʱ�䲿�֡�
			CallKrnlnFunc(fi_TimeToText, &RetData, 1, ArgInf);
			XString_AddText(pStr, "[");
			XString_AddText(pStr, RetData.m_pText);
			XString_AddText(pStr, "]");
			XString_AddTextF(pStr, "%s", s);
			MFree(RetData.m_pText); //!
			break;
		}
		case SDT_SUB_PTR:
			XString_AddTextF(pStr, "(�ӳ����ַ:%d)%s", *(DWORD*)p,s);  p+=sizeof(DWORD); break;
		case _SDT_NULL:
			XString_AddTextF(pStr, "(��)%s", s); p++; break; //p++ ��ֹ��ѭ��!
		default: XString_AddTextF(pStr, "(?δ֪?)%s", s); p++; break;
		}
	}
	XString_AddText(pStr, "} | ");
}
DEFINE_KRNLNEX_EXECUTE_CMD (fn_Global_Trace)
{
	try{
	//-------------------------------------------------------------------------
	XString str; XString_init_(&str);

	for(int i=0; i<nArgCount; i++)
	{
		PMDATA_INF pParam = &pArgInf[i];

		BOOL bIsArray = ((pParam->m_dtDataType & DT_IS_ARY) !=0 );
		if(bIsArray) pParam->m_dtDataType &= (~DT_IS_ARY);

		if(!bIsArray) //����Ϊ���������
		{
			Trace_DoWithParam(&str, pParam);
		}
		else //����Ϊ��������
		{
			Trace_DoWithParam_Array(&str, pParam);
		}
	}

	char* pStr = XString_GetText(&str); 
	if(pStr == NULL)
	{
		XString_destroy_(&str); return;
	}
	int chars=strlen(pStr);
	if(chars >= 3) pStr[chars-3] = '\0'; //ɾ�����ġ� | ��

	//ת������������ı�()��
	MDATA_INF RetData, ArgInf;
	ArgInf.m_dtDataType = SDT_TEXT;
	ArgInf.m_pText = pStr;
	CallKrnlnFunc(fi_OutputDebugInfo, &RetData, 1, &ArgInf);

	XString_destroy_(&str);
	//-------------------------------------------------------------------------
	}catch(...){ ASSERT(FALSE); /*Beep(500, 100);*/ return; }
}


//-----------------------------------------------------------------------------
// ������������Ϣ��ʵ�ִ���

#ifndef __E_STATIC_LIB

ARG_INFO Global_Verify_ArgInfo[] =
{
	{
/*name*/	_WT("�����ֵ"),
/*explain*/	_WT("����Ϊ��ͨ��ֵ������������/�������á������ȡ����������Ϊ����/�������û�����䣬���ǻᱻִ�У���ʹ�ڷǵ��԰汾�С�"),
/*bmp inx*/	0,
/*bmp num*/	0,
/*type*/	_SDT_ALL,
/*default*/	0,
/*state*/	AS_RECEIVE_ALL_TYPE_DATA|AS_DEFAULT_VALUE_IS_EMPTY,
	},
};

#define Global_Verify_CmdInfo \
	{\
/*ccname*/	_WT("��֤"),\
/*egname*/	_WT("Verify"),\
/*explain*/	_WT("�����������Ժ��Ŀ��еġ����()������������ڵ��԰�����֤����ֵ(���������)�Ƿ�Ϊ����ֵ����"\
	"����ǡ���ֵ�����׳����ִ�н�����ͣ�Ҿ�ʾ���൱�������������ϵ㣩��"\
	"�롰���()�����ͬ���ǣ������������а��н������ԡ���顱������裬���������ִ�в�����䣨���ڲ���Ϊ����/�������û��������������Ϊ��Ҫ����"\
	"���⣬��������Լ������������͵Ĳ������ҿ���ͬʱ�����������"\
	"����ṩ�˶�����������еĲ������ᱻ��֤����ֻҪ����һ������ֵ��������ͻᱻ��ͣ�Ҿ�ʾ��"\
	"����ֵ�����壺�ֽ���/��������/������/��������ֵ����0��С����/˫����С���;���ֵС��0.00001��"\
	"�߼���ֵΪ���١����ı���/�ֽڼ������ݳ��ȵ���0�������Ա������0������ʱ��ֵΪ��1899/12/30 00:00:00����"\
	"�ӳ���ָ���ִ�е�ַΪ0��ע��Ŀǰ�ݲ�֧�֡���������͡��Ĳ�����"),\
/*category*/17,\
/*state*/	CT_IS_HIDED|CMD_SUPPORT_OS|CT_ALLOW_APPEND_NEW_ARG,\
/*ret*/		_SDT_NULL,\
/*reserved*/0,\
/*level*/	LVL_SIMPLE,\
/*bmp inx*/	0,\
/*bmp num*/	0,\
/*ArgCount*/sizeof(Global_Verify_ArgInfo) / sizeof(Global_Verify_ArgInfo[0]),\
/*arg lp*/	Global_Verify_ArgInfo,\
	}

#endif

BOOL fn_verify_IsZeroValue(PMDATA_INF pParam)
{
	BOOL bIsZeroValue = FALSE;
	
	BOOL bIsArray = ((pParam->m_dtDataType & DT_IS_ARY) !=0 );
	if(bIsArray) pParam->m_dtDataType &= (~DT_IS_ARY);
	
	if(bIsArray)
	{
		int nArrayElementCount = 0;
		LPBYTE p = GetAryElementInf(pParam->m_pAryData, &nArrayElementCount);
		bIsZeroValue = (p==NULL || nArrayElementCount==0);
	}
	else
	{
		switch(pParam->m_dtDataType) 
		{
		case SDT_INT: case SDT_SHORT: case SDT_BYTE:
			bIsZeroValue = pParam->m_int == 0; break;
		case SDT_INT64:
			bIsZeroValue = pParam->m_int64 ==0; break;
		case SDT_FLOAT: 
			bIsZeroValue = (fabs(pParam->m_float)  < 0.00001); break;
		case SDT_DOUBLE:
			bIsZeroValue = (fabs(pParam->m_double) < 0.00001); break;
		case SDT_BOOL:
			bIsZeroValue = (pParam->m_bool==FALSE); break;
		case SDT_TEXT:
		{
			char* pText = pParam->m_pText;
			bIsZeroValue = (pText==NULL || strlen(pText)<=0);
			break;
		}
		case SDT_BIN:
		{
			if(pParam->m_pBin == NULL) //! �ֽڼ�Ϊ�յ����!
			{
				bIsZeroValue = TRUE; break;
			}
			int bytes = _GetIntByIndex(pParam->m_pBin, 1);
			LPBYTE pBin = (LPBYTE)_GetPointerByIndex(pParam->m_pBin, 2);
			bIsZeroValue = (pBin==NULL || bytes==0);
			break;
		}
		case SDT_DATE_TIME: //С��0Ҳ������, �������Գ�ʼֵΪ0: 1899-12-30
			bIsZeroValue = (fabs((DOUBLE)pParam->m_date) < 0.00001); break;
		case SDT_SUB_PTR:
			bIsZeroValue = ((DWORD)pParam->m_dwSubCodeAdr == 0); break;
		case _SDT_NULL:
			bIsZeroValue = FALSE; break; //����ʡ�Բ���������ʾ
		case SDT_STATMENT:
			//todo: ִ������䲢ȡ��ֵ
			bIsZeroValue = FALSE; //!!!
			break;
		default: bIsZeroValue = FALSE; break;
		}
	} //end of if(bIsArray)-else

	return bIsZeroValue;
}
DEFINE_KRNLNEX_EXECUTE_CMD (fn_Global_Verify)
{
	try{
	//-------------------------------------------------------------------------
	BOOL bVerifyFailed = FALSE;

	for(int i=0; i<nArgCount; i++)
	{
		if(fn_verify_IsZeroValue(&pArgInf[i])) //�����еĲ���������֤
			bVerifyFailed = TRUE;
	}
	
	//�����֤ʧ����Ϊ���԰���ת�������()��
	if(bVerifyFailed && NotifySys(NRS_GET_PRG_TYPE, 0, 0)==PT_DEBUG_RUN_VER)
	{
		MDATA_INF RetData, ArgInf;
		ArgInf.m_dtDataType = SDT_BOOL;
		ArgInf.m_bool = FALSE; //!
		CallKrnlnFunc(fi_Assert, &RetData, 1, &ArgInf);
	}
	//-------------------------------------------------------------------------
	}catch(...){ ASSERT(FALSE); return; }
}


//-----------------------------------------------------------------------------
// ������������Ϣ��ʵ�ִ���

#ifndef __E_STATIC_LIB

ARG_INFO Global_EnumerateFiles_ArgInfo[] =
{
	{
/*name*/	_WT("Ҫ������Ŀ¼"),
/*explain*/	_WT("Ŀ¼�ı�����������Ҳ����û�С�\\���ַ���"),
/*bmp inx*/	0,
/*bmp num*/	0,
/*type*/	SDT_TEXT,
/*default*/	0,
/*state*/	NULL,
	},
	{
/*name*/	_WT("�Ƿ�������Ŀ¼"),
/*explain*/	_WT("���Ϊ���桱��������ָ��Ŀ¼�����е�������Ŀ¼���ݹ飩������ֻ����ָ��Ŀ¼��"),
/*bmp inx*/	0,
/*bmp num*/	0,
/*type*/	SDT_BOOL,
/*default*/	1,
/*state*/	AS_HAS_DEFAULT_VALUE,
	},
	{
/*name*/	_WT("��������"),
/*explain*/	_WT(""),
/*bmp inx*/	0,
/*bmp num*/	0,
/*type*/	SDT_INT,
/*default*/	0,
/*state*/	AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
/*name*/	_WT("�û������ӳ���"),
/*explain*/	_WT("�û��ṩ���ӳ�������������Ҫ��1�����С��߼��͡�����ֵ��2������ֻ��һ�����ı��͡����������ڽ����ļ����ƣ���"\
	"��һ��ö�ٹ����У����ӳ���ᱻ��ε��ã�ÿö�ٵ�һ���ļ��͵���һ�Σ���"\
	"�û��ɸ��ݲ�������ġ�ȫ·���ļ����ơ��Ը��ļ����������������дɾ���Ȳ��ޣ���"\
	"����ڴ��ӳ����з��ء��١������ʾ��ֹ�˴�ö�ٹ��̡�"\
	"��ʾ�����ӳ�������ǰ�ӡ�&�����ɵõ����ӳ���ġ��ӳ���ָ�롱���硰&�ӳ���1�����ǡ��ӳ���1�����ӳ���ָ�롣"),
/*bmp inx*/	0,
/*bmp num*/	0,
/*type*/	SDT_SUB_PTR,
/*default*/	0,
/*state*/	NULL,
	},
};

#define Global_EnumerateFiles_CmdInfo \
	{\
/*ccname*/	_WT("ö���ļ�"),\
/*egname*/	_WT("EnumerateFiles"),\
/*explain*/	_WT("��ָ����Ŀ¼��ö�������ļ���ÿö�ٵ�һ���ļ������̵����û��ṩ�Ĵ����ӳ��򣨲������ļ����ƣ���"\
	"�û�ֻ���ṩһ������Ҫ��Ĵ����ӳ��򣬾Ϳ��Ժܷ���صݹ鴦��ָ��Ŀ¼�µ������ļ���"),\
/*category*/13,\
/*state*/	CMD_SUPPORT_OS,\
/*ret*/		_SDT_NULL,\
/*reserved*/0,\
/*level*/	LVL_SIMPLE,\
/*bmp inx*/	0,\
/*bmp num*/	0,\
/*ArgCount*/sizeof(Global_EnumerateFiles_ArgInfo) / sizeof(Global_EnumerateFiles_ArgInfo[0]),\
/*arg lp*/	Global_EnumerateFiles_ArgInfo,\
	}

#endif

typedef BOOL (WINAPI *EnumerateFunc) (LPCSTR str);

//�������ѱ����ã�����doFileEnumeration()
//ö��Ŀ¼���ļ�������doFilesΪTRUE��ʾö���ļ���ΪFALSE��ʾö��Ŀ¼
static BOOL s_bUserBreak = FALSE;
void doEnumeration(LPSTR lpPath, BOOL bRecursion, BOOL bDoFiles, EnumerateFunc pFunc)
{
	try{
	//-------------------------------------------------------------------------
	if(s_bUserBreak) return;

	int len = strlen(lpPath);
	if(lpPath==NULL || len<=0) return;

	NotifySys(NRS_DO_EVENTS, 0,0);
	
	char path[1024];
	strcpy(path, lpPath);
	if(lpPath[len-1] != '\\')
		strcat(path, "\\");
	strcat(path, "*.*");

	
	MDATA_INF RetData; MDATA_INF ArgInf[2];
	char buf[1024]; BOOL bUserRet=TRUE;
	
	//������ǰĿ¼�µ��ļ�
	if(bDoFiles)
	{
		ArgInf[0].m_dtDataType = SDT_TEXT; ArgInf[0].m_pText = path;
		//1��#ֻ���ļ��� 2��#�����ļ��� 4��#ϵͳ�ļ��� 16��#��Ŀ¼�� 32��#�浵�ļ�
		ArgInf[1].m_dtDataType = SDT_INT;  ArgInf[1].m_int = (bDoFiles ? 1+2+4+32 : 16);
		CallKrnlnFunc(fi_dir, &RetData, 2, ArgInf); 
		
		
		while(RetData.m_pText!=NULL && strlen(RetData.m_pText)>0)
		{
			strcpy(buf, path);
			strcat(buf, RetData.m_pText);
			if(pFunc)
			{
				bUserRet = pFunc(buf); 
				if(bUserRet==FALSE) { s_bUserBreak=TRUE; return; }
			}
			
			ArgInf[0].m_dtDataType = _SDT_NULL; ArgInf[0].m_pText = NULL; //���ṩ������
			//1��#ֻ���ļ��� 2��#�����ļ��� 4��#ϵͳ�ļ��� 16��#��Ŀ¼�� 32��#�浵�ļ�
			ArgInf[1].m_dtDataType = SDT_INT;  ArgInf[1].m_int = (bDoFiles ? 1+2+4+32 : 16);
			CallKrnlnFunc(fi_dir, &RetData, 2, ArgInf);
		}
	}

	
	if(bRecursion == FALSE) return;

	//-------------------------------------------------------------------------
	//����ݹ�������Ŀ¼ 
	
	ArgInf[0].m_dtDataType = SDT_TEXT; ArgInf[0].m_pText = path;
	ArgInf[1].m_dtDataType = SDT_INT;  ArgInf[1].m_int = 16; //16��#��Ŀ¼��
	CallKrnlnFunc(fi_dir, &RetData, 2, ArgInf); 

	while(RetData.m_pText!=NULL && strlen(RetData.m_pText)>0)
	{
		if(RetData.m_pText[strlen(RetData.m_pText)]!='.') 
		{
			strcpy(buf, path);
			strcat(buf, RetData.m_pText);
			if(pFunc && !bDoFiles)
			{
				bUserRet = pFunc(buf); 
				if(bUserRet==FALSE)
				{
					s_bUserBreak = TRUE; return;
				}
			}
			doEnumeration(buf, bRecursion, bDoFiles, pFunc); //�ݹ���ñ�����
		}

		ArgInf[0].m_dtDataType = _SDT_NULL; ArgInf[0].m_pText = NULL; //���ṩ������
		ArgInf[1].m_dtDataType = SDT_INT;  ArgInf[1].m_int = 16; //16��#��Ŀ¼��
		CallKrnlnFunc(fi_dir, &RetData, 2, ArgInf);
	}

	
	//-------------------------------------------------------------------------
	}catch(...){ ASSERT(FALSE); return; }
}


void doFileEnumeration(LPSTR lpPath, BOOL bRecursion, BOOL bEnumFiles, EnumerateFunc pFunc)
{
	try{
	//-------------------------------------------------------------------------
	if(s_bUserBreak) return;

	int len = strlen(lpPath);
	if(lpPath==NULL || len<=0) return;

	NotifySys(NRS_DO_EVENTS, 0,0);
	
	char path[MAX_PATH];
	strcpy(path, lpPath);
	if(lpPath[len-1] != '\\') strcat(path, "\\");
	strcat(path, "*");

	WIN32_FIND_DATA fd;
	HANDLE hFindFile = FindFirstFile(path, &fd);
	if(hFindFile == INVALID_HANDLE_VALUE)
	{
		::FindClose(hFindFile); return;
	}

	char tempPath[MAX_PATH]; BOOL bUserReture=TRUE; BOOL bIsDirectory;

	BOOL bFinish = FALSE;
	while(!bFinish)
	{
		strcpy(tempPath, lpPath);
		if(lpPath[len-1] != '\\') strcat(tempPath, "\\");
		strcat(tempPath, fd.cFileName);

		bIsDirectory = ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0);

		//�����.��..
		if( bIsDirectory
			&& (strcmp(fd.cFileName, ".")==0 || strcmp(fd.cFileName, "..")==0)) 
		{		
			bFinish = (FindNextFile(hFindFile, &fd) == FALSE);
			continue;
		}

		if(pFunc && bEnumFiles!=bIsDirectory)
		{
			bUserReture = pFunc(tempPath);
			if(bUserReture==FALSE)
			{
				s_bUserBreak = TRUE; ::FindClose(hFindFile); return;
			}
		}

		NotifySys(NRS_DO_EVENTS, 0,0);
		
		if(bIsDirectory && bRecursion) //����Ŀ¼
		{
			doFileEnumeration(tempPath, bRecursion, bEnumFiles, pFunc);
		}

		bFinish = (FindNextFile(hFindFile, &fd) == FALSE);
	}

	::FindClose(hFindFile);

	//-------------------------------------------------------------------------
	}catch(...){ ASSERT(FALSE); return; }
}

DEFINE_KRNLNEX_EXECUTE_CMD (fn_Global_EnumerateFiles)
{
	try{
	//-------------------------------------------------------------------------

		s_bUserBreak = FALSE;
		doFileEnumeration(pArgInf[0].m_pText, pArgInf[1].m_bool, TRUE, 
						  (EnumerateFunc)pArgInf[3].m_dwSubCodeAdr);

	//-------------------------------------------------------------------------
	}catch(...){ ASSERT(FALSE); return; }
}

//-----------------------------------------------------------------------------
// ������������Ϣ��ʵ�ִ���

#ifndef __E_STATIC_LIB

ARG_INFO Global_EnumerateDirs_ArgInfo[] =
{
	{
/*name*/	_WT("Ҫ������Ŀ¼"),
/*explain*/	_WT("Ŀ¼�ı�ĩβ������Ҳ����û�С�\\���ַ���"),
/*bmp inx*/	0,
/*bmp num*/	0,
/*type*/	SDT_TEXT,
/*default*/	0,
/*state*/	NULL,
	},
	{
/*name*/	_WT("�Ƿ�������Ŀ¼"),
/*explain*/	_WT("���Ϊ���桱����������ΧΪָ��Ŀ¼�����е�������Ŀ¼���ݹ飩������ֻ��ָ��Ŀ¼��������"),
/*bmp inx*/	0,
/*bmp num*/	0,
/*type*/	SDT_BOOL,
/*default*/	1,
/*state*/	AS_HAS_DEFAULT_VALUE,
	},
	{
/*name*/	_WT("��������"),
/*explain*/	_WT(""),
/*bmp inx*/	0,
/*bmp num*/	0,
/*type*/	SDT_INT,
/*default*/	0,
/*state*/	AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
/*name*/	_WT("�û������ӳ���"),
/*explain*/	_WT("�û��ṩ���ӳ�������������Ҫ��1�����С��߼��͡�����ֵ��2������ֻ��һ�����ı��͡����������ڽ�����Ŀ¼���ƣ���"\
	"��һ��ö�ٹ����У����ӳ���ᱻ��ε��ã�ÿö�ٵ�һ����Ŀ¼�͵���һ�Σ���"\
	"�û��ɸ��ݲ�������ġ�ȫ·��Ŀ¼���ơ���Ŀ¼�ı�ĩβ���ǲ�����\\���ַ����Ը���Ŀ¼���������������дɾ���Ȳ��ޣ���"\
	"����ڴ��ӳ����з��ء��١������ʾ��ֹ�˴�ö�ٹ��̡�"\
	"��ʾ�����ӳ�������ǰ�ӡ�&�����ɵõ����ӳ���ġ��ӳ���ָ�롱���硰&�ӳ���1�����ǡ��ӳ���1�����ӳ���ָ�롣"),
/*bmp inx*/	0,
/*bmp num*/	0,
/*type*/	SDT_SUB_PTR,
/*default*/	0,
/*state*/	NULL,
	},
};

#define Global_EnumerateDirs_CmdInfo \
	{\
/*ccname*/	_WT("ö����Ŀ¼"),\
/*egname*/	_WT("EnumerateDirs"),\
/*explain*/	_WT("ö��ָ��Ŀ¼�ڵ�������Ŀ¼��ÿö�ٵ�һ����Ŀ¼�����̵����û��ṩ�Ĵ����ӳ��򣨲�������Ŀ¼���ƣ���"\
	"�û�ֻ���ṩһ������Ҫ��Ĵ����ӳ��򣬾Ϳ��Ժܷ���صݹ鴦��ָ��Ŀ¼�µ�������Ŀ¼��"),\
/*category*/13,\
/*state*/	CMD_SUPPORT_OS,\
/*ret*/		_SDT_NULL,\
/*reserved*/0,\
/*level*/	LVL_SIMPLE,\
/*bmp inx*/	0,\
/*bmp num*/	0,\
/*ArgCount*/sizeof(Global_EnumerateDirs_ArgInfo) / sizeof(Global_EnumerateDirs_ArgInfo[0]),\
/*arg lp*/	Global_EnumerateDirs_ArgInfo,\
	}

#endif

DEFINE_KRNLNEX_EXECUTE_CMD (fn_Global_EnumerateDirs)
{
	try{
	//-------------------------------------------------------------------------

		s_bUserBreak = FALSE;
		doFileEnumeration(pArgInf[0].m_pText, pArgInf[1].m_bool, FALSE, 
						  (EnumerateFunc)pArgInf[3].m_dwSubCodeAdr);

	//-------------------------------------------------------------------------
	}catch(...){ ASSERT(FALSE); return; }
}


//-----------------------------------------------------------------------------
// ������������Ϣ��ʵ�ִ���

#ifndef __E_STATIC_LIB

ARG_INFO Global_CallFunction_ArgInfo[] =
{
	{
/*name*/	_WT("�Ƴ�ʱ��(��λ: ����)"),
/*explain*/	_WT("���������С�ڻ����0�����ӳ��򽫱����̵��á�"
	"��������������Ϊ 2147483647(0x7fffffff) ���루Լ 596 Сʱ����"),
/*bmp inx*/	0,
/*bmp num*/	0,
/*type*/	SDT_INT,
/*default*/	0,
/*state*/	NULL,
	},
	{
/*name*/	_WT("�ӳ���ָ����ӳ����ַ"),
/*explain*/	_WT("��ʾ�����ӳ�������ǰ�ӡ�&�����ɵõ����ӳ���ġ��ӳ���ָ�롱���硰&�ӳ���1�����ǡ��ӳ���1�����ӳ���ָ�룻"
				"�ӳ����ַ��ͨ�������⹦��֧�ֿ⡱�еġ�ȡ�ӳ����ַ()�������ȡ��"
				"������(&�ӳ���1)���ص�Ҳ���ӳ���1��ִ�е�ַ��"
				"Ҳ��ͨ��API��GetProcAddress()����ȡ�������ⲿ�����롣"),
/*bmp inx*/	0,
/*bmp num*/	0,
/*type*/	_SDT_ALL,
/*default*/	0,
/*state*/	NULL,
	},
	{
/*name*/	_WT("��������"),
/*explain*/	_WT(""),
/*bmp inx*/	0,
/*bmp num*/	0,
/*type*/	_SDT_ALL,
/*default*/	0,
/*state*/	AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
/*name*/	_WT("����ֵ"),
/*explain*/	_WT("���������ڽ����ӳ��򱻵��ú�ķ���ֵ��������ӳ���û�з���ֵ����Ҫ���շ���ֵ����ʡ�Ա�������"
	"�ṩ������ʱ��������ṩ׼ȷ���������ͣ��������ý�����ܲ���ȷ��"),
/*bmp inx*/	0,
/*bmp num*/	0,
/*type*/	_SDT_ALL,
/*default*/	0,
/*state*/	AS_RECEIVE_VAR|AS_DEFAULT_VALUE_IS_EMPTY,
	},
	{
/*name*/	_WT("����"),
/*explain*/	_WT("������ֵ����Ϊ�������뱻�����ӳ��������Ӧ�ӳ���û�в�������ʡ�Ա������������Ӧ�ӳ����ж�����������ظ��ṩ��������"
	"������ṩ׼ȷ�Ĳ������ͺͲ�������������������Ԥ֪��"),
/*bmp inx*/	0,
/*bmp num*/	0,
/*type*/	_SDT_ALL,
/*default*/	0,
/*state*/	AS_DEFAULT_VALUE_IS_EMPTY,
	},
};

#define Global_CallFunction_CmdInfo \
	{\
/*ccname*/	_WT("�����ӳ���"),\
/*egname*/	_WT("CallFunction"),\
/*explain*/	_WT("��stdcall��ʽ(��WINAPI��Pascal)����ָ�����ӳ����ӳ���ָ�룬���ӳ����ַ����ȡ�ر������ӳ���ķ���ֵ��"\
	"֧������������������֧�ֳ��ֽڼ�֮����������л����������͡�"\
	"�����ӳ���֮ǰ������Ҫ��ȷ��֪�����Ĳ������ͺͲ����������Լ�����ֵ���ͣ�"\
	"��Ҫʱʹ�á����ֽڡ�����������������������������С����������ֵ��������ǿ��ת���������͡�"\
	"������ء��桱����ʾ���ù�����û�г��쳣�����������ʾ�����õ��ӳ���ִ�гɹ���"\
	"Ŀǰ��֪���⣺����ͬʱ���С��ı��͡��͡�˫����С���ͣ�����ʱ���ͣ���ʱ���ᵼ�²������ݴ����ɻ��С���������ְ�æ"),\
/*category*/30,\
/*state*/	CT_IS_HIDED|CMD_SUPPORT_OS|CT_ALLOW_APPEND_NEW_ARG,\
/*ret*/		SDT_BOOL,\
/*reserved*/0,\
/*level*/	LVL_HIGH,\
/*bmp inx*/	0,\
/*bmp num*/	0,\
/*ArgCount*/sizeof(Global_CallFunction_ArgInfo) / sizeof(Global_CallFunction_ArgInfo[0]) - 1,\
/*arg lp*/	&(Global_CallFunction_ArgInfo[1]),\
	}

#endif

//�������ͷ���ֵ,�������ͷ��ص�ַ
//bytes�з������ݵ��ֽ���
#define		CF_VALUE_TYPE		INT
inline void CallFunction_GetValue(PMDATA_INF pMData, CF_VALUE_TYPE& HiValue, CF_VALUE_TYPE& LowValue, int& bytes)
{
	HiValue = LowValue = 0;
	if(pMData->m_dtDataType == _SDT_NULL) return;
	bytes = 4;
	
	switch(pMData->m_dtDataType) 
	{
	case SDT_INT: 
		LowValue = (CF_VALUE_TYPE)pMData->m_int; break;
	case SDT_SHORT: 
		LowValue = (CF_VALUE_TYPE)pMData->m_short; bytes = 2; break;
	case SDT_BYTE:
		LowValue = (CF_VALUE_TYPE)pMData->m_byte; bytes = 1; break;
	case SDT_INT64:
		{
			LowValue = (CF_VALUE_TYPE)_GetIntByIndex(&(pMData->m_int64), 0);
			HiValue  = (CF_VALUE_TYPE)_GetIntByIndex(&(pMData->m_int64), 1);
			bytes = 8;
			break;
		}
	case SDT_FLOAT: 
		//LowValue = (CF_VALUE_TYPE)pMData->m_float;  //�����϶��ǲ��е�
		{
			//ע��floatתint�Ĵ���ʽ(ͨ��ST0�Ĵ�����תһ��), �ο���VC���������ɵĻ�����
			float f = pMData->m_float;
			int i = 0;
			__asm fld f;
			__asm fst i;
			LowValue = (CF_VALUE_TYPE)i;
			bytes = 4;
			break;
		}
	case SDT_DOUBLE:
	case SDT_DATE_TIME:
		{
			LowValue = (CF_VALUE_TYPE)_GetIntByIndex(&(pMData->m_double), 0);
			HiValue  = (CF_VALUE_TYPE)_GetIntByIndex(&(pMData->m_double), 1);

			//LowValue = *((CF_VALUE_TYPE*)(&(pMData->m_double)));
			//HiValue = *((CF_VALUE_TYPE*)((LPBYTE)(&(pMData->m_double)) + sizeof(CF_VALUE_TYPE)));

			//-- ǰ�����ַ�ʽ��֤ʵ������ȷ��

			/*
			int temp[2];
			double d = pMData->m_double;
			__asm fld qword ptr d;
			__asm fst qword ptr temp;
			LowValue = temp[0];
			HiValue  = temp[1];
			*/

			bytes = 8;
			break;
		}
	case SDT_BOOL:
		LowValue = (CF_VALUE_TYPE)(pMData->m_bool?1:0); bytes = 4; break; 
	case SDT_TEXT:
		LowValue = (CF_VALUE_TYPE)(DWORD)pMData->m_pText; break;
	case SDT_BIN:
	{
		if(pMData->m_pBin == NULL) //! �ֽڼ�Ϊ�յ����!
		{
			LowValue = (CF_VALUE_TYPE)0; break;
		}
		LowValue = (CF_VALUE_TYPE)(DWORD)(LPBYTE)_GetPointerByIndex(pMData->m_pBin, 2);
		break;
	}
	case SDT_SUB_PTR:
		LowValue = (CF_VALUE_TYPE)((DWORD)pMData->m_dwSubCodeAdr); break;
	case _SDT_NULL:
		LowValue = (CF_VALUE_TYPE)0; break;
	case SDT_STATMENT:
		//todo: ִ������䲢ȡ��ֵ
		LowValue = (CF_VALUE_TYPE)0; //!!!
		break;
	default: LowValue = (CF_VALUE_TYPE)pMData->m_int; break;
	}
}
//���Ĵ���EAX��ST0�е�ֵд��pMData
void CallFunction_GetReturnedValue(PMDATA_INF pMData, int eaxValue,int edxValue,double stValue)
{
	if(pMData->m_dtDataType == _SDT_NULL) return;

	switch(pMData->m_dtDataType) 
	{
	case SDT_INT: case SDT_SHORT: case SDT_BYTE:
		*(pMData->m_pInt) = eaxValue;
		break;
	case SDT_INT64:
		{
			//EAX�ڵ�λ, EDX�ڸ�λ, ���double
			int temp[2]; 
			temp[0]=eaxValue; temp[1]=edxValue;
			*(pMData->m_pInt64) = *(INT64*)temp;
			break;
		}
	case SDT_FLOAT: 
		//����VC���������ɵĴ��룬���صĸ�����(float,double)Ӧ����ST0�У������ױ��������䲻ͬ��
		//*(pMData->m_pFloat) = (float)stValue; 
		{
			float f = 0;
			__asm fld eaxValue;
			__asm fst f;
			*(pMData->m_pFloat) = f;			
		}
		break;
	case SDT_DOUBLE:
	case SDT_DATE_TIME:
		//����VC���������ɵĴ��룬���صĸ�����(float,double)Ӧ����ST0�У������ױ��������䲻ͬ��
		//*(pMData->m_pDouble) = stValue;
		{
			//EAX�ڵ�λ, EDX�ڸ�λ, ���double
			int temp[2]; 
			temp[0]=eaxValue; temp[1]=edxValue;
			*(pMData->m_pDouble) = *(double*)temp;
		}
		break;
	case SDT_BOOL:
		*(pMData->m_pBool) = (eaxValue!=0);
		break;
	case SDT_TEXT:
		*(pMData->m_ppText) = CloneTextData((char*)eaxValue);
		break;
	case SDT_BIN:
		//pMData->m_pBin = CloneBinData((LPBYTE)intValue, n); //? �޷�֪���ֽڼ�����!
		break;
	case SDT_SUB_PTR:
		break;
	case _SDT_NULL:
		break;
	case SDT_STATMENT:
		break;

	default: 
		break;
	}
}

//�����ӳ���, liigoԭ��
//pMData: "�ӳ���ָ����ַ"�������ڴ��ַ��nArgCount: �������ӳ���Ĳ�������
BOOL Global_CallFunction(PMDATA_INF pFuncMData, INT nArgCount)
{
	try{
	//-------------------------------------------------------------------------

	//ȡ�������ӳ����ִ�е�ַ(pFunc)
	CF_VALUE_TYPE pFunc = NULL; //pArgInf[0].m_dwSubCodeAdr;
	CF_VALUE_TYPE temp  = 0;
	CallFunction_GetValue(pFuncMData, temp, pFunc, temp);
	if(pFunc == 0) return FALSE;

	//����ֵ
	PMDATA_INF pReturnMData = &pFuncMData[2];
	//����
	PMDATA_INF pParamsMData = &pFuncMData[3];

	//�������η���ѹջ
	CF_VALUE_TYPE  HiValue=0, LowValue=0;
	int bytes = 0;
	int byteValue  = 0;
	int shortValue = 0;
	if(!(pParamsMData[0].m_dtDataType==_SDT_NULL && nArgCount<=1)) //��һ��������ʡ�Ա�ʾû�в���
	{
		for(int i=nArgCount-1; i>=0; i--) //����ѹջ
		{
			CallFunction_GetValue(&pParamsMData[i], HiValue,LowValue, bytes); //�������û�Ӱ�����ջ��?
			
			//���鿴VC���������ɵĻ����룬����ѹջ������4�ֽ�Ϊ��λ
			byteValue = (int)(byte)LowValue; shortValue = (int)(short)LowValue;

			//�����8�ֽ���ֵ�Ļ�,�ȸ�λ��ջ,���λ��ջ
			if(bytes == 8)
			{
				__asm PUSH HiValue;
				__asm PUSH LowValue;
			}
			else if(bytes == 4)
				__asm PUSH LowValue;
			else if(bytes == 2)
				__asm PUSH shortValue;
			else if(bytes == 1)
				__asm PUSH byteValue; 
			else
				ASSERT(FALSE);
		}
	}

	//�����ӳ���
	__asm CALL pFunc; 

	//ȡ�������ӳ���ķ���ֵ (����CALL֮�����̶�ȡ)
	int eaxValue = 0, edxValue = 0;
	double stValue = 0.0;
	__asm mov eaxValue, eax;
	__asm mov edxValue, edx;
	__asm fst stValue; //! ȡST0�Ĵ����д洢�ĸ�����ֵ(float,double)

	if(pReturnMData->m_dtDataType != _SDT_NULL)
		CallFunction_GetReturnedValue(pReturnMData, eaxValue,edxValue,stValue);

	return TRUE;

	//-------------------------------------------------------------------------
	}catch(...){ ASSERT(FALSE); return FALSE; }

}

DEFINE_KRNLNEX_EXECUTE_CMD (fn_Global_CallFunction)
{
	pRetData->m_bool = FALSE;
	try{
	//-------------------------------------------------------------------------

	BOOL bOK = Global_CallFunction(pArgInf, nArgCount-3);

	pRetData->m_bool = bOK;
		
	//-------------------------------------------------------------------------
	}catch(...){ ASSERT(FALSE); return; }
}

//-----------------------------------------------------------------------------
// ������������Ϣ��ʵ�ִ���

#ifndef __E_STATIC_LIB

#define Global_DelayCallFunction_CmdInfo \
	{\
/*ccname*/	_WT("�Ƴٵ����ӳ���"),\
/*egname*/	_WT("DelayCallFunction"),\
/*explain*/	_WT("�����ִ��ʱ�����ڲ�����һ����ʱ����Ȼ�����̷��أ��Ա������Լ���ִ�к���ĳ�����룩��"\
	"����ʱʱ�䵽ʱ�ŵ��ò�����ָ�����ӳ�����������������������������Գ�������С�"\
	"��ע�ⲻҪ�ڱ������ѵ��õ���Ӧ�ӳ�����δִ����һ��ʱ�����ٴε��ñ������ֱ�ӷ��ء��١�����"\
	"������ĵ��ĸ�����������ֵ��Ŀǰ����ʹ�á�"),\
/*category*/30,\
/*state*/	CT_IS_HIDED|CMD_SUPPORT_OS|CT_ALLOW_APPEND_NEW_ARG,\
/*ret*/		SDT_BOOL,\
/*reserved*/0,\
/*level*/	LVL_HIGH,\
/*bmp inx*/	0,\
/*bmp num*/	0,\
/*ArgCount*/sizeof(Global_CallFunction_ArgInfo) / sizeof(Global_CallFunction_ArgInfo[0]),\
/*arg lp*/	Global_CallFunction_ArgInfo,\
	}

#endif

void* g_FuncDatas = NULL;
INT   g_ArgCount   = 0;
bool g_bIsTiming = false;
UINT g_TimerID = 0; 

VOID CALLBACK 
DelayCallFunction_TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	try
	{
		::KillTimer(NULL, g_TimerID);
		g_bIsTiming = false;
		if(g_FuncDatas)
			Global_CallFunction(PMDATA_INF(g_FuncDatas), g_ArgCount);
	}
	catch(...)
	{
	}
}

DEFINE_KRNLNEX_EXECUTE_CMD (fn_Global_DelayCallFunction)
{
	try{
	//-------------------------------------------------------------------------
	pRetData->m_bool = FALSE;

	if(g_bIsTiming) return;
	
	INT iDelay = pArgInf[0].m_int;
	if(iDelay > 0)
	{
		g_TimerID = ::SetTimer(NULL, 0, iDelay, (TIMERPROC)DelayCallFunction_TimerProc);
		g_bIsTiming = true;
		
		//����ص����ݱ����������������á�Todo: Ҫ�������õ����⡣
		if(g_FuncDatas) free(g_FuncDatas);
		int nBytes = sizeof(MDATA_INF) * (nArgCount-1);
		g_FuncDatas = malloc(nBytes);
		memcpy(g_FuncDatas, &(pArgInf[1]), nBytes); //��������������;)
		g_ArgCount = nArgCount - 4;

		pRetData->m_bool = TRUE;
	}
	//-------------------------------------------------------------------------
	}catch(...){ ASSERT(FALSE); return; }
}

//-----------------------------------------------------------------------------
// ������������Ϣ��ʵ�ִ���

#ifndef __E_STATIC_LIB

ARG_INFO Global_Wait_ArgInfo[] =
{
	{
/*name*/	_WT("Ҫ�ȴ���ʱ��(����)"),
/*explain*/	_WT("��ʾ��1000�������1�롣"),
/*bmp inx*/	0,
/*bmp num*/	0,
/*type*/	SDT_INT,
/*default*/	0,
/*state*/	NULL,
	},
};

#define Global_Wait_CmdInfo \
	{\
/*ccname*/	_WT("�ȴ�"),\
/*egname*/	_WT("Wait"),\
/*explain*/	_WT("�ȴ�һ��ʱ�䣬Ȼ�����ִ�к���ĳ�����롣"\
	"�������Ժ���֧�ֿ��еġ���ʱ()�����ͬ���ǣ��������ڵȴ��ڼ������û���������������������ť�ȣ�����л���������������Ӵ����"),\
/*category*/15,\
/*state*/	CT_IS_HIDED|CMD_SUPPORT_OS,\
/*ret*/		_SDT_NULL,\
/*reserved*/0,\
/*level*/	LVL_SIMPLE,\
/*bmp inx*/	0,\
/*bmp num*/	0,\
/*ArgCount*/sizeof(Global_Wait_ArgInfo) / sizeof(Global_Wait_ArgInfo[0]),\
/*arg lp*/	Global_Wait_ArgInfo,\
	}

#endif

DEFINE_KRNLNEX_EXECUTE_CMD (fn_Global_Wait)
{
	try{
	//-------------------------------------------------------------------------

	if(pArgInf[0].m_int <= 0) return;

	DWORD iEnd = ::GetTickCount() + pArgInf[0].m_int;

	while(1)
	{
		NotifySys(NRS_DO_EVENTS, 0,0);
		NotifySys(NRS_DO_EVENTS, 0,0);

		if(::GetTickCount() > iEnd) break;

		NotifySys(NRS_DO_EVENTS, 0,0);
		NotifySys(NRS_DO_EVENTS, 0,0);
	}

	//-------------------------------------------------------------------------
	}catch(...){ ASSERT(FALSE); return; }
}

//-----------------------------------------------------------------------------
// ������������Ϣ��ʵ�ִ���

#ifndef __E_STATIC_LIB

ARG_INFO Global_GetVarAddr_ArgInfo[] =
{
	{
/*name*/	_WT("����"),
/*explain*/	_WT(""),
/*bmp inx*/	0,
/*bmp num*/	0,
/*type*/	_SDT_ALL,
/*default*/	0,
/*state*/	AS_RECEIVE_VAR_OR_ARRAY,
	},
};

#define Global_GetVarAddr_CmdInfo \
	{\
/*ccname*/	_WT("ȡ�������ݵ�ַ"),\
/*egname*/	_WT("GetVarAddr"),\
/*explain*/	_WT("ȡָ�����������ݵ��ڴ��ַ������ֵΪ0��ʾû��ȡ�����ݵ�ַ��"\
	"���ı��ͻ��ֽڼ��ͱ������ԣ�����䳤��Ϊ0��������0��"\
	"������������ԣ�������Ա��Ϊ0��Ҳ������0��"\
	"�����ı��ͻ��ֽڼ����������������ֵΪ���������Ա���ݵĵ�ַ���ϡ����׵�ַ������ʵ�����ݵ�ַ"\
	"����Ϊ�ı��ͻ��ֽڼ������鲢δ�����г�Ա�е��ı����ֽڼ��洢��ͬһ���ڴ����򣩣�"\
	"���Կ�ͨ�����������Ա��Ϊ�������ñ��������ȡ�������Ա�е��ı����ֽڼ��ڴ��ַ��"\
	"ע�⣺һ������������������Χ�����ı���/�ֽڼ��ͱ��������¸�ֵ����������������¸�ֵ��"\
	"��ǰȡ���ı�����ַ�������Ч��ַ���ٶԸõ�ַ���ж�д�������п��ܵ��³��������"),\
/*category*/30,\
/*state*/	CT_IS_HIDED|CMD_SUPPORT_OS,\
/*ret*/		SDT_INT,\
/*reserved*/0,\
/*level*/	LVL_HIGH,\
/*bmp inx*/	0,\
/*bmp num*/	0,\
/*ArgCount*/sizeof(Global_GetVarAddr_ArgInfo) / sizeof(Global_GetVarAddr_ArgInfo[0]),\
/*arg lp*/	Global_GetVarAddr_ArgInfo,\
	}

#endif

DEFINE_KRNLNEX_EXECUTE_CMD (fn_Global_GetVarAddr)
{
	pRetData->m_int = 0;
	try{
	//-------------------------------------------------------------------------

	PMDATA_INF pParam = &(pArgInf[0]);
	BOOL bIsArray = ((pParam->m_dtDataType & DT_IS_ARY) !=0 );
	if(bIsArray) pParam->m_dtDataType &= (~DT_IS_ARY);

	int nAddr = 0;

	if(bIsArray)
	{
		int nLen = 0;
		nAddr = (int)GetAryElementInf(*(pParam->m_ppAryData), &nLen); //ȡ�������ݵ�ַ
		if(nLen == 0) nAddr = 0;
	}
	else
	{
		switch(pParam->m_dtDataType)
		{
		case SDT_BYTE:	
		case SDT_SHORT:
		case SDT_INT:
		case SDT_BOOL:
		case SDT_INT64:
		case SDT_FLOAT:
		case SDT_DOUBLE:
		case SDT_DATE_TIME:
		case SDT_SUB_PTR:
		case SDT_STATMENT:
			nAddr =  (int)pParam->m_pByte; //union, ��ַӦ������ͬ�İ�
			break;
		
		/*
		//ûʲô��ֵ
		case SDT_STATMENT:
			nAddr = (int)pParam->m_pStatment->m_dwStatmentSubCodeAdr; //����䷵��ִ�е�ַ
			break;
		*/
		
		case SDT_TEXT:
			{
				char* pText = *(pParam->m_ppText);
				nAddr = ((pText==NULL || strlen(pText)<=0) ? 0 : (int)pText); //����ı���Ϊ��, ȡ���ַ
				break;
			}
		case SDT_BIN:
			{
				LPBYTE pBin = *(pParam->m_ppBin);
				
				if(pBin == NULL)
				{
					nAddr = 0;
				}
				else
				{
					nAddr = ((_GetIntByIndex(pBin, 1)==0) ? 0 : (int)pBin + 8); //����ֽڼ���Ϊ��, ȡ���ַ
				}
				break;
			}
			
		default: nAddr = 0;
		}
	}

	pRetData->m_int = nAddr;

	//-------------------------------------------------------------------------
	}catch(...){ ASSERT(FALSE); return; }
}



#endif //#ifndef GLOBAL_FUNCTION_HPP
