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

{$IFDEF FPC}
  {$MODE Delphi}
{$ENDIF}

interface

uses
{$IFnDEF FPC}
  Windows,
{$ELSE}
  LCLIntf, LCLType, LMessages,
{$ENDIF}
  Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, FileCtrl, StdCtrls, Buttons, ComCtrls, IdFTP, IdFTPList;

type

  { TFrmMiniFTP }

  TFrmMiniFTP = class(TForm)
    grpMyComputer: TGroupBox;
    grpPS2: TGroupBox;
    lstbMyComputerFiles: TFileListBox;
    btnSendToRight: TBitBtn;
    btnSendToLeft: TBitBtn;
    btnClose: TBitBtn;
    lstbPS2Files: TListBox;
    lblPS2Content: TLabel;
    dlgLocalDirSelect: TSelectDirectoryDialog;
    btnChooseDir: TSpeedButton;
    txtLocalDir: TStaticText;
    StatusBar: TStatusBar;
    btnPS2DeleteFiles: TBitBtn;
    procedure btnChooseDirClick(Sender: TObject);
    procedure btnCloseClick(Sender: TObject);
    procedure btnSendToRightClick(Sender: TObject);
    procedure btnSendToLeftClick(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure btnPS2DeleteFilesClick(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure lstbMyComputerFilesDblClick(Sender: TObject);
    procedure grpMyComputerClick(Sender: TObject);
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

{$IFnDEF FPC}
  {$R *.dfm}
{$ELSE}
  {$R *.lfm}
{$ENDIF}

uses uFileAndDriveUtils;

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

procedure TFrmMiniFTP.btnSendToRightClick(Sender: TObject);
var
   k, q: Integer;
begin
   q := lstbMyComputerFiles.SelCount;

   if q <= 0 then Exit;

   if Application.MessageBox(PChar('Deseja transferir ' + IntToStr(q) + ' arquivo(s) selecionado(s) no PC para o PS2?'), 'Confirmação', MB_YESNO) <> MRYES then Exit;

   Screen.Cursor := crHourGlass;
   DesabilitaBotoes;

   with lstbMyComputerFiles do begin
      for k:=0 to Items.Count-1 do begin
         if Selected[k] then begin
            FrmMiniFTP.StatusBar.SimpleText := 'Copiando ' + Items[k] + ' do PC para o PS2...';
            FrmMiniFTP.StatusBar.Repaint;

            FTP.Put(IncludeTrailingBackslash(Directory) + Items[k], '/pfs/0/MISC/' + Items[k]);
         end;
      end;
   end;

   AtualizaListaArquivos;

   StatusBar.SimpleText := 'Pronto!';
   Screen.Cursor := crDefault;
   HabilitaBotoes;
end;

procedure TFrmMiniFTP.btnSendToLeftClick(Sender: TObject);
var
   k, q: Integer;
begin
   q := lstbPS2Files.SelCount;

   if q <= 0 then Exit;

   if Application.MessageBox(PChar('Deseja transferir ' + IntToStr(q) + ' arquivo(s) selecionado(s) no PS2 para o PC?'), 'Confirmação', MB_YESNO) <> MRYES then Exit;

   Screen.Cursor := crHourGlass;
   DesabilitaBotoes;

   with lstbPS2Files do begin
      for k:=0 to Items.Count-1 do begin
         if Selected[k] then begin
            FrmMiniFTP.StatusBar.SimpleText := 'Copiando ' + Items[k] + ' do PS2 para o PC...';
            FrmMiniFTP.StatusBar.Repaint;

            FTP.Get('/pfs/0/MISC/' + Items[k], IncludeTrailingBackslash(lstbMyComputerFiles.Directory) + Items[k], true);
         end;
      end;
   end;

   lstbMyComputerFiles.Update;

   StatusBar.SimpleText := 'Pronto!';
   Screen.Cursor := crDefault;
   HabilitaBotoes;
end;

procedure TFrmMiniFTP.btnCloseClick(Sender: TObject);
begin
   Close;
end;

procedure TFrmMiniFTP.btnPS2DeleteFilesClick(Sender: TObject);
var
   k: Integer;
begin
   if lstbPS2Files.SelCount <= 0 then Exit;

   if Application.MessageBox(PChar('Confirma a remoção do(s) arquivo(s) selecionados?'), 'Confirmação', MB_YESNO) <> MRYES then Exit;

   Screen.Cursor := crHourGlass;
   btnPS2DeleteFiles.Enabled := False;

   with lstbPS2Files do begin
      for k:=0 to Items.Count-1 do begin
         if Selected[k] then begin
            FrmMiniFTP.StatusBar.SimpleText := 'Deletando o arquivo ' + lstbPS2Files.Items[k] + ' do PS2...';
            FrmMiniFTP.StatusBar.Repaint;

            FTP.Delete('/pfs/0/MISC/' + lstbPS2Files.Items[k]);
         end;
      end;
   end;

   AtualizaListaArquivos;

   StatusBar.SimpleText := 'Pronto!';
   StatusBar.Repaint;
   Screen.Cursor := crDefault;
   btnPS2DeleteFiles.Enabled := True;

end;

procedure TFrmMiniFTP.btnChooseDirClick(Sender: TObject);
begin
   if dlgLocalDirSelect.Execute = true then
   begin
      txtLocalDir.Caption := dlgLocalDirSelect.FileName;
      lstbMyComputerFiles.Directory:= dlgLocalDirSelect.FileName;
      lstbMyComputerFiles.UpdateFileList;
   end;
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

   lstbPS2Files.Items.Clear;

   for i := 0 to FTP.DirectoryListing.Count-1 do begin
      if (FTP.DirectoryListing.Items[i].FileName <> '.') and (FTP.DirectoryListing.Items[i].FileName <> '..') then begin
         case FTP.DirectoryListing.Items[i].ItemType of
            ditFile: lstbPS2Files.Items.Add(FTP.DirectoryListing.Items[i].FileName);
         end;
      end;
   end;
end;

procedure TFrmMiniFTP.lstbMyComputerFilesDblClick(Sender: TObject);
begin
   Application.MessageBox(PChar(lstbMyComputerFiles.FileName), 'Nome do Arquivo:', 0);
end;

procedure TFrmMiniFTP.grpMyComputerClick(Sender: TObject);
begin

end;

procedure TFrmMiniFTP.FormClose(Sender: TObject; var Action: TCloseAction);
begin
   Action := caFree;
end;

procedure TFrmMiniFTP.FormShow(Sender: TObject);
begin
   try
      //FTP.MakeDir('/pfs/0/MISC');
   except
   end;

   txtLocalDir.Caption := '';
end;

end.
