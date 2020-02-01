program sdas;
uses crt;
procedure scobki(s:string);
var
  i:integer;
begin
  i:=pos('()', s);
  if i=0 then
  i:=pos('[]',s);
  if i=0 then
  i:=pos('<>',s);
  if i=0 then
  i:=pos('{}',s);
  if i=0 then
  begin
  if length(s)=0 then
  writeln('Right')
  else
  writeln('Error')
  end
  else
  begin
  Delete(s,i,2);
  scobki(s);
  end;
end;

var
  s:string;

begin
  readln(s);
  scobki(s);
  readkey
end.

