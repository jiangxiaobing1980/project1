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
    
    // ��ȡ�Ѱ�װ����������(������odbcinst.h��)#include <odbcinst.h>
    if (!SQLGetInstalledDrivers(szBuf, cbBufMax, &cbBufOut))
        return "";
    
    // �����Ѱ�װ�������Ƿ���Excel...
    do
    {
        if (strstr(pszBuf, "Excel") != 0)
        {
            //���� !
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
        
        "xls file(*.xls)|*.xls||");    //TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի���
    
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

	if(szState =="�Զ�����")
	{
		FilePathName = _T( "./data/PublicData.xls" ); // ������ȡ��Excel�ļ���

	}

	if(szState =="ѡ�����")
	{
		FilePathName =GetFilePathName() ; 
	}

	
  
    if(FilePathName.IsEmpty())
    {
        return ;   
    }
 /**/

	//��ձ�
	while (!m_PublicTable->IsEmpty())		
	{ 
		delete  m_PublicTable->GetHead();
		
		m_PublicTable->RemoveHead(); 
	}

	// ȫ����� 
	m_ListCtrl1->DeleteAllItems(); 
	while (m_ListCtrl1->DeleteColumn(0));	//������б�ͷ


    CDatabase db ;

        CString sDriver, sDsn , sSql ; // ,  sFile������ȡ��Excel�ļ���
        
        // �����Ƿ�װ��Excel���� "Microsoft Excel Driver (*.xls)"
        sDriver = GetExcelDriver();
        if (sDriver.IsEmpty())
        {
            // û�з���Excel����
            AfxMessageBox(_T( "û�а�װExcel����!" ));
            return ;
        }
        
        // �������д�ȡ���ַ���
        sDsn.Format(_T( "ODBC;DRIVER={%s};DSN='';DBQ=%s" ), sDriver, FilePathName);
        
        TRY
        {
            // �����ݿ�(��Excel�ļ�)    //����EXCEL
            db.Open(NULL, false , false , sDsn);
            
            CRecordset rs(&db);

            // ���ö�ȡ�Ĳ�ѯ���.
            sSql .Format( _T("SELECT * FROM %s" ),"[Sheet1$]" );    //�ֶ�����Ҫ�ִ�Сд��������
                     
            // ִ�в�ѯ���
            rs.Open(CRecordset::forwardOnly, sSql,CRecordset::none);

//����ȡ�ñ����ֶ�����
            short sFieldCount = rs.GetODBCFieldCount();

         CODBCFieldInfo fieldinfo;
            CStringArray strArrPublicFields;

            for( int i=0; i < sFieldCount; i++)
            {
                rs.GetODBCFieldInfo(i,fieldinfo);
 
                //�Ѷ����ı�ͷ��дһ���ַ�������                
                strArrPublicFields.Add(_T(fieldinfo.m_strName.GetBuffer(fieldinfo.m_strName.GetLength())));
            }    
 
            //Ϊ���ؼ����ñ�ͷ
            DWORD dwExtStyles1 = m_ListCtrl1->GetExtendedStyle();
            m_ListCtrl1->SetExtendedStyle(dwExtStyles1 | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
            for(i = 0 ; i < strArrPublicFields.GetSize() ; i++)
            {                
                m_ListCtrl1->InsertColumn(i,strArrPublicFields.GetAt(i),LVCFMT_LEFT,100,i);            
            }
            
    
            i =0 ;            
            // ��ȡ��ѯ���//��ȡ��¼
            while (!rs.IsEOF())
            {                    
                //�Ѽ�¼�е�����д�뵽�ڴ�����
                    CStringArray *pNewItem = new CStringArray ;

                    for(i = 0 ; i < strArrPublicFields.GetSize() ; ++i)
                    {
                        CString str ;
                        rs.GetFieldValue(strArrPublicFields.GetAt(i), str);    pNewItem->Add(str);    
                    }
                    //�Ѽ�¼���빫�����ݱ�
                    m_PublicTable->AddHead(pNewItem);                
                    //delete pNewItem;                    
                
                // �Ƶ���һ��
                rs.MoveNext();                  
            }
            
            rs.Close();
            // �ر����ݿ�
            db.Close();


							
			CStringArray *TempItem;
			
			POSITION pos=m_PublicTable->GetHeadPosition();
			
			//ѭ�������ҳ������е�������Ϣ
			
			while (pos!=NULL)
				
			{	
				TempItem =(CStringArray* ) m_PublicTable->GetNext(pos);
				
				for(i = 0 ; i < TempItem->GetSize() ; i++)
				{					
								//������д����ؼ�
						if (i == 0)
							m_ListCtrl1->InsertItem(0, TempItem->GetAt(0) );//������
						else
							m_ListCtrl1->SetItemText(0,i,TempItem->GetAt(i));//���ø��еĲ�ͬ�е���ʾ�ַ�						

				}
				
			}			
            
        }

	
		
        CATCH(CDBException, e)
        {
            // ���ݿ���������쳣ʱ...
            AfxMessageBox(_T( "���ݿ����: " ) + e->m_strError);
        }
        END_CATCH;    


}

void COperationExcel::WriteExcel()
{
	CString sExcelFile ;
	
	CFileDialog dlg(FALSE,"xls file(*.xls)|*.xls", NULL,
		
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		
		"xls file(*.xls)|*.xls||");    //TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի���
	
	if(dlg.DoModal()==IDOK)
	{
		
		sExcelFile=dlg.GetPathName();		
		
	}
	
	else return;
	


	//д��EXCEL
	
 
	//str  = _T(GetFileNameXls("Save"));
    //CString sExcelFile = str ; // Ҫ������Excel�ļ�
    
    
	
    CString sDriver = _T( "MICROSOFT EXCEL DRIVER (*.XLS)" ); // Excel��װ����
    //CString sExcelFile = _T( "./data/SeriesData.xls" ); // ������ȡ��Excel�ļ���

	CString  sSql;
	CDatabase db ;
    TRY
    {
        // �������д�ȡ���ַ���
        sSql.Format("DRIVER={%s};DSN='''';FIRSTROWHASNAMES=1;READONLY=FALSE;CREATE_DB=\"%s\";DBQ=%s",
            sDriver, sExcelFile, sExcelFile);
        // �������ݿ� (��Excel����ļ�)
        if ( db.OpenEx(sSql,CDatabase::noOdbcDialog) )
        {
            
            //�����쳣
			try
			{
                //ɾ����
                //db.ExecuteSQL(_T( "DROP  TABLE Test" ));
                
			}
			catch (CDBException *pe)
			{
				// The error code is in pe->m_nRetCode
				pe->ReportError();
				pe->Delete();
			}
			
            //������
            db.ExecuteSQL(_T( "CREATE TABLE Sheet1 (���� TEXT, ���� NUMBER, ���� NUMBER, ���� NUMBER)" ));
            
            // ������ֵ
            //db.ExecuteSQL(_T( "INSERT INTO Test (Name,Val,WeightMeter,UnitPrice) VALUES ('���Ͳ���Ϳ',0.0,0.0,29.5)" ));

			db.ExecuteSQL(_T( "INSERT INTO Sheet1 VALUES ('���Ͳ���Ϳ',0.0,0.0,29.5)" ));
			
			
        }
        // �ر����ݿ�
        db.Close();
    }
    CATCH_ALL(e)
    {
        TRACE1( "Excel����û�а�װ: %s" ,sDriver);
    }
    END_CATCH_ALL;
  
}
