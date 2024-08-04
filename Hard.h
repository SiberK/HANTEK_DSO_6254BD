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
	virtual ~CHard();
//Attributes
public:
  USHORT       	m_nDeviceIndex		;
  USHORT       	m_nDeviceNum		;
//USHORT 	m_nComType		;//0:USB; 1:LAN
  short*       	m_pSrcData[MAX_CH_NUM]	;//—читанные данные минус положение нулевого уровн€ (-255 ~ 255)
//USHORT 	m_nCalLevel[CAL_LEVEL_LEN];//Cal Level
  USHORT       	m_nTimeDIV		;
  USHORT       	m_nYTFormat		;
  BOOL 		m_bCollect		;
  CONTROLDATA 	m_stControl		;
  RELAYCONTROL 	RelayControl		;
  USHORT       	m_nTriggerMode		;
  USHORT       	m_nTriggerSweep		;
  USHORT       	m_nTriggerSlope		;
  USHORT       	m_nLeverPos[MAX_CH_NUM]	;
  COLORREF 	m_clrRGB[MAX_CH_NUM]	;
//WORD		pAmpLevel[AMPCALI_Len]	;

  int		m_nReadOK		;// ¬ерны ли данные, прочитанные в этот раз, 0, неправильные, не 0, неправильные;
  BOOL 		m_bStartNew		;// —тоит ли начинать новую коллекцию
//Operations
public:
  void 	 	Init()			;
  void  	SetChnlParams(TChnlParams* params);


  USHORT 	CollectData()		;// возвращаю m_nDeviceIndex (0xFF - устройство не обнаружено)
  bool 	 	FindeDev()		;
  void 	 	ReadData()		;
  void 	 	ReadSCANData()		;
  void 	 	SourceToDisplay(USHORT* pData,ULONG nDataLen,USHORT nCH,int nOffset=0);
};
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#endif

