#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "matrix.h"
#include "calc_matrix.h"
#include <QWidget>
#include <QLineEdit>
#include <QSpinBox>
#include <QString>
#include <QSize>
#include <QPushButton>
#include <QLabel>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QDate>
#include <QFileInfo>

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
private slots:
    void inputMatrix();
    void calculation();
    void cancel();
    void save();
    //void showHelp();
private:
    QSpinBox *spinBox;
    QPushButton *buttonCalculate;
    QPushButton *buttonHelp;
    QPushButton *buttonSize;
    QPushButton *buttonCancel;
    QPushButton *buttonSave;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QTableWidget *tableWidget;
    QTableWidget *tableWidget_2;
    QTableWidget *tableWidget_3;
    QMessageBox *mesBox;
    QMessageBox *mesBox_2;
    QHBoxLayout *HBoxLayout;
    QHBoxLayout *HBoxLayout_2;
    QVBoxLayout *VBoxLayout;
    double x, y;
    bool fillItem();
    void createWidgets();
};
#endif // MAINWINDOW_H
