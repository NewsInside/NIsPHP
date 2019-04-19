{
HDD MegaPack BR 9 - Painel de Controle
Copyright (c) 2007 Bruno Freitas
bootsector@ig.com.br

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
}

unit uFrmDetalhePrograma;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Buttons, uAppList;

type
  TFrmDetalhePrograma = class(TForm)
    GroupBox1: TGroupBox;
    Label1: TLabel;
    Edit1: TEdit;
    Label2: TLabel;
    Edit2: TEdit;
    Label3: TLabel;
    Memo1: TMemo;
    Label4: TLabel;
    Edit3: TEdit;
    BitBtn1: TBitBtn;
    BitBtn2: TBitBtn;
    procedure BitBtn2Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
    Item: TAppListItem;
  end;

var
  FrmDetalhePrograma: TFrmDetalhePrograma;

implementation


{$R *.dfm}

procedure TFrmDetalhePrograma.BitBtn2Click(Sender: TObject);
begin
   if Trim(Edit1.Text) = '' then begin
      Application.MessageBox('Você precisa especificar o Título do programa!', 'Atenção', 0);
      Edit1.SetFocus;
      Exit;
   end;

   if Trim(Edit2.Text) = '' then begin
      Application.MessageBox('Você precisa especificar o Autor do programa!', 'Atenção', 0);
      Edit2.SetFocus;
      Exit;
   end;

   if Trim(Memo1.Lines.Text) = '' then begin
      Application.MessageBox('Você precisa especificar a Descrição do programa!', 'Atenção', 0);
      Memo1.SetFocus;
      Exit;
   end;

   ModalResult := mrOK;

   Item.Titulo := Edit1.Text;
   Item.Autor := Edit2.Text;
   Item.Descricao := Memo1.Lines.Text;
   Item.Executavel := Edit3.Text;
end;

end.
