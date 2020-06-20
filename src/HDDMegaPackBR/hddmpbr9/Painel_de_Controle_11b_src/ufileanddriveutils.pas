unit uFileAndDriveUtils;

{$mode delphi}

interface

uses
    Classes, SysUtils, windows;

function GetDrives: TStrings;

implementation

const drivesSize = 128;

function GetDrives: TStrings;
var
  driveStringsSize: cardinal;
  drives: array[0..drivesSize] of char;
  drive: PChar;

  driveList: TStrings;
begin
     driveList := TStringList.Create;

     driveList.BeginUpdate;
     try
       driveList.Clear;

       driveStringsSize := GetLogicalDriveStrings( SizeOf(drives), drives );
       if driveStringsSize = 0 then Exit;

       drive := drives;

       while drive^ <> #0 do
       begin
         driveList.Add( StrPas(drive) );
         Inc(drive, SizeOf(drive) );
       end;

     finally
       driveList.EndUpdate;
     end;

     Result := driveList;
end;

end.

