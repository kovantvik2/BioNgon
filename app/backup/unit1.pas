unit Unit1;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, Forms, Controls, Graphics, Dialogs, StdCtrls, ActnList,
  Grids, ExtCtrls, Math;

type

  { TForm1 }

  dna_nucl_arr = array of real;

  TForm1 = class(TForm)
    Button1: TButton;
    Button2: TButton;
    Edit1: TEdit;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Memo1: TMemo;
    RadioButton1: TRadioButton;
    RadioButton2: TRadioButton;
    RadioGroup1: TRadioGroup;
    StringGrid1: TStringGrid;
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);

  private

  public

  end;

var
  Form1: TForm1;

implementation

{$R *.lfm}

{ TForm1 }

procedure OutDNA(
    dna_nucl: dna_nucl_arr;
    Label5: TLabel;
    StringGrid1: TStringGrid;
    length_res: integer);

var
  gc_percent, factor: real;
  i, j: integer;

begin
  factor := Power(10.0, 2);
  gc_percent := ((dna_nucl[2] + dna_nucl[3]) / length_res) * 100;
  gc_percent := Round(gc_percent * factor) / factor;
  Label5.Caption := (FloatToStr(gc_percent)) + '%';
  for i := 1 to StringGrid1.ColCount - 2 do
    for j := 1 to StringGrid1.RowCount -1 do
      begin
        StringGrid1.Cells[i, j] := FloatToStr(dna_nucl[j - 1]);
        gc_percent := ((dna_nucl[j - 1]) / length_res) * 100;
        gc_percent := Round(gc_percent * factor) / factor;
        StringGrid1.Cells[i + 1, j] := FloatToStr(gc_percent);
      end;
  SetLength(dna_nucl, 0)
end;

procedure LenNucl(
    dna_result: String;
    Label5: TLabel; StringGrid1: TStringGrid);

var
  dna_nucl: dna_nucl_arr;
  i, length_res: integer;

begin
  dna_nucl := [0.0, 0.0, 0.0, 0.0, 0.0];
  length_res := length(dna_result);
  for i := 1 to length_res do
    begin
      case dna_result[i] of
        'A': dna_nucl[0] := dna_nucl[0] + 1.0;
        'T': dna_nucl[1] := dna_nucl[1] + 1.0;
        'G': dna_nucl[2] := dna_nucl[2] + 1.0;
        'C': dna_nucl[3] := dna_nucl[3] + 1.0;
        else
          dna_nucl[4] := dna_nucl[4] + 1.0;
      end;
    end;
  OutDNA(dna_nucl, Label5, StringGrid1, length_res);
  SetLength(dna_result, 0)
end;

procedure TForm1.Button1Click(Sender: TObject);

var
  dna_result: String;

begin
  dna_result := StringReplace(Memo1.Lines.Text, sLineBreak, '', [rfReplaceAll]);
  if length(dna_result) <= 0 then
    Edit1.Text := 'Empty'
  else
    begin
      Edit1.Text := IntToStr(length(dna_result));
      LenNucl(dna_result, Label5, StringGrid1);
    end;
end;

procedure TForm1.Button2Click(Sender: TObject);

var
  i, j: integer;

begin
  Edit1.Clear;
  Label5.Caption := '0.0 %';
  Memo1.Clear;
  for i := 1 to StringGrid1.ColCount - 1 do
    for j := 1 to StringGrid1.RowCount - 1 do
      begin
        StringGrid1.Cells[i, j] := '';
      end;
end;

end.

