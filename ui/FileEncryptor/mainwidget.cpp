#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QFileDialog>
#include <iostream>
#include <QPainter>


MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    _targetFileName(""),
    _targetFilePath(""),
    _passwordFilePath(""),
    _outputFilePath(""),
    _lastFilePath(""),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    QPixmap mainPic(":/new/main/GPLpicture.png");

    QObject::connect(this, SIGNAL(lastFilePathChanged()),
                     this, SLOT(on_lineEditOutFile_textChanged()));
    QObject::connect(this, SIGNAL(targetFilePathChanged()),
                     this, SLOT(on_lineEditTargetFile_textChanged()));
    QObject::connect(this, SIGNAL(checkBoxToggle(bool)),
                     this, SLOT(toggleEncryptDecrypt(bool)));


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
    QString startFilePath = _lastFilePath.isEmpty() ? QDir::homePath() : _lastFilePath;
    QFileDialog fileDialog;

    _targetFilePath = fileDialog.getOpenFileName(this,
                                                 tr("Select Target File"),
                                                 startFilePath);
    QFileInfo targetFileInfo(_targetFilePath);
    _lastFilePath = targetFileInfo.absolutePath();
    _targetFileName = targetFileInfo.fileName();

    emit lastFilePathChanged();
    emit targetFilePathChanged();

}

void MainWidget::on_pushButtonEncrypt_clicked()
{
}

void MainWidget::on_lineEditOutFile_textChanged()
{
    if (!_targetFilePath.isEmpty()) {
        QString outFilePath;
#ifdef Q_OS_MSDOS
        outFilePath = QString("%1\\%2.enc").arg(_lastFilePath).arg(_targetFileName);
#else
        outFilePath = QString("%1/%2.enc").arg(_lastFilePath).arg(_targetFileName);
#endif
        ui->lineEditOutFile->setText(outFilePath);
    }
}

void MainWidget::on_lineEditTargetFile_textChanged()
{
    if (!_targetFilePath.isEmpty()) {
        ui->lineEditTargetFile->setText(_targetFilePath);
    }
}

void MainWidget::toggleEncryptDecrypt(bool encrypt)
{
    if (encrypt) {
        ui->pushButtonBrowseTargetFile->setText(targetEncryptText);
        ui->pushButtonEncrypt->setText(buttonEncryptText);
    }
    else {
        ui->pushButtonBrowseTargetFile->setText(targetDecryptText);
        ui->pushButtonEncrypt->setText(buttonDecryptText);
    }
}


void MainWidget::on_checkBoxToggleEncryptDecrypt_stateChanged()
{
    if (ui->checkBoxToggleEncryptDecrypt->isChecked()) {
        emit checkBoxToggle(true);
    }
    else {
        emit checkBoxToggle(false);
    }
}
