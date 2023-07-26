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
    
    // 获取已安装驱动的名称(涵数在odbcinst.h里)
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

void COutToExcel::WriteFrameData()
{			
				
		


	 	CoperationList oper;

	

 				double Alum_WeightMeter = oper.NameToWeightMeter(pSeriesTable,"窗框米重");
 				double InsulationBar_WeightMeter = oper.NameToWeightMeter(pSeriesTable,"窗框隔热条"); //隔热条米重
// 
// 
 				int xLength = oper.GetFrameRect(pBoxTable).Width();
 				int yLength = oper.GetFrameRect(pBoxTable).Height();
// 				
// 				
				double ComplexAlum_WeightMeter = Alum_WeightMeter + InsulationBar_WeightMeter;
				double Alum_UnitPrice = oper.NameToUnitPrice(pPublicTable,"喷涂铝型材");


				//int i = oper.GetCount( pPublicTable);


				//CString str ; 
				//str.Format("%0.1f", Alum_UnitPrice );
				//AfxMessageBox (str);
				
									
				double AlumFrameFile_xTotal = ComplexAlum_WeightMeter* Alum_UnitPrice* 2* xLength/ 1000;
				double AlumFrameFile_yTotal = ComplexAlum_WeightMeter* Alum_UnitPrice* 2* yLength/ 1000;

				sSql.Format( "%s('窗框','铝型材',%d,%d,%d,%0.3f,%d,'支',%0.2f,%0.2f,'含0.03损耗')" ,
					TableHand,
					xLength,0,0,ComplexAlum_WeightMeter,2,Alum_UnitPrice,AlumFrameFile_xTotal*1.03);
				database.ExecuteSQL(sSql);


				sSql.Format( "%s('窗框','铝型材',%d,%d,%d,%0.3f,%d,'支',%0.2f,%0.2f,'含0.03损耗')" ,
					TableHand,
					yLength,0,0,ComplexAlum_WeightMeter,2,Alum_UnitPrice,AlumFrameFile_yTotal*1.03);
				database.ExecuteSQL(sSql);


// 
// 				
			// 插入隔热条数值				
 				//double InsulationBar_WeightMeter = 0.055+0.055;
				double InsulationBar_UnitPrice =  oper.NameToUnitPrice(pSeriesTable,"窗框隔热条"); //隔热条米重	
 				int InsulationBar_Length = (xLength+yLength)*2 ;
 				double InsulationBar_Total = 1.1* InsulationBar_UnitPrice*InsulationBar_Length/1000;				
 				

// 
// 				//  插入复合隔热条加工费数值				
// 				
 				double InsulationBar_Process_UnitPrice = oper.NameToUnitPrice(pPublicTable,"穿条加工费");	
// 				
 				double InsulationBar_Process_Total = ComplexAlum_WeightMeter *InsulationBar_Length/1000 * InsulationBar_Process_UnitPrice  ;				
// 				

// 
// 				
// 
 				//插入复合隔热条差额数值			
// 				//全铝合金+隔热条+加工费-复合后价格
 				double InsulationBar_Difference = Alum_WeightMeter * Alum_UnitPrice * InsulationBar_Length/1000  +
 					InsulationBar_Total + InsulationBar_Process_Total-  AlumFrameFile_xTotal - AlumFrameFile_yTotal ;			
// 				
 				sSql.Format( "%s('窗框','隔热条差额',%d,%d,%d,%0.3f,%d,'项',%0.2f,%0.2f,'含0.1损耗')" ,
 					TableHand,InsulationBar_Length,0,0,InsulationBar_WeightMeter,1,InsulationBar_UnitPrice,InsulationBar_Difference);
 				database.ExecuteSQL(sSql);
// 				
// 
// 				
// // //			// 插入钢角片数值// 			
 				double SteelAngle_UnitPrice = oper.NameToUnitPrice(pSeriesTable,"窗框钢角片"); //窗框钢角片		
 				double SteelAngle_Total = SteelAngle_UnitPrice * 4 ;				
 				
 				sSql.Format( "%s('窗框','钢角片',%d,%d,%d,%0.3f,%d,'组',%0.2f,%0.2f,'')" ,
					TableHand,0,0,0,0.0,4,SteelAngle_UnitPrice,SteelAngle_Total);
 				database.ExecuteSQL(sSql);
// // 
// // 
// // 
// // 
// // //				// 插入角码数值				
 				double AlumAngle_UnitPrice = oper.NameToUnitPrice(pSeriesTable,"窗框角码");				
 				double AlumAngle_Total = AlumAngle_UnitPrice * 4;				
// 				
 				sSql.Format( "%s('窗框','角码',%d,%d,%d,%0.3f,%d,'组',%0.2f,%0.2f,'')" ,
					TableHand,0,0,0,0.0,4,AlumAngle_UnitPrice,AlumAngle_Total);
 				database.ExecuteSQL(sSql);
 
// 				
// // // 				// 插入内角码注胶数值				
 				int AlumAngle_Glue_len = oper.NameToValue(pSeriesTable,"窗框角码注胶长度");	
 				double Glue_UnitPrice = oper.NameToUnitPrice(pPublicTable,"角码注胶");				//角码注胶
 				double AlumAngle_Glue_Total =  Glue_UnitPrice * 4 * AlumAngle_Glue_len ;				
// 				
 				sSql.Format( "%s('窗框','角码注胶',%d,%d,%d,%0.3f,%d,'组',%0.3f,%0.2f,'')" ,
					TableHand,AlumAngle_Glue_len,0,0,0.0,4,Glue_UnitPrice,AlumAngle_Glue_Total);
 				database.ExecuteSQL(sSql);
// 
// 				
// // // 				// 插入断面胶数值
 				double SectionGlue_UnitPrice =  oper.NameToUnitPrice(pPublicTable,"断面胶");				
 				double SectionGlue_Total = SectionGlue_UnitPrice *4;				
// 				
 				sSql.Format( "%s('窗框','断面胶',%d,%d,%d,%0.3f,%d,'个',%0.2f,%0.2f,'')" ,
					TableHand,0,0,0,0.0,4,SectionGlue_UnitPrice,SectionGlue_Total);
 				database.ExecuteSQL(sSql);


}

void COutToExcel::WriteCasementData()
{
					
/**********************************************************************/
				//以下是窗扇的计算
	CoperationList oper;
	
	
	int xLength = 0 ;
	
	POSITION pos = pBoxTable->GetHeadPosition();
	for (int i = 0; i < pBoxTable->GetCount(); i++)
	{			
		//取得数据
		POSITION pos1 = pBoxTable->FindIndex(i);					
		CBox* d1 = (CBox* )pBoxTable->GetAt(pos1);			
		int it = d1->GetToType() ;
		CRect rt = d1->GetBox();
		
		//在这里查找所有中梃
		if(6 == it || 7 == it)
		{	
			
			

			double Bar_InFrame_Value = oper.NameToValue(pSeriesTable,"玻扇入框"); //
			// 
			// 
			int xLength = rt.Width() + Bar_InFrame_Value * 2  ;
			int yLength = rt.Height()+ Bar_InFrame_Value * 2  ;
			// 				
			// 				
			
			double Alum_WeightMeter = oper.NameToWeightMeter(pSeriesTable,"玻扇米重");
			double InsulationBar_WeightMeter = oper.NameToWeightMeter(pSeriesTable,"玻扇隔热条"); //隔热条米重
			// 

			// 				
			// 				
			double ComplexAlum_WeightMeter = Alum_WeightMeter + InsulationBar_WeightMeter;
			double Alum_UnitPrice = oper.NameToUnitPrice(pPublicTable,"喷涂铝型材");				
			
			double AlumFrameFile_xTotal = ComplexAlum_WeightMeter* Alum_UnitPrice* 2* xLength/ 1000;
			double AlumFrameFile_yTotal = ComplexAlum_WeightMeter* Alum_UnitPrice* 2* yLength/ 1000;
			
			sSql.Format( "%s('玻璃扇','铝型材',%d,%d,%d,%0.3f,%d,'支',%0.2f,%0.2f,'含0.03损耗')" ,
				TableHand,
				xLength,0,0,ComplexAlum_WeightMeter,2,Alum_UnitPrice,AlumFrameFile_xTotal*1.03);
			database.ExecuteSQL(sSql);
			
			
			sSql.Format( "%s('玻璃扇','铝型材',%d,%d,%d,%0.3f,%d,'支',%0.2f,%0.2f,'含0.03损耗')" ,
				TableHand,
				yLength,0,0,ComplexAlum_WeightMeter,2,Alum_UnitPrice,AlumFrameFile_yTotal*1.03);
				database.ExecuteSQL(sSql);


				// 插入隔热条数值				
				
				double InsulationBar_UnitPrice =  oper.NameToUnitPrice(pSeriesTable,"玻扇隔热条"); //隔热条价格	
				int InsulationBar_Length = (xLength+yLength)*2 ;
				double InsulationBar_Total = 1.1* InsulationBar_UnitPrice*InsulationBar_Length/1000;				
				
				
				// 
				// 				//  插入复合隔热条加工费数值				
				// 				
				double InsulationBar_Process_UnitPrice = oper.NameToUnitPrice(pPublicTable,"穿条加工费");					
				double InsulationBar_Process_Total = ComplexAlum_WeightMeter *InsulationBar_Length/1000 * InsulationBar_Process_UnitPrice  ;				
				// 				
				
				// 
				// 				
				// 
				//插入复合隔热条差额数值			
				// 				//全铝合金+隔热条+加工费-复合后价格
				double InsulationBar_Difference = Alum_WeightMeter * Alum_UnitPrice * InsulationBar_Length/1000  +
					InsulationBar_Total + InsulationBar_Process_Total-  AlumFrameFile_xTotal - AlumFrameFile_yTotal ;			
				// 				
				sSql.Format( "%s('玻璃扇','隔热条差额',%d,%d,%d,%0.3f,%d,'项',%0.2f,%0.2f,'含0.1损耗')" ,
					TableHand,InsulationBar_Length,0,0,InsulationBar_WeightMeter,1,InsulationBar_UnitPrice,InsulationBar_Difference);
				database.ExecuteSQL(sSql);
				// 				
				// 
				// 				
				// // //			// 插入钢角片数值// 			
				double SteelAngle_UnitPrice = oper.NameToUnitPrice(pSeriesTable,"玻璃扇钢角片"); //窗框钢角片
				int SteelAngle_Quantity = (int )oper.NameToValue(pSeriesTable,"玻璃扇钢角片"); //窗框钢角片	
				double SteelAngle_Total = SteelAngle_UnitPrice * 4 * SteelAngle_Quantity;				
				
				sSql.Format( "%s('玻璃扇','钢角片',%d,%d,%d,%0.3f,%d,'组',%0.2f,%0.2f,'')" ,
					TableHand,0,0,0,0.0,4* SteelAngle_Quantity,SteelAngle_UnitPrice,SteelAngle_Total);
				database.ExecuteSQL(sSql);
// // 

				//////////////////////////////////////////////////////////
				
				// // //				// 插入角码数值				
				double AlumAngle_UnitPrice = oper.NameToUnitPrice(pSeriesTable,"玻璃扇角码");				
				double AlumAngle_Total = AlumAngle_UnitPrice * 4;				
				// 				
				sSql.Format( "%s('玻璃扇','角码',%d,%d,%d,%0.3f,%d,'组',%0.2f,%0.2f,'')" ,
					TableHand,0,0,0,0.0,4,AlumAngle_UnitPrice,AlumAngle_Total);
				database.ExecuteSQL(sSql);
				
				// 				
				// // // 				// 插入角码注胶数值				
				int AlumAngle_Glue_len = oper.NameToValue(pSeriesTable,"玻璃扇角码注胶长度");	
				double Glue_UnitPrice = oper.NameToUnitPrice(pPublicTable,"角码注胶");				//角码注胶
				double AlumAngle_Glue_Total =  Glue_UnitPrice * 4 * AlumAngle_Glue_len ;				
				// 				
				sSql.Format( "%s('玻璃扇','角码注胶',%d,%d,%d,%0.3f,%d,'组',%0.3f,%0.2f,'')" ,
					TableHand,AlumAngle_Glue_len,0,0,0.0,4,Glue_UnitPrice,AlumAngle_Glue_Total);
				database.ExecuteSQL(sSql);
				
				
				// // // 				// 插入断面胶数值
				double SectionGlue_UnitPrice =  oper.NameToUnitPrice(pPublicTable,"断面胶");				
				double SectionGlue_Total = SectionGlue_UnitPrice * 4  ;				
				// 				
				sSql.Format( "%s('玻璃扇','断面胶',%d,%d,%d,%0.3f,%d,'个',%0.2f,%0.2f,'')" ,
					TableHand,0,0,0,0.0,4,SectionGlue_UnitPrice,SectionGlue_Total);
				database.ExecuteSQL(sSql);
				
				 
				//玻璃扇玻璃
				
				double Glass_Weight = oper.NameToWeightMeter(pPublicTable,"玻璃5+20A+5") ; //重量			
				double Glass_UnitPrice = oper.NameToUnitPrice(pPublicTable,"玻璃5+20A+5") ; //价格	
				
				double FixFileHight = oper.NameToValue(pSeriesTable,"玻扇大面");
				double GlassInFix = oper.NameToValue(pSeriesTable,"扇玻入扇");
				
				double GlassWidth =  xLength- FixFileHight * 2 + GlassInFix * 2 ;
				double  GlassHight = yLength- FixFileHight * 2 + GlassInFix * 2 ;
				
				double Glass_Total_Price = Glass_UnitPrice * GlassWidth /1000 * GlassHight /1000 ;
				
				
				sSql.Format( "%s('玻璃扇','玻璃',%d,%d,%d,%0.3f,%d,'个',%0.2f,%0.2f,'')" ,
					TableHand,0,(int )GlassWidth,(int )GlassHight,0.0,1,Glass_UnitPrice,Glass_Total_Price);
				database.ExecuteSQL(sSql);
				
				
				// //			// 插入EPDM胶条数值				
				//double InsulationBar_WeightMeter = 0.055+0.055;
				double EPDM_UnitPrice = oper.NameToUnitPrice(pSeriesTable,"扇玻璃EPDM胶条") ; //价格	
				double EPDM_Length = (GlassWidth+GlassHight)*2 ;
				double EPDM_Total = EPDM_UnitPrice*EPDM_Length/1000;				
				// 				
				sSql.Format( "%s('玻璃扇','扇玻璃EPDM胶条',%d,%d,%d,%0.3f,%d,'组',%0.2f,%0.2f,'')" ,
					TableHand,(int )EPDM_Length,0,0,0.0,1,EPDM_UnitPrice,EPDM_Total);
				database.ExecuteSQL(sSql);
				// 				
				
				// //			// 插入EPDM胶条数值				
				//double InsulationBar_WeightMeter = 0.055+0.055;
				double EPDM_UnitPrice_2 = oper.NameToUnitPrice(pSeriesTable,"扇密封EPDM胶条") ; //价格	
				double EPDM_Length_2 = (xLength+yLength)*2 ;
				double EPDM_Total_2 = EPDM_UnitPrice_2 *EPDM_Length_2/1000;				
				// 				
				sSql.Format( "%s('玻璃扇','扇密封EPDM胶条',%d,%d,%d,%0.3f,%d,'组',%0.2f,%0.2f,'')" ,
					TableHand,(int )EPDM_Length_2,0,0,0.0,1,EPDM_UnitPrice_2,EPDM_Total_2);
				database.ExecuteSQL(sSql);
				// 				

				
				
				// 				//固定玻璃包装贴膜
				// 							
				double GlassPack_UnitPrice =  oper.NameToUnitPrice(pPublicTable,"玻璃包装") ; //价格				
				double GlassPack_Total = GlassPack_UnitPrice * GlassWidth * GlassHight /1000 /1000 ;
				
				
				sSql.Format( "%s('玻璃扇','玻璃包装贴膜',%d,%d,%d,%0.3f,%d,'个',%0.2f,%0.2f,'')" ,
					TableHand,0,(int )GlassWidth,(int )GlassHight,0.0,1,GlassPack_UnitPrice,GlassPack_Total);
				database.ExecuteSQL(sSql);
				
				// 				// // 				// 插入玻璃垫块数值
				double Block_UnitPrice =  oper.NameToUnitPrice(pSeriesTable,"玻璃扇玻璃垫块");		//固定玻璃垫块
			
				double Block_Total = Block_UnitPrice * 4;				
				// 				
				sSql.Format( "%s('玻璃扇','玻璃垫块',%d,%d,%d,%0.3f,%d,'个',%0.2f,%0.2f,'')" ,
					TableHand,0,0,0,0.0,4,Block_UnitPrice,Block_Total);
				database.ExecuteSQL(sSql);
				
				///////////////////////////////////////////////////////////

				///////////////////////////////////////////////////////////
				
				
				// 				// // 				// 插入传动铝条数值
				double AlumBar_Weight =  oper.NameToWeightMeter(pPublicTable,"传动铝条");
				double AlumBar_UnitPrice =  oper.NameToUnitPrice(pPublicTable,"传动铝条");
				
				double AlumBar_Total = (yLength -300.0)  *  AlumBar_Weight * AlumBar_UnitPrice /1000;
				// 				
				sSql.Format( "%s('玻璃扇','传动铝条',%d,%d,%d,%0.3f,%d,'支',%0.2f,%0.2f,'')" ,
					TableHand,(int )(yLength -300.0),0,0,AlumBar_Weight,1,AlumBar_UnitPrice,AlumBar_Total);
				database.ExecuteSQL(sSql);
				
				///////////////////////////////////////////////////////////

				// 				// // 				// 插入五金数值
				double HandWave_UnitPrice =  oper.NameToUnitPrice(pSeriesTable,"玻璃扇五金");
				// 				
				sSql.Format( "%s('玻璃扇','五金',%d,%d,%d,%0.3f,%d,'套',%0.2f,%0.2f,'')" ,
					TableHand,0,0,0,0.0,1,0.0,HandWave_UnitPrice);
				database.ExecuteSQL(sSql);
				
				///////////////////////////////////////////////////////////


		}
	}
				

/**********************************************************************/
				

}

void COutToExcel::WriteStileData()
{

	//// 插入中梃数值


	//AfxMessageBox("000");
	
	CoperationList oper;


	int xLength = 0 ;
	
	POSITION pos = pBoxTable->GetHeadPosition();
	for (int i = 0; i < pBoxTable->GetCount(); i++)
	{			
		//取得数据
		POSITION pos1 = pBoxTable->FindIndex(i);					
		CBox* d1 = (CBox* )pBoxTable->GetAt(pos1);			
		int it = d1->GetToType() ;
		CRect rt = d1->GetBox();

		//在这里查找所有中梃
		if(2 == it || 12 == it)
		{	
			if( 2 == it)	xLength = rt.Height();
			if(12 == it)	xLength = rt.Width();
	
			
			if(xLength != 0)
			{	
							
				double Alum_WeightMeter = oper.NameToWeightMeter(pSeriesTable,"中梃米重");
				double InsulationBar_WeightMeter = oper.NameToWeightMeter(pSeriesTable,"中梃隔热条"); //隔热条米重
	
				int yLength = (int)oper.NameToValue(pSeriesTable,"中梃入框");

				
				double ComplexAlum_WeightMeter = Alum_WeightMeter + InsulationBar_WeightMeter;
				double Alum_UnitPrice = oper.NameToUnitPrice(pPublicTable,"喷涂铝型材");				
				
				double AlumFrameFile_xTotal = ComplexAlum_WeightMeter* Alum_UnitPrice*  (xLength + yLength *2 )/ 1000;

				sSql.Format( "%s('中梃','铝型材',%d,%d,%d,%0.3f,%d,'支',%0.2f,%0.2f,'含0.03损耗')" ,
					TableHand,
					xLength,0,0,ComplexAlum_WeightMeter,1,Alum_UnitPrice,AlumFrameFile_xTotal*1.03);
				database.ExecuteSQL(sSql);
				////////////////////////////////////////////////////////

				// 				
				// 插入中梃隔热条数值				
				//double InsulationBar_WeightMeter = 0.055+0.055;
				double InsulationBar_UnitPrice =  oper.NameToUnitPrice(pSeriesTable,"中梃隔热条"); //隔热条米重	
				int InsulationBar_Length = xLength+yLength*2 ;
				double InsulationBar_Total = 1.1* InsulationBar_UnitPrice*InsulationBar_Length/1000;				
				
			
				// 				//  插入复合隔热条加工费数值				
							
				double InsulationBar_Process_UnitPrice = oper.NameToUnitPrice(pPublicTable,"穿条加工费");	
								
				double InsulationBar_Process_Total = ComplexAlum_WeightMeter *InsulationBar_Length/1000 * InsulationBar_Process_UnitPrice  ;				
						
			
				//插入复合隔热条差额数值			
				// 				//全铝合金+隔热条+加工费-复合后价格
				double InsulationBar_Difference = Alum_WeightMeter * Alum_UnitPrice * InsulationBar_Length/1000  +
					InsulationBar_Total + InsulationBar_Process_Total-  AlumFrameFile_xTotal  ;			
				// 				
				sSql.Format( "%s('中梃','隔热条差额',%d,%d,%d,%0.3f,%d,'项',%0.2f,%0.2f,'含0.1损耗')" ,
					TableHand,InsulationBar_Length,0,0,InsulationBar_WeightMeter,1,InsulationBar_UnitPrice,InsulationBar_Difference);
 				database.ExecuteSQL(sSql);

				///////////////////////////////////////////

				// // //				// 插入角码数值				
				double AlumAngle_UnitPrice = oper.NameToUnitPrice(pSeriesTable,"中梃角码");				
				double AlumAngle_Total = AlumAngle_UnitPrice * 2;				
				// 				
				sSql.Format( "%s('中梃','角码',%d,%d,%d,%0.3f,%d,'组',%0.2f,%0.2f,'')" ,
					TableHand,0,0,0,0.0,2,AlumAngle_UnitPrice,AlumAngle_Total);
 				database.ExecuteSQL(sSql);
				// // // 				// 插入中梃角码注胶数值				
				int AlumAngle_Glue_len = oper.NameToValue(pSeriesTable,"中梃角码注胶长度");	
				double Glue_UnitPrice = oper.NameToUnitPrice(pPublicTable,"角码注胶");				//角码注胶
				double AlumAngle_Glue_Total =  Glue_UnitPrice * 2 * AlumAngle_Glue_len ;				
				// 				
				sSql.Format( "%s('中梃','角码注胶',%d,%d,%d,%0.3f,%d,'组',%0.3f,%0.2f,'')" ,
					TableHand,AlumAngle_Glue_len,0,0,0.0,2,Glue_UnitPrice,AlumAngle_Glue_Total);
 				database.ExecuteSQL(sSql);
				//////////////////////////////////////////////////////////////////////////////


				// // // 				// 插入中梃防水胶垫				
					
				double XPE_UnitPrice = oper.NameToUnitPrice(pSeriesTable,"中梃防水胶垫");				//角码注胶
				double AlumAngle_XPE_Total =  XPE_UnitPrice * 2  ;				
				// 				
				sSql.Format( "%s('中梃','防水胶垫',%d,%d,%d,%0.3f,%d,'个',%0.3f,%0.2f,'')" ,
					TableHand,0,0,0,0.0,2,XPE_UnitPrice,AlumAngle_XPE_Total);
				database.ExecuteSQL(sSql);
				//////////////////////////////////////////////////////////////////////////////


		
			}


		}

	}
	
							
				//// 插入中梃隔热条数值				
// 				//double InsulationBar_WeightMeter = 0.055+0.055;
// 				double InsulationBar_UnitPrice = 2.65+2.65 ;	
// 				int InsulationBar_Length = xLength ;
// 				double InsulationBar_Total = 1.1* InsulationBar_UnitPrice*InsulationBar_Length/1000;				
// 				
// 				sSql.Format( "%s('中梃隔热条',%d,%d,%0.3f,%d,'项',%0.2f,%0.2f,'含0.1损耗')" ,
// 					TableHand,InsulationBar_Length,0,InsulationBar_WeightMeter,1,InsulationBar_UnitPrice,InsulationBar_Total);
// 				database.ExecuteSQL(sSql);
// 				
// 				//  插入复合隔热条加工费数值				
// 				
// 				double InsulationBar_Process_UnitPrice = 1.06;	
// 				
// 				double InsulationBar_Process_Total = ComplexAlum_WeightMeter *InsulationBar_Length/1000 * InsulationBar_Process_UnitPrice  ;				
// 				
// 				sSql.Format( "%s('中梃隔热条复合加工费',%d,%d,%0.3f,%d,'项',%0.2f,%0.2f,'')" ,
// 					TableHand,InsulationBar_Length,0,0.0,1,InsulationBar_Process_UnitPrice,InsulationBar_Process_Total);
// 				database.ExecuteSQL(sSql);
// 				
// 				
// 				
// 				//插入复合隔热条差额数值			
// 				//全铝合金+隔热条+加工费-复合后价格
// 				double InsulationBar_Difference = Alum_WeightMeter * Alum_UnitPrice * InsulationBar_Length/1000  +
// 					InsulationBar_Total + InsulationBar_Process_Total-  AlumStileFile_Total ;			
// 				
// 				sSql.Format( "%s('隔热条差额',%d,%d,%0.3f,%d,'项',%0.2f,%0.2f,'')" ,
// 					TableHand,0,0,0.0,1,0.0,InsulationBar_Difference);
// 				database.ExecuteSQL(sSql);
// 				
// 		
// 				// //				// 插入角码数值				
// 				double AlumAngle_UnitPrice = 2.2+2.4;				
// 				double AlumAngle_Total = AlumAngle_UnitPrice * 2;				
// 				
// 				sSql.Format( "%s('中梃角码',%d,%d,%0.3f,%d,'个',%0.2f,%0.2f,'')" ,TableHand,0,0,0.0,2,AlumAngle_UnitPrice,AlumAngle_Total);
// 				database.ExecuteSQL(sSql);
// 				
// 				
// 				// // 				// 插入角码注胶数值				
// 				int AlumAngle_Glue_len = 33*2+20+19*2+20;
// 				double Glue_UnitPrice = 0.016;				
// 				double AlumAngle_Glue_Total =  Glue_UnitPrice * 2 * AlumAngle_Glue_len ;				
// 				
// 				sSql.Format( "%s('中梃角码注胶',%d,%d,%0.3f,%d,'个',%0.3f,%0.2f,'')" ,TableHand,AlumAngle_Glue_len,0,0.0,2,Glue_UnitPrice,AlumAngle_Glue_Total);
// 				database.ExecuteSQL(sSql);


}

void COutToExcel::WriteFixData()
{
	//				// 插入固定框数值

	
	CoperationList oper;
	
	
	int xLength = 0 ;
	
	POSITION pos = pBoxTable->GetHeadPosition();
	for (int i = 0; i < pBoxTable->GetCount(); i++)
	{			
		//取得数据
		POSITION pos1 = pBoxTable->FindIndex(i);					
		CBox* d1 = (CBox* )pBoxTable->GetAt(pos1);			
		int it = d1->GetToType() ;
		CRect rt = d1->GetBox();
		
		//在这里查找所有中梃
		if(5 == it )
		{	
			
	
	double Alum_WeightMeter = oper.NameToWeightMeter(pSeriesTable,"固定压线米重");
	double Bar_InFrame_Value = oper.NameToValue(pSeriesTable,"固定压线入框"); //隔热条米重
	// 
	// 
	int xLength = rt.Width() + Bar_InFrame_Value * 2  ;
	int yLength = rt.Height()+ Bar_InFrame_Value * 2  ;
	// 				
	// 				
				//double ComplexAlum_WeightMeter = Alum_WeightMeter + InsulationBar_WeightMeter;
				double Alum_UnitPrice = oper.NameToUnitPrice(pPublicTable,"喷涂铝型材");				
				
				double AlumFrameFile_xTotal = Alum_WeightMeter* Alum_UnitPrice* 2* xLength/ 1000;
				double AlumFrameFile_yTotal = Alum_WeightMeter* Alum_UnitPrice* 2* yLength/ 1000;
				
				sSql.Format( "%s('固定窗','铝型材',%d,%d,%d,%0.3f,%d,'支',%0.2f,%0.2f,'含0.03损耗')" ,
					TableHand,
					xLength,0,0,Alum_WeightMeter,2,Alum_UnitPrice,AlumFrameFile_xTotal*1.03);
				database.ExecuteSQL(sSql);
				
				
				sSql.Format( "%s('固定窗','铝型材',%d,%d,%d,%0.3f,%d,'支',%0.2f,%0.2f,'含0.03损耗')" ,
					TableHand,
					yLength,0,0,Alum_WeightMeter,2,Alum_UnitPrice,AlumFrameFile_yTotal*1.03);
				database.ExecuteSQL(sSql);

				//////////////////////////////////////////////////////////

				// // //				// 插入角码数值				
				double AlumAngle_UnitPrice = oper.NameToUnitPrice(pSeriesTable,"固定压线角码");				
				double AlumAngle_Total = AlumAngle_UnitPrice * 4;				
				// 				
				sSql.Format( "%s('固定窗','角码',%d,%d,%d,%0.3f,%d,'组',%0.2f,%0.2f,'')" ,
					TableHand,0,0,0,0.0,4,AlumAngle_UnitPrice,AlumAngle_Total);
				database.ExecuteSQL(sSql);
				
				// 				
				// // // 				// 插入角码注胶数值				
				int AlumAngle_Glue_len = oper.NameToValue(pSeriesTable,"固定压线角码注胶长度");	
				double Glue_UnitPrice = oper.NameToUnitPrice(pPublicTable,"角码注胶");				//角码注胶
				double AlumAngle_Glue_Total =  Glue_UnitPrice * 4 * AlumAngle_Glue_len ;				
				// 				
				sSql.Format( "%s('固定窗','角码注胶',%d,%d,%d,%0.3f,%d,'组',%0.3f,%0.2f,'')" ,
					TableHand,AlumAngle_Glue_len,0,0,0.0,4,Glue_UnitPrice,AlumAngle_Glue_Total);
 				database.ExecuteSQL(sSql);


				// // // 				// 插入断面胶数值
				double SectionGlue_UnitPrice =  oper.NameToUnitPrice(pPublicTable,"断面胶") /2;				
				double SectionGlue_Total = SectionGlue_UnitPrice * 4  ;				
				// 				
				sSql.Format( "%s('固定窗','断面胶',%d,%d,%d,%0.3f,%d,'个',%0.2f,%0.2f,'')" ,
					TableHand,0,0,0,0.0,4,SectionGlue_UnitPrice,SectionGlue_Total);
 				database.ExecuteSQL(sSql);

				// 
				//固定玻璃
				
				double Glass_Weight = oper.NameToWeightMeter(pPublicTable,"玻璃5+20A+5") ; //重量			
				double Glass_UnitPrice = oper.NameToUnitPrice(pPublicTable,"玻璃5+20A+5") ; //价格	
				
				double FixFileHight = oper.NameToValue(pSeriesTable,"压线高度");
				double GlassInFix = oper.NameToValue(pSeriesTable,"固玻入框");
				
				double GlassWidth =  xLength- FixFileHight * 2 + GlassInFix * 2 ;
				double  GlassHight = yLength- FixFileHight * 2 + GlassInFix * 2 ;
				
				double Glass_Total_Price = Glass_UnitPrice * GlassWidth /1000 * GlassHight /1000 ;

				
				sSql.Format( "%s('固定窗','玻璃',%d,%d,%d,%0.3f,%d,'个',%0.2f,%0.2f,'')" ,
					TableHand,0,(int )GlassWidth,(int )GlassHight,0.0,1,Glass_UnitPrice,Glass_Total_Price);
 				database.ExecuteSQL(sSql);


				// //			// 插入EPDM胶条数值				
				 				//double InsulationBar_WeightMeter = 0.055+0.055;
				 				double EPDM_UnitPrice = oper.NameToUnitPrice(pSeriesTable,"固定玻璃EPDM胶条") ; //价格	
				 				double EPDM_Length = (xLength+yLength)*2 ;
				 				double EPDM_Total = EPDM_UnitPrice*EPDM_Length/1000;				
				// 				
				sSql.Format( "%s('固定窗','玻璃EPDM胶条',%d,%d,%d,%0.3f,%d,'组',%0.2f,%0.2f,'')" ,
					TableHand,(int )EPDM_Length,0,0,0.0,1,EPDM_UnitPrice,EPDM_Total);
 				database.ExecuteSQL(sSql);
// 				



				// 				//固定玻璃包装贴膜
				// 							
				 				double GlassPack_UnitPrice =  oper.NameToUnitPrice(pPublicTable,"玻璃包装") ; //价格				
				 				double GlassPack_Total = GlassPack_UnitPrice * GlassWidth * GlassHight /1000 /1000 ;
	
								
								sSql.Format( "%s('固定窗','玻璃包装贴膜',%d,%d,%d,%0.3f,%d,'个',%0.2f,%0.2f,'')" ,
									TableHand,0,(int )GlassWidth,(int )GlassHight,0.0,1,GlassPack_UnitPrice,GlassPack_Total);
 				database.ExecuteSQL(sSql);

				// 				// // 				// 插入玻璃垫块数值
				 				double Block_UnitPrice =  oper.NameToUnitPrice(pSeriesTable,"固定玻璃垫块");		//固定玻璃垫块
				 				int Block_Quantity = (int ) (GlassWidth /300) ;
				 				if(Block_Quantity < 2 ) Block_Quantity = 2;
				 				double Block_Total = Block_UnitPrice * Block_Quantity;				
				// 				
								sSql.Format( "%s('固定窗','玻璃垫块',%d,%d,%d,%0.3f,%d,'个',%0.2f,%0.2f,'')" ,
									TableHand,0,0,0,0.0,Block_Quantity,Block_UnitPrice,Block_Total);
				database.ExecuteSQL(sSql);

///////////////////////////////////////////////////////////
				// 				// // 				// 插入挡水绵数值
				 				double WaterStopXPE_UnitPrice = oper.NameToUnitPrice(pSeriesTable,"固定玻璃挡水绵");	//固定玻璃挡水绵			
				// 				
				 				double WaterStopXPE_Total = WaterStopXPE_UnitPrice * GlassWidth /1000;				
				// 				
								sSql.Format( "%s('固定窗','挡水绵',%d,%d,%d,%0.3f,%d,'支',%0.2f,%0.2f,'')" ,
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
					//以下是纱网窗扇的计算
				//以下是窗扇的计算
	CoperationList oper;
	
	
	int xLength = 0 ;
	
	POSITION pos = pBoxTable->GetHeadPosition();
	for (int i = 0; i < pBoxTable->GetCount(); i++)
	{			
		//取得数据
		POSITION pos1 = pBoxTable->FindIndex(i);					
		CBox* d1 = (CBox* )pBoxTable->GetAt(pos1);			
		int it = d1->GetToType() ;
		CRect rt = d1->GetBox();
		
		//在这里查找所有开启扇
		if(6 == it || 7 == it)
		{	
			
			

			double Bar_InFrame_Value = oper.NameToValue(pSeriesTable,"纱扇入框"); //
			// 
			// 
			int xLength = rt.Width() + Bar_InFrame_Value * 2  ;
			int yLength = rt.Height()+ Bar_InFrame_Value * 2  ;
			// 				
			// 				
			
			double Alum_WeightMeter = oper.NameToWeightMeter(pSeriesTable,"纱扇米重");
		
			// 				
			// 				
			
			double Alum_UnitPrice = oper.NameToUnitPrice(pPublicTable,"喷涂铝型材");				
			
			double AlumFrameFile_xTotal = Alum_WeightMeter* Alum_UnitPrice* 2* xLength/ 1000;
			double AlumFrameFile_yTotal = Alum_WeightMeter* Alum_UnitPrice* 2* yLength/ 1000;
			
			sSql.Format( "%s('纱窗扇','铝型材',%d,%d,%d,%0.3f,%d,'支',%0.2f,%0.2f,'含0.03损耗')" ,
				TableHand,
				xLength,0,0,Alum_WeightMeter,2,Alum_UnitPrice,AlumFrameFile_xTotal*1.03);
			database.ExecuteSQL(sSql);
			
			
			sSql.Format( "%s('纱窗扇','铝型材',%d,%d,%d,%0.3f,%d,'支',%0.2f,%0.2f,'含0.03损耗')" ,
				TableHand,
				yLength,0,0,Alum_WeightMeter,2,Alum_UnitPrice,AlumFrameFile_yTotal*1.03);
				database.ExecuteSQL(sSql);

				
				// // //			// 插入钢角片数值// 			
				double SteelAngle_UnitPrice = oper.NameToUnitPrice(pSeriesTable,"纱窗扇钢角片"); //窗框钢角片
				int SteelAngle_Quantity = (int )oper.NameToValue(pSeriesTable,"纱窗扇钢角片"); //窗框钢角片	
				double SteelAngle_Total = SteelAngle_UnitPrice * 4 * SteelAngle_Quantity;				
				
				sSql.Format( "%s('纱窗扇','钢角片',%d,%d,%d,%0.3f,%d,'组',%0.2f,%0.2f,'')" ,
					TableHand,0,0,0,0.0,4* SteelAngle_Quantity,SteelAngle_UnitPrice,SteelAngle_Total);
				database.ExecuteSQL(sSql);
// // 

				//////////////////////////////////////////////////////////
				
				// // //				// 插入角码数值				
				double AlumAngle_UnitPrice = oper.NameToUnitPrice(pSeriesTable,"纱窗扇角码");				
				double AlumAngle_Total = AlumAngle_UnitPrice * 4;				
				// 				
				sSql.Format( "%s('纱窗扇','角码',%d,%d,%d,%0.3f,%d,'组',%0.2f,%0.2f,'')" ,
					TableHand,0,0,0,0.0,4,AlumAngle_UnitPrice,AlumAngle_Total);
				database.ExecuteSQL(sSql);
				
				// 				
				// // // 				// 插入角码注胶数值				
				int AlumAngle_Glue_len = oper.NameToValue(pSeriesTable,"纱窗扇角码注胶长度");	
				double Glue_UnitPrice = oper.NameToUnitPrice(pPublicTable,"角码注胶");				//角码注胶
				double AlumAngle_Glue_Total =  Glue_UnitPrice * 4 * AlumAngle_Glue_len ;				
				// 				
				sSql.Format( "%s('纱窗扇','角码注胶',%d,%d,%d,%0.3f,%d,'组',%0.3f,%0.2f,'')" ,
					TableHand,AlumAngle_Glue_len,0,0,0.0,4,Glue_UnitPrice,AlumAngle_Glue_Total);
				database.ExecuteSQL(sSql);
				
				
				// // // 				// 插入断面胶数值
				double SectionGlue_UnitPrice =  oper.NameToUnitPrice(pPublicTable,"断面胶");				
				double SectionGlue_Total = SectionGlue_UnitPrice * 4  ;				
				// 				
				sSql.Format( "%s('纱窗扇','断面胶',%d,%d,%d,%0.3f,%d,'个',%0.2f,%0.2f,'')" ,
					TableHand,0,0,0,0.0,4,SectionGlue_UnitPrice,SectionGlue_Total);
				database.ExecuteSQL(sSql);
				
				 
				//纱窗扇纱网
				
							
				double Glass_UnitPrice = oper.NameToUnitPrice(pPublicTable,"不锈钢网") ; //价格	
				
				double FixFileHight = oper.NameToValue(pSeriesTable,"纱扇大面");
				double GlassInFix = oper.NameToValue(pSeriesTable,"纱网入扇");
				
				double GlassWidth =  xLength- FixFileHight * 2 + GlassInFix * 2 ;
				double  GlassHight = yLength- FixFileHight * 2 + GlassInFix * 2 ;
				
				double Glass_Total_Price = Glass_UnitPrice * GlassWidth /1000 * GlassHight /1000 ;
				
				
				sSql.Format( "%s('纱窗扇','不锈钢网',%d,%d,%d,%0.3f,%d,'个',%0.2f,%0.2f,'')" ,
					TableHand,0,(int )GlassWidth,(int )GlassHight,0.0,1,Glass_UnitPrice,Glass_Total_Price);
				database.ExecuteSQL(sSql);
				
				
		
				
				// //			// 插入EPDM胶条数值				
				//double InsulationBar_WeightMeter = 0.055+0.055;
				double EPDM_UnitPrice_2 = oper.NameToUnitPrice(pSeriesTable,"纱扇密封EPDM胶条") ; //价格	
				double EPDM_Length_2 = (xLength+yLength)*2 ;
				double EPDM_Total_2 = EPDM_UnitPrice_2 *EPDM_Length_2/1000;				
				// 				
				sSql.Format( "%s('纱窗扇','纱扇密封EPDM胶条',%d,%d,%d,%0.3f,%d,'组',%0.2f,%0.2f,'')" ,
					TableHand,(int )EPDM_Length_2,0,0,0.0,1,EPDM_UnitPrice_2,EPDM_Total_2);
				database.ExecuteSQL(sSql);
				// 				

				
			

				///////////////////////////////////////////////////////////
				
				// 				// // 				// 插入传动铝条数值
				double AlumBar_Weight =  oper.NameToWeightMeter(pPublicTable,"传动铝条");
				double AlumBar_UnitPrice =  oper.NameToUnitPrice(pPublicTable,"传动铝条");

				double AlumBar_Total = (yLength -300.0)  *  AlumBar_Weight * AlumBar_UnitPrice /1000;
				// 				
				sSql.Format( "%s('纱窗扇','传动铝条',%d,%d,%d,%0.3f,%d,'支',%0.2f,%0.2f,'')" ,
					TableHand,(int )(yLength -300.0),0,0,AlumBar_Weight,1,AlumBar_UnitPrice,AlumBar_Total);
				database.ExecuteSQL(sSql);
				
				///////////////////////////////////////////////////////////

				// 				// // 				// 插入五金数值
				double HandWave_UnitPrice =  oper.NameToUnitPrice(pSeriesTable,"纱窗扇五金");
				// 				
				sSql.Format( "%s('纱窗扇','五金',%d,%d,%d,%0.3f,%d,'套',%0.2f,%0.2f,'')" ,
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
//DEL 		"xls file(*.xls)|*.xls||");    //TRUE为OPEN对话框，FALSE为SAVE AS对话框
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
    //读入EXCEL
   
    CString sItem1, sItem2;
    CString sDriver;
    CString sDsn;

	CString sFile = FilePathName.Replace("\\","\\\\") ;// 将被读取的Excel文件名
    
 	
    // 检索是否安装有Excel驱动 "Microsoft Excel Driver (*.xls)"
    sDriver = GetExcelDriver();
    if (sDriver.IsEmpty())
    {
        // 没有发现Excel驱动
        AfxMessageBox(_T( "没有安装Excel驱动!" ));
        return ;
    }
    
    // 创建进行存取的字符串
    sDsn.Format(_T( "ODBC;DRIVER={%s};DSN='';DBQ=%s" ), sDriver, sFile);
    
    TRY
    {	
		//AfxMessageBox("000");
        // 打开数据库(既Excel文件)
        database.Open(NULL, false , false , sDsn);
        
        CRecordset recset(&database);
        
        // 设置读取的查询语句.
        sSql .Format( "SELECT Name, Age FROM %s ORDER BY Name " , "demo");
        
	

        // 执行查询语句
        recset.Open(CRecordset::forwardOnly, sSql, CRecordset::readOnly);
        // 获取查询结果
        while (!recset.IsEOF())
        {
            //读取Excel内部数值
            recset.GetFieldValue(_T( "Name" ), sItem1);
            recset.GetFieldValue(_T( "Age" ), sItem2);
            AfxMessageBox(sItem1+"--"+sItem2);
            // 移到下一行
            recset.MoveNext();
        }
        
        // 关闭数据库
        database.Close();
        
    }
    CATCH(CDBException, e)
    {
        // 数据库操作产生异常时...
        AfxMessageBox(_T( "数据库错误: " ) + e->m_strError);
    }
    END_CATCH;
}

void COutToExcel::TestWrite()
{
	//写入EXCEL

	//CString str  = _T(GetFileNameXls("Save"));
	//CString sExcelFile = str ; // 要建立的Excel文件
	
	

    CString sDriver = _T( "MICROSOFT EXCEL DRIVER (*.XLS)" ); // Excel安装驱动
	CString sExcelFile = _T( "./data/SeriesData.xls" ); // 将被读取的Excel文件名



   
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
				database.ExecuteSQL(_T( "DROP  TABLE Test" ));
				
 			}
 			catch (CDBException *pe)
 			{
 				// The error code is in pe->m_nRetCode
 				pe->ReportError();
 				pe->Delete();
 			}
				
			//创建表
			database.ExecuteSQL(_T( "CREATE TABLE Test (Name TEXT, Val NUMBER, WeightMeter NUMBER, UnitPrice NUMBER)" ));
            
            // 插入数值
            database.ExecuteSQL(_T( "INSERT INTO Test (Name,Val,WeightMeter,UnitPrice) VALUES ('铝型材喷涂',0.0,0.0,29.5)" ));

	
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

void COutToExcel::TestRead(CSeriesList* tempList , CString TempTableName)
{

	//获取工作路径
 
	CString csFullPath =GetModuleDir();
	
	csFullPath.TrimRight("\\Debug");
	
	//读入EXCEL
 
    CString sItem1,	 sItem2,sItem3, sItem4;
    CString sDriver;
    CString sDsn;
  
	CString sFile = csFullPath +   "\\data\\SeriesData.xls"  ; // 将被读取的Excel文件名/data



	//return ;
    
    // 检索是否安装有Excel驱动 "Microsoft Excel Driver (*.xls)"
    sDriver = GetExcelDriver();
    if (sDriver.IsEmpty())
    {
        // 没有发现Excel驱动
        AfxMessageBox(_T( "没有安装Excel驱动!" ));
        return ;
    }
    
    // 创建进行存取的字符串
    sDsn.Format(_T( "ODBC;DRIVER={%s};DSN='';DBQ=%s" ), sDriver, sFile);
    
    TRY
    {
        // 打开数据库(既Excel文件)
        database.Open(NULL, false , false , sDsn);
        
        CRecordset recset(&database);     
		
        // 设置读取的查询语句.	从指定的表中选出的指定的列
        sSql .Format( _T("SELECT Name,Val,WeightMeter,UnitPrice FROM [%s$] ORDER BY Name" ), TempTableName);	//, "[天语二代$]" TempTableName"天语二代" "Public_UnitPrice"
        
        // 执行查询语句
        recset.Open(CRecordset::forwardOnly, sSql, CRecordset::readOnly);


        // 获取查询结果
        while (!recset.IsEOF())
        {
            //读取Excel内部数值
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
            // 移到下一行
            recset.MoveNext();	

        }

		recset.Close();

		/////////////////////////////////////////////////////////////////////////////////
	


		/////////////////////////////////////////////////////////////////////////////////


		
        
        // 关闭数据库
        database.Close();
        
    }
    CATCH(CDBException, e)
    {
        // 数据库操作产生异常时...
        AfxMessageBox(_T( "数据库错误: " ) + e->m_strError);
    }
    END_CATCH;

}


//DEL void COutToExcel::TestRead2(CSeriesList* tempList , CString TempTableName)
//DEL {
//DEL 
//DEL 	//获取工作路径
//DEL 	
//DEL 	CString csFullPath =GetModuleDir();
//DEL 
//DEL 	csFullPath.TrimRight("\\Debug");
//DEL 	
//DEL 	//读入EXCEL
//DEL 	
//DEL     CString sItem1,	 sItem2,sItem3, sItem4;
//DEL     CString sDriver;
//DEL     CString sDsn;
//DEL     CString sFile = csFullPath + "\\data\\SeriesData.xls"  ; // 将被读取的Excel文件名/data
//DEL 	
//DEL 	
//DEL 	//AfxMessageBox(sFile);
//DEL 	
//DEL 	
//DEL 	//return ;
//DEL     
//DEL     // 检索是否安装有Excel驱动 "Microsoft Excel Driver (*.xls)"
//DEL     sDriver = GetExcelDriver();
//DEL     if (sDriver.IsEmpty())
//DEL     {
//DEL         // 没有发现Excel驱动
//DEL         AfxMessageBox(_T( "没有安装Excel驱动!" ));
//DEL         return ;
//DEL     }
//DEL     
//DEL     // 创建进行存取的字符串
//DEL     sDsn.Format(_T( "ODBC;DRIVER={%s};DSN='';DBQ=%s" ), sDriver, sFile);
//DEL     
//DEL     TRY
//DEL     {
//DEL         // 打开数据库(既Excel文件)
//DEL         database.Open(NULL, false , false , sDsn);
//DEL         
//DEL         CRecordset recset(&database);     
//DEL 		
//DEL         // 设置读取的查询语句.	从指定的表中选出的指定的列
//DEL         sSql .Format( _T("SELECT Name,Val,WeightMeter,UnitPrice FROM [%s$] ORDER BY Name" ), TempTableName);	//, "[天语二代$]" TempTableName"天语二代" "Public_UnitPrice"
//DEL         
//DEL         // 执行查询语句
//DEL         recset.Open(CRecordset::forwardOnly, sSql, CRecordset::readOnly);
//DEL 		
//DEL 		
//DEL         // 获取查询结果
//DEL         while (!recset.IsEOF())
//DEL         {
//DEL             //读取Excel内部数值
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
//DEL             // 移到下一行
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
//DEL         // 关闭数据库
//DEL         database.Close();
//DEL         
//DEL     }
//DEL     CATCH(CDBException, e)
//DEL     {
//DEL         // 数据库操作产生异常时...
//DEL         AfxMessageBox(_T( "数据库错误: " ) + e->m_strError);
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
			
		"xls file(*.xls)|*.xls||");    //TRUE为OPEN对话框，FALSE为SAVE AS对话框

	
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

	//获取工作路径

		CString csFullPath =GetModuleDir();
	csFullPath.TrimRight("\\Debug");

		//读入EXCEL
 
    CString sItem1,	 sItem2,sItem3, sItem4;
    CString sDriver;
    CString sDsn;
    CString sFile = csFullPath +   "\\data\\SeriesData.xls"  ; // 将被读取的Excel文件名/data
    
    // 检索是否安装有Excel驱动 "Microsoft Excel Driver (*.xls)"
    sDriver = GetExcelDriver();
    if (sDriver.IsEmpty())
    {
        // 没有发现Excel驱动
        AfxMessageBox(_T( "没有安装Excel驱动!" ));
        return FALSE;
    }
    
    // 创建进行存取的字符串
    sDsn.Format(_T( "ODBC;DRIVER={%s};DSN='';DBQ=%s" ), sDriver, sFile);
    
    TRY
    {
        // 打开数据库(既Excel文件)
        database.Open(NULL, false , false , sDsn);


		/////////////////////////////////////////////////////////////////////////////////

		CRecordset rt(&database);     
		
        // 设置读取的查询语句.
        sSql .Format( _T("SELECT Name FROM %s ORDER BY Name" ),"[Tables$]" );	//字段名称要分大小写
        
        // 执行查询语句
        rt.Open(CRecordset::forwardOnly, sSql, CRecordset::readOnly);
		
		
        // 获取查询结果
        while (!rt.IsEOF())
        {
            //读取Excel内部数值			
            rt.GetFieldValue(_T( "Name" )	, sItem1);					
			//AfxMessageBox(sItem1 );	
			
			szArray.AddTail(sItem1);
		
            // 移到下一行
            rt.MoveNext();	
			
        }		
		rt.Close();
	


		/////////////////////////////////////////////////////////////////////////////////


		
        
        // 关闭数据库
        database.Close();
        
    }
    CATCH(CDBException, e)
    {
        // 数据库操作产生异常时...
        AfxMessageBox(_T( "数据库错误: " ) + e->m_strError);
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
//DEL 	//获取工作路径
//DEL 	
//DEL 	CString csFullPath =GetModuleDir(); 
//DEL csFullPath.TrimRight("\\Debug");	
//DEL 	//读入EXCEL
//DEL 	
//DEL     CString sItem1,	 sItem2,sItem3, sItem4;
//DEL     CString sDriver;
//DEL     CString sDsn;
//DEL     CString sFile = csFullPath +   "\\data\\SeriesData.xls"  ; // 将被读取的Excel文件名/data
//DEL     
//DEL     // 检索是否安装有Excel驱动 "Microsoft Excel Driver (*.xls)"
//DEL     sDriver = GetExcelDriver();
//DEL     if (sDriver.IsEmpty())
//DEL     {
//DEL         // 没有发现Excel驱动
//DEL         AfxMessageBox(_T( "没有安装Excel驱动!" ));
//DEL         return FALSE;
//DEL     }
//DEL     
//DEL     // 创建进行存取的字符串
//DEL     sDsn.Format(_T( "ODBC;DRIVER={%s};DSN='';DBQ=%s" ), sDriver, sFile);
//DEL     
//DEL     TRY
//DEL     {
//DEL         // 打开数据库(既Excel文件)
//DEL         database.Open(NULL, false , false , sDsn);
//DEL 		
//DEL 		
//DEL 		/////////////////////////////////////////////////////////////////////////////////
//DEL 		
//DEL 		CRecordset rt(&database);     
//DEL 		
//DEL         // 设置读取的查询语句.
//DEL         sSql .Format( _T("SELECT Name FROM %s ORDER BY Name" ),"[Tables$]" );	//字段名称要分大小写
//DEL         
//DEL         // 执行查询语句
//DEL         rt.Open(CRecordset::forwardOnly, sSql, CRecordset::readOnly);
//DEL 		
//DEL 		
//DEL         // 获取查询结果
//DEL         while (!rt.IsEOF())
//DEL         {
//DEL             //读取Excel内部数值			
//DEL             rt.GetFieldValue(_T( "Name" )	, sItem1);				
//DEL 			szArray.AddTail(sItem1);
//DEL 			
//DEL             // 移到下一行
//DEL             rt.MoveNext();	
//DEL 			
//DEL         }		
//DEL 		rt.Close();
//DEL 		
//DEL 		/////////////////////////////////////////////////////////////////////////////////
//DEL 	
//DEL         
//DEL         // 关闭数据库
//DEL         database.Close();
//DEL         
//DEL     }
//DEL     CATCH(CDBException, e)
//DEL     {
//DEL         // 数据库操作产生异常时...
//DEL         AfxMessageBox(_T( "数据库错误: " ) + e->m_strError);
//DEL     }
//DEL     END_CATCH;
//DEL 	
//DEL 	
//DEL 	
//DEL 	
//DEL 	return TRUE ;
//DEL }