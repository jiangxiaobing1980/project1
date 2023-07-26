// OutToExcel.cpp : implementation file
//

#include "stdafx.h"
#include "Test.h"
#include "OutToExcel.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutToExcel

IMPLEMENT_DYNCREATE(COutToExcel, CCmdTarget)

COutToExcel::COutToExcel()
{
	EnableAutomation();	
}

COutToExcel::~COutToExcel()
{

		//CoperationList oper;
		//oper.RemoveAll( pPublicTable);
}


void COutToExcel::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanUnitPrice required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(COutToExcel, CCmdTarget)
	//{{AFX_MSG_MAP(COutToExcel)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(COutToExcel, CCmdTarget)
	//{{AFX_DISPATCH_MAP(COutToExcel)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add sUnitPriceport for IID_IOutToExcel to sUnitPriceport typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {67E15B17-1771-4D26-88CD-8EF566055EF4}
static const IID IID_IOutToExcel =
{ 0x67e15b17, 0x1771, 0x4d26, { 0x88, 0xcd, 0x8e, 0xf5, 0x66, 0x5, 0x5e, 0xf4 } };

BEGIN_INTERFACE_MAP(COutToExcel, CCmdTarget)
	INTERFACE_PART(COutToExcel, IID_IOutToExcel, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutToExcel message handlers

CString COutToExcel::GetExcelDriver()
{

	char szBuf[2001];
    WORD cbBufMax = 2000;
    WORD cbBufOut;
    char *pszBuf = szBuf;
    CString sDriver;
    
    // ��ȡ�Ѱ�װ����������(������odbcinst.h��)
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

void COutToExcel::WriteFrameData()
{			
				
		


	 	CoperationList oper;

	

 				double Alum_WeightMeter = oper.NameToWeightMeter(pSeriesTable,"��������");
 				double InsulationBar_WeightMeter = oper.NameToWeightMeter(pSeriesTable,"���������"); //����������
// 
// 
 				int xLength = oper.GetFrameRect(pBoxTable).Width();
 				int yLength = oper.GetFrameRect(pBoxTable).Height();
// 				
// 				
				double ComplexAlum_WeightMeter = Alum_WeightMeter + InsulationBar_WeightMeter;
				double Alum_UnitPrice = oper.NameToUnitPrice(pPublicTable,"��Ϳ���Ͳ�");


				//int i = oper.GetCount( pPublicTable);


				//CString str ; 
				//str.Format("%0.1f", Alum_UnitPrice );
				//AfxMessageBox (str);
				
									
				double AlumFrameFile_xTotal = ComplexAlum_WeightMeter* Alum_UnitPrice* 2* xLength/ 1000;
				double AlumFrameFile_yTotal = ComplexAlum_WeightMeter* Alum_UnitPrice* 2* yLength/ 1000;

				sSql.Format( "%s('����','���Ͳ�',%d,%d,%d,%0.3f,%d,'֧',%0.2f,%0.2f,'��0.03���')" ,
					TableHand,
					xLength,0,0,ComplexAlum_WeightMeter,2,Alum_UnitPrice,AlumFrameFile_xTotal*1.03);
				database.ExecuteSQL(sSql);


				sSql.Format( "%s('����','���Ͳ�',%d,%d,%d,%0.3f,%d,'֧',%0.2f,%0.2f,'��0.03���')" ,
					TableHand,
					yLength,0,0,ComplexAlum_WeightMeter,2,Alum_UnitPrice,AlumFrameFile_yTotal*1.03);
				database.ExecuteSQL(sSql);


// 
// 				
			// �����������ֵ				
 				//double InsulationBar_WeightMeter = 0.055+0.055;
				double InsulationBar_UnitPrice =  oper.NameToUnitPrice(pSeriesTable,"���������"); //����������	
 				int InsulationBar_Length = (xLength+yLength)*2 ;
 				double InsulationBar_Total = 1.1* InsulationBar_UnitPrice*InsulationBar_Length/1000;				
 				

// 
// 				//  ���븴�ϸ������ӹ�����ֵ				
// 				
 				double InsulationBar_Process_UnitPrice = oper.NameToUnitPrice(pPublicTable,"�����ӹ���");	
// 				
 				double InsulationBar_Process_Total = ComplexAlum_WeightMeter *InsulationBar_Length/1000 * InsulationBar_Process_UnitPrice  ;				
// 				

// 
// 				
// 
 				//���븴�ϸ����������ֵ			
// 				//ȫ���Ͻ�+������+�ӹ���-���Ϻ�۸�
 				double InsulationBar_Difference = Alum_WeightMeter * Alum_UnitPrice * InsulationBar_Length/1000  +
 					InsulationBar_Total + InsulationBar_Process_Total-  AlumFrameFile_xTotal - AlumFrameFile_yTotal ;			
// 				
 				sSql.Format( "%s('����','���������',%d,%d,%d,%0.3f,%d,'��',%0.2f,%0.2f,'��0.1���')" ,
 					TableHand,InsulationBar_Length,0,0,InsulationBar_WeightMeter,1,InsulationBar_UnitPrice,InsulationBar_Difference);
 				database.ExecuteSQL(sSql);
// 				
// 
// 				
// // //			// ����ֽ�Ƭ��ֵ// 			
 				double SteelAngle_UnitPrice = oper.NameToUnitPrice(pSeriesTable,"����ֽ�Ƭ"); //����ֽ�Ƭ		
 				double SteelAngle_Total = SteelAngle_UnitPrice * 4 ;				
 				
 				sSql.Format( "%s('����','�ֽ�Ƭ',%d,%d,%d,%0.3f,%d,'��',%0.2f,%0.2f,'')" ,
					TableHand,0,0,0,0.0,4,SteelAngle_UnitPrice,SteelAngle_Total);
 				database.ExecuteSQL(sSql);
// // 
// // 
// // 
// // 
// // //				// ���������ֵ				
 				double AlumAngle_UnitPrice = oper.NameToUnitPrice(pSeriesTable,"�������");				
 				double AlumAngle_Total = AlumAngle_UnitPrice * 4;				
// 				
 				sSql.Format( "%s('����','����',%d,%d,%d,%0.3f,%d,'��',%0.2f,%0.2f,'')" ,
					TableHand,0,0,0,0.0,4,AlumAngle_UnitPrice,AlumAngle_Total);
 				database.ExecuteSQL(sSql);
 
// 				
// // // 				// �����ڽ���ע����ֵ				
 				int AlumAngle_Glue_len = oper.NameToValue(pSeriesTable,"�������ע������");	
 				double Glue_UnitPrice = oper.NameToUnitPrice(pPublicTable,"����ע��");				//����ע��
 				double AlumAngle_Glue_Total =  Glue_UnitPrice * 4 * AlumAngle_Glue_len ;				
// 				
 				sSql.Format( "%s('����','����ע��',%d,%d,%d,%0.3f,%d,'��',%0.3f,%0.2f,'')" ,
					TableHand,AlumAngle_Glue_len,0,0,0.0,4,Glue_UnitPrice,AlumAngle_Glue_Total);
 				database.ExecuteSQL(sSql);
// 
// 				
// // // 				// ������潺��ֵ
 				double SectionGlue_UnitPrice =  oper.NameToUnitPrice(pPublicTable,"���潺");				
 				double SectionGlue_Total = SectionGlue_UnitPrice *4;				
// 				
 				sSql.Format( "%s('����','���潺',%d,%d,%d,%0.3f,%d,'��',%0.2f,%0.2f,'')" ,
					TableHand,0,0,0,0.0,4,SectionGlue_UnitPrice,SectionGlue_Total);
 				database.ExecuteSQL(sSql);


}

void COutToExcel::WriteCasementData()
{
					
/**********************************************************************/
				//�����Ǵ��ȵļ���
	CoperationList oper;
	
	
	int xLength = 0 ;
	
	POSITION pos = pBoxTable->GetHeadPosition();
	for (int i = 0; i < pBoxTable->GetCount(); i++)
	{			
		//ȡ������
		POSITION pos1 = pBoxTable->FindIndex(i);					
		CBox* d1 = (CBox* )pBoxTable->GetAt(pos1);			
		int it = d1->GetToType() ;
		CRect rt = d1->GetBox();
		
		//�����������������
		if(6 == it || 7 == it)
		{	
			
			

			double Bar_InFrame_Value = oper.NameToValue(pSeriesTable,"�������"); //
			// 
			// 
			int xLength = rt.Width() + Bar_InFrame_Value * 2  ;
			int yLength = rt.Height()+ Bar_InFrame_Value * 2  ;
			// 				
			// 				
			
			double Alum_WeightMeter = oper.NameToWeightMeter(pSeriesTable,"��������");
			double InsulationBar_WeightMeter = oper.NameToWeightMeter(pSeriesTable,"���ȸ�����"); //����������
			// 

			// 				
			// 				
			double ComplexAlum_WeightMeter = Alum_WeightMeter + InsulationBar_WeightMeter;
			double Alum_UnitPrice = oper.NameToUnitPrice(pPublicTable,"��Ϳ���Ͳ�");				
			
			double AlumFrameFile_xTotal = ComplexAlum_WeightMeter* Alum_UnitPrice* 2* xLength/ 1000;
			double AlumFrameFile_yTotal = ComplexAlum_WeightMeter* Alum_UnitPrice* 2* yLength/ 1000;
			
			sSql.Format( "%s('������','���Ͳ�',%d,%d,%d,%0.3f,%d,'֧',%0.2f,%0.2f,'��0.03���')" ,
				TableHand,
				xLength,0,0,ComplexAlum_WeightMeter,2,Alum_UnitPrice,AlumFrameFile_xTotal*1.03);
			database.ExecuteSQL(sSql);
			
			
			sSql.Format( "%s('������','���Ͳ�',%d,%d,%d,%0.3f,%d,'֧',%0.2f,%0.2f,'��0.03���')" ,
				TableHand,
				yLength,0,0,ComplexAlum_WeightMeter,2,Alum_UnitPrice,AlumFrameFile_yTotal*1.03);
				database.ExecuteSQL(sSql);


				// �����������ֵ				
				
				double InsulationBar_UnitPrice =  oper.NameToUnitPrice(pSeriesTable,"���ȸ�����"); //�������۸�	
				int InsulationBar_Length = (xLength+yLength)*2 ;
				double InsulationBar_Total = 1.1* InsulationBar_UnitPrice*InsulationBar_Length/1000;				
				
				
				// 
				// 				//  ���븴�ϸ������ӹ�����ֵ				
				// 				
				double InsulationBar_Process_UnitPrice = oper.NameToUnitPrice(pPublicTable,"�����ӹ���");					
				double InsulationBar_Process_Total = ComplexAlum_WeightMeter *InsulationBar_Length/1000 * InsulationBar_Process_UnitPrice  ;				
				// 				
				
				// 
				// 				
				// 
				//���븴�ϸ����������ֵ			
				// 				//ȫ���Ͻ�+������+�ӹ���-���Ϻ�۸�
				double InsulationBar_Difference = Alum_WeightMeter * Alum_UnitPrice * InsulationBar_Length/1000  +
					InsulationBar_Total + InsulationBar_Process_Total-  AlumFrameFile_xTotal - AlumFrameFile_yTotal ;			
				// 				
				sSql.Format( "%s('������','���������',%d,%d,%d,%0.3f,%d,'��',%0.2f,%0.2f,'��0.1���')" ,
					TableHand,InsulationBar_Length,0,0,InsulationBar_WeightMeter,1,InsulationBar_UnitPrice,InsulationBar_Difference);
				database.ExecuteSQL(sSql);
				// 				
				// 
				// 				
				// // //			// ����ֽ�Ƭ��ֵ// 			
				double SteelAngle_UnitPrice = oper.NameToUnitPrice(pSeriesTable,"�����ȸֽ�Ƭ"); //����ֽ�Ƭ
				int SteelAngle_Quantity = (int )oper.NameToValue(pSeriesTable,"�����ȸֽ�Ƭ"); //����ֽ�Ƭ	
				double SteelAngle_Total = SteelAngle_UnitPrice * 4 * SteelAngle_Quantity;				
				
				sSql.Format( "%s('������','�ֽ�Ƭ',%d,%d,%d,%0.3f,%d,'��',%0.2f,%0.2f,'')" ,
					TableHand,0,0,0,0.0,4* SteelAngle_Quantity,SteelAngle_UnitPrice,SteelAngle_Total);
				database.ExecuteSQL(sSql);
// // 

				//////////////////////////////////////////////////////////
				
				// // //				// ���������ֵ				
				double AlumAngle_UnitPrice = oper.NameToUnitPrice(pSeriesTable,"�����Ƚ���");				
				double AlumAngle_Total = AlumAngle_UnitPrice * 4;				
				// 				
				sSql.Format( "%s('������','����',%d,%d,%d,%0.3f,%d,'��',%0.2f,%0.2f,'')" ,
					TableHand,0,0,0,0.0,4,AlumAngle_UnitPrice,AlumAngle_Total);
				database.ExecuteSQL(sSql);
				
				// 				
				// // // 				// �������ע����ֵ				
				int AlumAngle_Glue_len = oper.NameToValue(pSeriesTable,"�����Ƚ���ע������");	
				double Glue_UnitPrice = oper.NameToUnitPrice(pPublicTable,"����ע��");				//����ע��
				double AlumAngle_Glue_Total =  Glue_UnitPrice * 4 * AlumAngle_Glue_len ;				
				// 				
				sSql.Format( "%s('������','����ע��',%d,%d,%d,%0.3f,%d,'��',%0.3f,%0.2f,'')" ,
					TableHand,AlumAngle_Glue_len,0,0,0.0,4,Glue_UnitPrice,AlumAngle_Glue_Total);
				database.ExecuteSQL(sSql);
				
				
				// // // 				// ������潺��ֵ
				double SectionGlue_UnitPrice =  oper.NameToUnitPrice(pPublicTable,"���潺");				
				double SectionGlue_Total = SectionGlue_UnitPrice * 4  ;				
				// 				
				sSql.Format( "%s('������','���潺',%d,%d,%d,%0.3f,%d,'��',%0.2f,%0.2f,'')" ,
					TableHand,0,0,0,0.0,4,SectionGlue_UnitPrice,SectionGlue_Total);
				database.ExecuteSQL(sSql);
				
				 
				//�����Ȳ���
				
				double Glass_Weight = oper.NameToWeightMeter(pPublicTable,"����5+20A+5") ; //����			
				double Glass_UnitPrice = oper.NameToUnitPrice(pPublicTable,"����5+20A+5") ; //�۸�	
				
				double FixFileHight = oper.NameToValue(pSeriesTable,"���ȴ���");
				double GlassInFix = oper.NameToValue(pSeriesTable,"�Ȳ�����");
				
				double GlassWidth =  xLength- FixFileHight * 2 + GlassInFix * 2 ;
				double  GlassHight = yLength- FixFileHight * 2 + GlassInFix * 2 ;
				
				double Glass_Total_Price = Glass_UnitPrice * GlassWidth /1000 * GlassHight /1000 ;
				
				
				sSql.Format( "%s('������','����',%d,%d,%d,%0.3f,%d,'��',%0.2f,%0.2f,'')" ,
					TableHand,0,(int )GlassWidth,(int )GlassHight,0.0,1,Glass_UnitPrice,Glass_Total_Price);
				database.ExecuteSQL(sSql);
				
				
				// //			// ����EPDM������ֵ				
				//double InsulationBar_WeightMeter = 0.055+0.055;
				double EPDM_UnitPrice = oper.NameToUnitPrice(pSeriesTable,"�Ȳ���EPDM����") ; //�۸�	
				double EPDM_Length = (GlassWidth+GlassHight)*2 ;
				double EPDM_Total = EPDM_UnitPrice*EPDM_Length/1000;				
				// 				
				sSql.Format( "%s('������','�Ȳ���EPDM����',%d,%d,%d,%0.3f,%d,'��',%0.2f,%0.2f,'')" ,
					TableHand,(int )EPDM_Length,0,0,0.0,1,EPDM_UnitPrice,EPDM_Total);
				database.ExecuteSQL(sSql);
				// 				
				
				// //			// ����EPDM������ֵ				
				//double InsulationBar_WeightMeter = 0.055+0.055;
				double EPDM_UnitPrice_2 = oper.NameToUnitPrice(pSeriesTable,"���ܷ�EPDM����") ; //�۸�	
				double EPDM_Length_2 = (xLength+yLength)*2 ;
				double EPDM_Total_2 = EPDM_UnitPrice_2 *EPDM_Length_2/1000;				
				// 				
				sSql.Format( "%s('������','���ܷ�EPDM����',%d,%d,%d,%0.3f,%d,'��',%0.2f,%0.2f,'')" ,
					TableHand,(int )EPDM_Length_2,0,0,0.0,1,EPDM_UnitPrice_2,EPDM_Total_2);
				database.ExecuteSQL(sSql);
				// 				

				
				
				// 				//�̶�������װ��Ĥ
				// 							
				double GlassPack_UnitPrice =  oper.NameToUnitPrice(pPublicTable,"������װ") ; //�۸�				
				double GlassPack_Total = GlassPack_UnitPrice * GlassWidth * GlassHight /1000 /1000 ;
				
				
				sSql.Format( "%s('������','������װ��Ĥ',%d,%d,%d,%0.3f,%d,'��',%0.2f,%0.2f,'')" ,
					TableHand,0,(int )GlassWidth,(int )GlassHight,0.0,1,GlassPack_UnitPrice,GlassPack_Total);
				database.ExecuteSQL(sSql);
				
				// 				// // 				// ���벣�������ֵ
				double Block_UnitPrice =  oper.NameToUnitPrice(pSeriesTable,"�����Ȳ������");		//�̶��������
			
				double Block_Total = Block_UnitPrice * 4;				
				// 				
				sSql.Format( "%s('������','�������',%d,%d,%d,%0.3f,%d,'��',%0.2f,%0.2f,'')" ,
					TableHand,0,0,0,0.0,4,Block_UnitPrice,Block_Total);
				database.ExecuteSQL(sSql);
				
				///////////////////////////////////////////////////////////

				///////////////////////////////////////////////////////////
				
				
				// 				// // 				// ���봫��������ֵ
				double AlumBar_Weight =  oper.NameToWeightMeter(pPublicTable,"��������");
				double AlumBar_UnitPrice =  oper.NameToUnitPrice(pPublicTable,"��������");
				
				double AlumBar_Total = (yLength -300.0)  *  AlumBar_Weight * AlumBar_UnitPrice /1000;
				// 				
				sSql.Format( "%s('������','��������',%d,%d,%d,%0.3f,%d,'֧',%0.2f,%0.2f,'')" ,
					TableHand,(int )(yLength -300.0),0,0,AlumBar_Weight,1,AlumBar_UnitPrice,AlumBar_Total);
				database.ExecuteSQL(sSql);
				
				///////////////////////////////////////////////////////////

				// 				// // 				// ���������ֵ
				double HandWave_UnitPrice =  oper.NameToUnitPrice(pSeriesTable,"���������");
				// 				
				sSql.Format( "%s('������','���',%d,%d,%d,%0.3f,%d,'��',%0.2f,%0.2f,'')" ,
					TableHand,0,0,0,0.0,1,0.0,HandWave_UnitPrice);
				database.ExecuteSQL(sSql);
				
				///////////////////////////////////////////////////////////


		}
	}
				

/**********************************************************************/
				

}

void COutToExcel::WriteStileData()
{

	//// ����������ֵ


	//AfxMessageBox("000");
	
	CoperationList oper;


	int xLength = 0 ;
	
	POSITION pos = pBoxTable->GetHeadPosition();
	for (int i = 0; i < pBoxTable->GetCount(); i++)
	{			
		//ȡ������
		POSITION pos1 = pBoxTable->FindIndex(i);					
		CBox* d1 = (CBox* )pBoxTable->GetAt(pos1);			
		int it = d1->GetToType() ;
		CRect rt = d1->GetBox();

		//�����������������
		if(2 == it || 12 == it)
		{	
			if( 2 == it)	xLength = rt.Height();
			if(12 == it)	xLength = rt.Width();
	
			
			if(xLength != 0)
			{	
							
				double Alum_WeightMeter = oper.NameToWeightMeter(pSeriesTable,"��������");
				double InsulationBar_WeightMeter = oper.NameToWeightMeter(pSeriesTable,"���������"); //����������
	
				int yLength = (int)oper.NameToValue(pSeriesTable,"�������");

				
				double ComplexAlum_WeightMeter = Alum_WeightMeter + InsulationBar_WeightMeter;
				double Alum_UnitPrice = oper.NameToUnitPrice(pPublicTable,"��Ϳ���Ͳ�");				
				
				double AlumFrameFile_xTotal = ComplexAlum_WeightMeter* Alum_UnitPrice*  (xLength + yLength *2 )/ 1000;

				sSql.Format( "%s('����','���Ͳ�',%d,%d,%d,%0.3f,%d,'֧',%0.2f,%0.2f,'��0.03���')" ,
					TableHand,
					xLength,0,0,ComplexAlum_WeightMeter,1,Alum_UnitPrice,AlumFrameFile_xTotal*1.03);
				database.ExecuteSQL(sSql);
				////////////////////////////////////////////////////////

				// 				
				// ���������������ֵ				
				//double InsulationBar_WeightMeter = 0.055+0.055;
				double InsulationBar_UnitPrice =  oper.NameToUnitPrice(pSeriesTable,"���������"); //����������	
				int InsulationBar_Length = xLength+yLength*2 ;
				double InsulationBar_Total = 1.1* InsulationBar_UnitPrice*InsulationBar_Length/1000;				
				
			
				// 				//  ���븴�ϸ������ӹ�����ֵ				
							
				double InsulationBar_Process_UnitPrice = oper.NameToUnitPrice(pPublicTable,"�����ӹ���");	
								
				double InsulationBar_Process_Total = ComplexAlum_WeightMeter *InsulationBar_Length/1000 * InsulationBar_Process_UnitPrice  ;				
						
			
				//���븴�ϸ����������ֵ			
				// 				//ȫ���Ͻ�+������+�ӹ���-���Ϻ�۸�
				double InsulationBar_Difference = Alum_WeightMeter * Alum_UnitPrice * InsulationBar_Length/1000  +
					InsulationBar_Total + InsulationBar_Process_Total-  AlumFrameFile_xTotal  ;			
				// 				
				sSql.Format( "%s('����','���������',%d,%d,%d,%0.3f,%d,'��',%0.2f,%0.2f,'��0.1���')" ,
					TableHand,InsulationBar_Length,0,0,InsulationBar_WeightMeter,1,InsulationBar_UnitPrice,InsulationBar_Difference);
 				database.ExecuteSQL(sSql);

				///////////////////////////////////////////

				// // //				// ���������ֵ				
				double AlumAngle_UnitPrice = oper.NameToUnitPrice(pSeriesTable,"�������");				
				double AlumAngle_Total = AlumAngle_UnitPrice * 2;				
				// 				
				sSql.Format( "%s('����','����',%d,%d,%d,%0.3f,%d,'��',%0.2f,%0.2f,'')" ,
					TableHand,0,0,0,0.0,2,AlumAngle_UnitPrice,AlumAngle_Total);
 				database.ExecuteSQL(sSql);
				// // // 				// �����������ע����ֵ				
				int AlumAngle_Glue_len = oper.NameToValue(pSeriesTable,"�������ע������");	
				double Glue_UnitPrice = oper.NameToUnitPrice(pPublicTable,"����ע��");				//����ע��
				double AlumAngle_Glue_Total =  Glue_UnitPrice * 2 * AlumAngle_Glue_len ;				
				// 				
				sSql.Format( "%s('����','����ע��',%d,%d,%d,%0.3f,%d,'��',%0.3f,%0.2f,'')" ,
					TableHand,AlumAngle_Glue_len,0,0,0.0,2,Glue_UnitPrice,AlumAngle_Glue_Total);
 				database.ExecuteSQL(sSql);
				//////////////////////////////////////////////////////////////////////////////


				// // // 				// ���������ˮ����				
					
				double XPE_UnitPrice = oper.NameToUnitPrice(pSeriesTable,"�����ˮ����");				//����ע��
				double AlumAngle_XPE_Total =  XPE_UnitPrice * 2  ;				
				// 				
				sSql.Format( "%s('����','��ˮ����',%d,%d,%d,%0.3f,%d,'��',%0.3f,%0.2f,'')" ,
					TableHand,0,0,0,0.0,2,XPE_UnitPrice,AlumAngle_XPE_Total);
				database.ExecuteSQL(sSql);
				//////////////////////////////////////////////////////////////////////////////


		
			}


		}

	}
	
							
				//// ���������������ֵ				
// 				//double InsulationBar_WeightMeter = 0.055+0.055;
// 				double InsulationBar_UnitPrice = 2.65+2.65 ;	
// 				int InsulationBar_Length = xLength ;
// 				double InsulationBar_Total = 1.1* InsulationBar_UnitPrice*InsulationBar_Length/1000;				
// 				
// 				sSql.Format( "%s('���������',%d,%d,%0.3f,%d,'��',%0.2f,%0.2f,'��0.1���')" ,
// 					TableHand,InsulationBar_Length,0,InsulationBar_WeightMeter,1,InsulationBar_UnitPrice,InsulationBar_Total);
// 				database.ExecuteSQL(sSql);
// 				
// 				//  ���븴�ϸ������ӹ�����ֵ				
// 				
// 				double InsulationBar_Process_UnitPrice = 1.06;	
// 				
// 				double InsulationBar_Process_Total = ComplexAlum_WeightMeter *InsulationBar_Length/1000 * InsulationBar_Process_UnitPrice  ;				
// 				
// 				sSql.Format( "%s('������������ϼӹ���',%d,%d,%0.3f,%d,'��',%0.2f,%0.2f,'')" ,
// 					TableHand,InsulationBar_Length,0,0.0,1,InsulationBar_Process_UnitPrice,InsulationBar_Process_Total);
// 				database.ExecuteSQL(sSql);
// 				
// 				
// 				
// 				//���븴�ϸ����������ֵ			
// 				//ȫ���Ͻ�+������+�ӹ���-���Ϻ�۸�
// 				double InsulationBar_Difference = Alum_WeightMeter * Alum_UnitPrice * InsulationBar_Length/1000  +
// 					InsulationBar_Total + InsulationBar_Process_Total-  AlumStileFile_Total ;			
// 				
// 				sSql.Format( "%s('���������',%d,%d,%0.3f,%d,'��',%0.2f,%0.2f,'')" ,
// 					TableHand,0,0,0.0,1,0.0,InsulationBar_Difference);
// 				database.ExecuteSQL(sSql);
// 				
// 		
// 				// //				// ���������ֵ				
// 				double AlumAngle_UnitPrice = 2.2+2.4;				
// 				double AlumAngle_Total = AlumAngle_UnitPrice * 2;				
// 				
// 				sSql.Format( "%s('�������',%d,%d,%0.3f,%d,'��',%0.2f,%0.2f,'')" ,TableHand,0,0,0.0,2,AlumAngle_UnitPrice,AlumAngle_Total);
// 				database.ExecuteSQL(sSql);
// 				
// 				
// 				// // 				// �������ע����ֵ				
// 				int AlumAngle_Glue_len = 33*2+20+19*2+20;
// 				double Glue_UnitPrice = 0.016;				
// 				double AlumAngle_Glue_Total =  Glue_UnitPrice * 2 * AlumAngle_Glue_len ;				
// 				
// 				sSql.Format( "%s('�������ע��',%d,%d,%0.3f,%d,'��',%0.3f,%0.2f,'')" ,TableHand,AlumAngle_Glue_len,0,0.0,2,Glue_UnitPrice,AlumAngle_Glue_Total);
// 				database.ExecuteSQL(sSql);


}

void COutToExcel::WriteFixData()
{
	//				// ����̶�����ֵ

	
	CoperationList oper;
	
	
	int xLength = 0 ;
	
	POSITION pos = pBoxTable->GetHeadPosition();
	for (int i = 0; i < pBoxTable->GetCount(); i++)
	{			
		//ȡ������
		POSITION pos1 = pBoxTable->FindIndex(i);					
		CBox* d1 = (CBox* )pBoxTable->GetAt(pos1);			
		int it = d1->GetToType() ;
		CRect rt = d1->GetBox();
		
		//�����������������
		if(5 == it )
		{	
			
	
	double Alum_WeightMeter = oper.NameToWeightMeter(pSeriesTable,"�̶�ѹ������");
	double Bar_InFrame_Value = oper.NameToValue(pSeriesTable,"�̶�ѹ�����"); //����������
	// 
	// 
	int xLength = rt.Width() + Bar_InFrame_Value * 2  ;
	int yLength = rt.Height()+ Bar_InFrame_Value * 2  ;
	// 				
	// 				
				//double ComplexAlum_WeightMeter = Alum_WeightMeter + InsulationBar_WeightMeter;
				double Alum_UnitPrice = oper.NameToUnitPrice(pPublicTable,"��Ϳ���Ͳ�");				
				
				double AlumFrameFile_xTotal = Alum_WeightMeter* Alum_UnitPrice* 2* xLength/ 1000;
				double AlumFrameFile_yTotal = Alum_WeightMeter* Alum_UnitPrice* 2* yLength/ 1000;
				
				sSql.Format( "%s('�̶���','���Ͳ�',%d,%d,%d,%0.3f,%d,'֧',%0.2f,%0.2f,'��0.03���')" ,
					TableHand,
					xLength,0,0,Alum_WeightMeter,2,Alum_UnitPrice,AlumFrameFile_xTotal*1.03);
				database.ExecuteSQL(sSql);
				
				
				sSql.Format( "%s('�̶���','���Ͳ�',%d,%d,%d,%0.3f,%d,'֧',%0.2f,%0.2f,'��0.03���')" ,
					TableHand,
					yLength,0,0,Alum_WeightMeter,2,Alum_UnitPrice,AlumFrameFile_yTotal*1.03);
				database.ExecuteSQL(sSql);

				//////////////////////////////////////////////////////////

				// // //				// ���������ֵ				
				double AlumAngle_UnitPrice = oper.NameToUnitPrice(pSeriesTable,"�̶�ѹ�߽���");				
				double AlumAngle_Total = AlumAngle_UnitPrice * 4;				
				// 				
				sSql.Format( "%s('�̶���','����',%d,%d,%d,%0.3f,%d,'��',%0.2f,%0.2f,'')" ,
					TableHand,0,0,0,0.0,4,AlumAngle_UnitPrice,AlumAngle_Total);
				database.ExecuteSQL(sSql);
				
				// 				
				// // // 				// �������ע����ֵ				
				int AlumAngle_Glue_len = oper.NameToValue(pSeriesTable,"�̶�ѹ�߽���ע������");	
				double Glue_UnitPrice = oper.NameToUnitPrice(pPublicTable,"����ע��");				//����ע��
				double AlumAngle_Glue_Total =  Glue_UnitPrice * 4 * AlumAngle_Glue_len ;				
				// 				
				sSql.Format( "%s('�̶���','����ע��',%d,%d,%d,%0.3f,%d,'��',%0.3f,%0.2f,'')" ,
					TableHand,AlumAngle_Glue_len,0,0,0.0,4,Glue_UnitPrice,AlumAngle_Glue_Total);
 				database.ExecuteSQL(sSql);


				// // // 				// ������潺��ֵ
				double SectionGlue_UnitPrice =  oper.NameToUnitPrice(pPublicTable,"���潺") /2;				
				double SectionGlue_Total = SectionGlue_UnitPrice * 4  ;				
				// 				
				sSql.Format( "%s('�̶���','���潺',%d,%d,%d,%0.3f,%d,'��',%0.2f,%0.2f,'')" ,
					TableHand,0,0,0,0.0,4,SectionGlue_UnitPrice,SectionGlue_Total);
 				database.ExecuteSQL(sSql);

				// 
				//�̶�����
				
				double Glass_Weight = oper.NameToWeightMeter(pPublicTable,"����5+20A+5") ; //����			
				double Glass_UnitPrice = oper.NameToUnitPrice(pPublicTable,"����5+20A+5") ; //�۸�	
				
				double FixFileHight = oper.NameToValue(pSeriesTable,"ѹ�߸߶�");
				double GlassInFix = oper.NameToValue(pSeriesTable,"�̲����");
				
				double GlassWidth =  xLength- FixFileHight * 2 + GlassInFix * 2 ;
				double  GlassHight = yLength- FixFileHight * 2 + GlassInFix * 2 ;
				
				double Glass_Total_Price = Glass_UnitPrice * GlassWidth /1000 * GlassHight /1000 ;

				
				sSql.Format( "%s('�̶���','����',%d,%d,%d,%0.3f,%d,'��',%0.2f,%0.2f,'')" ,
					TableHand,0,(int )GlassWidth,(int )GlassHight,0.0,1,Glass_UnitPrice,Glass_Total_Price);
 				database.ExecuteSQL(sSql);


				// //			// ����EPDM������ֵ				
				 				//double InsulationBar_WeightMeter = 0.055+0.055;
				 				double EPDM_UnitPrice = oper.NameToUnitPrice(pSeriesTable,"�̶�����EPDM����") ; //�۸�	
				 				double EPDM_Length = (xLength+yLength)*2 ;
				 				double EPDM_Total = EPDM_UnitPrice*EPDM_Length/1000;				
				// 				
				sSql.Format( "%s('�̶���','����EPDM����',%d,%d,%d,%0.3f,%d,'��',%0.2f,%0.2f,'')" ,
					TableHand,(int )EPDM_Length,0,0,0.0,1,EPDM_UnitPrice,EPDM_Total);
 				database.ExecuteSQL(sSql);
// 				



				// 				//�̶�������װ��Ĥ
				// 							
				 				double GlassPack_UnitPrice =  oper.NameToUnitPrice(pPublicTable,"������װ") ; //�۸�				
				 				double GlassPack_Total = GlassPack_UnitPrice * GlassWidth * GlassHight /1000 /1000 ;
	
								
								sSql.Format( "%s('�̶���','������װ��Ĥ',%d,%d,%d,%0.3f,%d,'��',%0.2f,%0.2f,'')" ,
									TableHand,0,(int )GlassWidth,(int )GlassHight,0.0,1,GlassPack_UnitPrice,GlassPack_Total);
 				database.ExecuteSQL(sSql);

				// 				// // 				// ���벣�������ֵ
				 				double Block_UnitPrice =  oper.NameToUnitPrice(pSeriesTable,"�̶��������");		//�̶��������
				 				int Block_Quantity = (int ) (GlassWidth /300) ;
				 				if(Block_Quantity < 2 ) Block_Quantity = 2;
				 				double Block_Total = Block_UnitPrice * Block_Quantity;				
				// 				
								sSql.Format( "%s('�̶���','�������',%d,%d,%d,%0.3f,%d,'��',%0.2f,%0.2f,'')" ,
									TableHand,0,0,0,0.0,Block_Quantity,Block_UnitPrice,Block_Total);
				database.ExecuteSQL(sSql);

///////////////////////////////////////////////////////////
				// 				// // 				// ���뵲ˮ����ֵ
				 				double WaterStopXPE_UnitPrice = oper.NameToUnitPrice(pSeriesTable,"�̶�������ˮ��");	//�̶�������ˮ��			
				// 				
				 				double WaterStopXPE_Total = WaterStopXPE_UnitPrice * GlassWidth /1000;				
				// 				
								sSql.Format( "%s('�̶���','��ˮ��',%d,%d,%d,%0.3f,%d,'֧',%0.2f,%0.2f,'')" ,
									TableHand,(int )GlassWidth,0,0,0.0,1,WaterStopXPE_UnitPrice,WaterStopXPE_Total);
				database.ExecuteSQL(sSql);
	
				
		}
	}

	

// 				
// 				
// 
// 				
// 	

// 
// 

// 
// 

// 
// 




}


void COutToExcel::WriteScreensData()
{
					//������ɴ�����ȵļ���
				//�����Ǵ��ȵļ���
	CoperationList oper;
	
	
	int xLength = 0 ;
	
	POSITION pos = pBoxTable->GetHeadPosition();
	for (int i = 0; i < pBoxTable->GetCount(); i++)
	{			
		//ȡ������
		POSITION pos1 = pBoxTable->FindIndex(i);					
		CBox* d1 = (CBox* )pBoxTable->GetAt(pos1);			
		int it = d1->GetToType() ;
		CRect rt = d1->GetBox();
		
		//������������п�����
		if(6 == it || 7 == it)
		{	
			
			

			double Bar_InFrame_Value = oper.NameToValue(pSeriesTable,"ɴ�����"); //
			// 
			// 
			int xLength = rt.Width() + Bar_InFrame_Value * 2  ;
			int yLength = rt.Height()+ Bar_InFrame_Value * 2  ;
			// 				
			// 				
			
			double Alum_WeightMeter = oper.NameToWeightMeter(pSeriesTable,"ɴ������");
		
			// 				
			// 				
			
			double Alum_UnitPrice = oper.NameToUnitPrice(pPublicTable,"��Ϳ���Ͳ�");				
			
			double AlumFrameFile_xTotal = Alum_WeightMeter* Alum_UnitPrice* 2* xLength/ 1000;
			double AlumFrameFile_yTotal = Alum_WeightMeter* Alum_UnitPrice* 2* yLength/ 1000;
			
			sSql.Format( "%s('ɴ����','���Ͳ�',%d,%d,%d,%0.3f,%d,'֧',%0.2f,%0.2f,'��0.03���')" ,
				TableHand,
				xLength,0,0,Alum_WeightMeter,2,Alum_UnitPrice,AlumFrameFile_xTotal*1.03);
			database.ExecuteSQL(sSql);
			
			
			sSql.Format( "%s('ɴ����','���Ͳ�',%d,%d,%d,%0.3f,%d,'֧',%0.2f,%0.2f,'��0.03���')" ,
				TableHand,
				yLength,0,0,Alum_WeightMeter,2,Alum_UnitPrice,AlumFrameFile_yTotal*1.03);
				database.ExecuteSQL(sSql);

				
				// // //			// ����ֽ�Ƭ��ֵ// 			
				double SteelAngle_UnitPrice = oper.NameToUnitPrice(pSeriesTable,"ɴ���ȸֽ�Ƭ"); //����ֽ�Ƭ
				int SteelAngle_Quantity = (int )oper.NameToValue(pSeriesTable,"ɴ���ȸֽ�Ƭ"); //����ֽ�Ƭ	
				double SteelAngle_Total = SteelAngle_UnitPrice * 4 * SteelAngle_Quantity;				
				
				sSql.Format( "%s('ɴ����','�ֽ�Ƭ',%d,%d,%d,%0.3f,%d,'��',%0.2f,%0.2f,'')" ,
					TableHand,0,0,0,0.0,4* SteelAngle_Quantity,SteelAngle_UnitPrice,SteelAngle_Total);
				database.ExecuteSQL(sSql);
// // 

				//////////////////////////////////////////////////////////
				
				// // //				// ���������ֵ				
				double AlumAngle_UnitPrice = oper.NameToUnitPrice(pSeriesTable,"ɴ���Ƚ���");				
				double AlumAngle_Total = AlumAngle_UnitPrice * 4;				
				// 				
				sSql.Format( "%s('ɴ����','����',%d,%d,%d,%0.3f,%d,'��',%0.2f,%0.2f,'')" ,
					TableHand,0,0,0,0.0,4,AlumAngle_UnitPrice,AlumAngle_Total);
				database.ExecuteSQL(sSql);
				
				// 				
				// // // 				// �������ע����ֵ				
				int AlumAngle_Glue_len = oper.NameToValue(pSeriesTable,"ɴ���Ƚ���ע������");	
				double Glue_UnitPrice = oper.NameToUnitPrice(pPublicTable,"����ע��");				//����ע��
				double AlumAngle_Glue_Total =  Glue_UnitPrice * 4 * AlumAngle_Glue_len ;				
				// 				
				sSql.Format( "%s('ɴ����','����ע��',%d,%d,%d,%0.3f,%d,'��',%0.3f,%0.2f,'')" ,
					TableHand,AlumAngle_Glue_len,0,0,0.0,4,Glue_UnitPrice,AlumAngle_Glue_Total);
				database.ExecuteSQL(sSql);
				
				
				// // // 				// ������潺��ֵ
				double SectionGlue_UnitPrice =  oper.NameToUnitPrice(pPublicTable,"���潺");				
				double SectionGlue_Total = SectionGlue_UnitPrice * 4  ;				
				// 				
				sSql.Format( "%s('ɴ����','���潺',%d,%d,%d,%0.3f,%d,'��',%0.2f,%0.2f,'')" ,
					TableHand,0,0,0,0.0,4,SectionGlue_UnitPrice,SectionGlue_Total);
				database.ExecuteSQL(sSql);
				
				 
				//ɴ����ɴ��
				
							
				double Glass_UnitPrice = oper.NameToUnitPrice(pPublicTable,"�������") ; //�۸�	
				
				double FixFileHight = oper.NameToValue(pSeriesTable,"ɴ�ȴ���");
				double GlassInFix = oper.NameToValue(pSeriesTable,"ɴ������");
				
				double GlassWidth =  xLength- FixFileHight * 2 + GlassInFix * 2 ;
				double  GlassHight = yLength- FixFileHight * 2 + GlassInFix * 2 ;
				
				double Glass_Total_Price = Glass_UnitPrice * GlassWidth /1000 * GlassHight /1000 ;
				
				
				sSql.Format( "%s('ɴ����','�������',%d,%d,%d,%0.3f,%d,'��',%0.2f,%0.2f,'')" ,
					TableHand,0,(int )GlassWidth,(int )GlassHight,0.0,1,Glass_UnitPrice,Glass_Total_Price);
				database.ExecuteSQL(sSql);
				
				
		
				
				// //			// ����EPDM������ֵ				
				//double InsulationBar_WeightMeter = 0.055+0.055;
				double EPDM_UnitPrice_2 = oper.NameToUnitPrice(pSeriesTable,"ɴ���ܷ�EPDM����") ; //�۸�	
				double EPDM_Length_2 = (xLength+yLength)*2 ;
				double EPDM_Total_2 = EPDM_UnitPrice_2 *EPDM_Length_2/1000;				
				// 				
				sSql.Format( "%s('ɴ����','ɴ���ܷ�EPDM����',%d,%d,%d,%0.3f,%d,'��',%0.2f,%0.2f,'')" ,
					TableHand,(int )EPDM_Length_2,0,0,0.0,1,EPDM_UnitPrice_2,EPDM_Total_2);
				database.ExecuteSQL(sSql);
				// 				

				
			

				///////////////////////////////////////////////////////////
				
				// 				// // 				// ���봫��������ֵ
				double AlumBar_Weight =  oper.NameToWeightMeter(pPublicTable,"��������");
				double AlumBar_UnitPrice =  oper.NameToUnitPrice(pPublicTable,"��������");

				double AlumBar_Total = (yLength -300.0)  *  AlumBar_Weight * AlumBar_UnitPrice /1000;
				// 				
				sSql.Format( "%s('ɴ����','��������',%d,%d,%d,%0.3f,%d,'֧',%0.2f,%0.2f,'')" ,
					TableHand,(int )(yLength -300.0),0,0,AlumBar_Weight,1,AlumBar_UnitPrice,AlumBar_Total);
				database.ExecuteSQL(sSql);
				
				///////////////////////////////////////////////////////////

				// 				// // 				// ���������ֵ
				double HandWave_UnitPrice =  oper.NameToUnitPrice(pSeriesTable,"ɴ�������");
				// 				
				sSql.Format( "%s('ɴ����','���',%d,%d,%d,%0.3f,%d,'��',%0.2f,%0.2f,'')" ,
					TableHand,0,0,0,0.0,1,0.0,HandWave_UnitPrice);
				database.ExecuteSQL(sSql);
				
				///////////////////////////////////////////////////////////


		}
	}
				

/**********************************************************************/


}

//DEL BOOL COutToExcel::Open(CString sz)
//DEL {
//DEL 
//DEL 	return FALSE ;
//DEL }

//DEL BOOL COutToExcel::Open(CString sz)
//DEL {
//DEL 	CFileDialog dlg(TRUE,"xls file(*.xls)|*.xls", NULL,
//DEL 		
//DEL 		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
//DEL 		
//DEL 		"xls file(*.xls)|*.xls||");    //TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի���
//DEL 	
//DEL 	if(dlg.DoModal()==IDOK)
//DEL 	{
//DEL 		FilePathName=dlg.GetPathName();
//DEL 
//DEL 		if(FilePathName.GetLength() != 0)
//DEL 		{
//DEL //			TableName = sz;
//DEL //			ReadExcel();
//DEL 		}
//DEL 
//DEL 		return TRUE ;
//DEL 	}
//DEL 	else 
//DEL 	
//DEL 		return FALSE;
//DEL }

void COutToExcel::ReadExcel()
{
    //����EXCEL
   
    CString sItem1, sItem2;
    CString sDriver;
    CString sDsn;

	CString sFile = FilePathName.Replace("\\","\\\\") ;// ������ȡ��Excel�ļ���
    
 	
    // �����Ƿ�װ��Excel���� "Microsoft Excel Driver (*.xls)"
    sDriver = GetExcelDriver();
    if (sDriver.IsEmpty())
    {
        // û�з���Excel����
        AfxMessageBox(_T( "û�а�װExcel����!" ));
        return ;
    }
    
    // �������д�ȡ���ַ���
    sDsn.Format(_T( "ODBC;DRIVER={%s};DSN='';DBQ=%s" ), sDriver, sFile);
    
    TRY
    {	
		//AfxMessageBox("000");
        // �����ݿ�(��Excel�ļ�)
        database.Open(NULL, false , false , sDsn);
        
        CRecordset recset(&database);
        
        // ���ö�ȡ�Ĳ�ѯ���.
        sSql .Format( "SELECT Name, Age FROM %s ORDER BY Name " , "demo");
        
	

        // ִ�в�ѯ���
        recset.Open(CRecordset::forwardOnly, sSql, CRecordset::readOnly);
        // ��ȡ��ѯ���
        while (!recset.IsEOF())
        {
            //��ȡExcel�ڲ���ֵ
            recset.GetFieldValue(_T( "Name" ), sItem1);
            recset.GetFieldValue(_T( "Age" ), sItem2);
            AfxMessageBox(sItem1+"--"+sItem2);
            // �Ƶ���һ��
            recset.MoveNext();
        }
        
        // �ر����ݿ�
        database.Close();
        
    }
    CATCH(CDBException, e)
    {
        // ���ݿ���������쳣ʱ...
        AfxMessageBox(_T( "���ݿ����: " ) + e->m_strError);
    }
    END_CATCH;
}

void COutToExcel::TestWrite()
{
	//д��EXCEL

	//CString str  = _T(GetFileNameXls("Save"));
	//CString sExcelFile = str ; // Ҫ������Excel�ļ�
	
	

    CString sDriver = _T( "MICROSOFT EXCEL DRIVER (*.XLS)" ); // Excel��װ����
	CString sExcelFile = _T( "./data/SeriesData.xls" ); // ������ȡ��Excel�ļ���



   
    TRY
	{
		// �������д�ȡ���ַ���
		sSql.Format("DRIVER={%s};DSN='''';FIRSTROWHASNAMES=1;READONLY=FALSE;CREATE_DB=\"%s\";DBQ=%s",
			sDriver, sExcelFile, sExcelFile);
		// �������ݿ� (��Excel����ļ�)
		if ( database.OpenEx(sSql,CDatabase::noOdbcDialog) )
		{
			
			//�����쳣
 			try
 			{
				//ɾ����
				database.ExecuteSQL(_T( "DROP  TABLE Test" ));
				
 			}
 			catch (CDBException *pe)
 			{
 				// The error code is in pe->m_nRetCode
 				pe->ReportError();
 				pe->Delete();
 			}
				
			//������
			database.ExecuteSQL(_T( "CREATE TABLE Test (Name TEXT, Val NUMBER, WeightMeter NUMBER, UnitPrice NUMBER)" ));
            
            // ������ֵ
            database.ExecuteSQL(_T( "INSERT INTO Test (Name,Val,WeightMeter,UnitPrice) VALUES ('���Ͳ���Ϳ',0.0,0.0,29.5)" ));

	
        }
        // �ر����ݿ�
        database.Close();
    }
    CATCH_ALL(e)
    {
        TRACE1( "Excel����û�а�װ: %s" ,sDriver);
    }
	END_CATCH_ALL;
	

}

void COutToExcel::TestRead(CSeriesList* tempList , CString TempTableName)
{

	//��ȡ����·��
 
	CString csFullPath =GetModuleDir();
	
	csFullPath.TrimRight("\\Debug");
	
	//����EXCEL
 
    CString sItem1,	 sItem2,sItem3, sItem4;
    CString sDriver;
    CString sDsn;
  
	CString sFile = csFullPath +   "\\data\\SeriesData.xls"  ; // ������ȡ��Excel�ļ���/data



	//return ;
    
    // �����Ƿ�װ��Excel���� "Microsoft Excel Driver (*.xls)"
    sDriver = GetExcelDriver();
    if (sDriver.IsEmpty())
    {
        // û�з���Excel����
        AfxMessageBox(_T( "û�а�װExcel����!" ));
        return ;
    }
    
    // �������д�ȡ���ַ���
    sDsn.Format(_T( "ODBC;DRIVER={%s};DSN='';DBQ=%s" ), sDriver, sFile);
    
    TRY
    {
        // �����ݿ�(��Excel�ļ�)
        database.Open(NULL, false , false , sDsn);
        
        CRecordset recset(&database);     
		
        // ���ö�ȡ�Ĳ�ѯ���.	��ָ���ı���ѡ����ָ������
        sSql .Format( _T("SELECT Name,Val,WeightMeter,UnitPrice FROM [%s$] ORDER BY Name" ), TempTableName);	//, "[�������$]" TempTableName"�������" "Public_UnitPrice"
        
        // ִ�в�ѯ���
        recset.Open(CRecordset::forwardOnly, sSql, CRecordset::readOnly);


        // ��ȡ��ѯ���
        while (!recset.IsEOF())
        {
            //��ȡExcel�ڲ���ֵ
			//(Name,Val,WeightMeter,UnitPrice)
            recset.GetFieldValue(_T( "Name" )		, sItem1);	
			recset.GetFieldValue(_T( "Val" )		, sItem2);		
			recset.GetFieldValue(_T( "WeightMeter" ), sItem3);
			recset.GetFieldValue(_T( "UnitPrice" )	, sItem4);
			 
			if(sItem1 != "")
			{
				 //AfxMessageBox(sItem1 + "--" + sItem2+ "--" + sItem3+ "--" + sItem4);

				double dVal =			atof	(sItem2 );
				double dWeightMeter =	atof	(sItem3 );
				double dUnitPrice =		atof	(sItem4 );

				if(tempList )
				{
					CSeries * NewData = new CSeries (sItem1,dVal,dWeightMeter,dUnitPrice);
					tempList->AddTail(NewData);
				}
	

			}
            // �Ƶ���һ��
            recset.MoveNext();	

        }

		recset.Close();

		/////////////////////////////////////////////////////////////////////////////////
	


		/////////////////////////////////////////////////////////////////////////////////


		
        
        // �ر����ݿ�
        database.Close();
        
    }
    CATCH(CDBException, e)
    {
        // ���ݿ���������쳣ʱ...
        AfxMessageBox(_T( "���ݿ����: " ) + e->m_strError);
    }
    END_CATCH;

}


//DEL void COutToExcel::TestRead2(CSeriesList* tempList , CString TempTableName)
//DEL {
//DEL 
//DEL 	//��ȡ����·��
//DEL 	
//DEL 	CString csFullPath =GetModuleDir();
//DEL 
//DEL 	csFullPath.TrimRight("\\Debug");
//DEL 	
//DEL 	//����EXCEL
//DEL 	
//DEL     CString sItem1,	 sItem2,sItem3, sItem4;
//DEL     CString sDriver;
//DEL     CString sDsn;
//DEL     CString sFile = csFullPath + "\\data\\SeriesData.xls"  ; // ������ȡ��Excel�ļ���/data
//DEL 	
//DEL 	
//DEL 	//AfxMessageBox(sFile);
//DEL 	
//DEL 	
//DEL 	//return ;
//DEL     
//DEL     // �����Ƿ�װ��Excel���� "Microsoft Excel Driver (*.xls)"
//DEL     sDriver = GetExcelDriver();
//DEL     if (sDriver.IsEmpty())
//DEL     {
//DEL         // û�з���Excel����
//DEL         AfxMessageBox(_T( "û�а�װExcel����!" ));
//DEL         return ;
//DEL     }
//DEL     
//DEL     // �������д�ȡ���ַ���
//DEL     sDsn.Format(_T( "ODBC;DRIVER={%s};DSN='';DBQ=%s" ), sDriver, sFile);
//DEL     
//DEL     TRY
//DEL     {
//DEL         // �����ݿ�(��Excel�ļ�)
//DEL         database.Open(NULL, false , false , sDsn);
//DEL         
//DEL         CRecordset recset(&database);     
//DEL 		
//DEL         // ���ö�ȡ�Ĳ�ѯ���.	��ָ���ı���ѡ����ָ������
//DEL         sSql .Format( _T("SELECT Name,Val,WeightMeter,UnitPrice FROM [%s$] ORDER BY Name" ), TempTableName);	//, "[�������$]" TempTableName"�������" "Public_UnitPrice"
//DEL         
//DEL         // ִ�в�ѯ���
//DEL         recset.Open(CRecordset::forwardOnly, sSql, CRecordset::readOnly);
//DEL 		
//DEL 		
//DEL         // ��ȡ��ѯ���
//DEL         while (!recset.IsEOF())
//DEL         {
//DEL             //��ȡExcel�ڲ���ֵ
//DEL 			//(Name,Val,WeightMeter,UnitPrice)
//DEL             recset.GetFieldValue(_T( "Name" )		, sItem1);	
//DEL 			recset.GetFieldValue(_T( "Val" )		, sItem2);		
//DEL 			recset.GetFieldValue(_T( "WeightMeter" ), sItem3);
//DEL 			recset.GetFieldValue(_T( "UnitPrice" )	, sItem4);
//DEL 			
//DEL 			if(sItem1 != "")
//DEL 			{
//DEL 				//AfxMessageBox(sItem1 + "--" + sItem2+ "--" + sItem3+ "--" + sItem4);
//DEL 				
//DEL 				double dVal =			atof	(sItem2 );
//DEL 				double dWeightMeter =	atof	(sItem3 );
//DEL 				double dUnitPrice =		atof	(sItem4 );
//DEL 				
//DEL 				if(tempList )
//DEL 				{
//DEL 					CSeries * NewData = new CSeries (sItem1,dVal,dWeightMeter,dUnitPrice);
//DEL 					tempList->AddTail(NewData);
//DEL 				}
//DEL 				
//DEL 				
//DEL 			}
//DEL             // �Ƶ���һ��
//DEL             recset.MoveNext();	
//DEL 			
//DEL         }
//DEL 		
//DEL 		recset.Close();
//DEL 		
//DEL 		/////////////////////////////////////////////////////////////////////////////////
//DEL 		
//DEL 		
//DEL 		
//DEL 		/////////////////////////////////////////////////////////////////////////////////
//DEL 		
//DEL 		
//DEL 		
//DEL         
//DEL         // �ر����ݿ�
//DEL         database.Close();
//DEL         
//DEL     }
//DEL     CATCH(CDBException, e)
//DEL     {
//DEL         // ���ݿ���������쳣ʱ...
//DEL         AfxMessageBox(_T( "���ݿ����: " ) + e->m_strError);
//DEL     }
//DEL     END_CATCH;
//DEL 	
//DEL }


CString COutToExcel::GetFileNameXls(CString OpenSave)
{

	CString FilePathName ;

	BOOL bIsOpen;

	if(OpenSave == "open" || OpenSave == "Open") bIsOpen = TRUE;

	if(OpenSave == "save" || OpenSave == "Save") bIsOpen = FALSE;


		CFileDialog dlg(bIsOpen,"xls file(*.xls)|*.xls", NULL,
			
			OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
			
		"xls file(*.xls)|*.xls||");    //TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի���

	
	if(dlg.DoModal()==IDOK)		FilePathName=dlg.GetPathName();
		
	return FilePathName;

}

//DEL double COutToExcel::CStringToDouble(CString str  )
//DEL {
//DEL 		double temp ;
//DEL 		char *ch;
//DEL 		
//DEL 		int strLength = str.GetLength();
//DEL 	
//DEL     int commaIndex = str.Find('.');
//DEL 	
//DEL     ch = (char *)str.GetBuffer( strLength+ 1);
//DEL 	
//DEL 
//DEL 	
//DEL 	char chTemp[100];
//DEL 	
//DEL    
//DEL 	
//DEL     for(int i = 0; i < 100; i++)
//DEL 	{
//DEL     chTemp[i] = '0';
//DEL 	}
//DEL 
//DEL 	
//DEL     for(int j = 0; j < strLength; j++)
//DEL 	{
//DEL     chTemp[j] = *ch;
//DEL     ch += 2;
//DEL 	}
//DEL 
//DEL 	if (commaIndex < 0)
//DEL 		chTemp[strLength]= '.';
//DEL 
//DEL 	temp = (float) atof((char *)chTemp);
//DEL 	str.ReleaseBuffer();
//DEL 
//DEL 	return temp ;
//DEL }

BOOL COutToExcel::GetAllTableName(CStringList & szArray)
{

	szArray.RemoveAll();

	//��ȡ����·��

		CString csFullPath =GetModuleDir();
	csFullPath.TrimRight("\\Debug");

		//����EXCEL
 
    CString sItem1,	 sItem2,sItem3, sItem4;
    CString sDriver;
    CString sDsn;
    CString sFile = csFullPath +   "\\data\\SeriesData.xls"  ; // ������ȡ��Excel�ļ���/data
    
    // �����Ƿ�װ��Excel���� "Microsoft Excel Driver (*.xls)"
    sDriver = GetExcelDriver();
    if (sDriver.IsEmpty())
    {
        // û�з���Excel����
        AfxMessageBox(_T( "û�а�װExcel����!" ));
        return FALSE;
    }
    
    // �������д�ȡ���ַ���
    sDsn.Format(_T( "ODBC;DRIVER={%s};DSN='';DBQ=%s" ), sDriver, sFile);
    
    TRY
    {
        // �����ݿ�(��Excel�ļ�)
        database.Open(NULL, false , false , sDsn);


		/////////////////////////////////////////////////////////////////////////////////

		CRecordset rt(&database);     
		
        // ���ö�ȡ�Ĳ�ѯ���.
        sSql .Format( _T("SELECT Name FROM %s ORDER BY Name" ),"[Tables$]" );	//�ֶ�����Ҫ�ִ�Сд
        
        // ִ�в�ѯ���
        rt.Open(CRecordset::forwardOnly, sSql, CRecordset::readOnly);
		
		
        // ��ȡ��ѯ���
        while (!rt.IsEOF())
        {
            //��ȡExcel�ڲ���ֵ			
            rt.GetFieldValue(_T( "Name" )	, sItem1);					
			//AfxMessageBox(sItem1 );	
			
			szArray.AddTail(sItem1);
		
            // �Ƶ���һ��
            rt.MoveNext();	
			
        }		
		rt.Close();
	


		/////////////////////////////////////////////////////////////////////////////////


		
        
        // �ر����ݿ�
        database.Close();
        
    }
    CATCH(CDBException, e)
    {
        // ���ݿ���������쳣ʱ...
        AfxMessageBox(_T( "���ݿ����: " ) + e->m_strError);
    }
    END_CATCH;




	return TRUE ;
}


//DEL BOOL COutToExcel::GetAllTableName2(CStringList & szArray)
//DEL {
//DEL 	
//DEL 	szArray.RemoveAll();
//DEL 
//DEL 
//DEL 	//��ȡ����·��
//DEL 	
//DEL 	CString csFullPath =GetModuleDir(); 
//DEL csFullPath.TrimRight("\\Debug");	
//DEL 	//����EXCEL
//DEL 	
//DEL     CString sItem1,	 sItem2,sItem3, sItem4;
//DEL     CString sDriver;
//DEL     CString sDsn;
//DEL     CString sFile = csFullPath +   "\\data\\SeriesData.xls"  ; // ������ȡ��Excel�ļ���/data
//DEL     
//DEL     // �����Ƿ�װ��Excel���� "Microsoft Excel Driver (*.xls)"
//DEL     sDriver = GetExcelDriver();
//DEL     if (sDriver.IsEmpty())
//DEL     {
//DEL         // û�з���Excel����
//DEL         AfxMessageBox(_T( "û�а�װExcel����!" ));
//DEL         return FALSE;
//DEL     }
//DEL     
//DEL     // �������д�ȡ���ַ���
//DEL     sDsn.Format(_T( "ODBC;DRIVER={%s};DSN='';DBQ=%s" ), sDriver, sFile);
//DEL     
//DEL     TRY
//DEL     {
//DEL         // �����ݿ�(��Excel�ļ�)
//DEL         database.Open(NULL, false , false , sDsn);
//DEL 		
//DEL 		
//DEL 		/////////////////////////////////////////////////////////////////////////////////
//DEL 		
//DEL 		CRecordset rt(&database);     
//DEL 		
//DEL         // ���ö�ȡ�Ĳ�ѯ���.
//DEL         sSql .Format( _T("SELECT Name FROM %s ORDER BY Name" ),"[Tables$]" );	//�ֶ�����Ҫ�ִ�Сд
//DEL         
//DEL         // ִ�в�ѯ���
//DEL         rt.Open(CRecordset::forwardOnly, sSql, CRecordset::readOnly);
//DEL 		
//DEL 		
//DEL         // ��ȡ��ѯ���
//DEL         while (!rt.IsEOF())
//DEL         {
//DEL             //��ȡExcel�ڲ���ֵ			
//DEL             rt.GetFieldValue(_T( "Name" )	, sItem1);				
//DEL 			szArray.AddTail(sItem1);
//DEL 			
//DEL             // �Ƶ���һ��
//DEL             rt.MoveNext();	
//DEL 			
//DEL         }		
//DEL 		rt.Close();
//DEL 		
//DEL 		/////////////////////////////////////////////////////////////////////////////////
//DEL 	
//DEL         
//DEL         // �ر����ݿ�
//DEL         database.Close();
//DEL         
//DEL     }
//DEL     CATCH(CDBException, e)
//DEL     {
//DEL         // ���ݿ���������쳣ʱ...
//DEL         AfxMessageBox(_T( "���ݿ����: " ) + e->m_strError);
//DEL     }
//DEL     END_CATCH;
//DEL 	
//DEL 	
//DEL 	
//DEL 	
//DEL 	return TRUE ;
//DEL }