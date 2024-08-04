//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include 	<StdIO.h>
#include	<IO.h>
#include 	"ComWorL.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
static String	__FileNameLogFile 	;
//-------------------------------------------------------------------
void	LogException(String File,String Line,Exception &E,String App)
{String		ClName(E.ClassName())	;

// String	FName = ExtractFilePath(ParamStr(0)) + _FILENAME_LOGFILE;
 String	FName = /*ExtractFilePath(ParamStr(0)) + */_FILENAME_LOGFILE;
 if(!__FileNameLogFile.IsEmpty()) FName = __FileNameLogFile	;
 FILE*		fll = fopen(FName.c_str(),"at")			;

 if(fll){
   if(filelength(fileno(fll)) > 1000000L){
     fclose(fll)	;
     String	FNameNew = ChangeFileExt(FName,Now().FormatString("YYmmnnhhnn")+ ".log")		;
     rename(FName.c_str(),FNameNew.c_str())	;
     fll = fopen(FName.c_str(),"at")		;}
 }

 if(fll){
   if(ClName == "Exception") ClName = "**"	;
   fprintf(fll,"\n>%s %s %s %s  %s %s",
		Now().FormatString("YYYY.MM.dd hh:nn:ss").c_str(),
		ExtractFileName(File).c_str(),
		Line.c_str(),
		ClName.c_str(),
		E.Message.c_str(),
		App.c_str())	;
   fclose(fll)	;}
}
//---------------------------------------------------------------------------
void __fastcall	LogFile(char* FName,String Line)
{FILE* fll = fopen(FName,"at")	;
 if(fll){
   fputs(Line.c_str(),fll)	;
   fclose(fll)	;}
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
BOOL __fastcall	SetWinTransparent(HWND hdr,int color)
{SetWindowLong(hdr,GWL_EXSTYLE,GetWindowLong(hdr,GWL_EXSTYLE) & ~WS_EX_LAYERED)	;
 SetWindowLong(hdr,GWL_EXSTYLE,GetWindowLong(hdr,GWL_EXSTYLE) |  WS_EX_LAYERED)	;

 return ::SetLayeredWindowAttributes(hdr,color,180,LWA_ALPHA)			;}
//---------------------------------------------------------------------------

void GetVersionOfFile (char * pszAppName, // file
		       char * pszVerBuff, // receives version
		       int     iVerBuffLen, // size of buffer
		       char * pszLangBuff, // receives language
		       int iLangBuffLen) // size of buffer
{
   DWORD dwScratch;
   DWORD * pdwLangChar;
   DWORD dwInfSize ;
   UINT uSize;
   BYTE * pbyInfBuff;
   char szVersion [32];
   char szResource [80];
   char * pszVersion = szVersion;

   dwInfSize = GetFileVersionInfoSize (pszAppName, &dwScratch);

   if (dwInfSize)
   {
      pbyInfBuff = new BYTE [dwInfSize];
      memset (pbyInfBuff, 0, dwInfSize);
      if (pbyInfBuff)
      {
	 if (GetFileVersionInfo (pszAppName, 0, dwInfSize, pbyInfBuff))
	 {
	    if (VerQueryValue (pbyInfBuff,
			       "\\VarFileInfo\\Translation",
			       (void**)(&pdwLangChar),
			       &uSize))
	    {
	       if (VerLanguageName (LOWORD (*pdwLangChar),
				    szResource,
				    sizeof(szResource)))
	       {
		  strncpy (pszLangBuff, szResource, iLangBuffLen);
	       }
	       wsprintf (szResource, "\\StringFileInfo\\%04X%04X\\FileVersion",
			 LOWORD (*pdwLangChar), HIWORD (*pdwLangChar));

	       if (VerQueryValue (pbyInfBuff,
				  szResource,
				  (void**)(&pszVersion),
				  &uSize))
	       {
		  strncpy (pszVerBuff, pszVersion, iVerBuffLen-1);
	       }
	    }
	 }
	 delete [] pbyInfBuff;
      }
   }
}
//------------------------------------------------------------------------------------

