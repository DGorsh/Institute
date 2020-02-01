import java.util.Scanner;

public  class Main {
    public static void main(String[] args) {
        String InputData = "";
        while (true) {
            Scanner TextReader = new Scanner(System.in);
            System.out.println("Введите для продолжения: \'1\'-запуск программы, \'2\'-запуск тестов, \'3\'-показать помощь, \'0\'-показать помощь");
            InputData = TextReader.nextLine();
            switch (InputData) {
                case "0": {
                    return;
                }
                case "1": {
                    System.out.println("Введите параметр отклонения (в секундах)");
                    long TextDifference = 0;
                    try {
                        TextDifference = Integer.parseInt(TextReader.nextLine());
                    } catch (NumberFormatException ex) {
                        System.err.println("Что-то пошло не так при переводе строки в число");
                        System.exit(1);
                    }
                    System.out.println("Введите название файла с текстом");
                    String TextFileBuffer = TextReader.nextLine();
                    TextReader.close();
                    try {
                        LabFour LabWorkProgramm = new LabFour(TextFileBuffer, TextDifference);
                        LabWorkProgramm.mRun();
                    } catch (Exception ex) {
                        System.err.println(ex.getMessage());
                        System.exit(1);
                    }
                    System.exit(0);
                    break;
                }
                case "2": {
                    try {
                        LabOneTests();
                    } catch (Exception ex) {
                        System.out.println(ex.getMessage());
                        System.exit(1);
                    }
                    break;
                }
                case "3": {
                    System.out.println("Лабораторная работа № 4-5.\nАвтор: Горшков Д.С. (М8О-312Б)\nВыявление аномальных запросов: " +
                            " анализирует файл-лог, выявляя аномальные запросы.");
                    break;
                }
                default: {
                    System.out.println("Неверный ввод");
                    break;
                }
            }
        }
    }

    private static void LabOneTests() throws Exception {
        String[] FilenamesVector = {
                "log.txt"
        };
        long[] ConfignamesVector = {
                3, 6, 9, 12, 0
        };

        for (int i = 0; i < FilenamesVector.length; i++) {
            for (int j = 0; j < ConfignamesVector.length; j++) {
                System.out.println(" >> Тест: " + (i * ConfignamesVector.length + j) + "; Файл: " + FilenamesVector[i] +
                        "; Отклонение: " + ConfignamesVector[j]);
                LabFour LabWorkProgramm = new LabFour(FilenamesVector[i], ConfignamesVector[j]);
                LabWorkProgramm.mRun();
                System.out.println("~~~~~~~~");
            }
        }
    }
}
