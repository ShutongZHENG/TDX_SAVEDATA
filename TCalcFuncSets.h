#ifndef __TCALC_FUNC_SETS
#define __TCALC_FUNC_SETS
#include "PluginTCalcFunc.h"

#ifdef _X86_
extern "C" { int _afxForceUSRDLL; }
#else
extern "C" { int __afxForceUSRDLL; }
#endif




#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus
	__declspec(dllexport)BOOL RegisterTdxFunc(PluginTCalcFuncInfo** pFun);
#ifdef __cplusplus
}
#endif //__cplusplus

#endif //__TCALC_FUNC_SETS

BOOL funSaveDATA(LPCTSTR SaveDATA,
	DWORD dword_param_BufferSize);
