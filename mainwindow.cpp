#include "mainwindow.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Solving SLAE by Kramer's method");
    x = width() * 0.55;
    y = height() * 0.1;
    resize(x, y);

   createWidgets();

    connect(buttonSize, SIGNAL(clicked()), this, SLOT(inputMatrix()));
    connect(buttonCalculate, SIGNAL(clicked()), this, SLOT(calculation()));
    connect(buttonCancel, SIGNAL(clicked()), this, SLOT(cancel()));
    connect(buttonSave, SIGNAL(clicked()), this, SLOT(save()));
    //connect(buttonHelp, SIGNAL(clicked()), this, SLOT(showHelp()));
}

void Widget::createWidgets()
{
    label = new QLabel("Enter size of matrix &");
    spinBox = new QSpinBox(this);
    buttonSize = new QPushButton("&Input");
    label -> setBuddy(spinBox);
    buttonSize -> setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    HBoxLayout = new QHBoxLayout;
    HBoxLayout -> addWidget(spinBox);
    HBoxLayout -> addWidget(buttonSize);

    VBoxLayout = new QVBoxLayout();
    VBoxLayout -> addWidget(label);
    VBoxLayout -> addLayout(HBoxLayout);
    setLayout(VBoxLayout);

    buttonCalculate = new QPushButton("&Calculate");
    buttonCancel = new QPushButton("&Cancel");
    buttonSave = new QPushButton("Save&");

}

void Widget::inputMatrix()
{
    int n = spinBox -> value();

    label_2 = new QLabel("Enter coefficients of the matrix &");
    tableWidget = new QTableWidget(n, n, this);
    label_2 -> setBuddy(tableWidget);
    tableWidget -> verticalHeader() -> hide();
    tableWidget -> setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tableWidget -> setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tableWidget -> horizontalHeader() -> setDefaultSectionSize(30);
    tableWidget -> verticalHeader() -> setDefaultSectionSize(30);

    int tableHeight = tableWidget -> horizontalHeader() -> height() + 30 * n;
    int tableWidth = tableWidget -> horizontalHeader() ->length() + tableWidget -> verticalHeader() -> height();
    tableWidget -> setMinimumHeight(tableHeight);
    tableWidget -> setMinimumWidth(tableWidth);
    tableWidget -> setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    label_3 = new QLabel("Enter free members &");
    tableWidget_2 = new QTableWidget(1, n, this);
    label_3 -> setBuddy(tableWidget_2);
    tableWidget_2 -> horizontalHeader() -> hide();
    tableWidget_2 -> verticalHeader() -> hide();
    tableWidget_2 -> horizontalHeader() -> setDefaultSectionSize(30);
    tableWidget_2 -> verticalHeader() -> setDefaultSectionSize(30);
    tableWidget_2 -> setMaximumHeight(30);
    tableWidget_2 -> setMinimumWidth(tableWidth);
    tableWidget_2 -> setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    tableWidget_2 -> setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    buttonCalculate -> setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    buttonCalculate -> setVisible(true);

    VBoxLayout -> addWidget(label_2);
    VBoxLayout -> addWidget(tableWidget);
    VBoxLayout -> addWidget(label_3);
    VBoxLayout -> addWidget(tableWidget_2);
    VBoxLayout -> addWidget(buttonCalculate);
    setLayout(VBoxLayout);
}

bool Widget::fillItem()
{
    bool fillInMatrix = true;
   bool fillInMembers = true;
       for (int i = 0; i < tableWidget -> rowCount(); i++)
       {
           for (int j = 0; j < tableWidget -> columnCount(); j++)
           {
               if (tableWidget -> item(j, i) == nullptr)
               {
                   fillInMatrix = false;
               }
               if (!fillInMatrix) break;
           }
           if (!fillInMatrix) break;
       }
       for (int i = 0; i < tableWidget_2 -> columnCount(); i++)
       {
           if (tableWidget_2 -> item(0, i) == nullptr)
           {
               fillInMembers = false;
           }
           if (!fillInMembers) break;
       }

      if (!fillInMatrix)
      {
          mesBox = new QMessageBox();
          mesBox -> setWindowTitle("Entering of the matrix coefficients");
          mesBox -> setText("The table <b>isn't fully</b> fill in! <p>Enter missing elements!");
          mesBox -> setButtonText(QMessageBox::Ok, tr("Ok"));
          mesBox -> setIcon(QMessageBox::Information);
          int h = mesBox -> exec();
          if (h== QMessageBox::Ok) mesBox -> close();
          delete mesBox;
      }
      if (!fillInMembers)
      {
          mesBox_2 = new QMessageBox();
          mesBox_2 -> setWindowTitle("Entering of the free members");
          mesBox_2 -> setText("The table row <b>isn't fully</b> fill in! <p>Enter missing elements!");
          mesBox_2 -> setButtonText(QMessageBox::Ok, tr("Ok"));
          mesBox_2 -> setIcon(QMessageBox::Information);
          int c = mesBox_2 -> exec();
          if (c == QMessageBox::Ok) mesBox_2 -> close();
          delete mesBox_2;
      }
      return (fillInMatrix and fillInMembers);
}

void Widget::calculation()
{
    if (fillItem())
    {
        Calc_Matrix mat(tableWidget -> columnCount());
        buttonCalculate -> setVisible(false);
        for (int i = 0; i < tableWidget -> rowCount(); i++)
        {
            for (int j = 0; j < tableWidget -> columnCount(); j++)
            {
                double item = tableWidget -> item(i, j) -> text().toDouble();
                 mat.setA(i, j, item);
                 if (i == 0)
                 {
                     double item_2 = tableWidget_2 -> item(i, j) -> text().toDouble();
                     mat.setB(j, item_2);
                 }
            }
        }
        if (mat.IsZero() && mat.IsAllZeroDet())
        {
            lineEdit_2 = new QLineEdit();
            lineEdit_2 -> setText("The SLAE has countless roots!");
            lineEdit_2 -> setStyleSheet("color: red");
            lineEdit_2 -> setDisabled(true);
            VBoxLayout -> addWidget(lineEdit_2);
            setLayout(VBoxLayout);
        }
        else if (mat.IsZero() && mat.IsNotZeroAllDet())
        {
            lineEdit_3 = new QLineEdit("The SLAE has no solutions!");
            lineEdit_3 -> setStyleSheet("color: red");
            lineEdit_3 -> setDisabled(true);
            VBoxLayout -> addWidget(lineEdit_3);
            setLayout(VBoxLayout);
        } else
        {
            label_4 = new QLabel("Roots of the SLAE");
            tableWidget_3 = new QTableWidget(1, tableWidget_2 -> columnCount(), this);
            label_4 -> setBuddy(tableWidget_3);
            tableWidget_3 -> verticalHeader() -> hide();
            tableWidget_3 -> horizontalHeader() -> setDefaultSectionSize(30);
            tableWidget_3 -> verticalHeader() -> setDefaultSectionSize(30);
            tableWidget_3 -> setMaximumHeight(tableWidget_3 -> horizontalHeader() -> height() + 30);
            int tableWidth_3 = tableWidget_3 -> horizontalHeader() ->length() + tableWidget_3 -> verticalHeader() -> height();
            tableWidget_3 -> setMinimumWidth(tableWidth_3);
            tableWidget_3 -> setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
            tableWidget_3 -> setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


            for (int i = 0; i < tableWidget_3 -> columnCount(); i++)
            {
                tableWidget_3 -> setItem(0, i, new QTableWidgetItem(QString::number(mat.getX(i))));
                tableWidget_3 -> item(0, i) -> setFlags(Qt::ItemIsDragEnabled | Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
            }

            label_5 = new QLabel("Checking of solution");
            lineEdit = new QLineEdit;
            lineEdit -> setDisabled(true);
            if (mat.confirm_log())
            {
                lineEdit -> setText("The decision is true");
                lineEdit -> setStyleSheet("color: green");
            } else {
                lineEdit -> setText("The decision is false");
                lineEdit -> setStyleSheet("color: red");
            }

            VBoxLayout -> addWidget(label_4);
            VBoxLayout -> addWidget(tableWidget_3);
            VBoxLayout -> addWidget(label_5);
            VBoxLayout -> addWidget(lineEdit);
            setLayout(VBoxLayout);
        }
        HBoxLayout_2 = new QHBoxLayout();
        buttonCancel -> setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        buttonCancel -> setVisible(true);
        buttonSave -> setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        buttonSave -> setVisible(true);
        buttonSave -> setDisabled(false);
        HBoxLayout_2 -> addWidget(buttonCancel);
        HBoxLayout_2 -> addWidget(buttonSave);
        VBoxLayout -> addLayout(HBoxLayout_2);
        setLayout(VBoxLayout);
    }
}

void Widget::cancel()
{
    Calc_Matrix cancelMatrix(tableWidget -> columnCount());
    for (int i = 0; i < tableWidget -> rowCount(); i++)
    {
        for (int j = 0; j < tableWidget -> columnCount(); j++)
        {
            cancelMatrix.setA(i, j, tableWidget -> item(i, j) -> text().toDouble());
            if (i == 0)
            {
                cancelMatrix.setB(j,  tableWidget_2 -> item(i, j) -> text().toDouble());
            }
        }
    }
    if (cancelMatrix.IsZero() and cancelMatrix.IsAllZeroDet())
    {
        delete lineEdit_2;
    }
    else if (cancelMatrix.IsZero() and cancelMatrix.IsNotZeroAllDet())
    {
        delete lineEdit_3;
    }
    else
    {
        delete label_4; delete tableWidget_3;
        delete label_5; delete lineEdit;
    }
    delete label_2; delete tableWidget;
    delete label_3; delete tableWidget_2;
    buttonCancel -> setVisible(false);
    buttonSave -> setVisible(false);
    resize(sizeHint());
    resize(x, y);
}

void Widget::save() {
    QString path = QFileDialog::getSaveFileName(this, "Selecting a directory", ".txt");
    QString filename = path;
    QFile output(filename);
    QTextStream out(&output);
    QFileInfo fileInfo(filename);
    QDate lastReduct = fileInfo.lastModified().date();
    QDate currentDate = QDate::currentDate();
    if (lastReduct < currentDate) {
        if (output.open(QIODevice::WriteOnly | QIODevice::Truncate)) output.close();
    }
    if (output.open(QIODevice::WriteOnly | QIODevice:: Append)) {
        Calc_Matrix outMatrix(tableWidget -> columnCount());
        out << "Size of matrix: " << tableWidget -> columnCount();
        out << "\n" << "Coefficients of matrix: \n";
        for (int i = 0; i < tableWidget -> rowCount(); i++) {
            for (int j = 0; j < tableWidget -> columnCount(); j++) {
                out << tableWidget -> item(i, j) -> text() << "  ";
                outMatrix.setA(i, j, tableWidget -> item(i, j) -> text().toDouble());
                if (i == 0)
                {
                    outMatrix.setB(j,  tableWidget_2 -> item(i, j) -> text().toDouble());
                }
            }
            out << "\n";
        }
        out << "Free members: \n";
        for (int i = 0; i < tableWidget_2 -> columnCount(); i++) {
            out << tableWidget_2 -> item(0, i) -> text() << "  ";
        }
        if (outMatrix.IsZero() and outMatrix.IsAllZeroDet())
        {
            out << "\n" << lineEdit_2 -> text();
        }
        else if (outMatrix.IsZero() and outMatrix.IsNotZeroAllDet()) {
            out << "\n" << lineEdit_3 -> text();
        }
        else  {
            out << "\nRoots of SLAE:\n";
            for (int i = 0; i < tableWidget_3 -> columnCount(); i++)
                out << "x" << i + 1 << " = " << tableWidget_3 -> item(0, i) -> text() << "\n";
            out << "Checking of solution:\n";
            out << lineEdit -> text();
        }
        out << "\n---------------------------------\n";
        buttonSave -> setDisabled(true);
        output.close();  }
}

Widget::~Widget()
{
    delete spinBox;

    delete buttonCalculate; delete buttonHelp;
    delete buttonSize;        delete buttonCancel;        delete buttonSave;

    delete label;   delete label_2; delete label_3; delete label_4; delete label_5;

    delete lineEdit; delete lineEdit_2; delete lineEdit_3;

    delete tableWidget_3;  delete tableWidget; delete tableWidget_2;

    delete HBoxLayout; delete HBoxLayout_2;

    delete VBoxLayout;
}
