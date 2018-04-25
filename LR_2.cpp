#include <vcl.h>
#pragma hdrstop

#include <vcl.h>
#pragma hdrstop

#include "LR_2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
AnsiString MyFName="";
void __fastcall TForm1::N1Click(TObject *Sender)
{
  if(MyFName!="")
     Memo1->Lines->SaveToFile(MyFName);
   else
     if(SaveDialog1->Execute())
     {
       MyFName=SaveDialog1->FileName;
       Memo1->Lines->SaveToFile(SaveDialog1->FileName);
     }

}
//---------------------------------------------------------------------------
void __fastcall TForm1::N2Click(TObject *Sender)
{
 SaveDialog1->FileName=MyFName;
  if(SaveDialog1->Execute())
   {
     MyFName=SaveDialog1->FileName;
     Memo1->Lines->SaveToFile(SaveDialog1->FileName);
   }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N3Click(TObject *Sender)
{
if(OpenDialog1->Execute())
   {
     MyFName=OpenDialog1->FileName;
     RichEdit1->Lines->LoadFromFile(OpenDialog1->FileName);
   }
}
//---------------------------------------------------------------------------
int f=0;
void __fastcall TForm1::Button1Click(TObject *Sender)
{
 Memo1->Clear(); RichEdit1->Clear();
 LabeledEdit1->Clear(); LabeledEdit2->Clear(); 
 Memo1->SetFocus(); f=1;
}
//---------------------------------------------------------------------------
//Функция поиска слова word в строке str. В случае успеха
//возвращает номер позиции в строке, с которой начинается слово
int FindWord(char*str,char*word)
{ unsigned ls=strlen(str);
  for(unsigned i=0;i<ls;i++)
  { bool find=true;
    char*w=word;  int k=i;
    if(str[i]==*w)
    { while(*w) if(*w++!=str[k++])
      { find=false; break;}
//если в строке str есть слово word, то выход из цикла while - 
//по завершающему нулевому символу слова word в позиции i
      if(find) return k-strlen(word);} //вычитаем длину слова word
  }
  return -1;
}
//----------------------------------------------
int k1,k2;
unsigned l1,l2;
void __fastcall TForm1::Button2Click(TObject *Sender)
{
   Memo1->Lines->Add("НАЙТИ:");
   l1=LabeledEdit1->SelLength;//находим длину выделенного первого слова
//вызов функции FindWord() с преобразованием строк 
// типа AnsiString к типу char* 
   if((k1=FindWord(RichEdit1->Text.c_str(),
                  LabeledEdit1->SelText.c_str()))>=0) //искомое слово выделено
           {Memo1->Lines->Add("Первое слово - с позиции "+IntToStr(k1+1));
           RichEdit1->SelStart=k1; //ставим курсор перед первым словом 
           RichEdit1->SelLength=l1; //выделяем первое слово
           RichEdit1->SelAttributes->Style=
                RichEdit1->SelAttributes->Style<<fsBold;  //жирный шрифт
           RichEdit1->SelStart=k1+l1;}  //ставим курсор после первого слова
                                                           //для сохранения выделения
       else Memo1->Lines->Add("Нет первого слова!");
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
    l2=LabeledEdit2->SelLength;//находим длину выделенного второго слова
//вызов функции FindWord() с преобразованием строк 
// типа AnsiString к типу char* 
    if((k2=FindWord(RichEdit1->Text.c_str(),
                  LabeledEdit2->SelText.c_str()))>=0)  //искомое слово выделено
           {Memo1->Lines->Add("Второе слово - с позиции "+IntToStr(k2+1));
           RichEdit1->SelStart=k2;  //ставим курсор перед вторым словом
           RichEdit1->SelLength=l2;  //выделяем второе слово
           RichEdit1->SelAttributes->Style=
                RichEdit1->SelAttributes->Style<<fsBold;  //жирный шрифт
           RichEdit1->SelStart=k1+l2;}  //ставим курсор после второго слова
                                                           //для сохранения выделения  
       else Memo1->Lines->Add("Нет второго слова!");
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button4Click(TObject *Sender)
{
 AnsiString s="";  //строка для обмена
  unsigned d=0;    //беззнаковое целое для обмена
  if(k1>k2){  //условие неправильного порядка следования слов
            Memo1->Lines->Add("");
            Memo1->Lines->Add("УПОРЯДОЧИТЬ:");
            d=k1; k1=k2; k2=d;
            d=l1; l1=l2; l2=d;
            s=LabeledEdit1->Text;
            LabeledEdit1->Text=LabeledEdit2->Text;
            LabeledEdit2->Text=s;
            Memo1->Lines->Add("Первое слово - с позиции "+IntToStr(k1+1));
            Memo1->Lines->Add("Второе слово - с позиции "+IntToStr(k2+1));}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button5Click(TObject *Sender)
{
 if(k1>=0&&k2>=0&&f){  //проверяем, в тексте ли слова
     f=0; Memo1->Lines->Add("");
     Memo1->Lines->Add("ПОМЕНЯТЬ МЕСТАМИ:");
     RichEdit1->SelStart=k1;
     RichEdit1->SelLength=l1;
//ставим второе слово на место выделенного первого слова
     RichEdit1->SetSelTextBuf(LabeledEdit2->Text.c_str());
     RichEdit1->SelStart=k2+(l2-l1);
     RichEdit1->SelLength=l2;
//ставим первое слово на место выделенного второго слова
     RichEdit1->SetSelTextBuf(LabeledEdit1->Text.c_str());
     Memo1->Lines->Add("Второе слово - с позиции "+IntToStr(k1+1));
     Memo1->Lines->Add("Первое слово - с позиции "+
IntToStr(k2+1+(l2-l1)));}
}
//---------------------------------------------------------------------------


