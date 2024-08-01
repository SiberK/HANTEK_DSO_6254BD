//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "DSO_frame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "rxPlacemnt"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner): TForm(Owner)
{FormStorage1->IniFileName = ChangeFileExt(ParamStr(0),".ini")	;}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
 FrmDSO = new TFrmDSO(this)	;
 FrmDSO->Parent = pDSO		;
 FrmDSO->Align  = alClient	;

 FrmDSO->Init(this)		;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormDestroy(TObject *Sender){FrmDSO->Destroy(this)	;}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TForm1::timRefTimer(TObject *Sender)
{timRef->Enabled = false	;

 FrmDSO->CollectData()		;
 FrmDSO->OnDraw(Sender)		;

 timRef->Enabled = true		;
}
//---------------------------------------------------------------------------



