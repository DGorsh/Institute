import java.util.Scanner;

public  class Main {
    public static void main(String[] args) {
        String InputData = "";
        while (true) {
            Scanner TextReader = new Scanner(System.in);
            System.out.println("Введите для продолжения: \'1\'-запуск программы, \'2\'-показать помощь, \'0\'-выход");
            InputData = TextReader.nextLine();
            switch (InputData) {
                case "0": {
                    return;
                }
                case "1": {
                    try {
                        Database db = new Database("input.txt","groups.txt","subjects.txt","marks.txt");
                        System.out.println(db.getFinalResult());
                    } catch (Exception ex) {
                        System.err.println(ex.getMessage());
                        System.exit(1);
                    }
                    System.exit(0);
                    break;
                }
                case "2": {
                    System.out.println("Лабораторная работа № 6.\nАвтор: Горшков Д.С. (М8О-312Б)\nАггрегатор: " +
                            " анализирует файлы с данными (БД)");
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
