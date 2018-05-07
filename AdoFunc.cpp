#include "stdafx.h"
using namespace std;
void AdoTest()
{
	_ConnectionPtr HX_pConnection; // 数据库指针
	_RecordsetPtr HX_pRecordset; // 记录指针
	CoInitialize(NULL);
	try{
	HX_pConnection.CreateInstance(__uuidof(Connection));
	_bstr_t strConnect = "Provider=Microsoft.ACE.OLEDB.12.0;Data Source=rawdata.accdb;Persist Security Info=False";
	HX_pConnection->Open(strConnect,"","",adModeUnknown); //连接数据库
	}
	catch(_com_error e)
	{
		printf("fuck:%s\n",e.ErrorMessage());
		return;
	}

	HX_pRecordset.CreateInstance(__uuidof(Recordset));
	HX_pRecordset->Open("SELECT * FROM 研究所",  
		HX_pConnection.GetInterfacePtr(),
		adOpenForwardOnly,
		adLockReadOnly,
		adCmdText);

	while (!HX_pRecordset->adoEOF)
	{
		_variant_t var0,var1;
		var0 = HX_pRecordset->GetCollect((long)0);  
		var1 = HX_pRecordset->GetCollect((long)1);  
		cout<<"ID:"<<var0.intVal<<','<<(_bstr_t)var1<<endl;
		HX_pRecordset->MoveNext();
	}  
	if(HX_pRecordset!=NULL) HX_pRecordset->Close();
	HX_pConnection->Close();
	CoUninitialize();	
}
