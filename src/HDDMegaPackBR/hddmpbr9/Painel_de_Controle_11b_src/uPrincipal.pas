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

unit uPrincipal;

{$IFDEF FPC}
  {$MODE Delphi}
{$ENDIF}

interface

uses
{$IFnDEF FPC}
  ShellAPI, Windows,
{$ELSE}
  LCLIntf, LCLType, LMessages,
{$ENDIF}
  Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Buttons, CheckLst, IdComponent,
  IdTCPConnection, IdTCPClient, IdFTP, IdExplicitTLSClientServerBase, Menus,
  ComCtrls,
  // Colocados manualmente
  IdFTPList, IdReplyRFC,
  ExtCtrls, ImgList;

type
  TFrmPrincipal = class(TForm)
    grpCurrentlyInstalledPrograms                              : TGroupBox;
    grpProgramsToInstall                                       : TGroupBox;
    grpPS2Connection                                           : TGroupBox;
    grpGetProgramsToInstall                                    : TGroupBox;

    chklstbProgramsToInstall                                   : TCheckListBox;

    lstbInstalledPrograms                                      : TListBox;

    btnOpenCNFFile                                             : TBitBtn;
    btnInstallSelectedPrograms                                 : TBitBtn;
    btnDetails                                                 : TBitBtn;
    btnSelectAll                                               : TBitBtn;
    btnToogleSelection                                         : TBitBtn;
    btnConnect                                                 : TBitBtn;
    btnUninstall                                               : TBitBtn;
    sbtnDown                                                   : TSpeedButton;
    sbtnOrderBy                                                : TSpeedButton;
    sbtnUp                                                     : TSpeedButton;

    MainMenu                                                   : TMainMenu;
    menuTools                                               : TMenuItem;
    menuHelp                                                     : TMenuItem;
    menuAbout                                            : TMenuItem;
    InstalaroDMSHDDExplorernoPS21                              : TMenuItem;
    N1                                                         : TMenuItem;
    menuExit                                                      : TMenuItem;
    InstalaroDMSHDDExplorernoMemoryCard1                       : TMenuItem;
    InstalaroEXPLOIT1                                          : TMenuItem;
    N2                                                         : TMenuItem;
    RemoveroHDDMegaPackBRdoPS21                                : TMenuItem;
    menuUserManual                                            : TMenuItem;
    N3                                                         : TMenuItem;
    MiniFTP                                                   : TMenuItem;

    lblPS2IP                                                   : TLabel;
    lblAuthor                                                  : TLabel;

    edtPS2IP                                                   : TEdit;

    FTP                                                        : TIdFTP;

    StatusBar                                                  : TStatusBar;

    OpenDialogCNF                                              : TOpenDialog;
    SaveDialogAppListDat                                       : TSaveDialog;
    OpenDialogAppListDat                                       : TOpenDialog;

    ImageList1                                                 : TImageList;
    ImageList2                                                 : TImageList;

    procedure FormKeyDown(Sender: TObject; var Key: Word; Shift: TShiftState);
    procedure FormCloseQuery(Sender: TObject; var CanClose: Boolean);
    procedure FormCreate(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure FormShow(Sender: TObject);

    procedure btnConnectClick(Sender: TObject);
    procedure btnOpenCNFFileClick(Sender: TObject);
    procedure btnSelectAllClick(Sender: TObject);
    procedure btnToogleSelectionClick(Sender: TObject);
    procedure btnDetailsClick(Sender: TObject);
    procedure btnInstallSelectedProgramsClick(Sender: TObject);
    procedure btnUninstallClick(Sender: TObject);

    procedure sbtnUpClick(Sender: TObject);
    procedure sbtnDownClick(Sender: TObject);
    procedure sbtnOrderByClick(Sender: TObject);

    procedure chklstbProgramsToInstallDblClick(Sender: TObject);

    procedure menuExitClick(Sender: TObject);
    procedure menuUserManualClick(Sender: TObject);
    procedure menuAboutClick(Sender: TObject);

    procedure lblAuthorClick(Sender: TObject);

    procedure MiniFTPClick(Sender: TObject);

    procedure InstalaroEXPLOIT1Click(Sender: TObject);
    procedure InstalaroDMSHDDExplorernoMemoryCard1Click(Sender: TObject);
    procedure InstalaroDMSHDDExplorernoPS21Click(Sender: TObject);
    procedure RemoveroHDDMegaPackBRdoPS21Click(Sender: TObject);

    procedure FTPWork(ASender: TObject; AWorkMode: TWorkMode;
      AWorkCount: Integer);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  FrmPrincipal: TFrmPrincipal;

function TempPath: String;

implementation

uses uAppList, uInstallCnf, uFrmDetalhePrograma, uFrmInstalaExploit, uFrmSobre,
  uFrmInstalaDEV1, uMiniFTP;

var
   ListaInstalados: TList;
   ListaInstalar: TList;
   Conectado: Boolean;
   Instalando: Boolean;
   boot_encontrada: Boolean;

{$IFnDEF FPC}
  {$R *.dfm}
{$ELSE}
  {$R *.lfm}
{$ENDIF}

procedure AtualizaListaInstalados;
var
   i: Integer;
   Selecionado: Integer;
begin
   Selecionado := FrmPrincipal.lstbInstalledPrograms.ItemIndex;
   FrmPrincipal.lstbInstalledPrograms.Items.Clear;

   for i := 0 to ListaInstalados.Count-1 do begin
      FrmPrincipal.lstbInstalledPrograms.Items.Add(TAppListItem(ListaInstalados[i]).Titulo);
   end;

   if Selecionado < FrmPrincipal.lstbInstalledPrograms.Count then
      FrmPrincipal.lstbInstalledPrograms.ItemIndex := Selecionado;
end;

procedure AtualizaListaInstalar;
var
   i: integer;
   Selecionado: Integer;
begin
   Selecionado := FrmPrincipal.chklstbProgramsToInstall.ItemIndex;
   FrmPrincipal.chklstbProgramsToInstall.Items.Clear;

   for i := 0 to ListaInstalar.Count-1 do begin
      FrmPrincipal.chklstbProgramsToInstall.Items.Add(TAppListItem(ListaInstalar[i]).Titulo);
   end;

   if Selecionado < FrmPrincipal.chklstbProgramsToInstall.Count then
      FrmPrincipal.chklstbProgramsToInstall.ItemIndex := Selecionado;
end;

function ProgramaJaInstalado(Programa: TAppListItem): Boolean;
var
   i: Integer;
begin
   Result := False;

   for i := 0 to ListaInstalados.Count-1 do begin
      if UpperCase(Programa.Diretorio) = UpperCase(TAppListItem(ListaInstalados[i]).Diretorio) then begin
         Result := True;
         Break;
      end;
   end;
end;

function VerificaListaArquivosInstalar(JaInstalados: Boolean): Boolean;
var
   i, j: Integer;
   Item: TAppListItem;
   NomeArquivo: String;
begin
   Result := True;

   for i := 0 to ListaInstalar.Count-1 do begin
      if not FrmPrincipal.chklstbProgramsToInstall.Checked[i] then continue;

      Item := TAppListItem(ListaInstalar[i]);

      if (ProgramaJaInstalado(Item) and JaInstalados) or
         not ProgramaJaInstalado(Item) then begin

         for j := 0 to Item.ListaArquivos.Count-1 do begin
            NomeArquivo := IncludeTrailingBackslash(ExtractFilePath(FrmPrincipal.OpenDialogAppListDat.FileName)) + 'APPS\' + Item.Diretorio + '\' + Item.ListaArquivos[j];

            if not FileExists(NomeArquivo) then begin
               Application.MessageBox(PChar('O arquivo: '#13#10#13#10 + NomeArquivo + #13#10#13#10' não foi encontrado! Processo de instalação abortado!'), 'Erro', 0);
               Result := False;
               Exit;
            end;
         end;

      end;
   end;

end;


function ObtemListaProgramasJaInstalados: String;
var
   i: Integer;
   lista: String;
begin
   lista := '';

   with FrmPrincipal do begin
      for i := 0 to ListaInstalar.Count-1 do begin
         if (chklstbProgramsToInstall.Checked[i]) and (ProgramaJaInstalado(TAppListItem(ListaInstalar[i]))) then begin
            lista := lista + (TAppListItem(ListaInstalar[i]).Titulo + #13#10);
         end;
      end;
   end;

   Result := lista;
end;

function NumItensSelecionados: Integer;
var
   i,n: Integer;
begin
   n := 0;

   for i := 0 to FrmPrincipal.chklstbProgramsToInstall.Count-1 do begin
      if FrmPrincipal.chklstbProgramsToInstall.Checked[i] then Inc(n);
   end;

   Result := n;
end;

procedure DeletaItemListaInstalados(Diretorio: String);
var
   i: Integer;
   Item: TAppListItem;
begin
   for i := 0 to ListaInstalados.Count-1 do begin
      Item := TAppListItem(ListaInstalados[i]);
      if UpperCase(Item.Diretorio) = UpperCase(Diretorio) then begin
         DeletaItem(ListaInstalados, i);
         Break;
      end;
   end;
end;

procedure PreencheLista(FTP: TIdFTP; var ListaArquivos,ListaDiretorios: TStringList; Diretorio: String);
var
   Arquivos: TStringList;
   Diretorios: TStringList;
   i: Integer;
begin
   Arquivos := TStringList.Create;
   Diretorios := TStringList.Create;

   try
      FTP.ChangeDir(diretorio);
      FTP.List;
   except
      Exit;
   end;

   for i := 0 to FTP.DirectoryListing.Count-1 do begin
      if (FTP.DirectoryListing.Items[i].FileName <> '.') and (FTP.DirectoryListing.Items[i].FileName <> '..') then begin
         case FTP.DirectoryListing.Items[i].ItemType of
            ditFile: Arquivos.Add(FTP.DirectoryListing.Items[i].FileName);
            ditDirectory: Diretorios.Add(FTP.DirectoryListing.Items[i].FileName);
         end;
      end;
   end;

   for i := 0 to Diretorios.Count-1 do begin
      PreencheLista(FTP, ListaArquivos, ListaDiretorios, FTP.RetrieveCurrentDir + Diretorios[i]);
   end;

   for i := 0 to Arquivos.Count-1 do begin
      ListaArquivos.Add(FTP.RetrieveCurrentDir + Arquivos[i]);
   end;

   ListaDiretorios.Add(FTP.RetrieveCurrentDir);


   FTP.ChangeDirUp;

   Arquivos.Free;
   Diretorios.Free;
end;

procedure DeletaDiretorio(FTP: TIdFTP; diretorio: String);
var
   ListaArquivos: TStringList;
   ListaDiretorios: TStringList;
   i: Integer;
begin
   ListaArquivos := TStringList.Create;
   ListaDiretorios := TStringList.Create;

   PreencheLista(FTP, ListaArquivos, ListaDiretorios, diretorio);

   // Apaga os arquivos encontrados
   for i := 0 to ListaArquivos.Count-1 do begin
      FTP.Delete(ListaArquivos[i]);
   end;

   // Apaga os diretorios encontrados
   for i := 0 to ListaDiretorios.Count-1 do begin
      FTP.RemoveDir(ListaDiretorios[i]);
   end;

   ListaArquivos.Free;
   ListaDiretorios.Free;
end;

function TempPath: String;
const tempDirGlobal = false;
begin
   Result := GetTempDir( tempDirGlobal );
end;

procedure InstalaProgramas(FTP: TIdFTP; AtualizaInstalados: Boolean);
var
   i, j, n: Integer;
   Programa: TAppListItem;
   JaInstalado: Boolean;
   InstalarPrograma: Boolean;
begin
   n := 1;

   for i := 0 to ListaInstalar.Count-1 do begin
      if not FrmPrincipal.chklstbProgramsToInstall.Checked[i] then Continue;

      Programa := TAppListItem(ListaInstalar[i]);
      JaInstalado := ProgramaJaInstalado(Programa);

      InstalarPrograma := (not JaInstalado) or (JaInstalado and AtualizaInstalados);

      if not InstalarPrograma then Continue;

      FrmPrincipal.StatusBar.SimpleText := 'Instalando: ' + Programa.Titulo + '... (' + IntToStr(n) + ' de ' + IntToStr(NumItensSelecionados) + ')';
      FrmPrincipal.StatusBar.Repaint;

      // Primeira Parte - Atualizar lista de programas instalados:
      if JaInstalado then
         DeletaItemListaInstalados(Programa.Diretorio);

      ListaInstalados.Add(TAppListItem.Create(Programa.Titulo, Programa.Autor, Programa.Descricao, Programa.Executavel));

      // Segunda parte: FTP!!!
      if JaInstalado then
         DeletaDiretorio(FTP, '/pfs/0/' + Programa.Diretorio);

      try
         FTP.MakeDir('/pfs/0/' + Programa.Diretorio);
      Except
         on E: EIdReplyRFCError do begin
            //if E.Message <> 'Command successful.' then raise;
         end;
      end;

      for j := 0 to Programa.ListaArquivos.Count-1 do begin
         FTP.Put(IncludeTrailingBackslash(ExtractFilePath(FrmPrincipal.OpenDialogAppListDat.FileName)) + 'APPS\' + Programa.Diretorio + '\' + Programa.ListaArquivos[j], '/pfs/0/' + Programa.Diretorio + '/' + Programa.ListaArquivos[j]);
      end;

      CriaUninstallCnf(Programa, TempPath + 'uninstall.cnf');
      FTP.Put(TempPath + 'uninstall.cnf', '/pfs/0/' + Programa.Diretorio + '/uninstall.cnf');

      Inc(n);
   end;

   //OrdenaLista(ListaInstalados);

   FrmPrincipal.StatusBar.SimpleText := 'Atualizando lista de programas instalados...';
   FrmPrincipal.StatusBar.Repaint;

   SalvaAppList(ListaInstalados, TempPath + 'APPLIST.DAT');
   FTP.Put(TempPath + 'APPLIST.DAT', '/pfs/0/APPLIST.DAT');

   AtualizaListaInstalados;

   FrmPrincipal.StatusBar.SimpleText := 'Pronto!';
   FrmPrincipal.StatusBar.Repaint;
end;

procedure DesabilitaOpcoes;
begin
   with FrmPrincipal do begin
      //btnOpenCNFFile.Enabled := False;
      btnInstallSelectedPrograms.Enabled := False;
      btnDetails.Enabled := False;
      //btnSelectAll.Enabled := False;
      btnUninstall.Enabled := False;
      // Habilita digitação de novo IP
      edtPS2IP.Enabled := True;
      // Menus
      InstalaroDMSHDDExplorernoMemoryCard1.Enabled := False;
      InstalaroDMSHDDExplorernoPS21.Enabled := False;
      InstalaroEXPLOIT1.Enabled := False;
      RemoveroHDDMegaPackBRdoPS21.Enabled := False;
      MiniFTP.Enabled := False;
   end;
end;

procedure HabilitaOpcoes;
begin
   with FrmPrincipal do begin
      //btnOpenCNFFile.Enabled := True;
      if boot_encontrada then btnInstallSelectedPrograms.Enabled := True
      else btnInstallSelectedPrograms.Enabled := False;

      btnDetails.Enabled := True;
      //btnSelectAll.Enabled := True;
      btnUninstall.Enabled := True;
      // Desabilita digitação de novo IP
      edtPS2IP.Enabled := False;
      // Menus
      InstalaroDMSHDDExplorernoMemoryCard1.Enabled := True;

      if boot_encontrada then InstalaroDMSHDDExplorernoPS21.Enabled := True
      else InstalaroDMSHDDExplorernoPS21.Enabled := False;

      InstalaroEXPLOIT1.Enabled := True;

      if boot_encontrada then RemoveroHDDMegaPackBRdoPS21.Enabled := True
      else RemoveroHDDMegaPackBRdoPS21.Enabled := False;

      if boot_encontrada then MiniFTP.Enabled := True
      else MiniFTP.Enabled := False;
   end;
end;

procedure RemoverHDDMegaPackBR(FTP: TIdFTP);
var
   DiretoriosRaiz: TStringList;
   ArquivosRaiz: TStringList;
   i: Integer;
begin
   DiretoriosRaiz := TStringList.Create;
   ArquivosRaiz := TStringList.Create;

   FrmPrincipal.StatusBar.SimpleText := 'Acessando partição __boot...';
   FrmPrincipal.StatusBar.Repaint;

   try
      FTP.ChangeDir('/pfs/0');
      FTP.List;
   except
      Application.MessageBox('Não foi possível acessar a partição __boot', 'Erro', 0);
      FrmPrincipal.StatusBar.SimpleText := 'Pronto!';
      FrmPrincipal.StatusBar.Repaint;
      Exit;
   end;

   FrmPrincipal.StatusBar.SimpleText := 'Removendo o HDD MegaPack BR do PS2...';
   FrmPrincipal.StatusBar.Repaint;

   FrmPrincipal.btnConnect.Enabled := False;
   Screen.Cursor := crHourGlass;

   for i := 0 to FTP.DirectoryListing.Count-1 do begin
      if (FTP.DirectoryListing.Items[i].FileName <> '.') and (FTP.DirectoryListing.Items[i].FileName <> '..') then begin
         case FTP.DirectoryListing.Items[i].ItemType of
            ditFile: ArquivosRaiz.Add(FTP.RetrieveCurrentDir + FTP.DirectoryListing.Items[i].FileName);
            ditDirectory: DiretoriosRaiz.Add(FTP.RetrieveCurrentDir + FTP.DirectoryListing.Items[i].FileName);
         end;
      end;
   end;

   // Apaga os arquivos encontrados
   for i := 0 to ArquivosRaiz.Count-1 do begin
      FTP.Delete(ArquivosRaiz[i]);
   end;

   // Apaga diretorios
   for i := 0 to DiretoriosRaiz.Count-1 do begin
      DeletaDiretorio(FTP, DiretoriosRaiz[i]);
   end;

   FrmPrincipal.StatusBar.SimpleText := 'Atualizando lista de programas instalados...';
   FrmPrincipal.StatusBar.Repaint;


   // Limpa lista de programas instalados
   ListaInstalados.Clear;

   //// Cria novo APPLIST.DAT vazio e envia pro PS2
   //SalvaAppList(ListaInstalados, TempPath + '_APPLIST.DAT');
   //FTP.Put(TempPath + '_APPLIST.DAT', '/pfs/0/APPLIST.DAT');

   AtualizaListaInstalados;

   DiretoriosRaiz.Free;
   ArquivosRaiz.Free;

   FrmPrincipal.btnConnect.Enabled := True;
   Screen.Cursor := crDefault;
   FrmPrincipal.StatusBar.SimpleText := 'Pronto!';
   FrmPrincipal.StatusBar.Repaint;


   Application.MessageBox('HDD MegaPack BR desinstalado com sucesso!', 'Mensagem', 0);
end;


procedure TFrmPrincipal.btnConnectClick(Sender: TObject);
begin
   if Instalando then Exit;

   if Trim(edtPS2IP.Text) = '' then begin
      Application.MessageBox('Informe um endereço IP válido!', 'Atenção', 0);
      edtPS2IP.SetFocus;
      Exit;
   end;

   if not Conectado then begin
         StatusBar.SimpleText := 'Conectando a ' + edtPS2IP.Text + '...';
         StatusBar.Repaint;
         FTP.Host := edtPS2IP.Text;
         FTP.UseHOST := False;
         try
            FTP.Connect;
         Except
         on E: Exception do begin
            Application.MessageBox(PChar('Não foi possível conectar ao PS2! Verifique as conexões de rede, bem como as configurações!' + Chr(13)+Chr(10)+Chr(13)+Chr(10) + E.Message), 'Erro', 0);
            StatusBar.SimpleText := 'Pronto!';
            StatusBar.Repaint;
            Exit;
         end;
      end;

      boot_encontrada := True;

      try
         StatusBar.SimpleText := 'Montando partição __boot...';
         StatusBar.Repaint;

         FTP.SendCmd('SITE UMNT /pfs/0/');
         FTP.SendCmd('SITE MNT /pfs/0/ hdd:__boot');

         FTP.ChangeDir('/pfs/0');
         FTP.List;
      Except
         on E: Exception do begin
            Application.MessageBox('Não foi possível acessar a partição __boot! Verifique se o HDD está conectado e formatado adequadamente!'+#13#10#13#10+'Algumas funcionalidades estarão indisponíveis!', 'Atenção', 0);
            //StatusBar.SimpleText := 'Pronto!';
            //StatusBar.Repaint;
            //FTP.Quit;
            //Exit;
            boot_encontrada := False;
         end;
      end;

      try
         StatusBar.SimpleText := 'Obtendo lista de programas instalados...';
         StatusBar.Repaint;
         FTP.Get('/pfs/0/APPLIST.DAT', TempPath + '_APPLIST.DAT', True);
         AbreAppList(ListaInstalados, TempPath + '_APPLIST.DAT');
         AtualizaListaInstalados;
      Except
         //on E: Exception do begin
         //   Application.MessageBox('Não foi possível obter a lista de programas instalados (APPLIST.DAT)!', 'Erro', 0);
         //   StatusBar.SimpleText := 'Pronto!';
         //   StatusBar.Repaint;
         //   FTP.Quit;
         //   Exit;
         //end;
         ListaInstalados.Clear;
         AtualizaListaInstalados;
      end;

      StatusBar.SimpleText := 'Pronto!';
      StatusBar.Repaint;
      Conectado := True;
      btnConnect.Caption := '&Desconectar';
      btnConnect.Default := False;
      btnConnect.Glyph := nil;
      ImageList1.GetBitmap(1, btnConnect.Glyph);
      HabilitaOpcoes;
   end else begin
      try
         FTP.SendCmd('SITE UMNT /pfs/0/');
         FTP.Quit;
      except
      end;

      Conectado := False;
      ListaInstalados.Clear;
      AtualizaListaInstalados;
      chklstbProgramsToInstall.Clear;
      btnConnect.Caption := '&Conectar';
      btnConnect.Default := True;
      btnConnect.Glyph := nil;
      ImageList1.GetBitmap(0, btnConnect.Glyph);
      DesabilitaOpcoes;
   end;
end;


procedure TFrmPrincipal.btnOpenCNFFileClick(Sender: TObject);
begin
   if Instalando then Exit;

   OpenDialogCNF.InitialDir := ExtractFilePath(Application.ExeName) + 'MEGAPACK\';
   if OpenDialogCNF.Execute then begin
      AbreInstallCnf(ListaInstalar, OpenDialogCNF.FileName);
      AtualizaListaInstalar;
   end;
end;

procedure TFrmPrincipal.btnInstallSelectedProgramsClick(Sender: TObject);
var
   ListaJaInstalados: String;
   AtualizarJaInstalados: Boolean;
begin
   if Instalando then Exit;

   if chklstbProgramsToInstall.Count < 1 then begin
      Application.MessageBox('Você precisa, primeiramente, abrir uma lista de arquivos a serem instalados (INSTALL.CNF)!', 'Atenção', 0);
      btnOpenCNFFile.SetFocus;
      Exit;
   end;

   if NumItensSelecionados < 1 then begin
      Application.MessageBox('Você precisa selecionar, pelo menos, um programa para ser instalado!', 'Atenção', 0);
      chklstbProgramsToInstall.SetFocus;
      Exit;
   end;

   ListaJaInstalados := ObtemListaProgramasJaInstalados;

   AtualizarJaInstalados := False;
   if ListaJaInstalados <> '' then begin
      if Application.MessageBox(PChar('Os seguintes programas já estão instalados:'#13#10#13#10 + ListaJaInstalados + #13#10'Deseja atualizá-los para os programas selecionados?'), 'Atenção', MB_YESNO + MB_DEFBUTTON2) = MRYES then
         AtualizarJaInstalados := True;
   end;

   if not VerificaListaArquivosInstalar(AtualizarJaInstalados) then Exit;

   if Application.MessageBox('Confirma a instalação dos programas selecionados?', 'Confirmação', MB_YESNO + MB_DEFBUTTON2) <> MRYES then Exit;

   Screen.Cursor := crHourGlass;
   btnInstallSelectedPrograms.Enabled := False;
   btnConnect.Enabled := False;
   lstbInstalledPrograms.Enabled := False;
   chklstbProgramsToInstall.Enabled := False;
   Instalando := True;

   InstalaProgramas(FTP, AtualizarJaInstalados);

   Screen.Cursor := crDefault;
   btnInstallSelectedPrograms.Enabled := True;
   btnConnect.Enabled := True;
   lstbInstalledPrograms.Enabled := True;
   chklstbProgramsToInstall.Enabled := True;
   Instalando := False;

   Application.MessageBox(PChar('Processo de instalação concluído com sucesso!' + #13#13 + 'Caso essa seja a primeira instalação após uma formatação do HDD ou uma remoção completa do HDD MegPack BR do PS2, não se esqueça de instalar o DMS HDD Explorer através da opção ''Instalar o DMS HDD Explorer no HDD (DEV2)'' no menu ''Ferramentas'''), 'Mensagem', 0);   
end;

procedure TFrmPrincipal.btnDetailsClick(Sender: TObject);
begin
   if Instalando then Exit;
   
   if lstbInstalledPrograms.ItemIndex > -1 then begin
      Application.CreateForm(TFrmDetalhePrograma, FrmDetalhePrograma);
      FrmDetalhePrograma.Edit1.Text := TAppListItem(ListaInstalados[lstbInstalledPrograms.ItemIndex]).Titulo;
      FrmDetalhePrograma.Edit2.Text := TAppListItem(ListaInstalados[lstbInstalledPrograms.ItemIndex]).Autor;
      FrmDetalhePrograma.Memo1.Lines.Text := TAppListItem(ListaInstalados[lstbInstalledPrograms.ItemIndex]).Descricao;
      FrmDetalhePrograma.Edit3.Text := TAppListItem(ListaInstalados[lstbInstalledPrograms.ItemIndex]).Executavel;
      FrmDetalhePrograma.Item := TAppListItem(ListaInstalados[lstbInstalledPrograms.ItemIndex]);
      FrmDetalhePrograma.ShowModal;

      if FrmDetalhePrograma.ModalResult = MrOK then begin
         // Envia atualizações
         //AtualizaListaInstalados;
         btnConnect.Enabled := False;
         Screen.Cursor := crHourGlass;

         StatusBar.SimpleText := 'Atualizando lista...';
         StatusBar.Repaint;

         SalvaAppList(ListaInstalados, TempPath + 'APPLIST.DAT');
         FTP.Put(TempPath + 'APPLIST.DAT', '/pfs/0/APPLIST.DAT');

         AtualizaListaInstalados;

         btnConnect.Enabled := True;
         Screen.Cursor := crDefault;

         StatusBar.SimpleText := 'Pronto!';
         StatusBar.Repaint;
      end;

      FrmDetalhePrograma.Free;
   end;
end;

procedure TFrmPrincipal.btnSelectAllClick(Sender: TObject);
var
   i: Integer;
begin
   if Instalando then Exit;

   for i := 0 to chklstbProgramsToInstall.Count-1 do begin
      chklstbProgramsToInstall.Checked[i] := True;
   end;

end;

procedure TFrmPrincipal.btnToogleSelectionClick(Sender: TObject);
var
   i: Integer;
begin
   if Instalando then Exit;

   for i := 0 to chklstbProgramsToInstall.Count-1 do begin
      chklstbProgramsToInstall.Checked[i] := not chklstbProgramsToInstall.Checked[i];
   end;

end;
procedure TFrmPrincipal.btnUninstallClick(Sender: TObject);
begin
   if Instalando then Exit;

   if lstbInstalledPrograms.ItemIndex > -1 then begin
      if Application.MessageBox('Confirma a desinstalação do programa selecionado?', 'Confirmação', MB_YESNO + MB_DEFBUTTON2) <> MRYES then Exit;

      Screen.Cursor := crHourGlass;
      btnUninstall.Enabled := False;
      btnConnect.Enabled := False;

      StatusBar.SimpleText := 'Desinstalando: ' + TAppListItem(ListaInstalados[lstbInstalledPrograms.ItemIndex]).Titulo + '...';
      StatusBar.Repaint;

      DeletaDiretorio(FTP, '/pfs/0/' + TAppListItem(ListaInstalados[lstbInstalledPrograms.ItemIndex]).Diretorio);
      DeletaItem(ListaInstalados, lstbInstalledPrograms.ItemIndex);

      SalvaAppList(ListaInstalados, TempPath + 'APPLIST.DAT');
      FTP.Put(TempPath + 'APPLIST.DAT', '/pfs/0/APPLIST.DAT');

      AtualizaListaInstalados;

      StatusBar.SimpleText := 'Pronto!';
      StatusBar.Repaint;

      Screen.Cursor := crDefault;
      btnUninstall.Enabled := True;
      btnConnect.Enabled := True;
   end;
end;

procedure TFrmPrincipal.chklstbProgramsToInstallDblClick(Sender: TObject);
begin
   if chklstbProgramsToInstall.ItemIndex > -1 then begin
      Application.CreateForm(TFrmDetalhePrograma, FrmDetalhePrograma);
      FrmDetalhePrograma.Edit1.ReadOnly := True;
      FrmDetalhePrograma.Edit2.ReadOnly := True;
      FrmDetalhePrograma.Memo1.ReadOnly := True;
      FrmDetalhePrograma.Edit3.ReadOnly := True;
      FrmDetalhePrograma.BitBtn2.Enabled := False;

      FrmDetalhePrograma.Edit1.Text := TAppListItem(ListaInstalar[chklstbProgramsToInstall.ItemIndex]).Titulo;
      FrmDetalhePrograma.Edit2.Text := TAppListItem(ListaInstalar[chklstbProgramsToInstall.ItemIndex]).Autor;
      FrmDetalhePrograma.Memo1.Lines.Text := TAppListItem(ListaInstalar[chklstbProgramsToInstall.ItemIndex]).Descricao;
      FrmDetalhePrograma.Edit3.Text := TAppListItem(ListaInstalar[chklstbProgramsToInstall.ItemIndex]).Executavel;
      FrmDetalhePrograma.ShowModal;
      FrmDetalhePrograma.Free;
   end;
end;

procedure TFrmPrincipal.FormClose(Sender: TObject; var Action: TCloseAction);
begin
   if Conectado then begin
      try
         FTP.SendCmd('SITE UMNT /pfs/0/');
         FTP.Quit;
      Except
      end;
   end;
end;

procedure TFrmPrincipal.FormCloseQuery(Sender: TObject; var CanClose: Boolean);
begin
   if Instalando then begin
      CanClose := False;
      Exit;
   end;

   if Application.MessageBox('Deseja mesmo sair do programa?', 'Confirmação', MB_YESNO + MB_DEFBUTTON2) = MRYES then
      CanClose := True
   else
      CanClose := False;
end;

procedure TFrmPrincipal.FormCreate(Sender: TObject);
begin
   ListaInstalados := Tlist.Create;
   ListaInstalar := TList.Create;
   Conectado := False;
   Instalando := False;
end;

procedure TFrmPrincipal.FormKeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
   if Key = VK_ESCAPE then Close;
end;

procedure TFrmPrincipal.FormShow(Sender: TObject);
begin
   edtPS2IP.SelectAll;
end;

procedure TFrmPrincipal.FTPWork(ASender: TObject; AWorkMode: TWorkMode;
  AWorkCount: Integer);
begin
   FrmPrincipal.Repaint;
   Application.ProcessMessages;
end;

procedure TFrmPrincipal.InstalaroDMSHDDExplorernoMemoryCard1Click(
  Sender: TObject);
var
   Programa: String;
begin
   if Instalando then Exit;

   Application.CreateForm(TFrmInstalaDEV1, FrmInstalaDEV1);
   FrmInstalaDEV1.ShowModal;

   if FrmInstalaDEV1.ModalResult <> mrOK then begin
      FrmInstalaDEV1.Free;
      Exit;
   end;

   if FrmInstalaDEV1.RadioButton1.Checked then
      Programa := 'DMS/BOOT.ELF'
   else
      Programa := 'EXPLOIT/BOOT.ELF';

   FrmInstalaDEV1.Free;

   Screen.Cursor := crHourGlass;
   btnConnect.Enabled := False;

   StatusBar.SimpleText := 'Instalando DEV1 no Memory Card...';
   StatusBar.Repaint;
   Instalando := True;

   try
      FTP.MakeDir('/mc/0/BOOT');
   except
   end;

   try
      FTP.Put(ExtractFilePath(Application.ExeName) + Programa , '/mc/0/BOOT/BOOT.ELF');
   except
      on E: Exception do begin
         Application.MessageBox(PChar('Falha ao instalar DEV1 no Memory Card:'#13#10#13#10 + E.Message), 'Erro', 0);
         StatusBar.SimpleText := 'Pronto!';
         StatusBar.Repaint;
         Screen.Cursor := crDefault;
         btnConnect.Enabled := True;
         Instalando := False;
         Exit;
      end;
   end;

   StatusBar.SimpleText := 'Pronto!';
   StatusBar.Repaint;

   Screen.Cursor := crDefault;
   btnConnect.Enabled := True;
   Instalando := False;

   Application.MessageBox('DEV1 instalado com sucesso no Memory Card', 'Mensagem', 0);
end;

procedure TFrmPrincipal.InstalaroDMSHDDExplorernoPS21Click(Sender: TObject);
begin
   if Instalando then Exit;

   if Application.MessageBox('Confirma a instalação do DMS HDD Explorer no HDD (DEV2)?', 'Confirmação', MB_YESNO + MB_DEFBUTTON2) <> MRYES then
      Exit;

   Screen.Cursor := crHourGlass;
   btnConnect.Enabled := False;
   Instalando := True;

   StatusBar.SimpleText := 'Instalando DEV2 no Hard Disk Drive (HDD)...';
   StatusBar.Repaint;

   try
      FTP.Put(ExtractFilePath(Application.ExeName) + 'DMS/BOOT.ELF' , '/pfs/0/boot.elf');
   except
      on E: Exception do begin
         Application.MessageBox(PChar('Falha ao instalar DEV2 no HDD:'#13#10#13#10 + E.Message), 'Erro', 0);
         StatusBar.SimpleText := 'Pronto!';
         StatusBar.Repaint;
         Screen.Cursor := crDefault;
         btnConnect.Enabled := True;
         Instalando := False;
         Exit;
      end;
   end;

   StatusBar.SimpleText := 'Pronto!';
   StatusBar.Repaint;
   Instalando := False;

   Screen.Cursor := crDefault;
   btnConnect.Enabled := True;

   Application.MessageBox('DEV2 instalado com sucesso no HDD', 'Mensagem', 0);
end;

procedure TFrmPrincipal.InstalaroEXPLOIT1Click(Sender: TObject);
begin
   if Instalando then Exit;

   Application.CreateForm(TFrmInstalaExploit, FrmInstalaExploit);
   FrmInstalaExploit.FTP := FTP;
   FrmInstalaExploit.ShowModal;
end;

procedure TFrmPrincipal.lblAuthorClick(Sender: TObject);
begin
   OpenURL('http://www.brunofreitas.com/'); { *Converted from ShellExecute* }
end;

procedure TFrmPrincipal.menuUserManualClick(Sender: TObject);
begin
    OpenDocument(PChar(ExtractFilePath(Application.ExeName) + 'manual.pdf')); { *Converted from ShellExecute* }
end;

procedure TFrmPrincipal.MiniFTPClick(Sender: TObject);
begin
   if Instalando then Exit;

   Application.CreateForm(TFrmMiniFTP, FrmMiniFTP);
   FrmMiniFTP.FTP := FTP;
   FrmMiniFTP.ShowModal;
end;

procedure TFrmPrincipal.RemoveroHDDMegaPackBRdoPS21Click(Sender: TObject);
begin
   if Instalando then Exit;

   if Application.MessageBox('Essa operação irá ELIMINAR TOTALMENTE o HDD MegaPack BR do seu PS2! Deseja prosseguir?', 'ATENÇÃO!!!', MB_YESNO + MB_DEFBUTTON2) <> MRYES then
      Exit;

   Instalando := True;
   RemoverHDDMegaPackBR(FTP);
   Instalando := False;
end;

procedure TFrmPrincipal.menuExitClick(Sender: TObject);
begin
   if Instalando then Exit;

   Close;
end;

procedure TFrmPrincipal.menuAboutClick(Sender: TObject);
begin
   if Instalando then Exit;

   Application.CreateForm(TFrmSobre, FrmSobre);
   FrmSobre.ShowModal;
end;

procedure TFrmPrincipal.sbtnDownClick(Sender: TObject);
begin
   if Instalando then Exit;

   if lstbInstalledPrograms.ItemIndex <> -1 then begin
      if lstbInstalledPrograms.ItemIndex < lstbInstalledPrograms.Items.Count-1 then begin
         btnConnect.Enabled := False;
         sbtnDown.Enabled := False;

         StatusBar.SimpleText := 'Atualizando lista...';
         StatusBar.Repaint;

         ListaInstalados.Exchange(lstbInstalledPrograms.ItemIndex, lstbInstalledPrograms.ItemIndex+1);

         SalvaAppList(ListaInstalados, TempPath + 'APPLIST.DAT');
         FTP.Put(TempPath + 'APPLIST.DAT', '/pfs/0/APPLIST.DAT');

         AtualizaListaInstalados;
         lstbInstalledPrograms.ItemIndex := lstbInstalledPrograms.ItemIndex + 1;
         
         StatusBar.SimpleText := 'Pronto!';
         StatusBar.Repaint;

         btnConnect.Enabled := True;
         sbtnDown.Enabled := True;
      end;
   end;
end;

procedure TFrmPrincipal.sbtnOrderByClick(Sender: TObject);
begin
   if Instalando then Exit;

   if lstbInstalledPrograms.Items.Count < 1 then Exit;

   btnConnect.Enabled := False;
   sbtnOrderBy.Enabled := False;

   StatusBar.SimpleText := 'Atualizando lista...';
   StatusBar.Repaint;

   OrdenaLista(ListaInstalados);

   SalvaAppList(ListaInstalados, TempPath + 'APPLIST.DAT');
   FTP.Put(TempPath + 'APPLIST.DAT', '/pfs/0/APPLIST.DAT');

   AtualizaListaInstalados;

   StatusBar.SimpleText := 'Pronto!';
   StatusBar.Repaint;

   btnConnect.Enabled := True;
   sbtnOrderBy.Enabled := True;
end;

procedure TFrmPrincipal.sbtnUpClick(Sender: TObject);
begin
   if Instalando then Exit;

   if lstbInstalledPrograms.ItemIndex <> -1 then begin
      if lstbInstalledPrograms.ItemIndex > 0 then begin
         btnConnect.Enabled := False;
         sbtnUp.Enabled := False;

         StatusBar.SimpleText := 'Atualizando lista...';
         StatusBar.Repaint;

         ListaInstalados.Exchange(lstbInstalledPrograms.ItemIndex, lstbInstalledPrograms.ItemIndex-1);

         SalvaAppList(ListaInstalados, TempPath + 'APPLIST.DAT');
         FTP.Put(TempPath + 'APPLIST.DAT', '/pfs/0/APPLIST.DAT');

         AtualizaListaInstalados;
         lstbInstalledPrograms.ItemIndex := lstbInstalledPrograms.ItemIndex - 1;

         StatusBar.SimpleText := 'Pronto!';
         StatusBar.Repaint;

         btnConnect.Enabled := True;
         sbtnUp.Enabled := True;
      end;
   end;
end;

end.
