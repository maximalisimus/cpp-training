//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <conio.h>

#pragma hdrstop

//---------------------------------------------------------------------------

#pragma argsused
int main(int argc, char* argv[])
{
  //printf("list of printers:\n");
  AnsiString s="";
  TPrinter *Prntr = new TPrinter();
  for(int i=0;i<Prntr->Printers->Count;++i){
       s =   Prntr->Printers->Strings[i];
       printf("%s\n", s.c_str());
  }
  return 0;
}
//---------------------------------------------------------------------------
  
 
