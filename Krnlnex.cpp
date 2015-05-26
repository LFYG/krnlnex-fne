// NewLib.cpp : Defines the initialization routines for the DLL.
//

#include "StdAfx.h"
#include "share.hpp"


#ifdef __cplusplus
	#define EXTERN_C extern "C" 
#else
	#define EXTERN_C 
#endif

#define DEFINE_KRNLNEX_EXECUTE_CMD(fnName) \
	EXTERN_C void krnlnex##_##fnName (PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)


#if defined(__E_STATIC_LIB) || defined(__COMPILE_FNR)

	#define KRNLNEX_CMD(name)  krnlnex_##name  // ���ڲ�ͬ�Ŀ�, ������Ӧ�������޸�
	#define KRNLNEX_NULL_CMD(name)  NULL

#else if defined(__cplusplus)

    static CFreqMem _g_CmdNames;

    static PFN_EXECUTE_CMD _RecordCmdName (PFN_EXECUTE_CMD func, const TCHAR* szFuncName)
    {
        _g_CmdNames.AddDWord ((DWORD)szFuncName);
        return func;
    }

    static const TCHAR** _GetCmdNames ()
    {
        return (const TCHAR**)_g_CmdNames.GetPtr ();
    }

    #define KRNLNEX_CMD(name)  _RecordCmdName (krnlnex_##name, "krnlnex_" #name)  // ���ڲ�ͬ�Ŀ�, ������Ӧ�������޸�
    #define KRNLNEX_NULL_CMD(name)  _RecordCmdName(NULL, NULL)

#endif

#define KRNLNEX_NULL_CMD_1  KRNLNEX_NULL_CMD(NULL)
#define KRNLNEX_NULL_CMD_2  KRNLNEX_NULL_CMD_1,KRNLNEX_NULL_CMD_1
#define KRNLNEX_NULL_CMD_3  KRNLNEX_NULL_CMD_2,KRNLNEX_NULL_CMD_1
#define KRNLNEX_NULL_CMD_4  KRNLNEX_NULL_CMD_3,KRNLNEX_NULL_CMD_1
#define KRNLNEX_NULL_CMD_5  KRNLNEX_NULL_CMD_4,KRNLNEX_NULL_CMD_1
#define KRNLNEX_NULL_CMD_6  KRNLNEX_NULL_CMD_5,KRNLNEX_NULL_CMD_1
#define KRNLNEX_NULL_CMD_7  KRNLNEX_NULL_CMD_6,KRNLNEX_NULL_CMD_1
#define KRNLNEX_NULL_CMD_8  KRNLNEX_NULL_CMD_7,KRNLNEX_NULL_CMD_1
#define KRNLNEX_NULL_CMD_9  KRNLNEX_NULL_CMD_8,KRNLNEX_NULL_CMD_1
#define KRNLNEX_NULL_CMD_10 KRNLNEX_NULL_CMD_9,KRNLNEX_NULL_CMD_1

#include "Global_functions.hpp"


#ifndef __E_STATIC_LIB

//=============================================================================
// ֧�ֿⶨ�忪ʼ

INT WINAPI RunAddIn(INT nIndex)
{
    switch(nIndex) 
    {
    case 0: 
        break;
    default:
        break;
    }
    return 0;
}


//���������б�
LIB_DATA_TYPE_INFO s_DataType[]=
{
	MASK_DATATYPE_INFO_1,

};



///////////////////////////////////////////////////////////////////////////////
//*** ����������Ϣ:
// !!! ע�ⳣ��ֵ�����Ѿ����õ������У�����˳��ֵ���Բ��ܸĶ���

LIB_CONST_INFO s_ConstInfo [] =
{
	{_WT("֧�ֿ����"),_WT("LibAlias"),NULL,LVL_SIMPLE,CT_TEXT,_T("DebugHelper"),0,},

};


///////////////////////////////////////////////////////////////////////////////
// ���е���������б�

static CMD_INFO s_CmdInfo[] =
{
	Global_All_CmdInfo

};


///////////////////////////////////////////////////////////////////////////////
// ���е��������ִ�к�����

PFN_EXECUTE_CMD s_RunFunc [] =	// ����Ӧ��s_CmdInfo�е������˳���Ӧ
{
	Global_All_functions

};

#endif


EXTERN_C INT WINAPI krnlnex_ProcessNotifyLib (INT nMsg, DWORD dwParam1, DWORD dwParam2)
{
#ifndef __E_STATIC_LIB
	if(nMsg == NL_GET_CMD_FUNC_NAMES)
		return (INT) _GetCmdNames();
	else if(nMsg == NL_GET_NOTIFY_LIB_FUNC_NAME)
		return (INT) "krnlnex_ProcessNotifyLib";
	else if(nMsg == NL_GET_DEPENDENT_LIBS)
		return (INT) NULL;
#endif
	return ProcessNotifyLib(nMsg, dwParam1, dwParam2);
}

#ifndef __E_STATIC_LIB

///////////////////////////////////////////////////////////////////////////////
// �ⶨ�忪ʼ
static char* s_szInfo = "This is a runtime library file for EPL applications. The EPL is a software development environment. For details please visit www.dywt.com.cn/info";

LIB_INFO s_LibInfo =
{
/*Lib Format Ver*/		LIB_FORMAT_VER,		// ����δ�á�

// ��֧�ֿ��GUID��
#define		LI_LIB_GUID_STR	"{A00B8D30-A5AB-4dfe-9546-9E636E711B75}"
/*guid str*/			_T (LI_LIB_GUID_STR),

/*m_nMajorVersion*/		2,
/*m_nMinorVersion*/		0,
/*m_nBuildNumber*/		1,
/*m_nRqSysMajorVer*/		3,
/*m_nRqSysMinorVer*/		7,
/*m_nRqSysKrnlLibMajorVer*/	3,
/*m_nRqSysKrnlLibMinorVer*/	7,

/*name*/				_T ("ö���ļ���Ŀ¼֧�ֿ�"), //���Ϊ: ϵͳ������ǿ֧�ֿ�(��������֧�ֿ�)
/*lang*/				__COMPILE_LANG_VER,
/*explain*/				_WT("�ṩ��ö���ļ�()���͡�ö����Ŀ¼()��������Ժܷ���صݹ鴦��ָ��Ŀ¼�µ������ļ�����Ŀ¼��"
	"\r\n    1.0#0���ṩ���������()������֤()�������Ϊ���������Գ����ṩ��������ǿ�������Ժ��Ŀ��е���ص����������������ı�()�������()������"
	"\r\n    1.1#0�������ˡ�ö���ļ�()���͡�ö����Ŀ¼()������������Ժ��Ŀ��С�Ѱ���ļ�()���������ǿ�������Ժܷ���صݹ鴦��ָ��Ŀ¼�µ������ļ�����Ŀ¼��"
	"\r\n    1.2#0�������ˡ������ӳ���()�����֧������������������֧�ֳ��ֽڼ�֮����������л����������͡�"
	"\r\n    1.3#0�������ˡ��ȴ�()������������Ժ��Ŀ��С���ʱ()���������ǿ�����ڵȴ��ڼ���������Ӧ�û���������л�����������顣"
	"\r\n    1.5#0�������ˡ������ӳ���()����֧�ֵ��ú�����ַ������ȡ�����ú�ķ���ֵ���������˲��ֲ������ݴ���"
	"��������������Ƴٵ����ӳ���()���롰ȡ�������ݵ�ַ()��������������⣬�⽫�ǡ���������֧�ֿ⡱�����һ���汾��"
	"\r\n    2.0#0�棬֧�־�̬���룬�����ض���������Թٷ����⹦��֧�ֿ��ظ�������硰����������������ӳ��򡱡�ȡ�������ݵ�ַ���ȣ���ֻ������ö���ļ�()����ö����Ŀ¼()���������֧�ֿ�Ҳ������Ϊ��ö���ļ���Ŀ¼֧�ֿ⡱�����Ա��������ݡ�"
	"\r\n    �����Ժ���֧�ֿ��뱾֧�ֿ��������β�ͬ�����Ŀ��迼�������ͨ���ԡ���չ�Լ��������ԣ�������ֻ�迼���������û�����ʹ�á�"
	"\r\n    ��֧�ֿ�����汾�����������ǿ������ϵͳ����֧�ֿ��е�������������ĸ�������⣬��ӭ���顣"),
/*dwState*/				LIB_SUPPORT_OS,

/*szAuthor*/	_WT("liigo"),
/*szZipCode*/	_WT(""),
/*szAddress*/	_WT(""),
/*szPhoto*/		_WT(""),
/*szFax*/		_WT(""),
/*szEmail*/		_WT("com.liigo@gmail.com"),
/*szHomePage*/	_WT("http://blog.csdn.net/liigo"),
/*szOther*/		_WT("ף��һ����˳�������³ɣ�"),

/*type count*/			0, //sizeof(s_DataType) / sizeof(s_DataType[0]),
/*PLIB_DATA_TYPE_INFO*/	NULL, //s_DataType,

/*CategoryCount*/ 30,	// ���������Ӵ�ֵ��
/*category*/// ���˵����ÿ��Ϊһ�ַ���,ǰ��λ���ֱ�ʾͼ��������(��1��ʼ,0��).
			_T("0001���̿���\0"
            "0014��������\0"
            "0005�߼��Ƚ�\0"
            "0015λ����\0"
            "0002��������\0"
            "0000�������\0"
            "0000������ȡ\0"
            "0000ƴ������\0"
            "0000��ֵת��\0"
            "0000�ı�����\0"
            "0000ʱ�����\0"
            "0000�ֽڼ�����\0"
            "0000���̲���\0"
            "0000�ļ���д\0"
            "0000ϵͳ����\0"
            "0000ý�岥��\0"
            "0000�������\0"
            "0000����\0"
            "0021���ݿ�\0"
            "0000����ͨ��\0"
            "0000����̨����\0"
			"0000???\0"
			"0000???\0"
			"0000???\0"
			"0000???\0"
			"0000???\0"
			"0000???\0"
			"0000???\0"
			"0000???\0"
			"0000����\0"
            "\0"),
/*CmdCount*/				sizeof (s_CmdInfo) / sizeof (s_CmdInfo [0]),
/*BeginCmd*/				s_CmdInfo,
/*m_pCmdsFunc*/             s_RunFunc,
/*pfnRunAddInFn*/			RunAddIn,
/*szzAddInFnInfo*/			"",

/*pfnNotify*/				krnlnex_ProcessNotifyLib,

/*pfnRunSuperTemplate*/		NULL,
/*szzSuperTemplateInfo*/	NULL,

/*nLibConstCount*/			0, //sizeof (s_ConstInfo) / sizeof (s_ConstInfo [0]),
/*pLibConst*/				NULL, //s_ConstInfo,

/*szzDependFiles*/			NULL,
};


// ֧�ֿⶨ�����
//=============================================================================

/////////////////////////////////////////////////////////////////////////////
//��������

PLIB_INFO WINAPI GetNewInf ()
{
	ClearGlobalDatas();
	Get_Krnln_Functions_Address();

	return &s_LibInfo;
}

#endif
