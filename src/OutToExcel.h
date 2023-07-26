#if !defined(AFX_OUTTOEXCEL_H__463CA205_334A_4548_819B_EE90C57171A6__INCLUDED_)
#define AFX_OUTTOEXCEL_H__463CA205_334A_4548_819B_EE90C57171A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OutToExcel.h : header file
//

#include <afxdb.h>
#include <odbcinst.h>

#include "TestDoc.h"

#include "Box.h"
#include "Series.h"

#include <afxtempl.h>
typedef CTypedPtrList<CObList , CBox*> CBoxList;
typedef CTypedPtrMap <CMapStringToPtr, CString, int*> CRecords;
typedef CTypedPtrList<CObList , CSeries*> CSeriesList;
//typedef CTypedPtrList<CObList , CString&> CStringList;
//typedef CArray<CString , CString*> CStringArray;

/////////////////////////////////////////////////////////////////////////////
// COutToExcel command target

class COutToExcel : public CCmdTarget
{
	DECLARE_DYNCREATE(COutToExcel)

	COutToExcel();           // protected constructor used by dynamic creation

// Attributes
public:

	
	//CTestDoc* pDoc;

	CString	FilePathName;

//	CString	FileName;

//	CString TableName ;

	CDatabase database;	

	
	CString sSql;
	CString TableHand ;



	CSeriesList* pPublicTable;
	CSeriesList* pSeriesTable;

	CBoxList* pBoxTable;


// Operations
public:

	CString GetModuleDir(){
		HMODULE module=GetModuleHandle(0);
		char pFileName[MAX_PATH]={0};
		GetModuleFileName(module,pFileName,MAX_PATH);
		CString csFullName(pFileName);
		int nPos=csFullName.ReverseFind('\\');
		if(nPos<0)
			return CString("");
		else
			return csFullName.Left(nPos);	
	}


void SeveToFile() 
	{

		
		CFileDialog dlg(FALSE,"xls file(*.xls)|*.xls", NULL,
			
			OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
			
			"xls file(*.xls)|*.xls||");    //TRUE为OPEN对话框，FALSE为SAVE AS对话框
		
		if(dlg.DoModal()==IDOK)
		{
			
			FilePathName=dlg.GetPathName();		

		}

		else return;
		
	
		if(FilePathName.GetLength() != 0)
		{			
			

					
				//读取天语二代的数据
				//TestRead( _T("天语二代"));

			//pDoc->FilePathName.Empty();

			
			//pDoc->FilePathName = FilePathName;
			//pDoc->SetTitle ( pDoc->FilePathName) ;
			//AfxMessageBox("00");
				WriteToExcel();
		}

}

	
	void WriteToExcel()
	{
		
		//写入EXCEL
	
		
		CString sDriver = _T( "MICROSOFT EXCEL DRIVER (*.XLS)" ); // Excel安装驱动
		//CString sExcelFile =  FilePathName.Replace("\\","\\\\") ;// 将被读取的Excel文件名

		CString sExcelFile =  FilePathName;
    
	
		
		TRY
		{
			// 创建进行存取的字符串
			sSql.Format("DRIVER={%s};DSN='''';FIRSTROWHASNAMES=1;READONLY=FALSE;CREATE_DB=\"%s\";DBQ=%s",
                sDriver, sExcelFile, sExcelFile);
			// 创建数据库 (既Excel表格文件)
			if ( database.OpenEx(sSql,CDatabase::noOdbcDialog) )
			{
				
				//捕获异常
				try
				{
					//删除表
					database.ExecuteSQL(_T( "DROP  TABLE test " ));
					
				}
				catch (CDBException *pe)
				{
					// The error code is in pe->m_nRetCode
					pe->ReportError();
					pe->Delete();
				}
				
				
				//创建表
				database.ExecuteSQL(_T( "CREATE TABLE test (位置 TEXT,类型 TEXT,长度 NUMBER,宽度 NUMBER,高度 NUMBER,米重 NUMBER,数量 NUMBER,单位 TEXT,单价 NUMBER,金额 NUMBER,备注 TEXT)" ));
				
				TableHand	= "INSERT INTO test (位置,类型,长度,宽度,高度,米重,数量,单位,单价,金额,备注) VALUES ";

				WriteFrameData();	//四边框
				WriteStileData();	//线材
				WriteFixData();		//固定窗
				WriteCasementData();//开启扇
				WriteScreensData(); //纱窗扇
				
				
				
				
				
			}
			// 关闭数据库
			database.Close();
		}
		CATCH_ALL(e)
		{
			TRACE1( "Excel驱动没有安装: %s" ,sDriver);
		}
		END_CATCH_ALL;
		
	}
	
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutToExcel)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
public:
	BOOL GetAllTableName ( CStringList& szArray);
	CString GetFileNameXls(CString OpenSave);
	void TestRead(CSeriesList* tempList , CString TempTableName);
	void TestWrite();
	void ReadExcel();
	void WriteScreensData();
	void WriteFixData();
	void WriteStileData();
	void WriteCasementData();
	void WriteFrameData();
	CString GetExcelDriver();
	virtual ~COutToExcel();

	// Generated message map functions
	//{{AFX_MSG(COutToExcel)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(COutToExcel)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OUTTOEXCEL_H__463CA205_334A_4548_819B_EE90C57171A6__INCLUDED_)
