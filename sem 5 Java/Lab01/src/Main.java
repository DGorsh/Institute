import java.util.Scanner;
import java.util.Vector;

public  class Main {
    public static void main(String[] args) {
        Scanner TextReader = new Scanner(System.in);
        String InputData = "";
        while (true) {
            System.out.println ("Введите для продолжения: \'1\'-запуск программы, \'2\'-запуск тестов, \'3\'-показать помощь, \'0\'-выход");
            InputData = TextReader.nextLine();
            switch (InputData) {
                case "0": {
                    return;
                }
                case "1": {
                    if (args.length != 2) {
                        System.out.println("Неверное число аргументов");
                        System.exit(1);
                    }
                    String FilenameBuffer = args[0];
                    String ConfignameBuffer = args[1];
                    try {
                        LabOne LabWorkProgramm = new LabOne(FilenameBuffer, ConfignameBuffer);
                        if (LabWorkProgramm.mRun()) {
                            System.out.println("Проблем с текстом нет! Скобки расставлены верно!");
                        };
                    } catch (Exception ex) {
                        System.out.println(ex.getMessage());
                        System.exit(1);
                    }
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
                    System.out.println("Лабораторная работа № 1.\nАвтор: Горшков Д.С. (М8О-313Б)\nПравильность расстановки скобок" +
                            " проверяется с помощью стека");
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
                "test/text01.txt",
                "test/text02.txt",
                "test/text03.txt",
                "test/text04.txt",
                "test/text05.txt",
                "test/text06.txt",
                "test/text07.txt",
                "test/text08.txt",
                "test/text09.txt",
        };
        String[] ConfignamesVector = {
                "test/config01.json",
                "test/config02.json",
                "test/config03.json",
                "test/config04.json",
                "test/config05.json",
        };

        for (int i = 0; i < FilenamesVector.length; i++) {
            for (int j = 0; j < ConfignamesVector.length; j++) {
                System.out.println(" >> Test: " + (i*ConfignamesVector.length + j) + "; Text file: " + FilenamesVector[i] +
                        "; Config file: " + ConfignamesVector[j]);
                LabOne LabWorkProgramm = new LabOne(FilenamesVector[i], ConfignamesVector[j]);
                if (LabWorkProgramm.mRun()) {
                    System.out.println("Проблем с текстом нет! Скобки расставлены верно!");
                };
            }
        }
    }
}
