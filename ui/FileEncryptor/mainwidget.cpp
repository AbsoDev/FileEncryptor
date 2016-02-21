#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QFileDialog>
#include <iostream>
#include <QPainter>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    _targetFilePath(""),
    _passwordFilePath(""),
    _outputFilePath(""),
    _lastFilePath(""),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    QPixmap mainPic(":/new/main/Pictures/mainPic.jpg");

    QObject::connect(this, SIGNAL(lastFilePathChanged()),
                     this, SLOT(on_lineEditOutFile_textChanged()));

    int h = ui->labelProfilePicture->height();
    int w = ui->labelProfilePicture->width();

    QPixmap scaled = mainPic.scaled(w, h, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->labelProfilePicture->setPixmap(scaled);
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::on_pushButtonBrowseTargetFile_clicked()
{
    QString startFilePath = _lastFilePath.isEmpty() ? "~" : _lastFilePath;
    QFileDialog fileDialog;

    _targetFilePath = fileDialog.getOpenFileName(this,
                                                   tr("Select Target File"),
                                                   startFilePath
                                                   );
    _lastFilePath = fileDialog.directory().absolutePath();
    emit lastFilePathChanged();
    std::cout << std::endl << "Selected file path " << _targetFilePath.toStdString();
    std::cout << std::endl << "Last file path" << _lastFilePath.toStdString();
}

void MainWidget::on_pushButtonBrowsePassFile_clicked()
{
    QString startFilePath = _lastFilePath.isEmpty() ? "~" : _lastFilePath;
    QFileDialog fileDialog;

    _passwordFilePath = fileDialog.getOpenFileName(this,
                                                     tr("Select Password File"),
                                                     startFilePath
                                                     );
    _lastFilePath = fileDialog.directory().absolutePath();
    emit lastFilePathChanged();
    std::cout << std::endl << "Selected file path " << _passwordFilePath.toStdString();
    std::cout << std::endl << "Last file path" << _lastFilePath.toStdString();
}

void MainWidget::on_pushButtonEncrypt_clicked()
{
}

void MainWidget::on_lineEditOutFile_textChanged()
{
    if (!_passwordFilePath.isEmpty() && !_targetFilePath.isEmpty()) {
        ui->lineEditOutFile->setText(_lastFilePath);
    }
}
