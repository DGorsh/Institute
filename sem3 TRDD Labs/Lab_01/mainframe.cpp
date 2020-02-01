#include "mainframe.h"
#include "ui_mainframe.h"
#include "aboutframe.h"


MainFrame::MainFrame(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainFrame)
{
    ui->setupUi(this);

    //tree view
    model = new QFileSystemModel(this); //задаем модель файловой системы
    model->setFilter(QDir::AllDirs | QDir::NoDotAndDotDot); //фильтр для папок
    model->setRootPath(""); //коренной каталог, откуда начинаем искать файл с текстом
    ui->treeView->setModel(model);
    ui->treeView->hideColumn(1);
    ui->treeView->hideColumn(2);
    ui->treeView->hideColumn(3);

    //layout
    QVBoxLayout *vlay = new QVBoxLayout();
    QHBoxLayout *hlay = new QHBoxLayout();
    hlay->addWidget(ui->treeView);
    hlay->addWidget(ui->listWidget);
    hlay->addWidget(ui->textEdit);
    vlay->addLayout(hlay);
    QHBoxLayout *hlay2 = new QHBoxLayout();

    //Codec
    QVBoxLayout *vlayCodec = new QVBoxLayout();
    vlayCodec -> addWidget(ui->radioCP);
    vlayCodec -> addWidget(ui->radioUTF);
    ui->groupCodec->setLayout(vlayCodec);
    hlay2->addWidget(ui->groupCodec);
    //Style
    QVBoxLayout *vlayStyle = new QVBoxLayout();
    vlayStyle -> addWidget(ui->boxBold);
    vlayStyle -> addWidget(ui->boxItalic);
    vlayStyle -> addWidget(ui->boxUnder);
    ui->groupStyle->setLayout(vlayStyle);
    hlay2->addWidget(ui->groupStyle);
    //Other
    QVBoxLayout *vlayOther = new QVBoxLayout();
    QHBoxLayout *hlayOther = new QHBoxLayout();
    hlayOther -> addWidget(ui->label);
    hlayOther -> addWidget(ui->comboBox);
    vlayOther -> addLayout(hlayOther);
    vlayOther -> addWidget(ui->pushButton);
    vlayOther -> addWidget(ui->pushButtonSave);
    ui->groupOther->setLayout(vlayOther);
    hlay2->addWidget(ui->groupOther);
    //
    vlay->addWidget(ui->line);
    vlay->addLayout(hlay2);
    QWidget *widget = new QWidget();
    widget->setLayout(vlay);
    this->setCentralWidget(widget);
}


MainFrame::~MainFrame()
{
    delete ui;
}


void MainFrame::on_action_exit_triggered()
{
   QCoreApplication::quit();
}

void MainFrame::on_action_help_triggered()
{
    aboutframe aboutfr;
    aboutfr.setModal(true);
    aboutfr.exec();
}

// функция, меняющая лист при выборе папки.
void MainFrame::on_treeView_activated(const QModelIndex &index)
{
    // проверка валидации индекса
    if (!index.isValid()) return;
    QFileInfo fileinfo = model->fileInfo(index);
    fileWay = fileinfo.absoluteFilePath();
    //проверка на существование папки
    QDir Directory(fileWay);
    if (!Directory.exists()) {
        ui->textEdit->setText("Папки не существует");
        return;
    }
    //фильтр файлов (если он не нужен - закомментировать две след. строчки)
    QStringList nameFilter("*.txt");
    QStringList fileNames = Directory.entryList(nameFilter);
    //если не нужен фильтр - откомментировать след. строчку
    //QStringList fileNames = Directory.entryList(QDir::Files);

    ui->listWidget->clear();
    ui->listWidget->addItems(fileNames);
}

//чтение файла после выбора файла
void MainFrame::on_listWidget_activated(const QModelIndex &index)
{
    if (ui->listWidget->currentRow() == -1)
        return;

    QString fileName = ui->listWidget->item(ui->listWidget->currentRow())->text();
    QFile openedFile(fileWay + "/" + fileName);
    QFileInfo fileSuffix(openedFile);

    if (!openedFile.open(QFile::ReadOnly | QFile::Text) || fileSuffix.suffix() != "txt")
    {
        ui->textEdit->setText("Ошибка открытия файла");
        return;
    }

    QTextStream fileStream(&openedFile);

    if (ui->radioUTF->isChecked())
        fileStream.setCodec("UTF-8");
    else
        fileStream.setCodec("CP1251");

    if (!fileStream.codec())
    {
        ui->textEdit->setText("Ошибка кодировки");
        return;
    }

    ui->textEdit->setText("");
    while (!fileStream.atEnd())
        ui->textEdit->insertPlainText(fileStream.read(1024));

    openedFile.close();
}


void MainFrame::on_comboBox_currentIndexChanged(int index)
{
    //выбор цвета
    switch (index) {
        case 0: ui->textEdit->setTextColor(QColor(0, 0, 0)); break;
        case 1: ui->textEdit->setTextColor(QColor(255, 0, 0)); break;
        case 2: ui->textEdit->setTextColor(QColor(0, 255, 0)); break;
        case 3: ui->textEdit->setTextColor(QColor(0, 0, 255)); break;
        case 4: ui->textEdit->setTextColor(QColor(128,128,128)); break;
    }
    //костыль для мгновенного обновления цвета
    QString Text = ui->textEdit->toPlainText();
    ui->textEdit->setText(Text);
}


void MainFrame::on_boxBold_clicked()
{
    if (ui->boxBold->isChecked()) {
        ui->textEdit->setFontWeight(QFont::Bold);
    }
    else
    {
        ui->textEdit->setFontWeight(QFont::Normal);
    }
    //костыль для мгновенного обновления
    QString Text = ui->textEdit->toPlainText();
    ui->textEdit->setText(Text);
}

void MainFrame::on_boxItalic_clicked()
{
    if (ui->boxItalic->isChecked()) {
        ui->textEdit->setFontItalic(true);
    }
    else
    {
        ui->textEdit->setFontItalic(false);
    }
    //костыль для мгновенного обновления
    QString Text = ui->textEdit->toPlainText();
    ui->textEdit->setText(Text);
}

void MainFrame::on_boxUnder_clicked()
{
    if (ui->boxUnder->isChecked()) {
        ui->textEdit->setFontUnderline(true);
    }
    else
    {
        ui->textEdit->setFontUnderline(false);
    }
    //костыль для мгновенного обновления
    QString Text = ui->textEdit->toPlainText();
    ui->textEdit->setText(Text);
}

void MainFrame::on_pushButton_clicked()
{
    //обновляем шрифт текста
    ui->textEdit->setFontUnderline(false);
    ui->textEdit->setFontItalic(false);
    ui->textEdit->setFontWeight(QFont::Normal);
    ui->textEdit->setTextColor(QColor(0, 0, 0));
    //обновляем интерфейс
    ui->comboBox->setCurrentIndex(0);
    ui->boxBold->setChecked(false);
    ui->boxItalic->setChecked(false);
    ui->boxUnder->setChecked(false);
}

void MainFrame::on_pushButtonSave_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                QString::fromUtf8("Сохранить файл"), QDir::currentPath(), "Текст (*.txt)");
    QFile savingFile(fileName);
    if (!savingFile.open(QIODevice::WriteOnly))
    {
        qDebug() << "Ошибка при открытии файла";
    }
    QTextStream stream( &savingFile );
    stream << ui->textEdit->toPlainText() << endl;
    savingFile.close();
}
