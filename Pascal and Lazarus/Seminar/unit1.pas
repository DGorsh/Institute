unit Unit1;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, FileUtil, Forms, Controls, Graphics, Dialogs, ExtCtrls,
  StdCtrls;

type

  { TForm1 }

  TForm1 = class(TForm)
    Button1: TButton;
    Timer1: TTimer;
    procedure Button1Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure FormPaint(Sender: TObject);
    procedure Timer1StartTimer(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);
  private
    { private declarations }
  public
    { public declarations }
  end;

var
  Form1: TForm1;
  x: integer;
implementation

{$R *.lfm}

{ TForm1 }

procedure TForm1.FormPaint(Sender: TObject);
begin
  Form1.canvas.Brush.color:= $FFFFFFFF;
  Form1.canvas.Rectangle(x, 0, x+100, 75);
end;

procedure TForm1.Timer1StartTimer(Sender: TObject);
begin

end;

procedure TForm1.Timer1Timer(Sender: TObject);
begin
  inc(x);
  Repaint;
end;

procedure TForm1.Button1Click(Sender: TObject);
begin
  Form1.canvas.Brush.color:= $FFFFFFFF;
  Form1.canvas.Rectangle(195, 117, 205, 112);
end;

procedure TForm1.FormCreate(Sender: TObject);
begin
  x:=0;
end;

end.

