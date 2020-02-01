import java.io.IOException;
import java.util.Scanner;

public  class Main {
    public static void main(String[] args) {
        String InputData = "";
        while (true) {
            Scanner TextReader = new Scanner(System.in);
            System.out.println ("Введите для продолжения: \'1\'-запуск программы, \'2\'-показать помощь, \'0\'-показать помощь");
            InputData = TextReader.nextLine();
            switch (InputData) {
                case "0": {
                    return;
                }
                case "1": {
                    System.out.println("Введите название файла с текстом");
                    String TextFileBuffer = TextReader.nextLine();
                    System.out.println("Введите строчку, которую ищем");
                    String TextStringFind = TextReader.nextLine();
                    System.out.println("Введите количество строчек для записи в файл");
                    String TextString = TextReader.nextLine();
                    int TextLinesArray = 0;

                    TextLinesArray = Integer.parseInt(TextString);
                    try{
                        TextLinesArray = Integer.parseInt(TextString);
                    } catch (NumberFormatException ex){
                        System.out.println("Ошибка перевода из числа в строку (ввод количества записей)");
                        System.exit(1);
                    };
                    TextReader.close();
                    try {
                        if ((TextLinesArray <= 9) && (TextLinesArray >= 0)) {
                            LabThree LabWorkProgramm = new LabThree(TextFileBuffer, TextStringFind, TextLinesArray);
                            LabWorkProgramm.mRun();
                        } else {
                            throw new Exception("Ошибка ввода! число записей должно быть в диапазоне от 0 до 9");
                        }
                    } catch (Exception ex) {
                        System.out.println(ex.getMessage());
                        System.exit(1);
                    }
                    System.exit(0);
                    break;
                }
                case "2": {
                    System.out.println("Лабораторная работа № 2.\nАвтор: Горшков Д.С. (М8О-312Б)\nРазложение суммы денег: " +
                            " выводит все доступные варианты разложения денежной суммы с помощью рекурсии");
                    break;
                }
                default: {
                    System.out.println("Неверный ввод");
                    break;
                }
            }
        }
    }
}
