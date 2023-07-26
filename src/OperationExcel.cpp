// OperationExcel.cpp : implementation file
//

#include "stdafx.h"
#include "Test.h"
#include "OperationExcel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// COperationExcel

IMPLEMENT_DYNCREATE(COperationExcel, CCmdTarget)

COperationExcel::COperationExcel()
{
	EnableAutomation();
}

COperationExcel::~COperationExcel()
{
}


//DEL void COperationExcel::OnFinalRelease()
//DEL {
//DEL 	// When the last reference for an automation object is released
//DEL 	// OnFinalRelease is called.  The base class will automatically
//DEL 	// deletes the object.  Add additional cleanup required for your
//DEL 	// object before calling the base class.
//DEL 
//DEL 	CCmdTarget::OnFinalRelease();
//DEL }


BEGIN_MESSAGE_MAP(COperationExcel, CCmdTarget)
	//{{AFX_MSG_MAP(COperationExcel)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(COperationExcel, CCmdTarget)
	//{{AFX_DISPATCH_MAP(COperationExcel)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IOperationExcel to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {F85C91A1-B329-4FC8-A0C2-19B0D83C1395}
static const IID IID_IOperationExcel =
{ 0xf85c91a1, 0xb329, 0x4fc8, { 0xa0, 0xc2, 0x19, 0xb0, 0xd8, 0x3c, 0x13, 0x95 } };

BEGIN_INTERFACE_MAP(COperationExcel, CCmdTarget)
	INTERFACE_PART(COperationExcel, IID_IOperationExcel, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////


CString COperationExcel::GetExcelDriver()
{
	
    
    char szBuf[2001];
    WORD cbBufMax = 2000;
    WORD cbBufOut;
    char *pszBuf = szBuf;
    CString sDriver;
    
    // 获取已安装驱动的名称(涵数在odbcinst.h里)#include <odbcinst.h>
    if (!SQLGetInstalledDrivers(szBuf, cbBufMax, &cbBufOut))
        return "";
    
    // 检索已安装的驱动是否有Excel...
    do
    {
        if (strstr(pszBuf, "Excel") != 0)
        {
            //发现 !
            sDriver = CString(pszBuf);
            break;
        }
        pszBuf = strchr(pszBuf, '\0') + 1;
    }
    while (pszBuf[1] != '\0');
    
    return sDriver;


}

CString COperationExcel::GetFilePathName()
{
	CString FilePathName ;    
    CFileDialog dlg(TRUE,"xls file(*.xls)|*.xls", NULL,
        
        OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
        
        "xls file(*.xls)|*.xls||");    //TRUE为OPEN对话框，FALSE为SAVE AS对话框
    
    if(dlg.DoModal()==IDOK)
    {
        FilePathName = dlg.GetPathName();            
        //SetWindowText( FilePathName );     
    }

	return FilePathName;

}

void COperationExcel::ReadExcel(CObjectList *m_PublicTable , CListCtrl *m_ListCtrl1, CString szState)
{	
	
	CString FilePathName ="";

	if(szState =="自动加载")
	{
		FilePathName = _T( "./data/PublicData.xls" ); // 将被读取的Excel文件名

	}

	if(szState =="选择加载")
	{
		FilePathName =GetFilePathName() ; 
	}

	
  
    if(FilePathName.IsEmpty())
    {
        return ;   
    }
 /**/

	//清空表
	while (!m_PublicTable->IsEmpty())		
	{ 
		delete  m_PublicTable->GetHead();
		
		m_PublicTable->RemoveHead(); 
	}

	// 全部清空 
	m_ListCtrl1->DeleteAllItems(); 
	while (m_ListCtrl1->DeleteColumn(0));	//清空所有表头


    CDatabase db ;

        CString sDriver, sDsn , sSql ; // ,  sFile将被读取的Excel文件名
        
        // 检索是否安装有Excel驱动 "Microsoft Excel Driver (*.xls)"
        sDriver = GetExcelDriver();
        if (sDriver.IsEmpty())
        {
            // 没有发现Excel驱动
            AfxMessageBox(_T( "没有安装Excel驱动!" ));
            return ;
        }
        
        // 创建进行存取的字符串
        sDsn.Format(_T( "ODBC;DRIVER={%s};DSN='';DBQ=%s" ), sDriver, FilePathName);
        
        TRY
        {
            // 打开数据库(既Excel文件)    //读入EXCEL
            db.Open(NULL, false , false , sDsn);
            
            CRecordset rs(&db);

            // 设置读取的查询语句.
            sSql .Format( _T("SELECT * FROM %s" ),"[Sheet1$]" );    //字段名称要分大小写公共数据
                     
            // 执行查询语句
            rs.Open(CRecordset::forwardOnly, sSql,CRecordset::none);

//测试取得表中字段名称
            short sFieldCount = rs.GetODBCFieldCount();

         CODBCFieldInfo fieldinfo;
            CStringArray strArrPublicFields;

            for( int i=0; i < sFieldCount; i++)
            {
                rs.GetODBCFieldInfo(i,fieldinfo);
 
                //把读到的表头项写一个字符串数组                
                strArrPublicFields.Add(_T(fieldinfo.m_strName.GetBuffer(fieldinfo.m_strName.GetLength())));
            }    
 
            //为表格控件设置表头
            DWORD dwExtStyles1 = m_ListCtrl1->GetExtendedStyle();
            m_ListCtrl1->SetExtendedStyle(dwExtStyles1 | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
            for(i = 0 ; i < strArrPublicFields.GetSize() ; i++)
            {                
                m_ListCtrl1->InsertColumn(i,strArrPublicFields.GetAt(i),LVCFMT_LEFT,100,i);            
            }
            
    
            i =0 ;            
            // 获取查询结果//读取记录
            while (!rs.IsEOF())
            {                    
                //把记录中的数据写入到内存链表
                    CStringArray *pNewItem = new CStringArray ;

                    for(i = 0 ; i < strArrPublicFields.GetSize() ; ++i)
                    {
                        CString str ;
                        rs.GetFieldValue(strArrPublicFields.GetAt(i), str);    pNewItem->Add(str);    
                    }
                    //把记录加入公共数据表
                    m_PublicTable->AddHead(pNewItem);                
                    //delete pNewItem;                    
                
                // 移到下一行
                rs.MoveNext();                  
            }
            
            rs.Close();
            // 关闭数据库
            db.Close();


							
			CStringArray *TempItem;
			
			POSITION pos=m_PublicTable->GetHeadPosition();
			
			//循环遍历找出容器中的所有信息
			
			while (pos!=NULL)
				
			{	
				TempItem =(CStringArray* ) m_PublicTable->GetNext(pos);
				
				for(i = 0 ; i < TempItem->GetSize() ; i++)
				{					
								//把数据写入表格控件
						if (i == 0)
							m_ListCtrl1->InsertItem(0, TempItem->GetAt(0) );//插入行
						else
							m_ListCtrl1->SetItemText(0,i,TempItem->GetAt(i));//设置该行的不同列的显示字符						

				}
				
			}			
            
        }

	
		
        CATCH(CDBException, e)
        {
            // 数据库操作产生异常时...
            AfxMessageBox(_T( "数据库错误: " ) + e->m_strError);
        }
        END_CATCH;    


}

void COperationExcel::WriteExcel()
{
	CString sExcelFile ;
	
	CFileDialog dlg(FALSE,"xls file(*.xls)|*.xls", NULL,
		
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		
		"xls file(*.xls)|*.xls||");    //TRUE为OPEN对话框，FALSE为SAVE AS对话框
	
	if(dlg.DoModal()==IDOK)
	{
		
		sExcelFile=dlg.GetPathName();		
		
	}
	
	else return;
	


	//写入EXCEL
	
 
	//str  = _T(GetFileNameXls("Save"));
    //CString sExcelFile = str ; // 要建立的Excel文件
    
    
	
    CString sDriver = _T( "MICROSOFT EXCEL DRIVER (*.XLS)" ); // Excel安装驱动
    //CString sExcelFile = _T( "./data/SeriesData.xls" ); // 将被读取的Excel文件名

	CString  sSql;
	CDatabase db ;
    TRY
    {
        // 创建进行存取的字符串
        sSql.Format("DRIVER={%s};DSN='''';FIRSTROWHASNAMES=1;READONLY=FALSE;CREATE_DB=\"%s\";DBQ=%s",
            sDriver, sExcelFile, sExcelFile);
        // 创建数据库 (既Excel表格文件)
        if ( db.OpenEx(sSql,CDatabase::noOdbcDialog) )
        {
            
            //捕获异常
			try
			{
                //删除表
                //db.ExecuteSQL(_T( "DROP  TABLE Test" ));
                
			}
			catch (CDBException *pe)
			{
				// The error code is in pe->m_nRetCode
				pe->ReportError();
				pe->Delete();
			}
			
            //创建表
            db.ExecuteSQL(_T( "CREATE TABLE Sheet1 (名称 TEXT, 数据 NUMBER, 重量 NUMBER, 单价 NUMBER)" ));
            
            // 插入数值
            //db.ExecuteSQL(_T( "INSERT INTO Test (Name,Val,WeightMeter,UnitPrice) VALUES ('铝型材喷涂',0.0,0.0,29.5)" ));

			db.ExecuteSQL(_T( "INSERT INTO Sheet1 VALUES ('铝型材喷涂',0.0,0.0,29.5)" ));
			
			
        }
        // 关闭数据库
        db.Close();
    }
    CATCH_ALL(e)
    {
        TRACE1( "Excel驱动没有安装: %s" ,sDriver);
    }
    END_CATCH_ALL;
  
}
