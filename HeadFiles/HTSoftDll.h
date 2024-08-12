#ifndef _HT_SOFT_DLL_H
#define _HT_SOFT_DLL_H

#ifndef DLL_API
#define DLL_API extern "C" __declspec(dllimport)
#endif
#define WINAPI __stdcall

typedef struct _HT_CONTROL_DATA
{
  WORD  nCHSet		;// channel Enable/Disable
			   // the 0 bit: 0 CH1 is disable, 1 CH1 is enable
			   // the 1 bit: 0 CH2 is disable, 1 CH2 is enable
			   // the 2 bit: 0 CH3 is disable, 1 CH3 is enable
			   // the 3 bit: 0 CH4 is disable, 1 CH4 is enable
 WORD  nTimeDIV		;// the index of time base
 WORD  nTriggerSource	;// the index of the trigger source
 WORD  nHTriggerPos	;// the horizontal trigger pos (Value:0~100)
 WORD  nVTriggerPos	;// the vertical trigger pos
 WORD  nTriggerSlope	;// the edge trigger slope(0 is rise slope, 1 is fall slope)
 ULONG nBufferLen	;// Соответствует 10К, 1М, 2М...16М.
 ULONG nReadDataLen	;// Общая длина данных, которые будут считаны с оборудования.
 ULONG nAlreadyReadLen	;// Запишите длину данных, которые были прочитаны в этот раз.
			   // Она действительна в режиме сканирования/прокрутки
			   // и недействительна в НОРМАЛЬНОМ режиме.
 WORD  nALT		;// is alternate trigger of not
 WORD  nETSOpen		;// ETS enable/display（no use）
 WORD  nDriverCode	;// Номер водителя
 ULONG nLastAddress	;// конечный адрес последнего чтения в режиме сканирования.
 WORD  nFPGAVersion	;// FPGA номер версии
// 	WORD  nAddressOffset	;// Джиттер триггера плюс смещение
		
		
}CONTROLDATA,*PCONTROLDATA;


DLL_API WORD   WINAPI dsoSFInsert(WORD* pSourceData,WORD* pBufferData,PCONTROLDATA pControl,WORD nInsertMode,WORD nCH,ULONG* pState);
DLL_API WORD   WINAPI dsoSFProcessALTData(WORD* pOutData,WORD* pInData1,WORD* pInData2,ULONG nDataLen,WORD nHTriggerPos,WORD nCalData);
DLL_API ULONG  WINAPI dsoSFFindTrigger(WORD* SourceData,WORD* BufferData,PCONTROLDATA Control,double dInsert);//zhang addd dInsert
DLL_API WORD   WINAPI dsoSFFindTriggerCopy(WORD* SourceData,WORD* BufferData,PCONTROLDATA Control,ULONG TriggerPoint);
DLL_API WORD   WINAPI dsoSFInsertDataStep(WORD* SourceData,WORD* pBuffer,double div_data,PCONTROLDATA Control);
DLL_API WORD   WINAPI dsoSFInsertDataLine(WORD* SourceData,WORD* pBuffer,double div_data,PCONTROLDATA Control);
DLL_API WORD   WINAPI dsoSFInsertDataSin(WORD* SourceData,WORD* BufferData,PCONTROLDATA Control, double dbInsertNum,double* dbSinSheet);
DLL_API WORD   WINAPI dsoSFCalSinSheet(double div_data,double* dbSinSheet);
DLL_API double WINAPI dsoSFGetInsertNum(WORD nTimeDIV, WORD nALT, WORD nCHSet);   //modified by zhang  to fit 6104  from "bool bSingle" to "nCHSet"
DLL_API void   WINAPI dsoSFProcessInsertData(WORD* SourceData,WORD* BufferData,PCONTROLDATA pControl,WORD nInsertMode,BOOL bSingle,double* dbSinSheet,USHORT nCH);
DLL_API ULONG  WINAPI dsoSFGetSampleRate(WORD nTimeDIV,WORD nALT,WORD nCHState,WORD nCH);

DLL_API short  WINAPI HTPosConvertToScale(int x,int y);
DLL_API POINT  WINAPI HTGetTracePoint(RECT Rect,POINT pt,short nData,USHORT nDisLeverPos);
DLL_API ULONG  WINAPI HTGetTracePointIndex(RECT Rect,POINT pt,ULONG nDisDataLen,ULONG nSrcDataLen,USHORT nHTriggerPos);

DLL_API WORD   WINAPI dsoSFMathOperate(USHORT nOperate,const short* pSrcA,const short* pSrcB,short* pMathData,ULONG nDataLen);
DLL_API WORD   WINAPI dsoSFChooseData(WORD* pSrcData,ULONG nSrcDataLen,ULONG nChoose,WORD* pOutData,ULONG nOutDataLen);
DLL_API WORD   WINAPI dsoSFGetFFTSrcData(short* pSrcData,ULONG nCenterData,short* pFFTSrcData);
DLL_API double WINAPI dsoSFGetFFTSa(double dbTime);
DLL_API BOOL   WINAPI dsoSFCalPassFailData(short* pSrcData,ULONG nSrcDataLen,short* pOutData,float fH,float fV);
DLL_API BOOL   WINAPI dsoSFPassFail(short* pPFData,short* pSrcData,ULONG nDataLen);
DLL_API WORD   WINAPI dsoSFProcessALTData4CH(WORD* pOutData,WORD* pInData1,WORD* pInData2,WORD* pInData3,WORD* pInData4,ULONG nDataLen,WORD nHTriggerPos,WORD nCalData);
DLL_API double WINAPI dsoSFGetMiniScopeFFTSa(USHORT nTimeDIV,USHORT nCHNum,USHORT nMode);//·µ»ШµДКЗHz
DLL_API void   WINAPI dsoGetSoftTriggerPos(USHORT nTimeDIV,USHORT nTriggerSource,ULONG* pState,USHORT nFPGAVersion);
DLL_API void   WINAPI dsoGetSoftTriggerPosNew(PCONTROLDATA Control,ULONG* pState,USHORT nFPGAVersion);

DLL_API void   WINAPI dsoAdjustSquareWave(WORD* pSrcData, ULONG nSrcDataLen);
DLL_API void   WINAPI dsoAdjustADC(WORD* pSrcData, ULONG nSrcDataLen);
#endif
