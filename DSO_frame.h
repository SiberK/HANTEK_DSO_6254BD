//---------------------------------------------------------------------------

#ifndef DSO_frameH
#define DSO_frameH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#include "StdAfx.h"
#include "Hard.h"
//---------------------------------------------------------------------------
class TFrmDSO : public TFrame
{
__published:	// IDE-managed Components
	TScrollBox *pView;
private:	// User declarations
	CHard	m_Hard		;
	BOOL 	m_bStartNew	;//是否启动新一次采集 Стоит ли начинать новую коллекцию

 void __fastcall DrawWave    (HDC hdc,TRect Rect)	    	;
 void __fastcall DrawWaveInYT(HDC hdc,TRect Rect,USHORT nCH)	;

public:		// User declarations
	__fastcall TFrmDSO(TComponent* Owner)	;

 void __fastcall Init(TObject* Sender)		;
 void __fastcall Destroy(TObject* Sender)	;
 void __fastcall CollectData (void)		;
 void __fastcall OnDraw(TObject *Sender)	;
};
//---------------------------------------------------------------------------
extern PACKAGE TFrmDSO *FrmDSO;
//---------------------------------------------------------------------------
#endif
