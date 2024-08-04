//---------------------------------------------------------------------------
#ifndef ComWorLH
#define ComWorLH
#include	<Math.h>

#ifndef _BV
#define	_BV(X)	(1<<(X))
#endif
//---------------------------------------------------------------------------
bool	CheckFloat(void* Val){ return ((*(DWord*)Val)&0x7F800000) != 0x7F800000	;}
//---------------------------------------------------------------------------
extern 	BOOL __fastcall	SetWinTransparent(HWND hdr,int color)	;
//---------------------------------------------------------------------------
void GetVersionOfFile (char * pszAppName, // file
		       char * pszVerBuff, // receives version
		       int     iVerBuffLen, // size of buffer
		       char * pszLangBuff, // receives language
		       int iLangBuffLen); // size of buffer
//---------------------------------------------------------------------------
#ifndef	_FILENAME_LOGFILE
#define	_FILENAME_LOGFILE ChangeFileExt(ParamStr(0),".log")
#endif

extern void	LogException(String File,String Line,Exception &E,String App="")	;
//extern	String	__FileNameLogFile	;
extern 	void __fastcall	LogFile(char* FName,String Line)	;

#define	DEF_CATCH  catch(Exception &E){LogException(__FILE__,__LINE__,E);}
#define	DEF_CATCH_ catch(Exception &E){LogException(__FILE__,__LINE__,E);
//---------------------------------------------------------------------------
#endif
