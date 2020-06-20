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

unit uInstallCnf;

{$IFDEF FPC}
  {$MODE Delphi}
{$ENDIF}

interface

uses Classes, SysUtils, Dialogs, uAppList;

procedure AbreInstallCnf(var Lista: TList; NomeArquivo: String);
procedure CriaUninstallCnf(Item: TAppListItem; NomeArquivo: String);

implementation

procedure AbreInstallCnf(var Lista: TList; NomeArquivo: String);
var
   Arquivo: TextFile;
   Linha: String;
   Registro: TStringList;
   ListaArquivos: TStringList;
   ArquivoOK: Boolean;
   i: Integer;

   // Dados do Aplicativo
   Titulo: String;
   Autor: String;
   Descricao: String;
   Executavel: String;
   Item: TAppListItem;
begin
   ArquivoOK := False;

   AssignFile(Arquivo, NomeArquivo);
   Reset(Arquivo);

   Registro := TStringList.Create;
   ListaArquivos := TStringList.Create;

   Lista.Clear;

   while not Eof(Arquivo) do begin
      // Procura flag de [APP]
      repeat
         Readln(Arquivo, Linha);
      until (Trim(UpperCase(Linha)) = '[APP]') or (Eof(Arquivo));

      // Lê dados que se encontram entre [APP] e [/APP] para StringList
      if Trim(UpperCase(Linha)) = '[APP]' then begin
         Registro.Clear;
         while (Trim(UpperCase(Linha)) <> '[/APP]') and (not Eof(Arquivo)) do begin
            Readln(Arquivo, Linha);
            if (Trim(UpperCase(Linha)) <> '[/APP]') and (Trim(Linha) <> '') then Registro.Add(Linha);
         end;
         ArquivoOK := True;
      end;

      // Obtem as linhas que iniciam com COPY, identificando arquivos do pacote
      ListaArquivos.Clear;
      for i := 0 to Registro.Count-1 do begin
         if UpperCase(Copy(Registro[i], 1, 4)) = 'COPY' then
            ListaArquivos.Add(Copy(Registro[i], LastDelimiter('/', Registro[i]) + 1));
      end;

      Titulo := Copy(Registro.Text, Pos('[TITLE]', Registro.Text) + 9, Pos('[/TITLE]', Registro.Text) - Pos('[TITLE]', Registro.Text) - 11);
      Autor := Copy(Registro.Text, Pos('[AUTHOR]', Registro.Text) + 10, Pos('[/AUTHOR]', Registro.Text) - Pos('[AUTHOR]', Registro.Text) - 12);
      //Descricao :=  StringReplace(Copy(Registro.Text, Pos('[DESC]', Registro.Text) + 8, Pos('[/DESC]', Registro.Text) - Pos('[DESC]', Registro.Text) - 10), '\n', #10, [rfReplaceAll]);
      Descricao :=  Copy(Registro.Text, Pos('[DESC]', Registro.Text) + 8, Pos('[/DESC]', Registro.Text) - Pos('[DESC]', Registro.Text) - 10);
      Executavel := Copy(Registro.Text, Pos('[EXEC]', Registro.Text) + 8, Pos('[/EXEC]', Registro.Text) - Pos('[EXEC]', Registro.Text) - 10);

      if ArquivoOK then begin
         Item := TAppListItem.Create(Titulo, Autor, Descricao, Executavel);
         Item.ListaArquivos.AddStrings(ListaArquivos);
         Lista.Add(Item);
      end;

   end;

   Registro.Free;
   ListaArquivos.Free;
end;

procedure CriaUninstallCnf(Item: TAppListItem; NomeArquivo: String);
var
   dummy: array[0..4227] of char;
   Arquivo: File;
   posicao: Integer;
   n_arquivos: Integer;
   i, x: Integer;
   caminho: array[0..2047] of char;
begin
   AssignFile(Arquivo, NomeArquivo);
   Rewrite(Arquivo, 1);

   FillChar(dummy, sizeof(dummy), 0);

   BlockWrite(Arquivo, dummy, sizeof(dummy));

   Seek(Arquivo, 0);

   n_arquivos := Item.ListaArquivos.Count + 1;
   BlockWrite(Arquivo, n_arquivos, sizeof(n_arquivos));

   posicao := 4;
   x := 3;

   for i := 0 to Item.ListaArquivos.Count-1 do begin
      Seek(Arquivo, posicao);
      BlockWrite(Arquivo, x, sizeof(x));
      StrCopy(caminho, PChar('/' + Item.Diretorio + '/' + Item.ListaArquivos[i]));
      BlockWrite(Arquivo, caminho, StrLen(caminho));
      posicao := posicao + 132;
   end;

   Seek(Arquivo, posicao);
   x := 129;
   BlockWrite(Arquivo, x, sizeof(x));
   StrCopy(caminho, PChar('/' + Item.Diretorio));
   BlockWrite(Arquivo, caminho, StrLen(Caminho));

   CloseFile(Arquivo);
end;


end.
