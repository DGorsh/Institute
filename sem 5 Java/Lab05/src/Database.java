import java.io.FileInputStream;
import java.io.IOException;
import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public final class Database {

    int minMark = 2;
    int maxMark = 5;

    int byTop = 5;
    private HashMap<Integer, Puple> puples = new HashMap<>();
    private HashMap<Integer, Pair<String, ArrayList<Integer>>> groups = new HashMap<>(); //id , <groupname, puples>
    private HashMap<Integer, ArrayList<Mark>> marks = new HashMap<>();
    private HashMap<Integer, Subject> subjects = new HashMap<>();


    public Database(String filePuples, String fileGroups, String fileSubject, String fileMarks) throws Exception {
        //Читаем файл

        try {

            FileInputStream inputPuples = new FileInputStream(filePuples);
            FileInputStream inputGroups = new FileInputStream(fileGroups);
            FileInputStream inputSubjects = new FileInputStream(fileSubject);
            FileInputStream inputMarks = new FileInputStream(fileMarks);

            Scanner inputScanner = new Scanner(inputPuples);
            Pattern patter = Pattern.compile("(\\d+),([a-z, A-Z, а-я, А-Я]+)");

            //Читаем учеников
            while (inputScanner.hasNext()) {
                String currentLine = inputScanner.nextLine();
                Matcher matcher = patter.matcher(currentLine);
                if (matcher.find() && matcher.groupCount() == 2) {
                    if (!checkPuple(Integer.parseInt(matcher.group(1)))) {
                        puples.put(Integer.parseInt(matcher.group(1)), new Puple(Integer.parseInt(matcher.group(1)), matcher.group(2)));

                    } else {
                        throw new Exception("[Ошибка]: найдены дубликаты id");
                    }
                }
            }

            //Читаем группы
            inputScanner = new Scanner(inputGroups);
            patter = Pattern.compile("(\\d+),([a-z, A-Z, а-я, А-Я]+),(\\d+)");

            while (inputScanner.hasNext()) {
                String currentLine = inputScanner.nextLine();
                Matcher matcher = patter.matcher(currentLine);
                if (matcher.find() && matcher.groupCount() == 3) {
                    if (checkPuple(Integer.parseInt(matcher.group(3)))) {

                        if (!checkGroup(Integer.parseInt(matcher.group(1)))) {
                            groups.put(Integer.parseInt(matcher.group(1)), new Pair<>(matcher.group(2), new ArrayList<>()));

                        }

                        groups.get(Integer.parseInt(matcher.group(1))).getValue().add(Integer.parseInt(matcher.group(3)));
                    } else {
                        throw new Exception("[Ошибка]: пользователя с id = " +Integer.parseInt(matcher.group(3))+ " не существует");
                    }
                }
            }

            inputScanner = new Scanner(inputSubjects);
            patter = Pattern.compile("(\\d+),([a-z, A-Z, а-я, А-Я]+)");

            while (inputScanner.hasNext()) {
                String currentLine = inputScanner.nextLine();
                Matcher matcher = patter.matcher(currentLine);
                if (matcher.find() && matcher.groupCount() == 2) {
                    Integer id = Integer.parseInt(matcher.group(1));
                    String subjectName = matcher.group(2);

                    if (!checkSubject(id)) {
                        subjects.put(id, new Subject(id, subjectName));
                    } else {
                        throw new Exception("предмет с id =" + id + " существует.");
                    }
                }
            }

            inputScanner = new Scanner(inputMarks);
            patter = Pattern.compile("(\\d+),(\\d+),(\\d),(\\d{2}).(\\d{2}).(\\d{4})");

            while (inputScanner.hasNext()) {
                String currentLine = inputScanner.nextLine();
                Matcher matcher = patter.matcher(currentLine);

                if (matcher.find() && matcher.groupCount() == 6) {

                    //Здесь в качестве primary key испольщуется id предмета
                    int subject = Integer.parseInt(matcher.group(1));
                    int puple = Integer.parseInt(matcher.group(2));
                    int mark = Integer.parseInt(matcher.group(3));
                    int day = Integer.parseInt(matcher.group(4));
                    int month = Integer.parseInt(matcher.group(5));
                    int year = Integer.parseInt(matcher.group(6));

                    if (checkPuple(puple) && checkSubject(subject)) {

                        Date usedDate = new Date(year, month, day);
                        if (!checkMark(subject)) {
                            marks.put(subject, new ArrayList<>());
                        }

                        if (mark < minMark || mark > maxMark) {
                            throw new Exception("Hедопустимая оценка");
                        } else {
                            marks.get(subject).add(new Mark(subject, puple, mark, usedDate));
                        }
                    } else {
                        throw new Exception("Что-то не так с id ученика или предмета");
                    }
                } else {
                    throw new Exception("Какие-то параметры у вас в оценках некорректные");
                }


            }



        } catch (IOException exception) {
            System.out.println("File error!");
            exception.printStackTrace();
        }
    }

    private boolean checkPuple(int id) {
        return puples.containsKey(id);
    }

    private boolean checkGroup(int id) {
        return groups.containsKey(id);
    }

    private boolean checkSubject(int id) {
        return subjects.containsKey(id);
    }

    private boolean checkMark(int id) {
        return marks.containsKey(id);
    }

    private boolean chechPupleInGroup(int gid, int pid) {
        if (checkGroup(gid) && checkPuple(pid)) {
            return groups.get(gid).getValue().contains(pid);
        } else return false;
    }

    public float calculateMean(int id) {
        if (checkPuple(id)) {
            //Вычисляем среднее для ученика
            float subjSum = 0;
            float marksCount = 0;

            for (int subjectId :
                    subjects.keySet()) {
                if (marks.containsKey(subjectId)) {
                    for (Mark mark : marks.get(subjectId)) {
                        if (mark.getPupleId() == id) {
                            subjSum += mark.getValue();
                            marksCount++;
                        }
                    }
                }
            }

            if (marksCount != 0)
                return (subjSum / marksCount);
        }

        return 0;
    }

    public Pair<Integer, Float> calculateFailPercent(int id) {
        if (checkGroup(id)) {

            float badCount = 0;

            float allCount = groups.get(id).getValue().size();

            for (int pupleId : groups.get(id).getValue()) {
                //Теперь работаем с id учеников группы
                boolean goodStudent = true;

                for (ArrayList<Mark> markVector : marks.values()) {
                    if (goodStudent) { //Если ученик ещё подаёт надежды
                        for (Mark mark : markVector) {
                            if (mark.getPupleId() == pupleId && mark.getValue() == minMark) {
                                goodStudent = false; //Теперь ученик - двоечник
                                badCount += 1;
                                break;
                            }
                        }
                    } else break; //Иначе переходим к следующему ученику
                }
            }


            //Считаем процент двоечников
            return new Pair<Integer, Float>((int) badCount, (badCount * 100) / allCount);

        }

        return new Pair<Integer, Float>(0, (float) 0);
    }

    public float calculateSubjRateInGroup(int group, int subject) { //Задана группа, задан предмет
        if (checkGroup(group) && checkSubject(subject)) {
            float badCount = 0; //Считает количество сдач предмета
            float goodCount = 0;
            for (int pupleId : groups.get(group).getValue()) { //Берём всех студентов группы
                for (Mark mark : marks.get(subject)) {
                    if (mark.getPupleId() == pupleId && mark.getValue() == minMark) { //Встретили неуд - увеличиваем плохие оценки
                        badCount += 1;
                        break;
                    } else if (mark.getPupleId() == pupleId && mark.getValue() > minMark) {
                        goodCount += 1;
                        break;
                    }
                }
            }


            float allCount = goodCount + badCount; //Всего сдач в группе
            return (100*badCount / (goodCount + badCount));
        }
        return 0;
    }


    //ready
    public String getTopFivePuples() {

        //Решение - [
        //           Делаем прогулку по каждой группе. Делаем сортировку учеников в каждой группе
        // ]

        StringBuilder result = new StringBuilder("ТОП самых лучших студентов:\n");

        HashMap<Integer, Float> means = new HashMap<>(); //Хранит средние значения.

        for (Integer groupId :
                groups.keySet()) { //Прогуливаемся по id группы

            result.append(groups.get(groupId).getKey()).append("\n"); //Пишем имя группы

            groups.get(groupId).getValue().sort(new Comparator<Integer>() {
                @Override
                public int compare(Integer o1, Integer o2) { //Сортируем два значения по среднему баллу
                    float mean_1 = 0;
                    float mean_2 = 0;

                    if (means.containsKey(o1)) {
                        mean_1 = means.get(o1);
                    } else {
                        mean_1 = calculateMean(o1);
                        means.put(o1, mean_1);
                    }

                    if (means.containsKey(o2)) {
                        mean_2 = means.get(o2);
                    } else {
                        mean_2 = calculateMean(o2);
                        means.put(o2, mean_2);
                    }

                    return Float.compare(mean_2, mean_1);
                }
            });

            //Отсортировали вектор - теперь выведем данные

            int top = 0;
            for (int pupleId : groups.get(groupId).getValue()) {
                if (top < byTop) {
                    result.append("ФИО: ").append(puples.get(pupleId).fio).append(" Балл: ").append(means.get(pupleId)).append("\n");
                } else break;
                top++;
            }


        }

        return result.toString();
    }

    public String getTopFiveGroups() {
        StringBuilder result = new StringBuilder("ТОП групп с двоечниками:\n");

        HashMap<Integer, Pair<Integer, Float>> vals = new HashMap<>();

        ArrayList<Integer> groupsIds = new ArrayList<>(groups.keySet());

        groupsIds.sort(new Comparator<Integer>() {
            @Override
            public int compare(Integer o1, Integer o2) {
                float val_1 = 0;
                float val_2 = 0;

                if (vals.containsKey(o1)) {
                    val_1 = vals.get(o1).getValue();
                } else {
                    Pair<Integer, Float> pval_1 = calculateFailPercent(o1);
                    val_1 = pval_1.getValue();
                    vals.put(o1, pval_1);
                }
                if (vals.containsKey(o2)) {
                    val_2 = vals.get(o2).getValue();
                } else {
                    Pair<Integer, Float> pval_2 = calculateFailPercent(o2);
                    val_2 = pval_2.getValue();
                    vals.put(o2, pval_2);
                }


                return Float.compare(val_2, val_1);
            }
        });

        int top = 0;
        for (int group : groupsIds) {
            if (top < byTop) {
                result.append("Группа: ").append(groups.get(group).getKey()).append("\n");
                result.append("Количество двоечников: ").append(vals.get(group).getKey()).append(" ,Процент двоечников: ").append(vals.get(group).getValue()).append("\n");
            } else break;
            byTop++;
        }

        return result.toString();

    }

    public String getTopFiveSubj() {
        StringBuilder result = new StringBuilder("Топ провальных предметов:\n");


        for (int groupId : groups.keySet()) { //Берём группы
            result.append("-------------\nГруппа: ").append(groups.get(groupId).getKey()).append("\n");
            ArrayList<Integer> subjResult = new ArrayList<>(subjects.keySet());
            HashMap<Integer, Float> vals = new HashMap<>(); //Хранит пары ПРЕДМЕТ-ЗНАЧЕНИЕ

            subjResult.sort(new Comparator<Integer>() {
                @Override
                public int compare(Integer o1, Integer o2) {
                    float val_1 = 0;
                    float val_2 = 0;

                    if (vals.containsKey(o1)) {
                        val_1 = vals.get(o1);
                    } else {
                        val_1 = calculateSubjRateInGroup(groupId, o1);
                        vals.put(o1, val_1);
                    }
                    if (vals.containsKey(o2)) {
                        val_2 = vals.get(o2);
                    } else {
                        val_2 = calculateSubjRateInGroup(groupId, o2);
                        vals.put(o2, val_2);
                    }

                    return Float.compare(val_2, val_1);
                }
            });


            //Пишем результат

            result.append("\nПредметы:\n");

            int top = 0;

            for (int subjId : subjResult) {
                if (top < byTop) {
                    result.append(" Название предмета: ").append(subjects.get(subjId).getName()).append(", Процент: ").append(vals.get(subjId)).append("\n");
                } else
                    break;

                top++;
            }
        }
        return result.toString();
    }

    public String getFinalResult() {
        return new StringBuilder().append(getTopFivePuples()).append(getTopFiveGroups()).append(getTopFiveSubj()).toString();
    }

}

