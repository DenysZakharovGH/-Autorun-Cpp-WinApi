
#include <vcl.h>
#pragma hdrstop
#include "Unit2.h"
#include "Unit1.h"
#include "Unit1.cpp"
#include <iostream>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
LPCSTR UserChoice;
HKEY HkeyUserChoice = NULL;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
        Button5->Hide();
        Panel2->Hide();
        Button5->DisableAlign();
        Form2->RadioButton1->Checked = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button1Click(TObject *Sender)
{
        Form2->Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button4Click(TObject *Sender)
{
        OpenDialog1->Execute();
                Form2->Edit1->Text = OpenDialog1->FileName;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button2Click(TObject *Sender)
{
        Panel1->Hide();
        Panel2->Show();
        Button2->Hide();
        Button5->Show();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button3Click(TObject *Sender)
{
        Panel2->Hide();
        Panel1->Show();
        Button5->Hide();
        Button2->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button5Click(TObject *Sender)
{
        HKEY hKey = NULL;
        LONG lResult = 0;
        TCHAR szExeName[MAX_PATH+1];

        strcpy(szExeName,OpenDialog1->FileName.c_str());

        lResult = RegOpenKeyEx(
                HkeyUserChoice,
                UserChoice,
                0,
                KEY_ALL_ACCESS,
                &hKey);

        if(ERROR_SUCCESS == lResult)
        {
                RegSetValueEx(
                        hKey,
                        ExtractFileName(OpenDialog1->FileName).c_str(),
                        0,
                        REG_SZ,
                        (PBYTE)szExeName,
                        lstrlen(szExeName)*sizeof(TCHAR) + 1);

                RegCloseKey(hKey);

                Form2->Close();
                ShowQueryKey();
        }//if(ERROR_SUCCESS == lResult)
}
//---------------------------------------------------------------------------
//HKEY_LOCAL_MACHINE\\...\\Run

void __fastcall TForm2::RadioButton1Click(TObject *Sender)
{
        UserChoice ="Software\\Microsoft\\Windows\\CurrentVersion\\Run";
        HkeyUserChoice = HKEY_CURRENT_USER;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::RadioButton2Click(TObject *Sender)
{
        UserChoice ="Software\\Microsoft\\Windows\\CurrentVersion\\RunOnce";
        HkeyUserChoice = HKEY_CURRENT_USER;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::RadioButton3Click(TObject *Sender)
{
        UserChoice ="SOFTWARE\\WOW6432Node\\Microsoft\\Windows\\CurrentVersion\\Run";
        HkeyUserChoice = HKEY_LOCAL_MACHINE;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::RadioButton4Click(TObject *Sender)
{
        UserChoice ="SOFTWARE\\WOW6432Node\\Microsoft\\Windows\\CurrentVersion\\RunOnce";
        HkeyUserChoice = HKEY_LOCAL_MACHINE;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Edit1Change(TObject *Sender)
{
        Form2->Button2->Enabled=true;               
}
//---------------------------------------------------------------------------

