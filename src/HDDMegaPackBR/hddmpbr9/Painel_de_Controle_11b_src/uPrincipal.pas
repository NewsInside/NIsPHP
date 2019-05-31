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

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Buttons, CheckLst, IdBaseComponent, IdComponent,
  IdTCPConnection, IdTCPClient, IdExplicitTLSClientServerBase, IdFTP, Menus,
  ComCtrls,
  // Colocados manualmente
  IdFTPList, IdReplyRFC,
  ExtCtrls, ImgList, ShellAPI;

type
  TFrmPrincipal = class(TForm)
    GroupBox1: TGroupBox;
    GroupBox2: TGroupBox;
    CheckListBox1: TCheckListBox;
    ListBox1: TListBox;
    GroupBox3: TGroupBox;
    Label1: TLabel;
    Edit1: TEdit;
    BitBtn1: TBitBtn;
    GroupBox4: TGroupBox;
    BitBtn2: TBitBtn;
    BitBtn3: TBitBtn;
    Label2: TLabel;
    BitBtn4: TBitBtn;
    BitBtn5: TBitBtn;
    BitBtn6: TBitBtn;
    FTP: TIdFTP;
    MainMenu1: TMainMenu;
    Ferramentas1: TMenuItem;
    Sobre1: TMenuItem;
    Sobreoprograma1: TMenuItem;
    InstalaroDMSHDDExplorernoPS21: TMenuItem;
    N1: TMenuItem;
    Sair1: TMenuItem;
    StatusBar1: TStatusBar;
    OpenDialog1: TOpenDialog;
    BitBtn7: TBitBtn;
    ImageList1: TImageList;
    InstalaroDMSHDDExplorernoMemoryCard1: TMenuItem;
    InstalaroEXPLOIT1: TMenuItem;
    SaveDialog1: TSaveDialog;
    OpenDialog2: TOpenDialog;
    N2: TMenuItem;
    RemoveroHDDMegaPackBRdoPS21: TMenuItem;
    ImageList2: TImageList;
    SpeedButton1: TSpeedButton;
    SpeedButton2: TSpeedButton;
    SpeedButton3: TSpeedButton;
    Manualdousurio1: TMenuItem;
    N3: TMenuItem;
    MiniFTP1: TMenuItem;
    procedure FormKeyDown(Sender: TObject; var Key: Word; Shift: TShiftState);
    procedure FormCloseQuery(Sender: TObject; var CanClose: Boolean);
    procedure BitBtn1Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure BitBtn2Click(Sender: TObject);
    procedure BitBtn5Click(Sender: TObject);
    procedure BitBtn6Click(Sender: TObject);
    procedure BitBtn4Click(Sender: TObject);
    procedure CheckListBox1DblClick(Sender: TObject);
    procedure BitBtn3Click(Sender: TObject);
    procedure Sair1Click(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure BitBtn7Click(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure InstalaroEXPLOIT1Click(Sender: TObject);
    procedure InstalaroDMSHDDExplorernoMemoryCard1Click(Sender: TObject);
    procedure InstalaroDMSHDDExplorernoPS21Click(Sender: TObject);
    procedure RemoveroHDDMegaPackBRdoPS21Click(Sender: TObject);
    procedure Sobreoprograma1Click(Sender: TObject);
    procedure SpeedButton3Click(Sender: TObject);
    procedure SpeedButton1Click(Sender: TObject);
    procedure SpeedButton2Click(Sender: TObject);
    procedure Label2Click(Sender: TObject);
    procedure FTPWork(ASender: TObject; AWorkMode: TWorkMode;
      AWorkCount: Integer);
    procedure Manualdousurio1Click(Sender: TObject);
    procedure MiniFTP1Click(Sender: TObject);
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

{$R *.dfm}

procedure AtualizaListaInstalados;
var
   i: Integer;
   Selecionado: Integer;
begin
   Selecionado := FrmPrincipal.ListBox1.ItemIndex;
   FrmPrincipal.ListBox1.Items.Clear;

   for i := 0 to ListaInstalados.Count-1 do begin
      FrmPrincipal.ListBox1.Items.Add(TAppListItem(ListaInstalados[i]).Titulo);
   end;

   if Selecionado < FrmPrincipal.ListBox1.Count then
      FrmPrincipal.ListBox1.ItemIndex := Selecionado;
end;

procedure AtualizaListaInstalar;
var
   i: integer;
   Selecionado: Integer;
begin
   Selecionado := FrmPrincipal.CheckListBox1.ItemIndex;
   FrmPrincipal.CheckListBox1.Items.Clear;

   for i := 0 to ListaInstalar.Count-1 do begin
      FrmPrincipal.CheckListBox1.Items.Add(TAppListItem(ListaInstalar[i]).Titulo);
   end;

   if Selecionado < FrmPrincipal.CheckListBox1.Count then
      FrmPrincipal.CheckListBox1.ItemIndex := Selecionado;
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
      if not FrmPrincipal.CheckListBox1.Checked[i] then continue;

      Item := TAppListItem(ListaInstalar[i]);

      if (ProgramaJaInstalado(Item) and JaInstalados) or
         not ProgramaJaInstalado(Item) then begin

         for j := 0 to Item.ListaArquivos.Count-1 do begin
            NomeArquivo := IncludeTrailingBackslash(ExtractFilePath(FrmPrincipal.OpenDialog1.FileName)) + 'APPS\' + Item.Diretorio + '\' + Item.ListaArquivos[j];

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
         if (CheckListBox1.Checked[i]) and (ProgramaJaInstalado(TAppListItem(ListaInstalar[i]))) then begin
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

   for i := 0 to FrmPrincipal.CheckListBox1.Count-1 do begin
      if FrmPrincipal.CheckListBox1.Checked[i] then Inc(n);
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
var
   path: array[0..MAX_PATH] of Char;
begin
   GetTempPath(SizeOf(path), @path);
   Result := StrPas(path);
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
      if not FrmPrincipal.CheckListBox1.Checked[i] then Continue;

      Programa := TAppListItem(ListaInstalar[i]);
      JaInstalado := ProgramaJaInstalado(Programa);

      InstalarPrograma := (not JaInstalado) or (JaInstalado and AtualizaInstalados);

      if not InstalarPrograma then Continue;

      FrmPrincipal.StatusBar1.SimpleText := 'Instalando: ' + Programa.Titulo + '... (' + IntToStr(n) + ' de ' + IntToStr(NumItensSelecionados) + ')';
      FrmPrincipal.StatusBar1.Repaint;

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
         FTP.Put(IncludeTrailingBackslash(ExtractFilePath(FrmPrincipal.OpenDialog1.FileName)) + 'APPS\' + Programa.Diretorio + '\' + Programa.ListaArquivos[j], '/pfs/0/' + Programa.Diretorio + '/' + Programa.ListaArquivos[j]);
      end;

      CriaUninstallCnf(Programa, TempPath + 'uninstall.cnf');
      FTP.Put(TempPath + 'uninstall.cnf', '/pfs/0/' + Programa.Diretorio + '/uninstall.cnf');

      Inc(n);
   end;

   //OrdenaLista(ListaInstalados);

   FrmPrincipal.StatusBar1.SimpleText := 'Atualizando lista de programas instalados...';
   FrmPrincipal.StatusBar1.Repaint;

   SalvaAppList(ListaInstalados, TempPath + 'APPLIST.DAT');
   FTP.Put(TempPath + 'APPLIST.DAT', '/pfs/0/APPLIST.DAT');

   AtualizaListaInstalados;

   FrmPrincipal.StatusBar1.SimpleText := 'Pronto!';
   FrmPrincipal.StatusBar1.Repaint;
end;

procedure DesabilitaOpcoes;
begin
   with FrmPrincipal do begin
      //BitBtn2.Enabled := False;
      BitBtn3.Enabled := False;
      BitBtn4.Enabled := False;
      //BitBtn5.Enabled := False;
      BitBtn7.Enabled := False;
      // Habilita digitação de novo IP
      Edit1.Enabled := True;
      // Menus
      InstalaroDMSHDDExplorernoMemoryCard1.Enabled := False;
      InstalaroDMSHDDExplorernoPS21.Enabled := False;
      InstalaroEXPLOIT1.Enabled := False;
      RemoveroHDDMegaPackBRdoPS21.Enabled := False;
      MiniFTP1.Enabled := False;
   end;
end;

procedure HabilitaOpcoes;
begin
   with FrmPrincipal do begin
      //BitBtn2.Enabled := True;
      if boot_encontrada then BitBtn3.Enabled := True
      else BitBtn3.Enabled := False;

      BitBtn4.Enabled := True;
      //BitBtn5.Enabled := True;
      BitBtn7.Enabled := True;
      // Desabilita digitação de novo IP
      Edit1.Enabled := False;
      // Menus
      InstalaroDMSHDDExplorernoMemoryCard1.Enabled := True;

      if boot_encontrada then InstalaroDMSHDDExplorernoPS21.Enabled := True
      else InstalaroDMSHDDExplorernoPS21.Enabled := False;

      InstalaroEXPLOIT1.Enabled := True;

      if boot_encontrada then RemoveroHDDMegaPackBRdoPS21.Enabled := True
      else RemoveroHDDMegaPackBRdoPS21.Enabled := False;

      if boot_encontrada then MiniFTP1.Enabled := True
      else MiniFTP1.Enabled := False;
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

   FrmPrincipal.StatusBar1.SimpleText := 'Acessando partição __boot...';
   FrmPrincipal.StatusBar1.Repaint;

   try
      FTP.ChangeDir('/pfs/0');
      FTP.List;
   except
      Application.MessageBox('Não foi possível acessar a partição __boot', 'Erro', 0);
      FrmPrincipal.StatusBar1.SimpleText := 'Pronto!';
      FrmPrincipal.StatusBar1.Repaint;
      Exit;
   end;

   FrmPrincipal.StatusBar1.SimpleText := 'Removendo o HDD MegaPack BR do PS2...';
   FrmPrincipal.StatusBar1.Repaint;

   FrmPrincipal.BitBtn1.Enabled := False;
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

   FrmPrincipal.StatusBar1.SimpleText := 'Atualizando lista de programas instalados...';
   FrmPrincipal.StatusBar1.Repaint;


   // Limpa lista de programas instalados
   ListaInstalados.Clear;

   //// Cria novo APPLIST.DAT vazio e envia pro PS2
   //SalvaAppList(ListaInstalados, TempPath + '_APPLIST.DAT');
   //FTP.Put(TempPath + '_APPLIST.DAT', '/pfs/0/APPLIST.DAT');

   AtualizaListaInstalados;

   DiretoriosRaiz.Free;
   ArquivosRaiz.Free;

   FrmPrincipal.BitBtn1.Enabled := True;
   Screen.Cursor := crDefault;
   FrmPrincipal.StatusBar1.SimpleText := 'Pronto!';
   FrmPrincipal.StatusBar1.Repaint;


   Application.MessageBox('HDD MegaPack BR desinstalado com sucesso!', 'Mensagem', 0);
end;


procedure TFrmPrincipal.BitBtn1Click(Sender: TObject);
begin
   if Instalando then Exit;

   if Trim(Edit1.Text) = '' then begin
      Application.MessageBox('Informe um endereço IP válido!', 'Atenção', 0);
      Edit1.SetFocus;
      Exit;
   end;

   if not Conectado then begin
      try
         StatusBar1.SimpleText := 'Conectando a ' + Edit1.Text + '...';
         StatusBar1.Repaint;
         FTP.Host := Edit1.Text;
         FTP.Connect;
      Except
         on E: Exception do begin
            Application.MessageBox('Não foi possível conectar ao PS2! Verifique as conexões de rede, bem como as configurações!', 'Erro', 0);
            StatusBar1.SimpleText := 'Pronto!';
            StatusBar1.Repaint;
            Exit;
         end;
      end;

      boot_encontrada := True;

      try
         StatusBar1.SimpleText := 'Montando partição __boot...';
         StatusBar1.Repaint;

         FTP.SendCmd('SITE UMNT /pfs/0/');
         FTP.SendCmd('SITE MNT /pfs/0/ hdd:__boot');

         FTP.ChangeDir('/pfs/0');
         FTP.List;
      Except
         on E: Exception do begin
            Application.MessageBox('Não foi possível acessar a partição __boot! Verifique se o HDD está conectado e formatado adequadamente!'+#13#10#13#10+'Algumas funcionalidades estarão indisponíveis!', 'Atenção', 0);
            //StatusBar1.SimpleText := 'Pronto!';
            //StatusBar1.Repaint;
            //FTP.Quit;
            //Exit;
            boot_encontrada := False;
         end;
      end;

      try
         StatusBar1.SimpleText := 'Obtendo lista de programas instalados...';
         StatusBar1.Repaint;
         FTP.Get('/pfs/0/APPLIST.DAT', TempPath + '_APPLIST.DAT', True);
         AbreAppList(ListaInstalados, TempPath + '_APPLIST.DAT');
         AtualizaListaInstalados;
      Except
         //on E: Exception do begin
         //   Application.MessageBox('Não foi possível obter a lista de programas instalados (APPLIST.DAT)!', 'Erro', 0);
         //   StatusBar1.SimpleText := 'Pronto!';
         //   StatusBar1.Repaint;
         //   FTP.Quit;
         //   Exit;
         //end;
         ListaInstalados.Clear;
         AtualizaListaInstalados;
      end;

      StatusBar1.SimpleText := 'Pronto!';
      StatusBar1.Repaint;
      Conectado := True;
      BitBtn1.Caption := '&Desconectar';
      BitBtn1.Default := False;
      BitBtn1.Glyph := nil;
      ImageList1.GetBitmap(1, BitBtn1.Glyph);
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
      CheckListBox1.Clear;
      BitBtn1.Caption := '&Conectar';
      BitBtn1.Default := True;
      BitBtn1.Glyph := nil;
      ImageList1.GetBitmap(0, BitBtn1.Glyph);
      DesabilitaOpcoes;
   end;
end;


procedure TFrmPrincipal.BitBtn2Click(Sender: TObject);
begin
   if Instalando then Exit;

   OpenDialog1.InitialDir := ExtractFilePath(Application.ExeName) + 'MEGAPACK\';
   if OpenDialog1.Execute then begin
      AbreInstallCnf(ListaInstalar, OpenDialog1.FileName);
      AtualizaListaInstalar;
   end;
end;

procedure TFrmPrincipal.BitBtn3Click(Sender: TObject);
var
   ListaJaInstalados: String;
   AtualizarJaInstalados: Boolean;
begin
   if Instalando then Exit;

   if CheckListBox1.Count < 1 then begin
      Application.MessageBox('Você precisa, primeiramente, abrir uma lista de arquivos a serem instalados (INSTALL.CNF)!', 'Atenção', 0);
      BitBtn2.SetFocus;
      Exit;
   end;

   if NumItensSelecionados < 1 then begin
      Application.MessageBox('Você precisa selecionar, pelo menos, um programa para ser instalado!', 'Atenção', 0);
      CheckListBox1.SetFocus;
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
   BitBtn3.Enabled := False;
   BitBtn1.Enabled := False;
   ListBox1.Enabled := False;
   CheckListBox1.Enabled := False;
   Instalando := True;

   InstalaProgramas(FTP, AtualizarJaInstalados);

   Screen.Cursor := crDefault;
   BitBtn3.Enabled := True;
   BitBtn1.Enabled := True;
   ListBox1.Enabled := True;
   CheckListBox1.Enabled := True;
   Instalando := False;

   Application.MessageBox(PChar('Processo de instalação concluído com sucesso!' + #13#13 + 'Caso essa seja a primeira instalação após uma formatação do HDD ou uma remoção completa do HDD MegPack BR do PS2, não se esqueça de instalar o DMS HDD Explorer através da opção ''Instalar o DMS HDD Explorer no HDD (DEV2)'' no menu ''Ferramentas'''), 'Mensagem', 0);   
end;

procedure TFrmPrincipal.BitBtn4Click(Sender: TObject);
begin
   if Instalando then Exit;
   
   if ListBox1.ItemIndex > -1 then begin
      Application.CreateForm(TFrmDetalhePrograma, FrmDetalhePrograma);
      FrmDetalhePrograma.Edit1.Text := TAppListItem(ListaInstalados[ListBox1.ItemIndex]).Titulo;
      FrmDetalhePrograma.Edit2.Text := TAppListItem(ListaInstalados[ListBox1.ItemIndex]).Autor;
      FrmDetalhePrograma.Memo1.Lines.Text := TAppListItem(ListaInstalados[ListBox1.ItemIndex]).Descricao;
      FrmDetalhePrograma.Edit3.Text := TAppListItem(ListaInstalados[ListBox1.ItemIndex]).Executavel;
      FrmDetalhePrograma.Item := TAppListItem(ListaInstalados[ListBox1.ItemIndex]);
      FrmDetalhePrograma.ShowModal;

      if FrmDetalhePrograma.ModalResult = MrOK then begin
         // Envia atualizações
         //AtualizaListaInstalados;
         BitBtn1.Enabled := False;
         Screen.Cursor := crHourGlass;

         StatusBar1.SimpleText := 'Atualizando lista...';
         StatusBar1.Repaint;

         SalvaAppList(ListaInstalados, TempPath + 'APPLIST.DAT');
         FTP.Put(TempPath + 'APPLIST.DAT', '/pfs/0/APPLIST.DAT');

         AtualizaListaInstalados;

         BitBtn1.Enabled := True;
         Screen.Cursor := crDefault;

         StatusBar1.SimpleText := 'Pronto!';
         StatusBar1.Repaint;
      end;

      FrmDetalhePrograma.Free;
   end;
end;

procedure TFrmPrincipal.BitBtn5Click(Sender: TObject);
var
   i: Integer;
begin
   if Instalando then Exit;

   for i := 0 to CheckListBox1.Count-1 do begin
      CheckListBox1.Checked[i] := True;
   end;

end;

procedure TFrmPrincipal.BitBtn6Click(Sender: TObject);
var
   i: Integer;
begin
   if Instalando then Exit;

   for i := 0 to CheckListBox1.Count-1 do begin
      CheckListBox1.Checked[i] := not CheckListBox1.Checked[i];
   end;

end;
procedure TFrmPrincipal.BitBtn7Click(Sender: TObject);
begin
   if Instalando then Exit;

   if ListBox1.ItemIndex > -1 then begin
      if Application.MessageBox('Confirma a desinstalação do programa selecionado?', 'Confirmação', MB_YESNO + MB_DEFBUTTON2) <> MRYES then Exit;

      Screen.Cursor := crHourGlass;
      BitBtn7.Enabled := False;
      BitBtn1.Enabled := False;

      StatusBar1.SimpleText := 'Desinstalando: ' + TAppListItem(ListaInstalados[ListBox1.ItemIndex]).Titulo + '...';
      StatusBar1.Repaint;

      DeletaDiretorio(FTP, '/pfs/0/' + TAppListItem(ListaInstalados[ListBox1.ItemIndex]).Diretorio);
      DeletaItem(ListaInstalados, ListBox1.ItemIndex);

      SalvaAppList(ListaInstalados, TempPath + 'APPLIST.DAT');
      FTP.Put(TempPath + 'APPLIST.DAT', '/pfs/0/APPLIST.DAT');

      AtualizaListaInstalados;

      StatusBar1.SimpleText := 'Pronto!';
      StatusBar1.Repaint;

      Screen.Cursor := crDefault;
      BitBtn7.Enabled := True;
      BitBtn1.Enabled := True;
   end;
end;

procedure TFrmPrincipal.CheckListBox1DblClick(Sender: TObject);
begin
   if CheckListBox1.ItemIndex > -1 then begin
      Application.CreateForm(TFrmDetalhePrograma, FrmDetalhePrograma);
      FrmDetalhePrograma.Edit1.ReadOnly := True;
      FrmDetalhePrograma.Edit2.ReadOnly := True;
      FrmDetalhePrograma.Memo1.ReadOnly := True;
      FrmDetalhePrograma.Edit3.ReadOnly := True;
      FrmDetalhePrograma.BitBtn2.Enabled := False;

      FrmDetalhePrograma.Edit1.Text := TAppListItem(ListaInstalar[CheckListBox1.ItemIndex]).Titulo;
      FrmDetalhePrograma.Edit2.Text := TAppListItem(ListaInstalar[CheckListBox1.ItemIndex]).Autor;
      FrmDetalhePrograma.Memo1.Lines.Text := TAppListItem(ListaInstalar[CheckListBox1.ItemIndex]).Descricao;
      FrmDetalhePrograma.Edit3.Text := TAppListItem(ListaInstalar[CheckListBox1.ItemIndex]).Executavel;
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
   Edit1.SelectAll;
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
   BitBtn1.Enabled := False;

   StatusBar1.SimpleText := 'Instalando DEV1 no Memory Card...';
   StatusBar1.Repaint;
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
         StatusBar1.SimpleText := 'Pronto!';
         StatusBar1.Repaint;
         Screen.Cursor := crDefault;
         BitBtn1.Enabled := True;
         Instalando := False;
         Exit;
      end;
   end;

   StatusBar1.SimpleText := 'Pronto!';
   StatusBar1.Repaint;

   Screen.Cursor := crDefault;
   BitBtn1.Enabled := True;
   Instalando := False;

   Application.MessageBox('DEV1 instalado com sucesso no Memory Card', 'Mensagem', 0);
end;

procedure TFrmPrincipal.InstalaroDMSHDDExplorernoPS21Click(Sender: TObject);
begin
   if Instalando then Exit;

   if Application.MessageBox('Confirma a instalação do DMS HDD Explorer no HDD (DEV2)?', 'Confirmação', MB_YESNO + MB_DEFBUTTON2) <> MRYES then
      Exit;

   Screen.Cursor := crHourGlass;
   BitBtn1.Enabled := False;
   Instalando := True;

   StatusBar1.SimpleText := 'Instalando DEV2 no Hard Disk Drive (HDD)...';
   StatusBar1.Repaint;

   try
      FTP.Put(ExtractFilePath(Application.ExeName) + 'DMS/BOOT.ELF' , '/pfs/0/boot.elf');
   except
      on E: Exception do begin
         Application.MessageBox(PChar('Falha ao instalar DEV2 no HDD:'#13#10#13#10 + E.Message), 'Erro', 0);
         StatusBar1.SimpleText := 'Pronto!';
         StatusBar1.Repaint;
         Screen.Cursor := crDefault;
         BitBtn1.Enabled := True;
         Instalando := False;
         Exit;
      end;
   end;

   StatusBar1.SimpleText := 'Pronto!';
   StatusBar1.Repaint;
   Instalando := False;

   Screen.Cursor := crDefault;
   BitBtn1.Enabled := True;

   Application.MessageBox('DEV2 instalado com sucesso no HDD', 'Mensagem', 0);
end;

procedure TFrmPrincipal.InstalaroEXPLOIT1Click(Sender: TObject);
begin
   if Instalando then Exit;

   Application.CreateForm(TFrmInstalaExploit, FrmInstalaExploit);
   FrmInstalaExploit.FTP := FTP;
   FrmInstalaExploit.ShowModal;
end;

procedure TFrmPrincipal.Label2Click(Sender: TObject);
begin
   ShellExecute(Application.MainForm.Handle, Nil, 'http://www.brunofreitas.com/', '', '', SW_SHOWMAXIMIZED);
end;

procedure TFrmPrincipal.Manualdousurio1Click(Sender: TObject);
begin
   ShellExecute(Application.MainForm.Handle, Nil, PChar(ExtractFilePath(Application.ExeName) + 'manual.pdf'), '', '', SW_SHOWMAXIMIZED);
end;

procedure TFrmPrincipal.MiniFTP1Click(Sender: TObject);
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

procedure TFrmPrincipal.Sair1Click(Sender: TObject);
begin
   if Instalando then Exit;

   Close;
end;

procedure TFrmPrincipal.Sobreoprograma1Click(Sender: TObject);
begin
   if Instalando then Exit;

   Application.CreateForm(TFrmSobre, FrmSobre);
   FrmSobre.ShowModal;
end;

procedure TFrmPrincipal.SpeedButton1Click(Sender: TObject);
begin
   if Instalando then Exit;

   if ListBox1.ItemIndex <> -1 then begin
      if ListBox1.ItemIndex < ListBox1.Items.Count-1 then begin
         BitBtn1.Enabled := False;
         SpeedButton1.Enabled := False;

         StatusBar1.SimpleText := 'Atualizando lista...';
         StatusBar1.Repaint;

         ListaInstalados.Exchange(ListBox1.ItemIndex, ListBox1.ItemIndex+1);

         SalvaAppList(ListaInstalados, TempPath + 'APPLIST.DAT');
         FTP.Put(TempPath + 'APPLIST.DAT', '/pfs/0/APPLIST.DAT');

         AtualizaListaInstalados;
         ListBox1.ItemIndex := ListBox1.ItemIndex + 1;
         
         StatusBar1.SimpleText := 'Pronto!';
         StatusBar1.Repaint;

         BitBtn1.Enabled := True;
         SpeedButton1.Enabled := True;
      end;
   end;
end;

procedure TFrmPrincipal.SpeedButton2Click(Sender: TObject);
begin
   if Instalando then Exit;

   if ListBox1.Items.Count < 1 then Exit;

   BitBtn1.Enabled := False;
   SpeedButton2.Enabled := False;

   StatusBar1.SimpleText := 'Atualizando lista...';
   StatusBar1.Repaint;

   OrdenaLista(ListaInstalados);

   SalvaAppList(ListaInstalados, TempPath + 'APPLIST.DAT');
   FTP.Put(TempPath + 'APPLIST.DAT', '/pfs/0/APPLIST.DAT');

   AtualizaListaInstalados;

   StatusBar1.SimpleText := 'Pronto!';
   StatusBar1.Repaint;

   BitBtn1.Enabled := True;
   SpeedButton2.Enabled := True;
end;

procedure TFrmPrincipal.SpeedButton3Click(Sender: TObject);
begin
   if Instalando then Exit;

   if ListBox1.ItemIndex <> -1 then begin
      if ListBox1.ItemIndex > 0 then begin
         BitBtn1.Enabled := False;
         SpeedButton3.Enabled := False;

         StatusBar1.SimpleText := 'Atualizando lista...';
         StatusBar1.Repaint;

         ListaInstalados.Exchange(ListBox1.ItemIndex, ListBox1.ItemIndex-1);

         SalvaAppList(ListaInstalados, TempPath + 'APPLIST.DAT');
         FTP.Put(TempPath + 'APPLIST.DAT', '/pfs/0/APPLIST.DAT');

         AtualizaListaInstalados;
         ListBox1.ItemIndex := ListBox1.ItemIndex - 1;

         StatusBar1.SimpleText := 'Pronto!';
         StatusBar1.Repaint;

         BitBtn1.Enabled := True;
         SpeedButton3.Enabled := True;
      end;
   end;
end;

end.
