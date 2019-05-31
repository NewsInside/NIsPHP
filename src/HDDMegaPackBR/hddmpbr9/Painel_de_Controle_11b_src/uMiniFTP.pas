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

unit uMiniFTP;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, FileCtrl, StdCtrls, Buttons, ComCtrls, IdFTP, IdFTPList, IdReplyRFC,
  IdBaseComponent, IdComponent, IdTCPConnection, IdTCPClient,
  IdExplicitTLSClientServerBase;

type
  TFrmMiniFTP = class(TForm)
    GroupBox1: TGroupBox;
    GroupBox2: TGroupBox;
    DriveComboBox1: TComboBox;
    DirectoryListBox1: TListBox;
    FileListBox1: TFileListBox;
    BitBtn1: TBitBtn;
    BitBtn2: TBitBtn;
    BitBtn3: TBitBtn;
    ListBox1: TListBox;
    Label1: TLabel;
    StatusBar1: TStatusBar;
    BitBtn4: TBitBtn;
    procedure DriveComboBox1Change(Sender: TObject);
    procedure DirectoryListBox1Change(Sender: TObject);
    procedure BitBtn3Click(Sender: TObject);
    procedure BitBtn1Click(Sender: TObject);
    procedure BitBtn2Click(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure BitBtn4Click(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure FileListBox1DblClick(Sender: TObject);
  private
    { Private declarations }
    procedure AtualizaListaArquivos;
  public
    { Public declarations }
    FTP: TIdFTP;
  end;

var
  FrmMiniFTP: TFrmMiniFTP;

implementation

{$R *.dfm}

procedure DesabilitaBotoes;
var
   i: Integer;
begin
   for i := 0 to FrmMiniFTP.ComponentCount-1 do begin
      if FrmMiniFTP.Components[i] is TControl then begin
         TControl(FrmMiniFTP.Components[i]).Enabled := False;
      end;
   end;
end;

procedure HabilitaBotoes;
var
   i: Integer;
begin
   for i := 0 to FrmMiniFTP.ComponentCount-1 do begin
      if FrmMiniFTP.Components[i] is TControl then begin
         TControl(FrmMiniFTP.Components[i]).Enabled := True;
      end;
   end;
end;

procedure TFrmMiniFTP.BitBtn1Click(Sender: TObject);
var
   k, q: Integer;
begin
   q := FileListBox1.SelCount;

   if q <= 0 then Exit;

   if Application.MessageBox(PChar('Deseja transferir ' + IntToStr(q) + ' arquivo(s) selecionado(s) no PC para o PS2?'), 'Confirmação', MB_YESNO) <> MRYES then Exit;

   Screen.Cursor := crHourGlass;
   DesabilitaBotoes;

   with FileListBox1 do begin
      for k:=0 to Items.Count-1 do begin
         if Selected[k] then begin
            FrmMiniFTP.StatusBar1.SimpleText := 'Copiando ' + Items[k] + ' do PC para o PS2...';
            FrmMiniFTP.StatusBar1.Repaint;

            FTP.Put(IncludeTrailingBackslash(Directory) + Items[k], '/pfs/0/MISC/' + Items[k]);
         end;
      end;
   end;

   AtualizaListaArquivos;

   StatusBar1.SimpleText := 'Pronto!';
   Screen.Cursor := crDefault;
   HabilitaBotoes;
end;

procedure TFrmMiniFTP.BitBtn2Click(Sender: TObject);
var
   k, q: Integer;
begin
   q := ListBox1.SelCount;

   if q <= 0 then Exit;

   if Application.MessageBox(PChar('Deseja transferir ' + IntToStr(q) + ' arquivo(s) selecionado(s) no PS2 para o PC?'), 'Confirmação', MB_YESNO) <> MRYES then Exit;

   Screen.Cursor := crHourGlass;
   DesabilitaBotoes;

   with ListBox1 do begin
      for k:=0 to Items.Count-1 do begin
         if Selected[k] then begin
            FrmMiniFTP.StatusBar1.SimpleText := 'Copiando ' + Items[k] + ' do PS2 para o PC...';
            FrmMiniFTP.StatusBar1.Repaint;

            FTP.Get('/pfs/0/MISC/' + Items[k], IncludeTrailingBackslash(FileListBox1.Directory) + Items[k], true);
         end;
      end;
   end;

   FileListBox1.Update;

   StatusBar1.SimpleText := 'Pronto!';
   Screen.Cursor := crDefault;
   HabilitaBotoes;
end;

procedure TFrmMiniFTP.BitBtn3Click(Sender: TObject);
begin
   Close;
end;

procedure TFrmMiniFTP.BitBtn4Click(Sender: TObject);
var
   k: Integer;
begin
   if ListBox1.SelCount <= 0 then Exit;

   if Application.MessageBox(PChar('Confirma a remoção do(s) arquivo(s) selecionados?'), 'Confirmação', MB_YESNO) <> MRYES then Exit;

   Screen.Cursor := crHourGlass;
   BitBtn4.Enabled := False;

   with ListBox1 do begin
      for k:=0 to Items.Count-1 do begin
         if Selected[k] then begin
            FrmMiniFTP.StatusBar1.SimpleText := 'Deletando o arquivo ' + ListBox1.Items[k] + ' do PS2...';
            FrmMiniFTP.StatusBar1.Repaint;

            FTP.Delete('/pfs/0/MISC/' + ListBox1.Items[k]);
         end;
      end;
   end;

   AtualizaListaArquivos;

   StatusBar1.SimpleText := 'Pronto!';
   StatusBar1.Repaint;
   Screen.Cursor := crDefault;
   BitBtn4.Enabled := True;

end;

procedure TFrmMiniFTP.DirectoryListBox1Change(Sender: TObject);
begin
   //FileListBox1.Directory := DirectoryListBox1.Directory;
end;

procedure TFrmMiniFTP.DriveComboBox1Change(Sender: TObject);
begin
   //DirectoryListBox1.Drive := DriveComboBox1.Drive;
end;

procedure TFrmMiniFTP.AtualizaListaArquivos;
var
   i: Integer;
begin
   try
      FTP.ChangeDir('/pfs/0/MISC');
      FTP.List;
   except
      Application.MessageBox('Não foi possível acessar o conteúdo de "hdd0:__boot/MISC/"', 'Erro', 0);
      Close;
      Exit;
   end;

   ListBox1.Items.Clear;

   for i := 0 to FTP.DirectoryListing.Count-1 do begin
      if (FTP.DirectoryListing.Items[i].FileName <> '.') and (FTP.DirectoryListing.Items[i].FileName <> '..') then begin
         case FTP.DirectoryListing.Items[i].ItemType of
            ditFile: ListBox1.Items.Add(FTP.DirectoryListing.Items[i].FileName);
         end;
      end;
   end;
end;

procedure TFrmMiniFTP.FileListBox1DblClick(Sender: TObject);
begin
   Application.MessageBox(PChar(FileListBox1.FileName), 'Nome do Arquivo:', 0);
end;

procedure TFrmMiniFTP.FormClose(Sender: TObject; var Action: TCloseAction);
begin
   Action := caFree;
end;

procedure TFrmMiniFTP.FormShow(Sender: TObject);
begin
   try
      FTP.MakeDir('/pfs/0/MISC');
   except
   end;

   AtualizaListaArquivos;
end;

end.
