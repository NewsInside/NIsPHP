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

program HDDMPBRAppInstall;

uses
  Forms,
  uPrincipal in 'uPrincipal.pas' {FrmPrincipal},
  uAppList in 'uAppList.pas',
  uInstallCnf in 'uInstallCnf.pas',
  uFrmDetalhePrograma in 'uFrmDetalhePrograma.pas' {FrmDetalhePrograma},
  uFrmInstalaExploit in 'uFrmInstalaExploit.pas' {FrmInstalaExploit},
  uFrmSobre in 'uFrmSobre.pas' {FrmSobre},
  uFrmInstalaDEV1 in 'uFrmInstalaDEV1.pas' {FrmInstalaDEV1},
  uMiniFTP in 'uMiniFTP.pas' {FrmMiniFTP};

{$R *.res}

begin
  Application.Initialize;
  Application.Title := 'HDD MegaPack BR - Painel de Controle';
  Application.CreateForm(TFrmPrincipal, FrmPrincipal);
  Application.Run;
end.
