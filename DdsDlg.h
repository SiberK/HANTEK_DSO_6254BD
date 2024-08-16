//---------------------------------------------------------------------------

#ifndef DdsDlgH
#define DdsDlgH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Mask.hpp>
#include "rxCurrEdit.hpp"
#include "rxPlacemnt.hpp"
#include "rxToolEdit.hpp"
//---------------------------------------------------------------------------
class TDdsDialog : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TComboBox *cbDdsMode;
	TCurrencyEdit *eFrq;
	TComboBox *cbFrq;
	TCurrencyEdit *eAmpl;
	TCurrencyEdit *eOffset;
	TFormStorage *FormStorage1;
	void __fastcall DdsChange(TObject *Sender);
	void __fastcall FormMouseWheel(TObject *Sender, TShiftState Shift,
          int WheelDelta, TPoint &MousePos, bool &Handled);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall FormStorage1RestorePlacement(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TDdsDialog(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TDdsDialog *DdsDialog;
extern void __fastcall	WhMouse(TCurrencyEdit* ed,TPoint &MPos,int Sgn, double mux);
//---------------------------------------------------------------------------
#endif
