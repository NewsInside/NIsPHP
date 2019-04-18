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

unit uAppList;

interface

uses SysUtils, Classes, Dialogs;

type

TAppListItem = class
   private
      vTitulo: String;
      vAutor: String;
      vDescricao: String;
      vExecutavel: String;
      vListaArquivos: TStringList;
      procedure SetTitulo(pTitulo: String);
      procedure SetAutor(pAutor: String);
      procedure SetDescricao(pDescricao: String);
      procedure SetExecutavel(pExecutavel: String);
      function GetDiretorio: String;
   public
      property Titulo: String read vTitulo write SetTitulo;
      property Autor: String read vAutor write SetAutor;
      property Descricao: String read vDescricao write SetDescricao;
      property Executavel: String read vExecutavel write SetExecutavel;
      property Diretorio: String read GetDiretorio;
      property ListaArquivos: TStringList read vListaArquivos;
      constructor Create(pTitulo: String; pAutor: String; pDescricao: String; pExecutavel: String);
      Destructor Destroy; override;
end;

procedure AbreAppList(var Lista: TList; NomeArquivo: String);
procedure SalvaAppList(var Lista: TList; NomeArquivo: String);
procedure DeletaItem(var Lista: TList; posicao: Integer);
procedure OrdenaLista(var Lista: TList);

implementation

type

RegItem = record
   titulo: array[0..127] of char;
   autor: array[0..31] of char;
   descricao: array[0..1023] of char;
   executavel: array[0..127] of char;
end;

procedure TAppListItem.SetTitulo(pTitulo: string);
begin
   vTitulo := Copy(pTitulo, 1, 127);
end;

function TAppListItem.GetDiretorio: String;
begin
   Result := Copy(vExecutavel, Pos('/', vExecutavel) + 1, LastDelimiter('/', vExecutavel) - 2);
end;


procedure TAppListItem.SetAutor(pAutor: string);
begin
   vAutor := Copy(pAutor, 1, 31);
end;

procedure TAppListItem.SetDescricao(pDescricao: string);
begin
   vDescricao := Copy(pDescricao, 1, 1023);
   vDescricao := StringReplace(vDescricao, #13, '', [rfReplaceAll]);
   vDescricao := StringReplace(vDescricao, '\n', #10, [rfReplaceAll]);
end;

procedure TAppListItem.SetExecutavel(pExecutavel: string);
begin
   vExecutavel := Copy(pExecutavel, 1, 127);
end;

constructor TAppListItem.Create(pTitulo: String; pAutor: String; pDescricao: String; pExecutavel: String);
begin
   SetTitulo(pTitulo);
   SetAutor(pAutor);
   SetDescricao(pDescricao);
   SetExecutavel(pExecutavel);
   vListaArquivos := TStringList.Create;
end;

destructor TAppListItem.Destroy;
begin
   vListaArquivos.Free;
   inherited;
end;

// Funções Diversas

procedure AbreAppList(var Lista: TList; NomeArquivo: String);
var
   Arquivo: File;
   dados: RegItem;
   total_aplicacoes, cont: Integer;
begin
   AssignFile(Arquivo, NomeArquivo);
   Reset(Arquivo, 1);

   Lista.Clear;

   if FileSize(Arquivo) < 12 then begin
      CloseFile(Arquivo);
      Exit;
   end;

   Seek(Arquivo, 12);
   BlockRead(Arquivo, total_aplicacoes, sizeof(total_aplicacoes));

   Seek(Arquivo, 16);

   cont := 1;
   while (not EOF(Arquivo)) and (cont <= total_aplicacoes) do begin
      BlockRead(Arquivo, dados, sizeof(dados));
      Lista.Add(TAppListItem.Create(dados.titulo, dados.autor, dados.descricao, dados.executavel));
      Inc(cont);
   end;

   CloseFile(Arquivo);
end;

procedure SalvaAppList(var Lista: TList; NomeArquivo: String);
var
   Arquivo: File;
   dados: RegItem;
   assinatura: array[0..3] of char;
   versao, checksum, tam_dados, n_aplicacoes, i: Integer;
   AppItem: TAppListItem;
begin
   AssignFile(Arquivo, NomeArquivo);
   Rewrite(Arquivo, 1);

   assinatura[0] := 'D';
   assinatura[1] := 'M';
   assinatura[2] := 'S';
   assinatura[3] := '3';

   checksum := 0;
   versao := $10;
   n_aplicacoes := Lista.Count;

   BlockWrite(Arquivo, assinatura, sizeof(assinatura));
   BlockWrite(Arquivo, checksum, sizeof(checksum));
   BlockWrite(Arquivo, versao, sizeof(versao));
   BlockWrite(Arquivo, n_aplicacoes, sizeof(n_aplicacoes));

   for i := 0 to Lista.Count-1 do begin
      FillChar(dados, sizeof(dados), 0);
      AppItem := TAppListItem(Lista[i]);

      StrCopy(dados.titulo, PChar(AppItem.Titulo));
      StrCopy(dados.autor, PChar(AppItem.Autor));
      StrCopy(dados.descricao, PChar(AppItem.Descricao));
      StrCopy(dados.executavel, PChar(AppItem.Executavel));

      BlockWrite(Arquivo, dados, sizeof(dados));

      tam_dados := StrLen(dados.titulo) + StrLen(dados.autor) + StrLen(dados.descricao) + StrLen(dados.executavel);
      checksum := checksum + (sizeof(dados) - tam_dados);
   end;

   Seek(Arquivo, 4);
   BlockWrite(Arquivo, checksum, sizeof(checksum));

   CloseFile(Arquivo);
end;

procedure DeletaItem(var Lista: TList; posicao: Integer);
begin
   if (posicao < 0) or (posicao > Lista.Count-1) then
      Exit;

   TAppListItem(Lista[posicao]).Free;
   Lista.Delete(posicao);
end;

function CompareByTitulo(Item1: Pointer; Item2: Pointer): Integer;
var
   App1, App2: TAppListItem;
begin
   App1 := TAppListItem(Item1);
   App2 := TAppListItem(Item2);

   if UpperCase(App1.Titulo) > UpperCase(App2.Titulo) then
      Result := 1
   else if UpperCase(App1.Titulo) = UpperCase(App2.Titulo) then
      Result := 0
   else
      Result := -1;
end;

procedure OrdenaLista(var Lista: TList);
begin
   Lista.Sort(CompareByTitulo);
end;

end.

