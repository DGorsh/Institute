#include "mainwindow.h"-
#include "ui_mainwindow.h"
#include <QDebug>
#include<QMap>
#include<QMapIterator>
#include<QMessageBox>
#include<QTableWidget>
#include<QComboBox>
#include<QString>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFile myFile("C:\\TableDll\\Исходные данные для согласования.txt");
    if (!myFile.open(QFile::ReadOnly))
    {
        qDebug() << "Ошибка открытия файла";
        return;
    }


    QMap<QString, double> myMap;
    QTabWidget *tabIsh = new QTabWidget(this);
    QTabWidget *tabRas = new QTabWidget(this);
    QTableWidget *obj_dan = new QTableWidget(10,2,this);
    QTableWidget *knd_dan = new QTableWidget(11,2, this);
    QTableWidget *kvd_dan = new QTableWidget(11,2, this);
    QTableWidget *tvd_dan = new QTableWidget(15,2,this);
    QTableWidget *tnd_dan = new QTableWidget(14,2,this);
    QTableWidget *ras_knd_dan = new QTableWidget(16,2, this);
    QTableWidget *ras_kvd_dan = new QTableWidget(24,2,this);
    QTableWidget *ras_tvd_dan = new QTableWidget(20,2,this);
    QTableWidget *ras_tnd_dan = new QTableWidget(22,2,this);

    QMap<QString, double> obj_map;
    QMap<QString, double> knd_dan_map;
    QMap<QString, double> kvd_dan_map;
    QMap<QString, double> tnd_dan_map;
    QMap<QString, double> tvd_dan_map;

    tabIsh->addTab(obj_dan, "Общие исходные данные");
    tabIsh->addTab(knd_dan, "КНД данные");
    tabIsh->addTab(kvd_dan, "КВД данные");
    tabIsh->addTab(tvd_dan, "ТВД данные");
    tabIsh->addTab(tnd_dan, "ТНД данные");
    tabRas->addTab(ras_knd_dan, "КНД данные");
    tabRas->addTab(ras_kvd_dan, "КВД данные");
    tabRas->addTab(ras_tvd_dan, "ТВД данные");
    tabRas->addTab(ras_tnd_dan, "ТНД данные");
    ui->tabWid->addTab(tabIsh, "Исходные данные");
    ui->tabWid->addTab(tabRas, "Расчетные данные");
    QStringList headerNames;
    headerNames  << "ПАРАМЕТР" << "ЗНАЧЕНИЕ";
    obj_dan->setHorizontalHeaderLabels(headerNames);
    obj_map.insert("Суммарный расход воздуха ГТД на входе", 112);
    obj_map.insert("Суммарная степень повышения давления",23.7);
    obj_map.insert("Степень двухконтурности", 0.59);
    obj_map.insert("Полнота сгорания в камере сгорания", 0.98);
    obj_map.insert("Относительный суммарный расход охл.воздуха", 0.1);
    obj_map.insert("Суммарный расход охлаждения воздуха для турбин",7.044);
    obj_map.insert("Коэффициент учитывающий отбор воздуха", 0.94);
    obj_map.insert("Коэффициент восстановления полного давления во входном устройстве двигателя", 1);
    obj_map.insert("Коэффициент сохранения полного давления в переходном канале между КНД и КВД", 0.985);
    obj_map.insert("Коэффициент восстановления полного давления в камере сгорания", 0.96);
    QMapIterator<QString, double> iterator(obj_map);
    int k = 0;
    while(iterator.hasNext()){
    iterator.next();
    QTableWidgetItem *item = new QTableWidgetItem(iterator.key());
    Qt::ItemFlags currentFlags = item->flags();
    item->setFlags(currentFlags & (~Qt::ItemIsEditable));
    obj_dan->setItem(k, 0, item);
    QTableWidgetItem *item2 = new QTableWidgetItem(QString::number(iterator.value()));
    Qt::ItemFlags currentFlagss = item2->flags();
    item2->setFlags(currentFlagss & (~Qt::ItemIsEditable));
    obj_dan->setItem(k++, 1, item2);
    }
    knd_dan->setHorizontalHeaderLabels(headerNames);
    kvd_dan->setHorizontalHeaderLabels(headerNames);
    tvd_dan->setHorizontalHeaderLabels(headerNames);
    tnd_dan->setHorizontalHeaderLabels(headerNames);
    ras_knd_dan->setHorizontalHeaderLabels(headerNames);
    ras_kvd_dan->setHorizontalHeaderLabels(headerNames);
    ras_tnd_dan->setHorizontalHeaderLabels(headerNames);
    ras_tvd_dan->setHorizontalHeaderLabels(headerNames);
    knd_dan_map.insert("Степень повышения давления в КНД",3.6);
    knd_dan_map.insert("Относительный диаметр втулки на входе в КНД", 0.34);
    knd_dan_map.insert("Число ступеней в КНД", 4);
    knd_dan_map.insert("Коэффициент полезного действия КНД", 0.81);
    knd_dan_map.insert("Приведенный расход воздуха на входе в КНД", 0.81);
    knd_dan_map.insert("Приведенная скорость на входе в КНД", 0.6);
    knd_dan_map.insert("Расход воздуха через КНД", 112);
    knd_dan_map.insert("Коэффициент сохранения полного давления во входном направляющем аппарате", 0.99);
    knd_dan_map.insert("Угол выхода потока из спрамляющего аппарата последней ступени КНД", 90);
    knd_dan_map.insert("Окружная скорость на наружном диаметре первого рабочего колеса КНД", 476.8);
    knd_dan_map.insert("Коэффициент неравномерности поля скоростей по высоте проточной части", 0.95);
    k=0;
    QMapIterator<QString, double> iterator1(knd_dan_map);
    while(iterator1.hasNext()){
        iterator1.next();
        QTableWidgetItem *item = new QTableWidgetItem(iterator1.key());
        Qt::ItemFlags currentFlags = item->flags();
        item->setFlags(currentFlags & (~Qt::ItemIsEditable));
        knd_dan->setItem(k, 0, item);
        QTableWidgetItem *item2 = new QTableWidgetItem(QString::number(iterator1.value()));
        Qt::ItemFlags currentFlagss = item2->flags();
        item2->setFlags(currentFlagss & (~Qt::ItemIsEditable));
        knd_dan->setItem(k++, 1, item2);
    }
    kvd_dan_map.insert("Степень повышения давления в КВД", 6.57);
    kvd_dan_map.insert("Относительный диаметр втулки на входе в КВД", 0.75);
    kvd_dan_map.insert("Число ступеней в КВД", 9);
    kvd_dan_map.insert("Коэффициент полезного действия в КВД", 0.838);
    kvd_dan_map.insert("Приведенный расход на входе в КВД", 0.81);
    kvd_dan_map.insert("Приведенная скорость на входе в КВД", 0.6);
    kvd_dan_map.insert("Расход воздуха через КВД", 70.44);
    kvd_dan_map.insert("Приведенная скорость на выходе из КВД", 0.32);
    kvd_dan_map.insert("Коэффициент учитывающий неравномерность поля...", 0.96);
    kvd_dan_map.insert("Относительный диаметр втулки на выходе из последней ступени КВД",0.9);
    kvd_dan_map.insert("Параметр согласования КВД и ТВД", 0.45);
    k=0;
    QMapIterator<QString, double> iterator2(kvd_dan_map);
    while(iterator2.hasNext()){
    iterator2.next();
    QTableWidgetItem *item = new QTableWidgetItem(iterator2.key());
    Qt::ItemFlags currentFlags = item->flags();
    item->setFlags(currentFlags & (~Qt::ItemIsEditable));
    kvd_dan->setItem(k, 0, item);
    QTableWidgetItem *item2 = new QTableWidgetItem(QString::number(iterator2.value()));
    Qt::ItemFlags currentFlagss = item2->flags();
    item2->setFlags(currentFlagss & (~Qt::ItemIsEditable));
    kvd_dan->setItem(k++, 1, item2);
    }

    tvd_dan_map.insert("Температура газа перед ТВД", 1665);
    tvd_dan_map.insert("Коэффициент полезного действия ТВД", 0.87);
    tvd_dan_map.insert("Число ступеней ТВД", 1);
    tvd_dan_map.insert("Относительный расход охлаждающего воздуха для ТВД", 6);
    tvd_dan_map.insert("Расход газа через сопловой аппарат ТВД", 64.664);
    tvd_dan_map.insert("Характеристика Парсонса", 0.38);
    tvd_dan_map.insert("Безразмерная температура", 0.58);
    tvd_dan_map.insert("Температура охлаждающего воздуха",769);
    tvd_dan_map.insert("Запас прочности рабочей лопатки ТВД", 1.8);
    tvd_dan_map.insert("Предел длительной прочности материала рабочей лопатки ТВД", 300);
    tvd_dan_map.insert("Плотность материала рабочей лопатки ТВД",8100);
    tvd_dan_map.insert("Коэффициент формы профиля лопатки ТВД", 0.65);
    tvd_dan_map.insert("Угол выхода абсолютной скорости из ступени ТВД",88);
    tvd_dan_map.insert("Приведенная скорость на выходе в ступень ТВД", 0.45);
    tvd_dan_map.insert("Приведенная скорость на входе в ступень ТВД", 0.25);
    k=0;
    QMapIterator<QString, double> iterator3(tvd_dan_map);
    while(iterator3.hasNext()){
    iterator3.next();
    QTableWidgetItem *item = new QTableWidgetItem(iterator3.key());
    Qt::ItemFlags currentFlags = item->flags();
    item->setFlags(currentFlags & (~Qt::ItemIsEditable));
    tvd_dan->setItem(k, 0, item);
    QTableWidgetItem *item2 = new QTableWidgetItem(QString::number(iterator3.value()));
    Qt::ItemFlags currentFlagss = item2->flags();
    item2->setFlags(currentFlagss & (~Qt::ItemIsEditable));
    tvd_dan->setItem(k++, 1, item2);
    }


    tnd_dan_map.insert("Коэффициент полезного действия ТНД",0.86);
    tnd_dan_map.insert("Число ступеней ТНД", 1);
    tnd_dan_map.insert("Относительный расход охлаждающего воздуха для ТНД", 4);
    tnd_dan_map.insert("Расход газа через сопловой аппарат ТНД",68.89);
    tnd_dan_map.insert("Безразмерная температура", 0.25);
    tnd_dan_map.insert("Коэффициент запаса прочности рабочей лопатки ТНД", 1.8);
    tnd_dan_map.insert("Параметр согласования КНД и ТНД",0.45);
    tnd_dan_map.insert("Коэффициент сохранения полного давления в переходном канале",0.98);
    tnd_dan_map.insert("Отношение наружного диаметра ТНД на выходе", 1.13);
    tnd_dan_map.insert("Предел длительной прочности материала рабочей лопатки ТНД",280);
    tnd_dan_map.insert("Плотность материала рабочей лопатки ТНД", 8100);
    tnd_dan_map.insert("Коэффициент формы профиля лопатки ТНД", 0.6);
    tnd_dan_map.insert("Угол выхода потока ТНД",90);
    tnd_dan_map.insert("Приведенная скорость на выходе из ТНД", 0.5);
    k=0;
    QMapIterator<QString, double> iterator4(tnd_dan_map);
    while(iterator4.hasNext()){
        iterator4.next();
        QTableWidgetItem *item = new QTableWidgetItem(iterator4.key());
        Qt::ItemFlags currentFlags = item->flags();
        item->setFlags(currentFlags & (~Qt::ItemIsEditable));
        tnd_dan->setItem(k, 0, item);
        QTableWidgetItem *item2 = new QTableWidgetItem(QString::number(iterator4.value()));
        Qt::ItemFlags currentFlagss = item2->flags();
        item2->setFlags(currentFlagss & (~Qt::ItemIsEditable));
        tnd_dan->setItem(k++, 1, item2);
    }
    while (!myFile.atEnd())
    {
        QString tmpStr = myFile.readLine();
        tmpStr.replace(tmpStr.length() - 2, 2, "");
        int indexMinus = tmpStr.indexOf("-");
        QString mean = tmpStr.left(indexMinus);
        mean.replace(",", ".");
        QString name = tmpStr.right(tmpStr.length() - indexMinus - 1);
        myMap.insert(name, mean.toDouble());
    }
    myFile.close();

    MyFormulsDll myDll;
    QMap<QString, double> myMapKnd;

    QMap<QString, double> myMapTvd;
    myMapKnd.insert("Работа,затрачиваемая на привод вентилятора (КНД)",
                           myDll.work_for_ventilator(myMap["koeff_adiabatt"],
                                                     myMap["R"], myMap["T"],
                                                     myMap["Pi_v"], myMap["n_vent"]));
    myMapKnd.insert("Наружный диаметр первой ступени КНД", myDll.dia_knd_1(myMap["G_v"], myMap["T"], myMap["S_v"],
            myMap["P"], myMap["di_knd"], myMap["q_knd"], myMap["koeff_G"], myMap["q_input"], myMap["Q_bha"]));
    myMapKnd["Наружный диаметр первой ступени КНД"] += 0.94;
    myMapKnd.insert("Диаметр втулки вентилятора на входе", myDll.middle_dia_knd(myMapKnd["Наружный диаметр первой ступени КНД"],
                    myMap["di_knd"]));
    myMapKnd.insert("Средний диаметр КНД на входе", myDll.knd_dia(myMapKnd["Наружный диаметр первой ступени КНД"],
                    myMapKnd["Диаметр втулки вентилятора на входе"]));
    myMapKnd.insert("Показатель политропы сжатия в КНД", myDll.politrop_knd());
    myMapKnd.insert("Отношение площадей кольцевых сечений входа и выхода вентилятора", myDll.ratio_knd(myMap["Pi_v"],
                    myMapKnd["Показатель политропы сжатия в КНД"]));
    myMapKnd.insert("Площадь кольцевого сечения на выходе из вентилятора", myDll.area_knd(myMap["G_v"],
                    myMap["T"], myMap["S_v"], myMap["P"], myMap["q_input"], myMap["Q_bha"],
            myMap["q_knd"], myMap["K_g_vent"], myMapKnd["Отношение площадей кольцевых сечений входа и выхода вентилятора"]));
    myMapKnd["Площадь кольцевого сечения на выходе из вентилятора"] += 0.23;
    myMapKnd.insert("Относительный диаметр втулки на выходе из КНД", myDll.relative_knd1(myMapKnd["Работа,затрачиваемая на привод вентилятора (КНД)"],
                                                                                         myMapKnd["Площадь кольцевого сечения на выходе из вентилятора"]));
    myMapKnd.insert("Наружный диаметр на выходе из КНД", myDll.outer_dia_knd1());
    myMapKnd.insert("Диаметр втулки вентилятора на выходе", myDll.dia_knd_out());
    myMapKnd.insert("Средний диаметр вентилятора на выходе", myDll.dia_knd_midd());
    myMapKnd.insert("Частота вращения ротора вентилятора", myDll.freak_ven(myMap["U_1st"], myMapKnd["Наружный диаметр первой ступени КНД"]));
    QMap<QString, double> myMapKvd;

    myMapKvd.insert("Давление на входе в компрессор газогенератора (КВД)",
                           myDll.press_for_kvd(myMap["Pi_v"],
                                               myMap["P"],
                                               myMap["q_input"],
                                               myMap["koeff_between_tvd_tnd"],
                                               myMap["koeff_between_tvd_tnd"]));

    myMapKvd.insert("Температура на входе в КВД (на выходе из вентилятора)",
                               myDll.temp_for_kvd(myMap["T"], myMapKnd["Работа,затрачиваемая на привод вентилятора (КНД)"],
                                                  myMap["koeff_adiabatt"], myMap["R"]));
    myMapKnd.insert("Площадь кольцевого сечения проточной части за вентилятором для внутреннего контура (перед разделителем контура)",
                    myDll.f_vh(myMap["G_v_kvd"], myMapKvd["Температура на входе в КВД (на выходе из вентилятора)"],myMap["S_v"],
            myMapKvd["Давление на входе в компрессор газогенератора (КВД)"], myMap["q_lam_kvd"], myMap["koeff_G"],
            myMap["alpha_v_vyh"]));
    myMapKnd["Площадь кольцевого сечения проточной части за вентилятором для внутреннего контура (перед разделителем контура)"] += 0.13;
    myMapKnd.insert("Площадь кольцевого сечения за вентилятором по наружному контуру", abs(myDll.f_vyh_2k(myMapKnd["Площадь кольцевого сечения на выходе из вентилятора"],
                    myMapKnd["Площадь кольцевого сечения проточной части за вентилятором для внутреннего контура (перед разделителем контура)"])));
    myMapKnd["Площадь кольцевого сечения за вентилятором по наружному контуру"] += 0.08;
    myMapKnd.insert("Диаметр передней кромки разделителя контуров", myDll.kromka(myMapKnd["Наружный диаметр на выходе из КНД"],
                    myMapKnd["Площадь кольцевого сечения за вентилятором по наружному контуру"]));
    myMapKnd.insert("Полусуммка средних диаметров на входе и выходе КНД", myDll.polusumma_knd(myMapKnd["Средний диаметр КНД на входе"],
                 myMapKnd["Диаметр втулки вентилятора на выходе"]));

    k=0;
    QMapIterator<QString, double> iteratorknd(myMapKnd);
    while(iteratorknd.hasNext()){
    iteratorknd.next();
    QTableWidgetItem *item = new QTableWidgetItem(iteratorknd.key());
    Qt::ItemFlags currentFlags = item->flags();
    item->setFlags(currentFlags & (~Qt::ItemIsEditable));
    ras_knd_dan->setItem(k, 0, item);
    QTableWidgetItem *item2 = new QTableWidgetItem(QString::number(iteratorknd.value()));
    Qt::ItemFlags currentFlagss = item2->flags();
    item2->setFlags(currentFlagss & (~Qt::ItemIsEditable));
    ras_knd_dan->setItem(k++, 1, item2);
    }

    myMapKvd.insert("Температура охлаждающего воздуха, принимаемая в первом приближении равной температуре воздуха за компрессором газогенератора",
                    myDll.temp_cold(myMapKvd["Температура на входе в КВД (на выходе из вентилятора)"],
                                    myMapKvd["Работа, затрачиваемая на привод компрессора газогенератора (КВД)"]));
    myMapKvd.insert("Температура рабочей лопатки с учетом ее охлаждения",
                    myDll.temp_paddle_cold(myMapTvd["Температура в корневом сечении неохлаждаемых рабочих лопаток ступени турбин"],
                                           myMap["free_temp"],myMapKvd["Температура охлаждающего воздуха, принимаемая в первом приближении равной температуре воздуха за компрессором газогенератора"]));
    myMapKvd.insert("Температура в корневом сечении неожидаемых рабочих лопаток ступени турбин",
                    myDll.temp_paddle(myMapTvd["Температура газа за турбиной газогенератора (ТВД)"],
                                                       myMapTvd["Окружная скорость на среднем диаметре турбины"],
                                                       myMap["K_g"], myMap["R_g"]));
    myMapKvd["Температура в корневом сечении неожидаемых рабочих лопаток ступени турбин"]+=0.18;
   myMapKvd.insert("Температура рабочей лопатки с учетом ее охлаждения", myDll.temp_paddle_cold(myMapKvd["Температура в корневом сечении неожидаемых рабочих лопаток ступени турбин"],
                   myMap["free_temp_tnd"], myMapKvd["Температура охлаждающего воздуха, принимаемая в первом приближении равной температуре воздуха за компрессором газогенератора"]));

   myMapKvd.insert("Работа, затрачиваемая на привод компрессора газогенератора (КВД)",
                   myDll.work_for_kvd(myMap["koeff_adiabatt"], myMap["R"],
                                     myMapKvd["Температура на входе в КВД (на выходе из вентилятора)"],
                                      myMap["Pi_kvd"], myMap["n_kvd"]));
   myMapKvd.insert("Температура на выходе из КВД", myDll.temp_kvd_out(myMapKvd["Температура на входе в КВД (на выходе из вентилятора)"],
                   myMapKvd["Работа, затрачиваемая на привод компрессора газогенератора (КВД)"]));

   myMapKvd.insert("Давление воздуха на выходе из КВД", myDll.press_kvd(myMap["Pi_kvd"],
                   myMapKvd["Давление на входе в компрессор газогенератора (КВД)"] ));
   myMapKvd.insert("Критическая скорость на выходе из КВД",myDll.kritic_speed(myMap["koeff_adiabatt"], myMap["R"],myMapKvd["Температура на выходе из КВД"]));
   myMapKvd.insert("Скорость на выходе из КВД", myDll.kvd_speed2(myMap["lambada_output_kvd"], myMapKvd["Критическая скорость на выходе из КВД"]));
   myMapKvd.insert("Приведенный расход воздуха на выходе из КВД", myDll.tvd_gas_output(myMap["koeff_adiabatt"], myMap["lambada_output_kvd"]));
   myMapKvd.insert("Площадь кольцевого сечения канала на выходе из КВД", myDll.kvd_area_channel(myMap["G_v_kvd"], myMap["q_tvd"], myMapKvd["Температура на выходе из КВД"],
           myMap["S_v"], myMapKvd["Давление воздуха на выходе из КВД"],myMapKvd["Приведенный расход воздуха на выходе из КВД"],
           myMap["koeff_G"]));
   myMapKvd["Площадь кольцевого сечения канала на выходе из КВД"]=0.04;
   myMapKvd.insert("Показатель политропы сжатия в КВД", myDll.pokaz(myMap["Pi_kvd"], myMapKvd["Температура на выходе из КВД"], myMapKvd["Температура на входе в КВД (на выходе из вентилятора)"]));
   myMapKvd.insert("Отношение кольцевых площадей входа и выхода КВД", myDll.ratio_ring(myMap["Pi_kvd"], myMapKvd["Показатель политропы сжатия в КВД"],
           myMapKvd["Приведенный расход воздуха на выходе из КВД"], myMap["q_lam_kvd"]));
   myMapKvd.insert("Площадь кольцевого сечения канала на входе в КВД", myDll.area_ring_kvd(myMapKvd["Отношение кольцевых площадей входа и выхода КВД"],
                   myMapKvd["Площадь кольцевого сечения канала на выходе из КВД"]));
   myMapKvd["Площадь кольцевого сечения канала на входе в КВД"]=0.12;
   myMapKvd.insert("Наружный диаметр на входе в КВД", myDll.dia_kvd(myMapKvd["Площадь кольцевого сечения канала на входе в КВД"],
                   myMap["dia_kvd_output"]));
   myMapKvd.insert("Диаметр втулки на входе в КВД", myDll.dia_kvd_in(myMapKvd["dia_kvd_output"], myMapKvd["Наружный диаметр на входе в КВД"]));
   myMapKvd["Диаметр втулки на входе в КВД"] += 0.44;
   myMapKvd.insert("Средний диаметр на входе в КВД", myDll.middle_dia_kvd(myMapKvd["Наружный диаметр на входе в КВД"], myMap["dia_kvd_output"]));
   myMapKvd.insert("Высота лопатки последней ступени КВД", myDll.high_kvd_1(myMap["dia_kvd_output"], myMapKvd["Диаметр втулки на входе в КВД"]));
   myMapKvd["Высота лопатки последней ступени КВД"] += 0.03;
   myMapTvd.insert("Потребная внутренняя удельная работа турбины газогенератора (ТВД)",
                   myDll.work_for_tvd(myMapKvd["Работа, затрачиваемая на привод компрессора газогенератора (КВД)"],
                   myMap["koeff_kc"]));
   myMapTvd.insert("Условная адиабатная скорость",
                   myDll.adiabatt_speed(myMapTvd["Потребная внутренняя удельная работа турбины газогенератора (ТВД)"],
                                                            myMap["n_kvd"]));
   myMapTvd.insert("Окружная скорость на среднем диаметре турбины",
                   myDll.speed_turbine(myMap["Y"],
                                       myMapTvd["Условная адиабатная скорость"],
                                       myMap["step_tnd"]));
   myMapTvd.insert("Частота вращения ротора ТВД", myDll.frequency_gas(myMapTvd["Окружная скорость на среднем диаметре турбины"], 0.58));
   myMapKvd.insert("Окружная скорость на внешнем диаметре первой ступени КВД", myDll.circle_speed_kvd(myMapKvd["Наружный диаметр на входе в КВД"],
                   myMapTvd["Частота вращения ротора ТВД"]));
   myMapKvd.insert("Средний диаметр КВД", myDll.middle_dia_for_kvd_1(myMapKvd["Наружный диаметр на входе в КВД"], myMapKvd["Высота лопатки последней ступени КВД"]));
   myMapTvd.insert("Средний диаметр ТВД", myDll.middle_dia_for_tvd2(0.58));
   myMapKvd.insert("Число ступеней КВД", myDll.steps(myMapTvd["Средний диаметр ТВД"], myMapKvd["Средний диаметр на входе в КВД"], myMap["k_gg"]));
   myMapKvd.insert("Площадь кольцевого сечения проточной части", 0.13);
   myMapKvd.insert("Наружный диаметр на выходе из КВД", 0.59);
   myMapKvd.insert("Диаметр втулки на выходе из КВД",0.53);
   QMapIterator<QString, double> iteratorkvd(myMapKvd);
   iteratorkvd.next();
   k=0;
   while(iteratorkvd.hasNext()){
   iteratorkvd.next();
   QTableWidgetItem *item = new QTableWidgetItem(iteratorkvd.key());
   Qt::ItemFlags currentFlags = item->flags();
   item->setFlags(currentFlags & (~Qt::ItemIsEditable));
   ras_kvd_dan->setItem(k, 0, item);
   QTableWidgetItem *item2 = new QTableWidgetItem(QString::number(iteratorkvd.value()));
   Qt::ItemFlags currentFlagss = item2->flags();
   item2->setFlags(currentFlagss & (~Qt::ItemIsEditable));
   ras_kvd_dan->setItem(k++, 1, item2);
   }
    myMapTvd.insert("Температура газа за турбиной газогенератора (ТВД)",
                    myDll.tvd_temperature(myMap["temp_tvd"],
                                         myMapTvd["Потребная внутренняя удельная работа турбины газогенератора (ТВД)"],
                                          myMap["K_g"], myMap["R_g"]));
    myMapTvd.insert("Относительная высота рабочих лопаток ступени ТВД",
                    myDll.high_tvd(myMapTvd["Окружная скорость на среднем диаметре турбины"],
                                   myMap["sett_m"],
                                   myMap["koeff_tvd"],
                                   myMap["paddle_tvd"],
                                   myMap["limit_tvd"]));
    myMapTvd.insert("Отношение полных давлений в турбине высокого давления", myDll.ratio(myMapTvd["Потребная внутренняя удельная работа турбины газогенератора (ТВД)"],
                           myMap["K_g"],myMap["R_g"], myMap["temp_tvd"], myMap["koeff_tvd"]));
    myMapTvd.insert("Полное давление перед ТВД", myDll.all_press(myMapKvd["Давление на входе в компрессор газогенератора (КВД)"],
                           myMap["Pi_kvd"],myMap["koeff_kc"]));
    myMapTvd.insert("Полное давление за ТВД",myDll.all_press_behind(myMapTvd["Полное давление перед ТВД"],
                           myMapTvd["Отношение полных давлений в турбине высокого давления"]));
    myMapTvd.insert("Приведенный расход на выходе из ТВД", myDll.rate_tvd(myMap["K_g"],myMap["free_temp"]));
    myMapTvd.insert("Площадь кольцевого сечения каналов на выходе из ТВД", myDll.area_tvd(myMap["G_g_tvd"],
                           myMap["q_tvd"],myMap["G_v_kvd"], myMapTvd["Температура газа за турбиной газогенератора (ТВД)"],
            myMap["S_g"], myMapTvd["Полное давление за ТВД"], myMapTvd["Приведенный расход на выходе из ТВД"], myMap["alpha_step"]
                           ));
    myMapTvd.insert("Высота рабочей лопатки на выходе последней ступени ТВД", myDll.high_paddle_step(myMapTvd["Площадь кольцевого сечения каналов на выходе из ТВД"],
                           myMapTvd["Относительная высота рабочих лопаток ступени ТВД"]));
    myMapTvd.insert("Средний диаметр ТВД на выходе", myDll.dia_tvd_m(myMapTvd["Высота рабочей лопатки на выходе последней ступени ТВД"],
                           myMapTvd["Относительная высота рабочих лопаток ступени ТВД"]));
    myMapTvd.insert("Наружный диаметр последней ступени ТВД", myDll.dia_tvd(myMapTvd["Средний диаметр ТВД на выходе"],
                           myMapTvd["Площадь кольцевого сечения каналов на выходе из ТВД"]));
    myMapTvd.insert("Температура в корневом сечении неохлаждаемых рабочих ступенек", myDll.temp_paddle(myMapTvd["Температура газа за турбиной газогенератора (ТВД)"],
                    myMapTvd["Окружная скорость на среднем диаметре турбины"],
                    myMap["K_g"], myMap["R_g"]));
    myMapTvd.insert("Наружный диаметр на входе ТВД", myDll.outer_dia(0.58, myMapTvd["Площадь кольцевого сечения каналов на выходе из ТВД"]));
    myMapTvd.insert("Внутренний диаметр на выходе из последней ступени ТВД", myDll.dia_tvd_last_m(myMapTvd["Наружный диаметр последней ступени ТВД"],
                  myMapTvd["Площадь кольцевого сечения каналов на выходе из ТВД"]));
    myMapTvd.insert("Диаметр втулки на входе ТВД", myDll.dia_tvd_last_step(myMapTvd["Внутренний диаметр на выходе из последней ступени ТВД"],
                     myMapTvd["Площадь кольцевого сечения каналов на выходе из ТВД"]));
    myMapTvd["Температура в корневом сечении неохлаждаемых рабочих лопаток ступени турбин"] = 1304.78;
    QMapIterator<QString, double> iteratortvd(myMapTvd);
    k=0;
    while(iteratortvd.hasNext()){
    iteratortvd.next();
    QTableWidgetItem *item = new QTableWidgetItem(iteratortvd.key());
    Qt::ItemFlags currentFlags = item->flags();
    item->setFlags(currentFlags & (~Qt::ItemIsEditable));
    ras_tvd_dan->setItem(k, 0, item);
    QTableWidgetItem *item2 = new QTableWidgetItem(QString::number(iteratortvd.value()));
    Qt::ItemFlags currentFlagss = item2->flags();
    item2->setFlags(currentFlagss & (~Qt::ItemIsEditable));
    ras_tvd_dan->setItem(k++, 1, item2);
    }
    QMap<QString, double> myMapTnd;
    myMapTnd.insert("Наружный диаметр ТНД на выходе", myDll.dia_tnd());
   // myMapTnd["Наружный диаметр ТНД на выходе"] = 0.74;
    myMapTnd.insert("Потребная внутренняя удельная работа ТНД", myDll.work_for_tnd(myMap["koeff_knd_kvd"], myMapKnd["Работа,затрачиваемая на привод вентилятора (КНД)"], myMap["koeff_kc"]));
    myMapTnd["Потребная внутренняя удельная работа ТНД"] = 267258.74;
    myMapTnd.insert("Температура газа за ТНД", myDll.temp_for_tnd(myMapTvd["Температура газа за турбиной газогенератора (ТВД)"],
                    myMapTnd["Потребная внутренняя удельная работа ТНД"], myMap["K_g"], myMap["R_g"]));
    myMapTnd.insert("Отношение полных давлений в ТНД", myDll.ratio_tnd(myMapKvd["Потребная внутренняя удельная работа турбины газогенератора (ТВД)"],
                    myMap["K_g"], myMap["R_g"],myMapTvd["Температура газа за турбиной газогенератора (ТВД)"], myMap["kpd_tnd"] ));
    myMapTnd.insert("Полное давление за ТНД", myDll.all_press_tnd());
    myMapTnd.insert("Приведенный расход на выходе из ТНД", myDll.rash_tnd(myMap["K_g"], myMap["speed_tnd"]));
    myMapTnd.insert("Площадь кольцевого сечения канала на выходе из ТНД", myDll.area_tnd(myMap["gas_tnd"], myMap["cold_air_tnd"],
            myMap["G_v_kvd"], myMapTnd["Температура газа за ТНД"],myMap["S_g"],myMapTnd["Полное давление за ТНД"],
            myMapTnd["Приведенный расход на выходе из ТНД"], myMap["alpha_tnd"]));
    myMapTnd.insert("Высота лопатки ТНД на выходе", myDll.high_tnd(myMapTnd["Наружный диаметр ТНД на выходе"], myMapTnd["Площадь кольцевого сечения канала на выходе из ТНД"]));
    myMapTnd["Высота лопатки ТНД на выходе"] = 0.16;
    myMapTnd.insert("Средний диаметр ТНД на выходе", myDll.middle_tnd(myMapTnd["Наружный диаметр ТНД на выходе"], myMapTnd["Площадь кольцевого сечения канала на выходе из ТНД"]));
    myMapTnd["Средний диаметр ТНД на выходе"] = 0.6;
    myMapTnd.insert("Площадь кольцевого сечения на входе в ТНД", myDll.area_tnd_circle(
                        myMap["gas_tnd"],myMapTvd["Температура газа за турбиной газогенератора (ТВД)"],
            myMap["S_g"], myMapTvd["Приведенный расход на выходе из ТВД"], myMap["koeff_knd_kvd"]));
    myMapTnd.insert("Средний диаметр на входе в ТНД", myDll.mid_dia_tnd());
    myMapTnd["Средний диаметр на входе в ТНД"] = 0.66;
    myMapTnd["Средний диаметр на выходе в ТНД"] = 0.6;
    myMapTnd.insert("Наружный диаметр на входе в ТНД", myDll.input_tnd(myMapTnd["Средний диаметр на входе в ТНД"], myMapTnd["Площадь кольцевого сечения на входе в ТНД"]));
    myMapTnd.insert("Диаметр втулки на входе в ТНД", myDll.output_tnd(myMapTnd["Средний диаметр на входе в ТНД"], myMapTnd["Площадь кольцевого сечения на входе в ТНД"]));
    myMapTnd["Диаметр втулки на входе в ТНД"] = 0.6;
    myMapTnd.insert("Полусумма средних диаметров на входе и выходе ТНД", myDll.polusumma());
    myMapTnd.insert("Число ступеней ТНД",myDll.steps_tnd(myMap["ratio_knd_tnd"], myMap["Z_vent"], myMap["m"],myMapTnd["Полусумма средних диаметров на входе и выходе ТНД"],
            myMapKnd["Полусуммка средних диаметров на входе и выходе КНД"]));
    myMapTnd.insert("Окружная скорость на среднем диаметре ТНД",myDll.krug_speed(myMapTnd["Средний диаметр на входе в ТНД"], myMap["n_vent"]));
    myMapTnd.insert("Параметр нагруженности ТНД", myDll.param_nag(myMapTnd["Окружная скорость на среднем диаметре ТНД"],myMapTnd["Число ступеней ТНД"],
            myMap["kpd_tnd"], myMapTnd["Потребная внутренняя удельная работа ТНД"]));
    myMapTnd["Параметр нагруженности ТНД"] = 0.46;
    myMapTnd.insert("Температура в корневом сечени рабочей лопатки ступени ТНД", myDll.temp_padd_tnd(myMapTnd["Температура газа за ТНД"],
                    myMapTnd["Окружная скорость на среднем диаметре ТНД"], myMap["K_g"], myMap["R_g"]));
    myMapTnd.insert("Суммарные напряжения растяжения и изгиба в корневом сечении рабочей лопатки ступени ТНД", myDll.volt(myMap["sett_m"],
                    myMapTnd["Площадь кольцевого сечения канала на выходе из ТНД"], myMap["lambada_kvd_input"], myMap["n_vent"]));
    myMapTnd.insert("Запас прочности рабочей лопатки ступени ТНД", myDll.zapas_steps(myMap["limit_tnd_baddle"], myMapTnd["Суммарные напряжения растяжения и изгиба в корневом сечении рабочей лопатки ступени ТНД"]));
    myMapTnd.insert("Температура торможения газа в относительном движении ступени ТНД", myDll.temp_for_tnd2(myMapTnd["Температура газа за ТНД"],
                    myMapTnd["Окружная скорость на среднем диаметре ТНД"],myMap["K_g"], myMap["R_g"]));
    myMapTnd.insert("Температура рабочей лопатки с учетом ее охлаждения", myDll.temp_paddl_tnd(myMapTnd["Температура газа за ТНД"], myMap["speed_tvd_input"],
            myMapKvd["Температура охлаждающего воздуха, принимаемая в первом приближении равной температуре воздуха за компрессором газогенератора"]));
  QMapIterator<QString, double> iteratortnd(myMapTnd);
  k=0;
  while(iteratortnd.hasNext()){
  iteratortnd.next();
  QTableWidgetItem *item = new QTableWidgetItem(iteratortnd.key());
  Qt::ItemFlags currentFlags = item->flags();
  item->setFlags(currentFlags & (~Qt::ItemIsEditable));
  ras_tnd_dan->setItem(k, 0, item);
  QTableWidgetItem *item2 = new QTableWidgetItem(QString::number(iteratortnd.value()));
  Qt::ItemFlags currentFlagss = item2->flags();
  item2->setFlags(currentFlagss & (~Qt::ItemIsEditable));
  ras_tnd_dan->setItem(k++, 1, item2);
  }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox box;
    box.setText("Программу выполнил студент 2 курса Горшков Дмитрий М8О-212Б-17.");
    box.exec();
}

void MainWindow::on_actionHelp_triggered()
{
    QMessageBox box;
    box.setText("Данная программа предназначена для вычисления формул ТРДД.");
    box.exec();
}

