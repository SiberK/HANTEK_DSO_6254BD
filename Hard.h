//---------------------------------------------------------------------------
#ifndef HardH
#define HardH
//---------------------------------------------------------------------------
#include "StdAfx.h"
//---------------------------------------------------------------------------
// Hard.h: interface for the CHard class.
//
//////////////////////////////////////////////////////////////////////
#pragma once

class CHard
{
public:
	CHard();
       ~CHard();//{}
//Attributes
public:
  USHORT       	m_nDeviceIndex		;
  USHORT       	m_nDeviceNum		;
//USHORT 	m_nComType		;//0:USB; 1:LAN
  short*       	m_pSrcData[MAX_CH_NUM]	;//Считанные данные минус положение нулевого уровня (-255 ~ 255)
//USHORT 	m_nCalLevel[CAL_LEVEL_LEN];//Cal Level
  size_t       	m_nTimeDiv		;
  USHORT       	m_nYTFormat		;
  bool 		m_bCollect		;
  CONTROLDATA 	m_stControl		;
  RELAYCONTROL 	RelayControl		;
  USHORT       	m_nTriggerMode		;
  USHORT       	m_nTriggerSweep		;
  USHORT       	m_nTriggerSlope		;
  USHORT       	m_nLeverPos[MAX_CH_NUM]	;
  COLORREF 	m_clrRGB[MAX_CH_NUM]	;
  WORD		m_nCHSet		;
  bool		flDbg1,flDbg2,flDbg3,flDbg4	;
//WORD		pAmpLevel[AMPCALI_Len]	;
  double	TimStrth		;// растяжка
  double	MultY[MAX_CH_NUM] 	;

  int		m_nReadOK		;// Верны ли данные, прочитанные в этот раз, 0, неправильные, не 0, неправильные;
  BOOL 		m_bStartNew		;// Стоит ли начинать новую коллекцию
  WORD		m_nCHMod		;// 1,2,4	??????????????
//Operations
public:
  void 	 	Init()			;
  void  	SetChnlParams(TChnlParams* params)	;
  void		SetLvl (int nCh,USHORT lvl)		;
  void		SetTrgT(int nCh,USHORT lvl)		;
  void		SetTrgV(int nCh,USHORT lvl)		;
  bool   	SetTimeDiv(TTimeParams* timPrms)	;// вернёт "уст. растяжка"
  bool 		SetStrth(bool val)			;//{ TimStrth = val	;}
  double	GetTimStrth(void){ return TimStrth	;}
  double	GetTimDiv(void)				;
  double	GetVltDiv(void)				;
  WORD		CalcCHMode(void)			;

  void 		SetTriggerMode (uint16_t val)		;
  void 		SetTriggerSweep(uint16_t val)		;
  void 		SetTriggerSlope(uint16_t val)		;
  void 		SetTriggerSrc  (uint16_t val)		;

  int 		CntChnlW(void)		;// кол-во включенных каналов
  ULONG		BufferLen(void) { return m_stControl.nBufferLen	;}

  double        SamplingRate()		;
  double 	SmplPerDiv(void)	;

  USHORT 	CollectData()		;// возвращаю m_nDeviceIndex (0xFF - устройство не обнаружено)
  bool 	 	FindeDev()		;
  int 	 	ReadData()		;
  void 	 	ReadSCANData()		;
  void 	 	SourceToDisplay(USHORT* pData,ULONG nDataLen,USHORT nCH,int nOffset=0);
};
//---------------------------------------------------------------------------
const double TIME_STRETH = 0.1		;// растяжка!!!

extern const double   tblTimDiv[]	;
extern const size_t   SIZE_TBL_TIM_DIV	;
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#endif

