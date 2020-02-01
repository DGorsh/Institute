#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model = new  QStandardItemModel();

    //заголовки по горизонтали
    QStringList horizontalHeader;
    for (int i = 0; i<26 ; i++) {
       char ch = 65+i;
       horizontalHeader.append(QChar::fromLatin1(ch));
    }
    //Заголовки строк
    QStringList verticalHeader;
    for (int i = 1; i<=100 ; i++) {
       verticalHeader.append(QString::number(i));
    }

    model->setHorizontalHeaderLabels(horizontalHeader);
    model->setVerticalHeaderLabels(verticalHeader);


//    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    ui->tableView->setModel(model);
    ui->tableView->verticalHeader()->setDefaultSectionSize(20);

    for(int i = 0; i < 26; i++){
        for (int j = 0; j<100; j++) {
            model->setData(model->index(j, i), "");
            QBrush brush;
            brush.setStyle(Qt::SolidPattern);
            brush.setColor(Qt::white);
            model->setData(model->index(j, i), brush, Qt::BackgroundRole);
            model->item(j, i)->setTextAlignment(Qt::AlignLeft);
        }
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_open_triggered()
{
    QString XlsxPath = QFileDialog::getOpenFileName(0, "Открытие файла", "","Файлы таблиц Excel (*.xlsx)");
    xlsxFile = new QXlsx::Document(XlsxPath);
    qDebug() << XlsxPath;
    for(int i = 0; i < 26; i++){
        for (int j = 0; j<100; j++) {
            model->setData(model->index(j, i), xlsxFile->read(j+1, i+1));
            qDebug()<<xlsxFile->cellAt(j+1, i+1)->cellType();
            QXlsx::Format format = xlsxFile->cellAt(j+1, i+1)->format();
            QFont font = format.font();
            model->setData(model->index(j, i), font, Qt::FontRole);
            model->setData(model->index(j, i), format.fontColor(), Qt::ForegroundRole);
            QBrush brush;
            brush.setColor(format.patternBackgroundColor());
            //model->setData(model->index(j, i), QColor(Qt::white), Qt::ForegroundRole);
            switch (format.horizontalAlignment()) {
                case QXlsx::Format::AlignLeft: model->item(j, i)->setTextAlignment(Qt::AlignLeft); break;
                case QXlsx::Format::AlignHCenter: model->item(j, i)->setTextAlignment(Qt::AlignCenter); break;
                case QXlsx::Format::AlignRight: model->item(j, i)->setTextAlignment(Qt::AlignRight); break;
            default: break;
            }
            switch (format.fillPattern()) {

            case QXlsx::Format::PatternSolid : brush.setStyle(Qt::SolidPattern); break;
            case QXlsx::Format::PatternGray0625 : brush.setStyle(Qt::Dense1Pattern); break;
            case QXlsx::Format::PatternGray125 : brush.setStyle(Qt::Dense2Pattern); break;
            case QXlsx::Format::PatternLightTrellis : brush.setStyle(Qt::Dense3Pattern); break;
            case QXlsx::Format::PatternMediumGray : brush.setStyle(Qt::Dense4Pattern); break;
            case QXlsx::Format::PatternDarkGrid : brush.setStyle(Qt::Dense5Pattern); break;
            case QXlsx::Format::PatternDarkGray : brush.setStyle(Qt::Dense6Pattern); break;
            case QXlsx::Format::PatternDarkTrellis : brush.setStyle(Qt::Dense7Pattern); break;
            case QXlsx::Format::PatternNone : brush.setStyle(Qt::NoBrush); break;

            default: break;
            }
            model->setData(model->index(j, i), brush, Qt::BackgroundRole);
        }
    }
    qDebug()<<QString("complete");
/* не работает
 *     db.setDatabaseName("DRIVER={Microsoft Excel Driver (*.xls, *.xlsx, *.xlsm, *.xlsb)};DBQ=" + XlsxPath);

        if(db.open()) {

            QSqlQuery query("select from [" + QString("Sheet1") + "$A1:B5]"); // Select range, place A1:B5 after $
                while (query.next())
                {
                    QString column1= query.value(0).toString();
                    qDebug() << column1;
                }
        } */
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    changeButtons();
}

void MainWindow::on_Button_Font_clicked()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, QFont("Helvetica [Cronyx]", 10), this);
    model->setData(ui->tableView->currentIndex(), font, Qt::FontRole);
    changeButtons();
}

void MainWindow::changeButtons() {
    ui->Button_Font->setText(model->item(ui->tableView->currentIndex().row(),ui->tableView->currentIndex().column())->font().family());
    ui->spinBox_Size->setValue(model->item(ui->tableView->currentIndex().row(),ui->tableView->currentIndex().column())->font().pointSize());
    switch(model->item(ui->tableView->currentIndex().row(),ui->tableView->currentIndex().column())->background().style()) {
        case Qt::SolidPattern: ui->combo_BackStyle->setCurrentIndex(0); break;
        case Qt::Dense1Pattern: ui->combo_BackStyle->setCurrentIndex(1); break;
        case Qt::Dense2Pattern: ui->combo_BackStyle->setCurrentIndex(2); break;
        case Qt::Dense3Pattern: ui->combo_BackStyle->setCurrentIndex(3); break;
        case Qt::Dense4Pattern: ui->combo_BackStyle->setCurrentIndex(4); break;
        case Qt::Dense5Pattern: ui->combo_BackStyle->setCurrentIndex(5); break;
        case Qt::Dense6Pattern: ui->combo_BackStyle->setCurrentIndex(6); break;
        case Qt::Dense7Pattern: ui->combo_BackStyle->setCurrentIndex(7); break;
        case Qt::NoBrush: ui->combo_BackStyle->setCurrentIndex(8); break;
        default: break;
    }
    switch(model->item(ui->tableView->currentIndex().row(),ui->tableView->currentIndex().column())->textAlignment()) {
        case Qt::AlignLeft: ui->combo_Align->setCurrentIndex(0); break;
        case Qt::AlignCenter: ui->combo_Align->setCurrentIndex(1); break;
        case Qt::AlignRight: ui->combo_Align->setCurrentIndex(2); break;
        default: break;
    }
    if (model->item(ui->tableView->currentIndex().row(),ui->tableView->currentIndex().column())->font().bold())
        ui->checkBox_Bold->setChecked(true);
    else
        ui->checkBox_Bold->setChecked(false);


    if (model->item(ui->tableView->currentIndex().row(),ui->tableView->currentIndex().column())->font().italic())
        ui->checkBox_Italic->setChecked(true);
    else
        ui->checkBox_Italic->setChecked(false);


    if (model->item(ui->tableView->currentIndex().row(),ui->tableView->currentIndex().column())->font().underline())
        ui->checkBox_Underline->setChecked(true);
    else
        ui->checkBox_Underline->setChecked(false);


}

void MainWindow::on_tableView_entered(const QModelIndex &index)
{
}

void MainWindow::on_Button_TextColor_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white, this);
    model->setData(ui->tableView->currentIndex(), color, Qt::ForegroundRole);
}

void MainWindow::on_Button_BackColor_clicked()
{
    QBrush brush;
    brush.setStyle(model->item(ui->tableView->currentIndex().row(),ui->tableView->currentIndex().column())->background().style());
    brush.setColor(QColorDialog::getColor(Qt::white, this));
    model->setData(ui->tableView->currentIndex(), brush, Qt::BackgroundRole);
}

void MainWindow::on_combo_BackStyle_currentIndexChanged(int index)
{
    QBrush brush;
    brush.setColor(model->item(ui->tableView->currentIndex().row(),ui->tableView->currentIndex().column())->background().color());
    switch(index) {
        case 0: brush.setStyle(Qt::SolidPattern); break;
        case 1: brush.setStyle(Qt::Dense1Pattern); break;
        case 2: brush.setStyle(Qt::Dense2Pattern); break;
        case 3: brush.setStyle(Qt::Dense3Pattern); break;
        case 4: brush.setStyle(Qt::Dense4Pattern); break;
        case 5: brush.setStyle(Qt::Dense5Pattern); break;
        case 6: brush.setStyle(Qt::Dense6Pattern); break;
        case 7: brush.setStyle(Qt::Dense7Pattern); break;
        case 8: brush.setStyle(Qt::NoBrush); break;
    }
    model->setData(ui->tableView->currentIndex(), brush, Qt::BackgroundRole);
    changeButtons();
}

void MainWindow::on_spinBox_Size_valueChanged(int arg1)
{
    QFont font = model->item(ui->tableView->currentIndex().row(),ui->tableView->currentIndex().column())->font();
    font.setPointSize(arg1);
    model->setData(ui->tableView->currentIndex(), font, Qt::FontRole);
    changeButtons();
}

void MainWindow::on_combo_Align_activated(int index)
{
    QStandardItem *item = model->item(ui->tableView->currentIndex().row(),ui->tableView->currentIndex().column());
    switch (index) {
        case 0: item->setTextAlignment(Qt::AlignLeft); break;
        case 1: item->setTextAlignment(Qt::AlignCenter); break;
        case 2: item->setTextAlignment(Qt::AlignRight); break;
    }
    changeButtons();
}

void MainWindow::on_checkBox_Bold_clicked()
{
    QFont font = model->item(ui->tableView->currentIndex().row(),ui->tableView->currentIndex().column())->font();
    if (ui->checkBox_Bold->isChecked()) {
        font.setBold(true);
    } else {
        font.setBold(false);
    }
    model->setData(ui->tableView->currentIndex(), font, Qt::FontRole);
    changeButtons();
}

void MainWindow::on_checkBox_Italic_clicked()
{
    QFont font = model->item(ui->tableView->currentIndex().row(),ui->tableView->currentIndex().column())->font();
    if (ui->checkBox_Italic->isChecked()) {
        font.setItalic(true);
    } else {
        font.setItalic(false);
    }
    model->setData(ui->tableView->currentIndex(), font, Qt::FontRole);
    changeButtons();
}

void MainWindow::on_checkBox_Underline_clicked()
{

    QFont font = model->item(ui->tableView->currentIndex().row(),ui->tableView->currentIndex().column())->font();
    if (ui->checkBox_Underline->isChecked()) {
        font.setUnderline(true);
    } else {
        font.setUnderline(false);
    }
    model->setData(ui->tableView->currentIndex(), font, Qt::FontRole);
    changeButtons();
}



void MainWindow::on_action_save_triggered()
{
    QString XlsxPath = QFileDialog::getSaveFileName(this, QString::fromUtf8("Сохранить файл"), QDir::currentPath(), "Таблицы Excel (*.xlsx)");
    qDebug() << "Path: " << XlsxPath;
    xlsxFileSave = new QXlsx::Document(XlsxPath);
    for(int i = 0; i < 26; i++){
        for (int j = 0; j<100; j++) {
            QStandardItem *item = model->item(j, i);
            QXlsx::Format format;
            format.setFontColor(item->foreground().color());
            format.setFontSize(item->text().size());
            format.setFont(item->font());
            format.setPatternBackgroundColor(item->background().color());
            format.setPatternForegroundColor(Qt::white);
            format.setVerticalAlignment(QXlsx::Format::AlignVCenter);
            switch (item->textAlignment()) {
                case Qt::AlignLeft: format.setHorizontalAlignment(QXlsx::Format::AlignLeft); break;
                case Qt::AlignCenter: format.setHorizontalAlignment(QXlsx::Format::AlignHCenter); break;
                case Qt::AlignRight: format.setHorizontalAlignment(QXlsx::Format::AlignRight); break;
            }

            switch(item->background().style()) {
                case Qt::SolidPattern: format.setFillPattern(QXlsx::Format::PatternSolid); break;
                case Qt::Dense1Pattern: format.setFillPattern(QXlsx::Format::PatternGray0625); break;
                case Qt::Dense2Pattern: format.setFillPattern(QXlsx::Format::PatternGray125); break;
                case Qt::Dense3Pattern: format.setFillPattern(QXlsx::Format::PatternLightTrellis); break;
                case Qt::Dense4Pattern: format.setFillPattern(QXlsx::Format::PatternMediumGray); break;
                case Qt::Dense5Pattern: format.setFillPattern(QXlsx::Format::PatternDarkGrid); break;
                case Qt::Dense6Pattern: format.setFillPattern(QXlsx::Format::PatternDarkGray); break;
                case Qt::Dense7Pattern: format.setFillPattern(QXlsx::Format::PatternDarkTrellis); break;
                case Qt::NoBrush: format.setFillPattern(QXlsx::Format::PatternNone); break;
            }

            format.setBorderStyle(QXlsx::Format::BorderThin);
            xlsxFileSave->write(j+1, i+1, item->data(Qt::DisplayRole), format);
       }
    }
    xlsxFileSave->saveAs(XlsxPath);
}

void MainWindow::on_action_prepod_triggered()
{
    for(int i = 0; i < 26; i++){
        for (int j = 0; j<100; j++) {
            model->setData(model->index(j, i), "");
            QBrush brush;
            brush.setStyle(Qt::SolidPattern);
            brush.setColor(Qt::white);
            model->setData(model->index(j, i), brush, Qt::BackgroundRole);
            model->item(j, i)->setTextAlignment(Qt::AlignLeft);
        }
    }
    QBrush brush;
    QFont font;
    font.setFamily("Arial"); font.setBold(true); font.setPointSize(10);
    brush.setColor(Qt::green); brush.setStyle(Qt::Dense6Pattern);
    model->setData(model->index(0, 1), "Преподаватель");
    model->setData(model->index(0, 2), "Группа");
    model->setData(model->index(0, 3), "Предмет и аудитория");

    model->setData(model->index(0, 1), font, Qt::FontRole);
    model->setData(model->index(0, 2), font, Qt::FontRole);
    model->setData(model->index(0, 3), font, Qt::FontRole);

    model->setData(model->index(0, 1), brush, Qt::BackgroundRole);
    model->setData(model->index(0, 2), brush, Qt::BackgroundRole);
    model->setData(model->index(0, 3), brush, Qt::BackgroundRole);
    font.setFamily("Arial"); font.setBold(true); font.setPointSize(10);
    brush.setColor(Qt::white); brush.setStyle(Qt::SolidPattern);

    int UsedData = 1;
    for (int i = 1; i <= 80; i++) {
        QString prep = xlsxFile->read(2+i, 5).toString();
        QString disc = xlsxFile->read(2+i, 4).toString();
        QString group = xlsxFile->read(1, 4).toString();
        bool Valid = true;
        for (int j = 0; j<UsedData;j++){
            if ((model->item(j, 1)->text() == prep && model->item(j, 2)->text() == group  && model->item(j, 3)->text() == disc) || (prep == "") || (group == "") || (disc == "")) {
               Valid = false;
               break;
            }
        }
        if (Valid) {
            model->setData(model->index(0+UsedData, 0), QString::number(UsedData));
            model->setData(model->index(0+UsedData, 1), prep);
            model->setData(model->index(0+UsedData, 2), group);
            model->setData(model->index(0+UsedData, 3), disc);

            model->setData(model->index(0+UsedData, 1), font, Qt::FontRole);
            model->setData(model->index(0+UsedData, 2), font, Qt::FontRole);
            model->setData(model->index(0+UsedData, 3), font, Qt::FontRole);

            model->setData(model->index(0+UsedData, 1), brush, Qt::BackgroundRole);
            model->setData(model->index(0+UsedData, 2), brush, Qt::BackgroundRole);
            model->setData(model->index(0+UsedData, 3), brush, Qt::BackgroundRole);
            UsedData++;
        }
    }
}


void MainWindow::on_pushButton_Table_clicked()
{
    for(int i = 0; i < 26; i++){
        for (int j = 0; j<100; j++) {
            model->setData(model->index(j, i), "");
            QBrush brush;
            brush.setStyle(Qt::SolidPattern);
            brush.setColor(Qt::white);
            model->setData(model->index(j, i), brush, Qt::BackgroundRole);
            model->item(j, i)->setTextAlignment(Qt::AlignLeft);
        }
    }
    QBrush brush;
    QFont font;
    font.setFamily("Arial"); font.setBold(true); font.setPointSize(10);
    brush.setColor(Qt::green); brush.setStyle(Qt::Dense6Pattern);
    for (int i = 0; i<7; i++){
        model->setData(model->index(0, 2+i), QString::number(i+1));
        model->setData(model->index(0, 2+i), font, Qt::FontRole);
        model->setData(model->index(0, 2+i), brush, Qt::BackgroundRole);
    }
    brush.setColor(Qt::cyan); brush.setStyle(Qt::Dense6Pattern);
    model->setData(model->index(1, 1), "Понедельник");
    model->setData(model->index(1, 1), font, Qt::FontRole);
    model->setData(model->index(1, 1), brush, Qt::BackgroundRole);

    model->setData(model->index(5, 1), "Вторник");
    model->setData(model->index(5, 1), font, Qt::FontRole);
    model->setData(model->index(5, 1), brush, Qt::BackgroundRole);

    model->setData(model->index(9, 1), "Среда");
    model->setData(model->index(9, 1), font, Qt::FontRole);
    model->setData(model->index(9, 1), brush, Qt::BackgroundRole);

    model->setData(model->index(13, 1), "Четверг");
    model->setData(model->index(13, 1), font, Qt::FontRole);
    model->setData(model->index(13, 1), brush, Qt::BackgroundRole);

    model->setData(model->index(17, 1), "Пятница");
    model->setData(model->index(17, 1), font, Qt::FontRole);
    model->setData(model->index(17, 1), brush, Qt::BackgroundRole);

    model->setData(model->index(21, 1), "Суббота");
    model->setData(model->index(21, 1), font, Qt::FontRole);
    model->setData(model->index(21, 1), brush, Qt::BackgroundRole);

    brush.setColor(Qt::green); brush.setStyle(Qt::Dense6Pattern);
    for (int i=1; i<7; i++){
        for (int j=0; j<7; j++) {
             model->setData(model->index(4*i-1, 2+j), font, Qt::FontRole);
             model->setData(model->index(4*i-1, 2+j), brush, Qt::BackgroundRole);
             model->setData(model->index(4*i, 2+j), font, Qt::FontRole);
             model->setData(model->index(4*i, 2+j), brush, Qt::BackgroundRole);
             model->setData(model->index(4*i-1, 0), "II");
             model->setData(model->index(4*i-3, 0), "I");
             model->setData(model->index(4*i-1, 0), font, Qt::FontRole);
             model->setData(model->index(4*i-3, 0), font, Qt::FontRole);
             model->setData(model->index(4*i-1, 0), brush, Qt::BackgroundRole);
             model->setData(model->index(4*i, 0), font, Qt::FontRole);
             model->setData(model->index(4*i, 0), brush, Qt::BackgroundRole);
        }
    }

    for (int i = 0; i < 80; i++){
        QString prep = xlsxFile->read(3+i, 5).toString();
        QString disc = xlsxFile->read(3+i, 4).toString();
        QString group = xlsxFile->read(1, 4).toString();
        font.setFamily("Times New Roman"); font.setBold(true); font.setPointSize(10);
        if (prep == ui->textEdit->toPlainText()) {
            int day = i/14;
            if (i%2 != 0) {
               bool *ok;
               int pair = xlsxFile->read(2+i ,3).toInt(ok);
               model->setData(model->index(4*(day+1)-1, 2+pair), disc);
               model->setData(model->index(4*(day+1)-1, 2+pair), font, Qt::FontRole);
               model->setData(model->index(4*(day+1), 2+pair), group);
               model->setData(model->index(4*(day+1), 2+pair), font, Qt::FontRole);
            } else {
                bool *ok;
                int pair = xlsxFile->read(3+i ,3).toInt(ok);
                model->setData(model->index(4*(day+1)-3, 2+pair), disc);
                model->setData(model->index(4*(day+1)-3, 2+pair), font, Qt::FontRole);
                model->setData(model->index(4*(day+1)-2, 2+pair), group);
                model->setData(model->index(4*(day+1)-2, 2+pair), font, Qt::FontRole);
            }
        }
    }
}

void MainWindow::on_action_packet_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(0, "Открытие файла", "","Файлы пакетов (*.pct)");
    QFile packetFile(fileName);
    QTextStream stream( &packetFile );
    while (!stream.atEnd())
    {
       QString line = stream.readLine(); //read one line at a time
       qDebug()<< line;
    }
}
