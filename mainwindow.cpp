#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPort>
#include <QDebug>
#include <QRegularExpression>
#include <QTextCodec>

QString disconnected = QString::fromStdString("Disconnected");
QString connected = QString::fromStdString("Connected");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serial = new QSerialPort(this);
    //serial->write("start_message");
    ui->label_4->setText(disconnected);
    connect(serial, SIGNAL(readyRead()), this, SLOT(serialRecieved()));
}

MainWindow::~MainWindow()
{
    delete ui;
    serial->close();
}

void MainWindow::serialRecieved()
{

    QByteArray byteReadArray;
    byteReadArray = serial->readAll();
    QString DataAsString = QTextCodec::codecForMib(106)->toUnicode(byteReadArray);
    if(DataAsString == ""){
         ui->label_4->setText("Disconnected");
    }

    QString pattern = "("+ui->comboBox_2->currentText()+")(\\d+)";
    QRegularExpression re(pattern);
    QRegularExpressionMatchIterator i = re.globalMatch(DataAsString);
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        QString word = match.captured(2);
        float calibratedValue_int = word.toFloat();
        QString calibratedValue_str_temp  = QString::number((5*(calibratedValue_int / 1024))/0.01, 'f', 2);
        QString calibratedValue_str_voltage  = QString::number(5*(calibratedValue_int / 1024), 'f', 2);
        ui->tableWidget->setItem(0, 0, new QTableWidgetItem(calibratedValue_str_temp+" degC"));
        ui->tableWidget->setItem(0, 1, new QTableWidgetItem(calibratedValue_str_voltage));
        serial->write("start_message");
    }
}

void MainWindow::openSerialPort()
{
        serial->setPortName(ui->comboBox->currentText());
        serial->setBaudRate(QSerialPort::Baud9600);
        serial->setDataBits(QSerialPort::Data8);
        serial->setParity(QSerialPort::NoParity);
        serial->setStopBits(QSerialPort::OneStop);
        serial->setFlowControl(QSerialPort::NoFlowControl);
        if(serial->open(QIODevice::ReadWrite)){
            ui->label_4->setText(connected);
            serial->write("start_message");
        }
}

void MainWindow::on_pushButton_2_clicked()
{
    if(serial->open(QIODevice::ReadWrite)==false)openSerialPort();
    qDebug()<<serial->open(QIODevice::ReadWrite);
}

void MainWindow::on_pushButton_3_clicked()
{
    if(serial->isOpen()){
        serial->close();
        ui->label_4->setText(disconnected);
        ui->tableWidget->setItem(0, 0, new QTableWidgetItem(""));
        ui->tableWidget->setItem(0, 1, new QTableWidgetItem(""));
    }
}

