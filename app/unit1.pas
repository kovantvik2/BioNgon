unit Unit1;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, Forms, Controls, Graphics, Dialogs, StdCtrls, ActnList,
  Grids, ExtCtrls, Math;

type

  { TForm1 }

  TForm1 = class(TForm)
    Button1: TButton;
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

  private

  public

  end;

var
  Form1: TForm1;

implementation

{$R *.lfm}

{ TForm1 }

procedure OutDNA(
    len_a, len_t, len_g, len_c: real;
    dna_result: String;
    Label5: TLabel;
    StringGrid1: TStringGrid);

var
  gc_percent, factor: real;

begin
  factor := Power(10.0, 2);
  gc_percent := ((len_g + len_c) / length(dna_result)) * 100;
  gc_percent := Round(gc_percent * factor) / factor;
  Label5.Caption := (FloatToStr(gc_percent)) + '%';
  StringGrid1.Cells[1, 1] := FloatToStr(len_a);
end;

procedure LenNucl(
    dna_base, dna_result: String;
    Label5: TLabel; StringGrid1: TStringGrid);

type
  dna_nucl_arr = array of real;

var
 (* len_a, len_t, len_g, len_c: real; *)
  dna_nucl: dna_nucl_arr;
  i: integer;

begin
  dna_nucl := [0.0, 0.0, 0.0, 0.0];
  (* len_a := 0.0;
  len_t := 0.0;
  len_g := 0.0;
  len_c := 0.0; *)
  for i := 1 to length(dna_result) do
    begin
      begin
        if dna_result[i] = dna_base[1] then
          len_a := len_a + 1.0
        else if dna_result[i] = dna_base[2] then
          len_t := len_t + 1.0
        else if dna_result[i] = dna_base[3] then
          len_g := len_g + 1.0
        else if dna_result[i] = dna_base[4] then
          len_c := len_c + 1.0
      end;
    end;
  OutDNA(len_a, len_t, len_g, len_c, dna_result, Label5, StringGrid1);
end;

procedure TForm1.Button1Click(Sender: TObject);

var
  dna_result: String;
  dna_base: String;

begin
  dna_base := 'ATGC';
  dna_result := StringReplace(Memo1.Lines.Text, sLineBreak, '', [rfReplaceAll]);
  Edit1.Text := IntToStr(length(dna_result));
  LenNucl(dna_base, dna_result, Label5, StringGrid1);
end;




end.

