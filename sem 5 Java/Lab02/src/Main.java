import java.util.Scanner;

public  class Main {
    public static void main(String[] args) {
        String InputData = "";
        while (true) {
            Scanner TextReader = new Scanner(System.in);
            System.out.println ("Введите для продолжения: \'1\'-запуск программы, \'2\'-показать помощь, \'0\'-выход");
            InputData = TextReader.nextLine();
            switch (InputData) {
                case "0": {
                    return;
                }
                case "1": {
                    System.out.println("Введите имя файла с настройками - номиналами");
                    String ConfignameBuffer = TextReader.nextLine();
                    System.out.println("Введите значение суммы для размена");
                    int MoneyValue = 0;
                    try {
                        MoneyValue = Integer.parseInt(TextReader.nextLine());
                    } catch (NumberFormatException Exc) {
                        System.err.println("Неверный ввод данных для денежной суммы!");
                        System.exit(1);
                    }
                    try {
                        if ((MoneyValue > 0) && (MoneyValue <= 1000)) {
                            LabTwo LabWorkProgramm = new LabTwo(MoneyValue, ConfignameBuffer);
                            if (!LabWorkProgramm.mRun()) {
                                System.out.println("Нет способов разложить!");
                            }
                        } else {
                            throw new Exception("Ошибка в записи суммы! Число должно быть в диапазоне от 1 до 1000");
                        }
                    } catch (Exception ex) {
                        System.err.println(ex.getMessage());
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
