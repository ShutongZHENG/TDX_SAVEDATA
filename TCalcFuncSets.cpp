#include "pch.h"
#include "TCalcFuncSets.h"
#include <vector>
#include <map>
#include <iostream>

struct DATA_Stock
{
	float Code;
	float High;
	float Low;
	float Date;
	float Open;
	float Close;
};

static std::vector<DATA_Stock> DataStock;

//生成的dll及相关依赖dll请拷贝到通达信安装目录的T0002/dlls/下面,再在公式管理器进行绑定
 /*
* 功能:股票每日最高/低价格存储
* 参数：pfINa 股票代码 pfINb 最高价 pfINc 最低价
* 返回：无
*/
void TestPlugin1(int DataLen,float* pfOUT,float* pfINa,float* pfINb,float* pfINc)
{
	DATA_Stock t_DS;
	for (int i = 0; i < DataLen; i++)
	{
		t_DS.Code = pfINa[i];
		t_DS.High = pfINb[i];
		t_DS.Low = pfINc[i];
		t_DS.Open = 0.;
		t_DS.Close = 0.;
		DataStock.push_back(t_DS);
	}

}

/*
* 功能:股票每日收/关盘价格存储
* 参数：pfINa股票代码 pfINb 开盘价 pfINc 收盘价 
* 返回：无
*/
void TestPlugin2(int DataLen,float* pfOUT,float* pfINa,float* pfINb,float* pfINc)
{
	for (int i = 0; i < DataLen; i++)
	{
		DataStock[i].Open = pfINb[i];
		DataStock[i].Close = pfINc[i];
	}

}



/*
* 功能:股票日期存储
* 参数：pfINa股票代码 pfINb 日期 pfINc 无关参数
* 返回：无
*/
void TestPlugin3(int DataLen, float* pfOUT, float* pfINa, float* pfINb, float* pfINc)
{
	
	for (int i = 0; i < DataLen; i++)
	{
		DataStock[i].Date = pfINb[i];
	}
}


/*
* 功能:进行本地数据存储
* 参数：无
* 返回：无
*/
void TestPlugin4(int DataLen, float* pfOUT, float* pfINa, float* pfINb, float* pfINc)
{

	CString DATE;
	CString LOW;
	CString HIGH;
	CString OPEN;
	CString CLOSE;
	CString CODE;
	CString Res;
	int int_CODE;
	int int_Date;

	for (unsigned i = 0; i < DataStock.size(); i++)
	{
				int_CODE = static_cast<int>(DataStock[i].Code);
				int_Date = static_cast<int>(DataStock[i].Date);
				CODE.Format(_T("%d"), int_CODE);
				DATE.Format(_T(" %d"), int_Date);
				HIGH.Format(_T(" %.2f"), DataStock[i].High);
				OPEN.Format(_T(" %.2f"), DataStock[i].Open);
				LOW.Format(_T(" %.2f"),DataStock[i].Low);
				CLOSE.Format(_T(" %.2f\n"),DataStock[i].Close);
				Res = Res + CODE + DATE + HIGH + LOW + OPEN + CLOSE;
				
	}
	funSaveDATA(Res, wcslen(Res) * sizeof(wchar_t));
	DataStock.clear();

}





//加载的函数
PluginTCalcFuncInfo g_CalcFuncSets[] = 
{
	{1,(pPluginFUNC)&TestPlugin1},
	{2,(pPluginFUNC)&TestPlugin2},
	{3,(pPluginFUNC)&TestPlugin3},
	{4,(pPluginFUNC)&TestPlugin4},
	{0,NULL},
};

//导出给TCalc的注册函数
BOOL RegisterTdxFunc(PluginTCalcFuncInfo** pFun)
{
	if(*pFun==NULL)
	{
		(*pFun)=g_CalcFuncSets;
		return TRUE;
	}
	return FALSE;
}

BOOL funSaveDATA(LPCTSTR SaveDATA, DWORD dword_param_BufferSize) {
	HANDLE handle_File = NULL;
	DWORD dword_NumberOfBytesToWrite = 0;
	handle_File = CreateFile(L"D:\DATA.txt",
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (handle_File == INVALID_HANDLE_VALUE)
	{
		handle_File = CreateFile(L"D:\DATA.txt",
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_WRITE,
			NULL,
			CREATE_NEW,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		if (handle_File == INVALID_HANDLE_VALUE)
		{

			return FALSE;
		}
		else
		{

			WORD dword_UnicodeFlag = 0xFEFF;
			WriteFile(handle_File,
				&dword_UnicodeFlag,
				sizeof(WORD),
				&dword_NumberOfBytesToWrite,
				NULL);

		}
	}
	else
	{

		SetFilePointer(handle_File, 0, NULL, FILE_END);
	}
	WriteFile(handle_File,
		SaveDATA,
		dword_param_BufferSize,
		&dword_NumberOfBytesToWrite,
		NULL);

	CloseHandle(handle_File);

	return TRUE;

}



