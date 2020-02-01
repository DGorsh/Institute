program pseudographic;

uses
  crt,
  SysUtils;

const
  {Flags}
  Flag_Paused = 0;
  Flag_OpenFileWork = 2;
  Flag_Launched = 3;
  Flag_Chooser = 4;
var
  fgraph, fdata, fconfig, fout, flog, fload: Text;
  Config_Info: array [1..8] of byte;
  Error_Messages: array [1..3] of string;
  UsedScript: word;
  Programm_Flags: word;
  Year, Month, Day: word;
  YearS, MonthS, DayS, FileName: string;
  Input, CommandInput, LogFile: string;
  Colorer, CorrectInput, Scripted, Saved, Translate, Loaded, Created: boolean;
  i, j, k: word;
  Output: string;
  key, unused, symb_paint: char;
  t1, t2, t3, t4, t5, t6, t7: integer;
  {Переменные для работы с графикой}
  cursor_xpos, cursor_ypos: byte; {курсор}
  starter_xpos, starter_ypos: byte; {}
  ender_xpos, ender_ypos: byte; {}
  n1_pressed, n2_pressed: boolean;
  n1_xpos, n1_ypos: byte; {}
  ch: char;
  selected_instr, size, color_symb, color_bg, pbucket_method, opacity, figure, used_char: byte;  {инструмент}
  drawed_char: array [1..1220] of char;
  drawed_color: array [1..1220] of byte;

 procedure LogSave;
begin
    close(flog);
  Assign(flog, LogFile);
   {$I-}
  Append(flog);
   {$I+}
end;

{Процедура, генерирующая сообщение о фатальной ошибке без
 использования графической составляющей программы}
  procedure ErrorFW(Number: integer);
  begin
    writeln('Fatal Error #', Number, ': ', Error_Messages[Number]);
    writeln(flog, '[', Day, '-', Month, '-', Year, ': ', TimeToStr(Time),
      '] [E] Fatal Error #', Number, ': ', Error_Messages[Number]);
    LogSave;
    readln;
    halt;
  end;

 {Перевод из 16-ого кода в 10-й}
  function Perevod(chr: string): longint;
  var
    i: byte;
  begin
    Perevod := 0;
    for i := 1 to length(chr) do
      Perevod := Perevod * 256 + Ord(chr[i]);
  end;

{посимвольное чтение}
  procedure scan_f(MaxLength: byte);
  begin
    Input:='';
    while (key <> #10) and (key <> #13) do
    begin
      if (length(Input)>MaxLength) then begin
         Input:='';
         break;
      end;
      key := readkey;
      if not(key in ['A'..'Z']) and not(key in ['a'..'z']) and not(key in ['_',',','+','-', #75, #72,'=']) and not(key in [#0..#32]) then begin
        Input:='';
        writeln(flog, '[', Day, '-', Month, '-', Year, ': ', TimeToStr(Time),
        '] [E] Incorrect data input!'); LogSave;
        break;
      end;
      if key in [#0..#31] then begin
      if key = #8 then begin
        If Input <> '' then
      begin
        GotoXY(WhereX - 1, WhereY);
        Write(' ');
        GotoXY(WhereX - 1, WhereY);
        Delete(Input, length(Input), 1);
      end;
        end;
      end
      else
      begin
        Write(key);
        Input := Input + key;
      end;
    end;
  end;

{Отрисовка изображения}
  procedure Draw_Image(id, PosX, PosY: byte);
  var
    i, j, size: longint;
    strr: string;
    ch: char;
    sizeX, sizeY, X_pos, y_pos: byte;
    Colorer: boolean;
  begin
    {Возврат в начало файла}
    Close(fdata);
    Close(fgraph);
    Assign(fgraph, 'GRAPHDATA.pgd'); {файл графики}
   {$I-}
    Reset(fgraph);
   {$I+}
    if ioresult <> 0 then
      ErrorFW(1);
    Assign(fdata, 'DATADATA.pgd');  {файл с данными}
   {$I-}
    Reset(fdata);
   {$I+}
    if ioresult <> 0 then
      ErrorFW(2);
    for i := 0 to 1018 + id * 4 do
    begin
      Read(fdata, ch);
    end;
    for i := 1 to 4 do
    begin   {перевод из 16-ой системы в 10-ую}
      Read(fdata, ch);
      strr := strr + ch;
    end;
    size := Perevod(strr);
    for i := 0 to size + 16 do Read(fgraph, ch);
    sizeX := Perevod(ch);
    Read(fgraph, ch);
    sizeY := Perevod(ch);
    x_pos := 0;
    y_pos := 0;
    Colorer := True;
    gotoxy(posx, posy);
    for i := 1 to (sizeX * sizeY) * 2 do
    begin
      Read(fgraph, ch);
      if x_pos = sizeX then
      begin
        if (y_pos <> sizeY) and (WhereX <> 80) then
          gotoxy(WhereX - x_pos, WhereY + 1);
        Inc(y_pos);
        x_pos := 0;
      end;
      if Colorer then
      begin
        TextColor((Ord(ch) and 15));
        TextBackground((Ord(ch) and 240) shr 4);
        Colorer := False;
      end
      else
      begin
        Write(ch);
        Inc(x_pos);
        Colorer := True;
      end;
    end;

  end;

{Отрисовка линии}
procedure DrawLine(x1, x2, y1, y2: integer);
var delta_xpos, delta_ypos, delta2, delta3, mask_op, t1, t2, Careter, smb: integer;
begin
    delta_xpos:= abs(x2-x1);
    delta_ypos:= abs(y2-y1);
    delta2:=delta_xpos-delta_ypos;
    delta3:=delta2*2;
    if delta_xpos > delta_ypos then mask_op:= delta_xpos div (opacity+1) else mask_op:= delta_ypos div (opacity+1);
    if x1 < x2 then t1:=1 else t1:=-1;
    if y1 < y2 then t2:=1 else t2:=-1;
    Careter:=0;
    smb:=opacity;
    gotoXY(18+x1, 4 + y1);
    while (x1 <> x2) or (y1 <> y2) do begin
      gotoXY(18+x1, 3 + y1);
      delta3:=delta2*2;
      case smb of
         0: symb_paint:=' ';
         1: symb_paint:=#176;
         2: symb_paint:=#177;
         3: symb_paint:=#178;
         4: symb_paint:=#219;
      end;
      write(symb_paint);
      gotoXY(WhereX-1, WhereY);
      drawed_color[(y1-1)*61+x1] :=  color_symb + (color_bg shl 4);
      drawed_char[(y1-1)*61+x1] := symb_paint;
      if delta3 > delta_ypos * (-1) then begin
         delta2 := delta2 - delta_ypos;
         x1 := x1 + t1;
         end;
      if delta3 < delta_xpos then begin
      delta2 := delta2 + delta_xpos;
      y1 := y1 + t2;
      end;
    if (Careter = mask_op) and (pbucket_method = 2) then begin
       if (smb > 0) then dec(smb);
       Careter:=0;
       end else inc(Careter);
    end;
    n1_pressed := false;
    n2_pressed := false;
  case smb of
       0: symb_paint:=' ';
       1: symb_paint:=#176;
       2: symb_paint:=#177;
       3: symb_paint:=#178;
       4: symb_paint:=#219;
  end;
    gotoXY(18+x2, 4 + y2 - 1);
    write(symb_paint);
    gotoXY(WhereX-1, WhereY);
    drawed_color[(y1-1)*61+x1] :=  color_symb + (color_bg shl 4);
    drawed_char[(y1-1)*61+x1] := symb_paint;
    end;

{отрисовка окна с интерфейсом выбранного инструмента}
procedure Select_Instr(instr: byte);
begin
  if UsedScript = 7 then begin
   Draw_Image(29+selected_instr*3, 4, 7+selected_instr);
   selected_instr:=instr;
   Draw_Image(29+selected_instr*3+1, 4, 7+selected_instr);
   case instr of
      1,2: Draw_Image(70, 4, 17);
      3: Draw_Image(71, 4, 17);
      4: Draw_Image(72, 4, 17);
      5: Draw_Image(73, 4, 17);
      6: Draw_Image(76, 4, 17);
      7: Draw_Image(74, 4, 17);
      8: Draw_Image(75, 4, 17);
   end;
    writeln(flog, '[', Day, '-', Month, '-', Year, ': ', TimeToStr(Time),
      '] [I] Selected instrument #', instr);
    LogSave;
   gotoXY(18+cursor_xpos, 4+cursor_ypos);
   if (Programm_Flags and (1 shl Flag_Chooser) = 0) then
        Programm_Flags:=Programm_Flags + (1 shl Flag_Chooser);
  end;
end;
begin
  {Задание и обнуление переменных (а также заданиe начальных значений); создание лог файла}
  Error_Messages[1] := 'Cant open file GRAPHDATA.pgd!';
  Error_Messages[2] := 'Cant open file DATADATA.pgd!';
  Error_Messages[3] := 'Cant open file CONFIGDATA.pgd!';
  n1_pressed:=false;
  n2_pressed:=false;
  Colorer := True;
  FileName :='';
  for i:=1 to 1220 do begin
     drawed_char[i]:=' ';
     drawed_color[i]:=15;
  end;
  Saved:=false;
  Created:=false;
  selected_instr := 1;
  {Получение значения даты}
  DeCodeDate(Date, Year, Month, Day);
  str(Day, DayS);
  str(Month, MonthS);
  str(Year, YearS);
  Output := 'PG_LOG_' + DayS + '_' + MonthS + '_' + YearS + '.txt';
  LogFile:= Output;
  Assign(flog, Output);
  Rewrite(flog);
  {Открытие файлов}
  Assign(fgraph, 'GRAPHDATA.pgd'); {файл графики}
   {$I-}
  Reset(fgraph);
   {$I+}
  if ioresult <> 0 then
    ErrorFW(1);
      writeln(flog, '[', Day, '-', Month, '-', Year, ': ', TimeToStr(Time),
      '] [S] Program start!');
   writeln(flog, '[', Day, '-', Month, '-', Year, ': ', TimeToStr(Time),
      '] [F] Graphic file opened!');
   LogSave;
  Assign(fdata, 'DATADATA.pgd');  {файл с данными}
   {$I-}
  Reset(fdata);
   {$I+}
  if ioresult <> 0 then
    ErrorFW(2);
   writeln(flog, '[', Day, '-', Month, '-', Year, ': ', TimeToStr(Time),
      '] [F] Data file opened!'); LogSave;
  Assign(fconfig, 'CONFIGDATA.pgd'); {файл конфигурации}
   {$I-}
  Reset(fconfig);
   {$I+}
  if ioresult <> 0 then
    ErrorFW(3);
   writeln(flog, '[', Day, '-', Month, '-', Year, ': ', TimeToStr(Time),
      '] [F] Config file opened!'); LogSave;
  UsedScript := 1;
  for k:=1 to 7 do begin
     read(fconfig, ch);
     Config_Info[k]:=Perevod(ch);
  end;
  figure := Config_Info[1];
  used_char:=Config_Info[2];
  size:= Config_Info[3];
  color_symb:=Config_Info[4];
  color_bg:=Config_Info[5];
  pbucket_method:=Config_Info[6];
  opacity:=Config_Info[7];
  Loaded:=false;
  {Основная часть программы}
  while (UsedScript <> 54) do
  begin {цикл с работой программы. Будет работать, пока не будет выполняться скрипт 54.}
    Scripted:=false;
    if UsedScript = 1 then
    begin {скрипт запуска программы и отрисовки окна}
      Draw_Image(60, 1, 1);
      UsedScript := 2;
      Programm_Flags := Programm_Flags + 1 shl Flag_Launched;
      {Установка флага, указывающего на то, что программа запущена.}
    end;

    if UsedScript = 2 then
    begin {скрипт проверки состояния программы и отрисовки интерфейса под текущее состояние}
      if (Programm_Flags and (1 shl Flag_Launched) = (1 shl (Flag_Launched)))
      {проверка на флаг запуска} then
      begin
        if (Programm_Flags and (1 shl Flag_Paused) = (1 shl (Flag_Paused)))
           then Programm_Flags:=Programm_Flags - (1 shl Flag_Paused);
        Draw_Image(61, 2, 4);
        Draw_Image(62, 19, 4);
        Draw_Image(1, 14, 2);{N}
        Draw_Image(4, 26, 2);{L}
        Draw_Image(7, 40, 2);{S}
        Draw_Image(10, 53, 2);{I}
        Draw_Image(13, 64, 2);{C}
        GotoXY(1, 25);
      end;
    end;

    if UsedScript = 4 then
    begin {скрипт создания нового файла}
      if (Programm_Flags and (1 shl Flag_OpenFileWork) = 0) or (Programm_Flags and (1 shl Flag_Paused) = 1 shl Flag_Paused) then{Проверка }
      begin
        Programm_Flags:=Programm_Flags + (1 shl Flag_OpenFileWork);
        Draw_Image(63, 19, 4);
        Draw_Image(2, 14, 2);
        TextColor(7);
        TextBackground(0);
        {Чтение названия файла}
        GotoXY(23, 12);
        TextColor(7);
        scan_f(23);
        {Очистка строки}
        GotoXY(23, 12);
        write('                        ');
        GotoXY(23, 12);
        if Input <> '' then begin
           if ((filename <> '') and not Saved and Created) or Loaded then close(fout);
           FileName:=Input+'.pgf';
           Assign(fout, FileName);
           {$I-}
           Rewrite(fout);
           {$I+}
           write('                       ');
           Draw_Image(64, 41, 12);
           GotoXY(1, 25);
           writeln(flog, '[', Day, '-', Month, '-', Year, ': ', TimeToStr(Time),
           '] [F] File ', filename, ' created!'); LogSave;
           unused:=readkey;
           for t1:=1 to 1220 do begin
           drawed_color[t1] :=  0;
           drawed_char[t1] := ' ';
          end;
          UsedScript := 7;
          Created:=true;
          if (Programm_Flags and (1 shl Flag_Chooser) = 0) then
             Programm_Flags:=Programm_Flags + (1 shl Flag_Chooser);
        end;
        Programm_Flags:=Programm_Flags - (1 shl Flag_OpenFileWork);
        if UsedScript <> 7 then if (Programm_Flags and (1 shl Flag_Paused) = (1 shl Flag_Paused)) and (Programm_Flags and (1 shl Flag_Launched) = (1 shl Flag_Launched))
           then
              begin
              UsedScript := 2;
              end else UsedScript := 7;
        Scripted:=true;
        Draw_Image(1, 14, 2);
      end
      else if (Programm_Flags and (1 shl Flag_Launched) = (1 shl Flag_Launched))
      {проверка на флаг запуска} then
        UsedScript := 2;
    end;

    if UsedScript = 5 then
    begin {скрипт открытия файла}
     if (Programm_Flags and (1 shl Flag_OpenFileWork) = 0) or (Programm_Flags and (1 shl Flag_Paused) = 1 shl Flag_Paused) then{Проверка }
      begin
        Programm_Flags:=Programm_Flags + (1 shl Flag_OpenFileWork);
        Draw_Image(77, 19, 4);
        Draw_Image(5, 26, 2);{L}
        TextColor(7);
        TextBackground(0);
        {Чтение названия файла}
        GotoXY(23, 12);
        TextColor(7);
        scan_f(23);
        {Очистка строки}
        GotoXY(23, 12);
        write('                        ');
        GotoXY(23, 12);
        if Input <> '' then begin
           FileName:=Input+'.pgf';
           Assign(fload, FileName);
           {$I-}
           Reset(fload);
           {$I+}
           if ioresult <> 0 then begin Draw_Image(78,42,14) end else begin
           Colorer:=true;
           for t1:=1 to 1220 do begin
               Read(fload, ch);
               drawed_color[t1] :=  ord(ch);
               Read(fload, ch);
               drawed_char[t1] := ch;
           end;
           write('                       ');
           Draw_Image(82, 41, 12);
           GotoXY(1, 25);
           unused:=readkey;
           UsedScript := 7;
           Loaded:=true;
           close(fload);
           if (Programm_Flags and (1 shl Flag_Launched) = (1 shl Flag_Launched)) then begin
              FileName:=Input+'.pgf';
              Assign(fout, FileName);
              {$I-}
              Rewrite(fout);
              {$I+}
           end;
           writeln(flog, '[', Day, '-', Month, '-', Year, ': ', TimeToStr(Time),
           '] [F] File ', filename, ' opened!'); LogSave;
           end;
        end;
        Programm_Flags:=Programm_Flags - (1 shl Flag_OpenFileWork);
        if UsedScript <> 7 then if (Programm_Flags and (1 shl Flag_Paused) = (1 shl Flag_Paused)) and (Programm_Flags and (1 shl Flag_Launched) = (1 shl Flag_Launched))
           then
              begin
              UsedScript := 2;
              end else UsedScript := 7;
        Scripted:=true;
        Draw_Image(4, 26, 2);{L}
    end; end;


    if UsedScript = 6 then
    begin {скрипт сохранения файла}
      if (Programm_Flags and (1 shl Flag_Launched) = 0) then begin
          Draw_Image(8, 40, 2);{S}
        if Saved then begin
          Assign(fout, FileName);
          {$I-}
          Rewrite(fout);
          {$I+}
          end;
        for i:=1 to 1220 do begin
          write (fout, chr(drawed_color[i]));
          write (fout, drawed_char[i]);
        end;
        close (fout);
        Draw_Image(65, 41, 12);
        unused:=readkey;
        UsedScript := 7;
        Saved:=true;
        writeln(flog, '[', Day, '-', Month, '-', Year, ': ', TimeToStr(Time),
        '] [F] File saved!');  LogSave;
      end else begin
        Draw_Image(68, 36, 12);
        UsedScript := 2;
        writeln(flog, '[', Day, '-', Month, '-', Year, ': ', TimeToStr(Time),
       '] [FE] File didnt save!');
      end;
          Draw_Image(7, 40, 2);{S}
    end;

    if UsedScript = 7 then
    begin {скрипт работы с графикой}
      if ((Programm_Flags and (1 shl Flag_Launched) = (1 shl Flag_Launched)) or (Programm_Flags and (1 shl Flag_Paused) = 1 shl Flag_Paused)) then begin
        GotoXY(19, 4);
        for t1:=0 to 19 do begin
          for t2:=1 to 61 do begin
            TextBackground((drawed_color[t1*61+t2] and 240) shr 4);
            TextColor(drawed_color[t1*61+t2] and 15);
            write (drawed_char[t1*61+t2]);
          end;
          GotoXY(19, WhereY+1);
        end;
        Draw_Image(66, 2, 4);
        for i:=1 to 8 do begin
        if i <> selected_instr then Draw_Image(29+i*3, 4, 7+i) else Draw_Image(30+i*3, 4, 7+i);
        end;
        GotoXY(19, 4);
         if (Programm_Flags and (1 shl Flag_Launched) = (1 shl Flag_Launched)) then
        Programm_Flags:=Programm_Flags - (1 shl Flag_Launched);
         if (Programm_Flags and (1 shl Flag_Paused) = 1 shl Flag_Paused) then
        Programm_Flags:=Programm_Flags - (1 shl Flag_Paused);
        if (Programm_Flags and (1 shl Flag_Chooser) = 0) then
        Programm_Flags:=Programm_Flags + (1 shl Flag_Chooser);
        cursor_xpos:=1;
        cursor_ypos:=0;
      end;
      if ((Programm_Flags and (1 shl Flag_Chooser) = (1 shl Flag_Chooser))) then begin
      case selected_instr of
      1,2: begin
          Draw_Image(70, 4, 17);
          TextBackground(0); TextColor(7);
          gotoXY(14,17); Write(size);
          gotoXY(14,18); Write(opacity);
          TextColor(15); TextBackground(COLOR_BG);
          gotoXY(14,19); Write(color_bg);
          TextBackground(0); TextColor(COLOR_symb);
          gotoXY(14,20); Write('  ');
          gotoXY(14,20); Write(color_symb); end;
        3: begin
          Draw_Image(71, 4, 17);
          TextBackground(0); TextColor(7);
          gotoXY(11,17);
          if pbucket_method = 1 then Write(#143#174#171#173) else Write(#131#224#160#164);
          gotoXY(14,17);
          TextColor(15); TextBackground(COLOR_BG);
          gotoXY(14,18); Write('  ');
          gotoXY(14,18); Write(color_bg);
          TextBackground(0); TextColor(COLOR_symb);
          gotoXY(14,19); Write('  ');
          gotoXY(14,19); Write(color_symb); end;
        4: begin
          Draw_Image(72, 4, 17);
          TextBackground(0); TextColor(7);
          gotoXY(11,17);
          if figure = 1 then Write(#52#45#168#170) else Write(#51#45#168#170);
          gotoXY(14,18); gotoXY(11,18);
          if pbucket_method = 1 then Write(#143#174#171#173) else Write(#131#224#160#164);
          gotoXY(14,19);
          TextColor(15); TextBackground(COLOR_BG);
          gotoXY(14,19); Write('  ');
          gotoXY(14,19); Write(color_bg);
          TextBackground(0); TextColor(COLOR_symb);
          gotoXY(14,20); Write('  ');
          gotoXY(14,20); Write(color_symb); end;
        5: begin
          Draw_Image(73, 4, 17);
          TextBackground(0); TextColor(7);
          gotoXY(14,17); write(chr(used_char));
          TextColor(15); TextBackground(COLOR_BG);
          gotoXY(14,19); Write('  ');
          gotoXY(14,19); Write(color_bg);
          TextBackground(0); TextColor(COLOR_symb);
          gotoXY(14,20); Write('  ');
          gotoXY(14,20); Write(color_symb); end;
        6: Draw_Image(76, 4, 17);
        7: begin
          Draw_Image(74, 4, 17);
          TextBackground(0); TextColor(7);
          gotoXY(14,17); write(size);
          TextColor(15); TextBackground(COLOR_BG);
          gotoXY(14,18); Write('  ');
          gotoXY(14,18); Write(color_bg); end;
        8: begin
          Draw_Image(75, 4, 17);
          TextBackground(0); TextColor(COLOR_symb);
          gotoXY(14,17); Write('  ');
          gotoXY(14,17); Write(color_symb);
          TextColor(15); TextBackground(COLOR_BG);
          gotoXY(14,18); Write('  ');
          gotoXY(14,18); Write(color_bg);
        end;end;
    Programm_Flags:= Programm_Flags - (1 shl Flag_Chooser);
    gotoXY(18+cursor_xpos, 4+cursor_ypos);
    end; end;

    if UsedScript = 43 then
    begin {скрипт редактирования меню}
      case selected_instr of
      1, 2: begin
         case t1 of
         1: begin
           TextBackground(0); TextColor(10);
           gotoXY(14,17);Write(size);
           TextColor(7);gotoXY(14,18);
           Write(opacity);TextColor(15);
           TextBackground(COLOR_BG);
           gotoXY(14,19);Write(color_bg);
           TextBackground(0);TextColor(COLOR_symb);
           gotoXY(14,20);Write('  ');
           gotoXY(14,20);Write(color_symb);end;
         2: begin
           TextBackground(0);TextColor(10);
           gotoXY(14,18);Write(opacity);
           TextColor(7);gotoXY(14,17);
           Write(size);TextColor(15);
           TextBackground(COLOR_BG);
           gotoXY(14,19);Write(color_bg);
           TextBackground(0);TextColor(COLOR_symb);
           gotoXY(14,20);Write('  ');
           gotoXY(14,20);Write(color_symb);end;
         3: begin
            TextBackground(0);TextColor(7);
            gotoXY(14,18);Write(opacity);
            gotoXY(14,17);Write(size);
            TextColor(15);TextBackground(COLOR_BG);
            gotoXY(14,19);Write('  ');
            gotoXY(14,19);Write(color_bg);
            TextBackground(0);TextColor(COLOR_symb);
            gotoXY(14,20);Write('  ');
            gotoXY(14,20);Write(color_symb);end;
         4: begin
            TextBackground(0);TextColor(7);
            gotoXY(14,18);Write(opacity);
            gotoXY(14,17);Write(size);
            TextColor(15);TextBackground(COLOR_BG);
            gotoXY(14,19);Write('  ');
            gotoXY(14,19);Write(color_bg);
            TextBackground(0);TextColor(COLOR_symb);
            gotoXY(14,20);Write('  ');
            gotoXY(14,20);Write(color_symb);end;
            end;end;
         3: begin
            case t1 of
              1: begin
            TextBackground(0);TextColor(10);
            gotoXY(11,17);
            if pbucket_method = 1 then Write(#143#174#171#173) else Write(#131#224#160#164);
            gotoXY(14,17);TextColor(15);
            TextBackground(COLOR_BG);
            gotoXY(14,18);Write('  ');
            gotoXY(14,18);Write(color_bg);
            TextBackground(0);TextColor(COLOR_symb);
            gotoXY(14,19);Write('  ');
            gotoXY(14,19);Write(color_symb);end;
              2: begin
            TextBackground(0);TextColor(7);
            gotoXY(11,17);
            if pbucket_method = 1 then Write(#143#174#171#173) else Write(#131#224#160#164);
            gotoXY(14,17);
            TextColor(15); TextBackground(COLOR_BG);
            gotoXY(14,18);Write('  ');
            gotoXY(14,18);Write(color_bg);
            TextBackground(0);TextColor(COLOR_symb);
            gotoXY(14,19);Write('  ');
            gotoXY(14,19);Write(color_symb);end;
              3: begin
            TextBackground(0);TextColor(7);
            gotoXY(11,17);
            if pbucket_method = 1 then Write(#143#174#171#173) else Write(#131#224#160#164);
            gotoXY(14,17);
            TextColor(15);TextBackground(COLOR_BG);
            gotoXY(14,18);Write('  ');
            gotoXY(14,18);Write(color_bg);
            TextBackground(0);TextColor(COLOR_symb);
            gotoXY(14,19);Write('  ');
            gotoXY(14,19);Write(color_symb);end;
            end;end;
         4: begin
            case t1 of
              1: begin
            TextBackground(0);TextColor(10);
            gotoXY(11,17);
            if figure = 1 then Write(#52#45#168#170) else Write(#51#45#168#170);
            gotoXY(14,18);TextColor(7);
            gotoXY(11,18);
            if pbucket_method = 1 then Write(#143#174#171#173) else Write(#131#224#160#164);
            gotoXY(14,19);TextColor(15);
            TextBackground(COLOR_BG);
            gotoXY(14,19);Write('  ');
            gotoXY(14,19);Write(color_bg);
            TextBackground(0);TextColor(COLOR_symb);
            gotoXY(14,20);Write('  ');
            gotoXY(14,20);Write(color_symb);end;
              2: begin
            TextBackground(0);TextColor(7);
            gotoXY(11,17);
            if figure = 1 then Write(#52#45#168#170) else Write(#51#45#168#170);
            gotoXY(14,18);TextColor(10); gotoXY(11,18);
            if pbucket_method = 1 then Write(#143#174#171#173) else Write(#131#224#160#164);
            gotoXY(14,19);TextColor(15);
            TextBackground(COLOR_BG);
            gotoXY(14,19);Write('  ');
            gotoXY(14,19);Write(color_bg);
            TextBackground(0);TextColor(COLOR_symb);
            gotoXY(14,20);Write('  ');
            gotoXY(14,20);Write(color_symb);end;
              3, 4: begin
            TextBackground(0);TextColor(7);
            gotoXY(11,17);
            if figure = 1 then Write(#52#45#168#170) else Write(#51#45#168#170);
            gotoXY(14,18);gotoXY(11,18);
            if pbucket_method = 1 then Write(#143#174#171#173) else Write(#131#224#160#164);
            gotoXY(14,19);TextColor(15);
            TextBackground(COLOR_BG);
            gotoXY(14,19);Write('  ');
            gotoXY(14,19);Write(color_bg);
            TextBackground(0);TextColor(COLOR_symb);
            gotoXY(14,20);Write('  ');gotoXY(14,20);
            Write(color_symb);end;
            end;end;
         5: begin
         case t1 of
              1: begin
            TextBackground(0);TextColor(10);
            gotoXY(14,17);write(chr(used_char));
            TextColor(15);TextBackground(COLOR_BG);
            gotoXY(14,19);Write('  ');
            gotoXY(14,19);Write(color_bg);
            TextBackground(0);TextColor(COLOR_symb);
            gotoXY(14,20);Write('  ');
            gotoXY(14,20);Write(color_symb);end;
              2,3: begin
            TextBackground(0);TextColor(7);
            gotoXY(14,17);write(chr(used_char));
            TextColor(15);TextBackground(COLOR_BG);
            gotoXY(14,19);Write('  ');
            gotoXY(14,19);Write(color_bg);
            TextBackground(0);TextColor(COLOR_symb);
            gotoXY(14,20);Write('  ');
            gotoXY(14,20);Write(color_symb);end;
            end;end;
         7: begin
         case t1 of
              1: begin
            TextBackground(0);TextColor(10);
            gotoXY(14,17);write(size);
            TextColor(15);TextBackground(COLOR_BG);
            gotoXY(14,18);Write('  ');
            gotoXY(14,18);Write(color_bg);
            end;
              2: begin
            TextBackground(0);TextColor(7);
            gotoXY(14,17);write(size);
            TextColor(15);TextBackground(COLOR_BG);
            gotoXY(14,18);Write('  ');
            gotoXY(14,18);Write(color_bg);end;
            end;end;
         8: begin
         case t1 of
              1,2: begin
            TextBackground(0);TextColor(COLOR_symb);
            gotoXY(14,17); Write('  ');
            gotoXY(14,17); Write(color_symb);
            TextColor(15); TextBackground(COLOR_BG);
            gotoXY(14,18); Write('  ');
            gotoXY(14,18); Write(color_bg);end;
            end;
            end;
      end;
    end;

    if UsedScript = 50 then
     begin {скрипт окна с настройками}
       if (Programm_Flags and (1 shl Flag_OpenFileWork) = 0) or (Programm_Flags and (1 shl Flag_Paused) = 1 shl Flag_Paused) then{Проверка }
      begin
        if (Programm_Flags and (1 shl Flag_OpenFileWork) = 0) then
            Programm_Flags:=Programm_Flags + (1 shl Flag_OpenFileWork);
        Draw_Image(81, 19, 4);
        Draw_Image(14, 64, 2);{I}
        TextColor(7);
        TextBackground(0);
        unused:=#0;
        t1:=1;
        while (unused <>#10) and (unused <> #13) do begin
           GotoXY(32,13); case Config_Info[1] of
           1: write(#52#45#168#170); 2: Write(#51#45#168#170);  end;
           GotoXY(32,14); write(chr(Config_Info[2]));
           GotoXY(32,15); write(Config_Info[3]);
           GotoXY(36,16); write('  ');
           GotoXY(36,17); write('  ');
           GotoXY(36,16); TextColor(Config_Info[4]); write(Config_Info[4]);
           GotoXY(36,17); TextBackground(Config_Info[5]); TextColor(15); write(Config_Info[5]);
           TextBackground(0); TextColor(7);
           GotoXY(33,18); case Config_Info[6] of
           1: write(#143#174#171#173); 2: Write(#131#224#160#164);  end;
           GotoXY(38,19); write(Config_Info[7]);
           for t2:=1 to 7 do begin
             gotoXY(23,12+t2); write(' ');
           end;
           gotoXY(23,12+t1); write('>');gotoXY(23,12+t1);
           unused:=#0;
           unused:=readkey;
           if unused = #0 then begin
             unused:=readkey;
             case unused of
                #72: begin {Bверх}
                  if t1 >1 then dec(t1);
                end;
                #80: begin {Bниз}
                  if t1 <7 then inc(t1);
                end;
                #75: begin {Влево}
                  case t1 of
                     1, 3, 6: if Config_Info[t1] > 1 then dec(Config_Info[t1]);
                     2: if Config_Info[t1] > 32 then dec(Config_Info[t1]);
                     7, 5, 4: if Config_Info[t1] > 0 then dec(Config_Info[t1]);
                     end;
                  end;
                #77: begin
                  case t1 of
                     1, 6: if Config_Info[t1] < 2 then inc(Config_Info[t1]);
                     2: if Config_Info[t1] < 254 then inc(Config_Info[t1]);
                     3: if Config_Info[t1] < 8 then inc(Config_Info[t1]);
                     4, 5: if Config_Info[t1] < 15 then inc(Config_Info[t1]);
                     7: if Config_Info[t1] < 4 then inc(Config_Info[t1]);
                     end;
                  end;
                end;
                end;
           end;
           close(fconfig);
           Assign(fconfig, 'CONFIGDATA.PGD');
           {$I+}
           Rewrite(fconfig);
           {$I-}
           for t2:=1 to 7 do write(fconfig, chr(Config_Info[t2]));
           close(fconfig);
           Assign(fconfig, 'CONFIGDATA.PGD');
           {$I+}
           Reset(fconfig);
           {$I-}
        writeln(flog, '[', Day, '-', Month, '-', Year, ': ', TimeToStr(Time),
        '] [F] Start config has been changed!'); LogSave;
        Draw_Image(13, 64, 2);{I}
        if (Programm_Flags and (1 shl Flag_Paused) = (1 shl Flag_Paused)) and (Programm_Flags and (1 shl Flag_Launched) = (1 shl Flag_Launched))
           then
              begin
              UsedScript := 2;
              end else UsedScript := 7;
        Scripted:=true;
        Draw_Image(4, 26, 2);{L}
    end; end;

    if UsedScript = 51 then
    begin {скрипт открытия окна с информацией}
       if (Programm_Flags and (1 shl Flag_OpenFileWork) = 0) or (Programm_Flags and (1 shl Flag_Paused) = 1 shl Flag_Paused) then{Проверка }
      begin
        if (Programm_Flags and (1 shl Flag_OpenFileWork) = 0) then
            Programm_Flags:=Programm_Flags + (1 shl Flag_OpenFileWork);
        Draw_Image(80, 19, 4);
        Draw_Image(11, 53, 2);{I}
        TextColor(7);
        TextBackground(0);
        {Чтение названия файла}
        unused:=#0;
        while (unused <>#10) and (unused <> #13) do unused:=readkey;
        Draw_Image(10, 53, 2);{I}
        if (Programm_Flags and (1 shl Flag_Paused) = (1 shl Flag_Paused)) and (Programm_Flags and (1 shl Flag_Launched) = (1 shl Flag_Launched))
           then
              begin
              UsedScript := 2;
              end else UsedScript := 7;
        Scripted:=true;
        Draw_Image(4, 26, 2);{L}
    end; end;

    {нажатие клавиш}
    if not Scripted then begin {проверка на то, что в текущей итерации цикла не выполняется скрипт,
    и что можно проверять нажатие клавиш}
    key := readkey;
    {writeln(ord(key);} {для отладки}
    case key of
      #0:
      begin
        key := ReadKey; {Read ScanCode}
        {writeln(ord(key)); для отладки}
        case key of
          #75: begin {кнопка Влево}
            if UsedScript = 7 then begin
              if WhereX-1 <> 18 then begin gotoXY(WhereX-1,WhereY);
              dec(cursor_xpos);
              end;
              end;
            if Programm_Flags and (1 shl Flag_Chooser) = (1 shl Flag_Chooser) then begin
              if UsedScript in [10..14] then
                 if UsedScript <> 10 then UsedScript:= UsedScript - 1;
            end;
            if UsedScript = 43 then begin
              case selected_instr of
                1, 2: begin
                      case t1 of
                      1: if size > 1 then dec(size);
                      2: if opacity > 0 then dec(opacity);
                      3: if color_bg > 0 then dec(color_bg);
                      4: if color_symb > 0 then dec(color_symb);
                      end;
                      end;
                3: begin
                      case t1 of
                      1: if pbucket_method > 1 then dec(pbucket_method);
                      2: if color_bg > 0 then dec(color_bg);
                      3: if color_symb > 0 then dec(color_symb);
                      end;
                      end;
                4: begin
                      case t1 of
                      1: if figure > 1 then dec(figure);
                      2: if pbucket_method > 1 then dec(pbucket_method);
                      3: if color_bg > 0 then dec(color_bg);
                      4: if color_symb > 0 then dec(color_symb);
                      end;
                      end;
                5: begin
                      case t1 of
                      1: if used_char > 32 then dec(used_char);
                      2: if color_bg > 0 then dec(color_bg);
                      3: if color_symb > 0 then dec(color_symb);
                      end;
                      end;
                7: begin
                      case t1 of
                      1: if size > 1 then dec(size);
                      2: if color_bg > 0 then dec(color_bg);
                      end;
                      end;
                8: begin
                      case t1 of
                      1: if color_symb > 0 then dec(color_symb);
                      2: if color_bg > 0 then dec(color_bg);
                      end;
                      end;
                end; end;
          end;
          #77: begin {кнопка Вправо}
            if UsedScript = 7 then begin
              if WhereX+1 <> 80 then begin gotoXY(WhereX+1,WhereY);
              inc(cursor_xpos);
              end;
              end;
            if UsedScript = 43 then begin
              case selected_instr of
                1, 2: begin
                      case t1 of
                      1: if size < 8 then inc(size);
                      2: if opacity < 4 then inc(opacity);
                      3: if color_bg < 15 then inc(color_bg);
                      4: if color_symb < 15 then inc(color_symb);
                      end;
                      end;
                3: begin
                      case t1 of
                      1: if pbucket_method < 2 then inc(pbucket_method);
                      2: if color_bg < 15 then inc(color_bg);
                      3: if color_symb < 15 then inc(color_symb);
                      end;
                      end;
                4: begin
                      case t1 of
                      1: if figure < 2 then inc(figure);
                      2: if pbucket_method < 2 then inc(pbucket_method);
                      3: if color_bg < 15 then inc(color_bg);
                      4: if color_symb < 15 then inc(color_symb);
                      end;
                      end;
                5: begin
                      case t1 of
                      1: if used_char < 254 then inc(used_char);
                      2: if color_bg < 15 then inc(color_bg);
                      3: if color_symb < 15 then inc(color_symb);
                      end;
                      end;
                7: begin
                      case t1 of
                      1: if size < 8 then inc(size);
                      2: if color_bg < 15 then inc(color_bg);
                      end;
                      end;
                8: begin
                      case t1 of
                      1: if color_symb < 15 then inc(color_symb);
                      2: if color_bg < 15 then inc(color_bg);
                      end;
                      end;
                end;
              end;
          end;
          #72: begin {кнопка Вверх}
            if UsedScript = 7 then begin
              if WhereY-1 <> 3 then begin gotoXY(WhereX,WhereY-1);
              dec(cursor_ypos);
              end;
              end;
            if UsedScript = 43 then begin
              if t1>1 then dec(t1);
            end;
            end;
          #80: begin  {кнопка Вниз}
            if UsedScript = 7 then begin
              if WhereY+1 <> 24 then begin gotoXY(WhereX,WhereY+1);
              inc(cursor_ypos);
              end;
              end;
              if UsedScript = 43 then begin
              if t1<5 then inc(t1);
              end;
            end;
          #49: begin {N}
            UsedScript := 4;
            if Programm_Flags and (1 shl Flag_Paused) = 0 then
               Programm_Flags:=Programm_Flags + (1 shl Flag_Paused);
          end;
          #38: begin {L}
            UsedScript := 5;
            if Programm_Flags and (1 shl Flag_Paused) = 0 then
               Programm_Flags:=Programm_Flags + (1 shl Flag_Paused);
          end;
          #31: begin
            UsedScript := 6;
            if Programm_Flags and (1 shl Flag_Paused) = 0 then
               Programm_Flags:=Programm_Flags + (1 shl Flag_Paused);
          end;    {S}
          #46: begin
            UsedScript := 50;
            if Programm_Flags and (1 shl Flag_Paused) = 0 then
               Programm_Flags:=Programm_Flags + (1 shl Flag_Paused);
            end;{C}
          #23: begin
            UsedScript := 51;
            if Programm_Flags and (1 shl Flag_Paused) = 0 then
               Programm_Flags:=Programm_Flags + (1 shl Flag_Paused);
            end;{I}
        end;
      end;
      #13: begin  {кнопка Enter}
        If UsedScript = 7 then begin
           case selected_instr of
             1: begin
               TextColor(color_symb);
               TextBackground(color_bg);
               t2:=cursor_xpos;
               t4:=cursor_ypos;
               for t1:=cursor_ypos to cursor_ypos + size -1 do begin
                  for t3:=cursor_xpos to cursor_xpos + size -1 do begin
                   if (t3 < 62) and (t3 > 0) and (t1 < 20) and (t1 >= 0) then begin
                      case opacity of
                      0: symb_paint:=' ';
                      1: symb_paint:=#176;
                      2: symb_paint:=#177;
                      3: symb_paint:=#178;
                      4: symb_paint:=#219;
                      end;
                      write(symb_paint);
                      drawed_color[t1*61+t3] :=  color_symb + (color_bg shl 4);
                      drawed_char[t1*61+t3] := symb_paint;
                      end;
                  end;
                  if (t1 < 19) and (t1 >= 0) then
                    gotoXY(18+cursor_xpos,WhereY+1)
                  else
                    gotoXY(18+cursor_xpos,WhereY);
               end;
               gotoXY(18+cursor_xpos,4+cursor_ypos);
           end;
             2:begin
             TextColor(color_symb);
               TextBackground(color_bg);
               t2:=cursor_xpos;
               t4:=cursor_ypos;
               t5:=size div (opacity+1);
               t6:=opacity;
               t7:=1;
               for t1:=cursor_ypos to cursor_ypos + size -1 do begin
                  for t3:=cursor_xpos to cursor_xpos + size -1 do begin
                   if (t3 < 62) and (t3 > 0) and (t1 < 20) and (t1 >= 0) then begin
                      case t6 of
                      0: symb_paint:=' ';
                      1: symb_paint:=#176;
                      2: symb_paint:=#177;
                      3: symb_paint:=#178;
                      4: symb_paint:=#219;
                      end;
                      write(symb_paint);
                      drawed_color[t1*61+t3] :=  color_symb + (color_bg shl 4);
                      drawed_char[t1*61+t3] := symb_paint;
                      if t7 = t5 then begin
                        t7:=1;
                        dec(t6);
                        end else inc(t7);
                      end;
                  end;
                  t6:=opacity;
                  if (t1 < 19) and (t1 >= 0) then
                    gotoXY(18+cursor_xpos,WhereY+1)
                  else
                    gotoXY(18+cursor_xpos,WhereY);
               end;
               gotoXY(18+cursor_xpos,4+cursor_ypos);
               end;
               3: begin
               TextColor(color_symb);
               TextBackground(color_bg);
               if not n1_pressed then begin
                 starter_xpos:=cursor_xpos;
                 starter_ypos:=cursor_ypos;
                 TextColor(0);
                 TextBackground(15);
                 write('1');
                 gotoXY(WhereX-1, WhereY);
                 n1_pressed := true;
               end else begin if (starter_xpos <> cursor_xpos) or (starter_ypos <> cursor_ypos) then begin
                 {Отрисовка линии по алгоритму Брезенхэма}
                   DrawLine(starter_xpos, cursor_xpos, starter_ypos+1, cursor_ypos+1);
                   end;
                 cursor_xpos:=WhereX-18;
                 cursor_ypos:=WhereY-4;
               end;
             end;
             4: begin   {Инструмент ФИГУРА}
               if figure = 1 then begin  {Фигура - ПРЯМОУГОЛЬНИК}
                 if not n1_pressed then begin
                   starter_xpos:=cursor_xpos;starter_ypos:=cursor_ypos;
                   TextColor(0);TextBackground(15);
                   write('1');
                   gotoXY(WhereX-1, WhereY);
                   TextColor(color_symb);TextBackground(color_bg);
                   n1_pressed := true;
                 end else begin if (starter_xpos <> cursor_xpos) or (starter_ypos <> cursor_ypos) then begin
                         t1:=cursor_xpos; t2:= starter_ypos+1; {Вершина В}
                         t3:=starter_xpos; t4:=cursor_ypos+1; {Вершина D}
                         if t1 < t3 then t5:=-1 else t5:=1;
                         if t2 < t4 then t6:=-1 else t6:=1;
                         Translate:=false;
                         while t3-t5 <> t1 do begin
                           DrawLine(starter_xpos, t3, starter_ypos+1, t4);
                           t3:=t3+t5;
                         end;
                         while t4-t6 <> t2 do begin
                           DrawLine(starter_xpos, t1, starter_ypos+1, t4);
                           t4:=t4+t6;
                         end;
                         cursor_xpos:=WhereX-18;cursor_ypos:=WhereY-4;
                     end;
                 end;
               end;
               if figure = 2 then begin {Фигура - ТРЕУГОЛЬНИК}
                 if not n1_pressed or not n2_pressed then begin
                   if not n1_pressed then begin
                      starter_xpos:=cursor_xpos; starter_ypos:=cursor_ypos;
                   end else begin
                      n1_xpos:=cursor_xpos; n1_ypos:=cursor_ypos+1;
                   end;
                   TextColor(0); TextBackground(15);
                   if not n1_pressed then write('1') else write('2');
                   gotoXY(WhereX-1, WhereY);
                   TextColor(color_symb); TextBackground(color_bg);
                   cursor_xpos:=WhereX-18; cursor_ypos:=WhereY-4;
                   if not n1_pressed then n1_pressed := true else n2_pressed := true
                 end else begin if (starter_xpos <> cursor_xpos) or (starter_ypos <> cursor_ypos) then begin
                    ender_xpos:=cursor_xpos; ender_ypos:=cursor_ypos+1;
                    t1:=abs(ender_xpos-n1_xpos);
                    t2:=abs(ender_ypos-n1_ypos);
                    t3:=t1-t2;
                    if n1_xpos < ender_xpos then t6:=1 else t6:=-1;
                    if n1_ypos < ender_ypos then t7:=1 else t7:=-1;
                    while (n1_xpos <> ender_xpos) or (n1_ypos <> ender_ypos) do begin
                      DrawLine(starter_xpos, n1_xpos, starter_ypos+1, n1_ypos);
                      t4:=t3*2;
                        if t4 > t2 * (-1) then begin
                           t3 := t3 - t2;
                           n1_xpos := n1_xpos + t6;
                           end;
                        if t4 < t1 then begin
                           t3 := t3 + t1;
                           n1_ypos := n1_ypos + t7;
                        end;
                      end;
                    DrawLine(starter_xpos, cursor_xpos, starter_ypos+1, cursor_ypos+1);
                    cursor_xpos:=WhereX-18;
                    cursor_ypos:=WhereY-4;
               end;  end;  end; end;
             5: begin  {Отрисовка символа}
               TextColor(color_symb);
               TextBackground(color_bg);
               write(chr(used_char));
               gotoXY(WhereX-1,WhereY);
               drawed_color[cursor_ypos*61+cursor_xpos] :=  color_symb + (color_bg shl 4);
               drawed_char[cursor_ypos*61+cursor_xpos] := chr(used_char);
               cursor_xpos:=WhereX-18;
               cursor_ypos:=WhereY-4;
             end;
             6: begin {Пипетка}
               color_bg := (drawed_color[cursor_ypos*61+cursor_xpos] and 240) shr 4;
               color_symb := drawed_color[cursor_ypos*61+cursor_xpos] and 15;
               used_char := ord(drawed_char[cursor_ypos*61+cursor_xpos]);
               end;
             7: begin {Ластик}
               TextColor(color_symb);
               TextBackground(color_bg);
               t2:=cursor_xpos;
               t4:=cursor_ypos;
               for t1:=cursor_ypos to cursor_ypos + size -1 do begin
                  for t3:=cursor_xpos to cursor_xpos + size -1 do begin
                   if (t3 < 62) and (t3 > 0) and (t1 < 20) and (t1 >= 0) then begin
                      (write(' '));
                      drawed_color[t1*61+t3] :=  color_symb + (color_bg shl 4);
                      drawed_char[t1*61+t3] := ' ';
                      end;
                  end;
                  if (t1 < 19) and (t1 >= 0) then
                    gotoXY(18+cursor_xpos,WhereY+1)
                  else
                    gotoXY(18+cursor_xpos,WhereY);
               end;
               gotoXY(18+cursor_xpos,4+cursor_ypos);
           end;
           8: begin    {Заливка}
             TextColor(color_symb);
             TextBackground(color_bg);
             gotoXY(19,4);
             t1:=20 div (opacity+1);
             t3:=opacity;
             t2:=1;
             for i:=0 to 19 do begin
               for j:=1 to 61 do begin
                   case t3 of
                   0: symb_paint:=' ';
                   1: symb_paint:=#176;
                   2: symb_paint:=#177;
                   3: symb_paint:=#178;
                   4: symb_paint:=#219;
                   end;
                   write(symb_paint);
                   drawed_color[i*61+j] :=  color_symb + (color_bg shl 4);
                   drawed_char[i*61+j] := symb_paint;
                   end;
               if t2 = t1 then begin
                      if t3 <> 0 then begin
                      dec(t3); t2:=1;
                      end;
                      end else inc(t2);
                   gotoXY(19,WhereY+1);
               end;
             gotoXY(19,4);
             cursor_xpos:=WhereX-18;
             cursor_ypos:=WhereY-4;
             end;
           end; end;
        If UsedScript = 43 then begin
        if (Programm_Flags and (1 shl Flag_Paused) = (1 shl Flag_Paused)) then
           Programm_Flags := Programm_Flags - (1 shl Flag_Paused);
           UsedScript:=7;
           gotoXY(18+cursor_xpos, 4+cursor_ypos);
           key:=#0;
      end;end;


      #47, #46: begin  {кнопка /}
        if Programm_Flags and (1 shl Flag_Paused) = 0 then begin
           TextColor(15);
           TextBackground(0);
           GotoXY(1, 25);
           write('/');
           scan_f(64);
           CommandInput:=Input;
           key:=#0;
           t1:=UsedScript;
           Programm_Flags:=Programm_Flags + (1 shl Flag_Paused);
           GotoXY(1, 25);
           Write('                                                                  ');
           writeln(flog, '[', Day, '-', Month, '-', Year, ': ', TimeToStr(Time),
           '] [C] Command input: ', CommandInput); LogSave;
           case CommandInput of
          'file_new': UsedScript:=4;
          'file_save': UsedScript:=6;
          'file_load': UsedScript:=5;
          'exit': UsedScript:=54;
          'config':UsedScript:=50;
          'info':UsedScript:=51;
          end;end;
      end;
      #43, #61: if size < 8 then inc(size); {+}
      #45, #95: if size > 1 then dec(size); {-}
      #97, #65, #148, #228, #55: begin     {A, a, 7}
      Select_Instr(7);
      end;
      #101, #69, #147, #227, #56: begin    {E, e, 8}
      Select_Instr(8);
      end;
      #70, #102, #128, #160, #54: begin    {F, f, 6}
      Select_Instr(6);
      end;
      #117, #85, #131, #163, #53: begin   {U, u, 5}
      Select_Instr(5);
      end;
      #108, #76, #132, #164, #52: begin  {L, l, 4}
      Select_Instr(4);
      end;
      #83, #115, #155, #235, #51: begin  {S, s, 3}
      Select_Instr(3);
      end;
      #66, #98, #136, #168, #50: begin  {B, b, 2}
      Select_Instr(2);
      end;
      #112, #80, #135, #167, #49: begin {P, p, 1}
      Select_Instr(1);
      end;
      #171, #139, #75, #107: begin {K, k}
      t1:=1;
      if UsedScript = 7 then begin
        Programm_Flags := Programm_Flags + (1 shl Flag_Chooser);
        Programm_Flags := Programm_Flags + (1 shl Flag_Paused);
        {t1:=2;}
        key:=#0;
        UsedScript := 43;
        GotoXY(1, 25);
        gotoXY(18+cursor_xpos, 4+cursor_ypos);
        end;
      end;
    end;
  end;
  end;
end.
