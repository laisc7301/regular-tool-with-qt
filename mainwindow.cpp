#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "global.h"

//创建菜单栏，工具栏，状态栏应当包含的头文件
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QStatusBar>
#include <QMessageBox>
#include <QSettings>
#include <QTimer>

#include <iostream>
#include "regex_replacement.h"
#include "regex_match.h"
#include "regex_find.h"
#include "about.h"

#include <QMdiSubWindow>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QToolBar *toolBar = new QToolBar();
    addToolBar(toolBar);


    QAction *m1 = toolBar->addAction("正则查找");
    connect(m1,&QAction::triggered,this,[=](){
        //std::cout << "new action" << std::endl;
        regex_find *regex_find1 = new regex_find;
        QMdiSubWindow *subWindow1 = ui->mdiArea->addSubWindow(regex_find1);
        subWindow1->show();
    });

    QAction *m2 = toolBar->addAction("正则匹配");
    connect(m2,&QAction::triggered,this,[=](){
        //std::cout << "new action" << std::endl;
        regex_match *regex_match1 = new regex_match;
        QMdiSubWindow *subWindow1 = ui->mdiArea->addSubWindow(regex_match1);
        subWindow1->show();
    });

    QAction *m3 = toolBar->addAction("正则替换");
    connect(m3,&QAction::triggered,this,[=](){

        regex_replacement *regex_replacement1 = new regex_replacement();
        QMdiSubWindow *subWindow1 = ui->mdiArea->addSubWindow(regex_replacement1);
        subWindow1->show();
        //subWindow1->resize(QSize(550,250));

    });

//        QAction *m4 = ui->mainToolBar->addAction("关于");
//        connect(m4,&QAction::triggered,this,[=](){

//            About *About1 = new About();

//            QMdiSubWindow *subWindow1 = ui->mdiArea->addSubWindow(About1);
//            subWindow1->show();

//            //subWindow1->resize(QSize(550,250));
//            //setAttribute(Qt::WA_DeleteOnClose)
//            //QMessageBox::aboutQt(NULL, "About Qt");

//        });

    QAction *m5 = toolBar->addAction("关于");
    connect(m5,&QAction::triggered,this,[=](){

        About *About2 = new About();
        About2->show();
    });

    QTimer *timer = new QTimer();
    connect(timer,&QTimer::timeout,this,[=](){

        toolBar->show();

    });
    timer->start(1000);

    QSettings *mysetting = new QSettings("setting.ini", QSettings::IniFormat);
    regex_replacement_regularExpression = mysetting->value("regularExpression/regularExpression").toString();

    regex_replacement_replace = mysetting->value("regularExpression/replace").toString();

    regex_replacement_replaceInput = mysetting->value("regularExpression/replaceInput").toString();



}

MainWindow::~MainWindow()
{
    delete ui;

    QSettings *mysetting = new QSettings("setting.ini", QSettings::IniFormat);
    mysetting->setValue("regularExpression/regularExpression",regex_replacement_regularExpression);
    mysetting->setValue("regularExpression/replace",regex_replacement_replace);
    mysetting->setValue("regularExpression/replaceInput",regex_replacement_replaceInput);
}

