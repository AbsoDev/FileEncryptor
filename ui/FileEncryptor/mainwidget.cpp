#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QFileDialog>
#include <iostream>
#include <QPainter>
#include <QTextStream>


MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    _targetFileName(""),
    _targetFilePath(""),
    _passwordFilePath(""),
    _outputFilePath(""),
    _lastFilePath(""),
    _encryptEnabled(true),
    _pathToBackendExec("/Users/arbulgazar/AbsoDev/FileEncryptor/ui/encryptor"),
    ui(new Ui::MainWidget)
{
    _backendProcess = new QProcess(this);
    ui->setupUi(this);
    QPixmap mainPic(":/new/main/GPLpicture.png");

    QObject::connect(this, SIGNAL(lastFilePathChanged()),
                     this, SLOT(on_lineEditOutFile_textChanged()));
    QObject::connect(this, SIGNAL(targetFilePathChanged()),
                     this, SLOT(on_lineEditTargetFile_textChanged()));
    QObject::connect(this, SIGNAL(checkBoxToggle(bool)),
                     this, SLOT(toggleEncryptDecrypt(bool)));
    QObject::connect(_backendProcess, SIGNAL(error(QProcess::ProcessError)),
                     this, SLOT(handleBackendError(QProcess::ProcessError)));
    QObject::connect(_backendProcess, SIGNAL(started()),
                     this, SLOT(notifyBackendStart()));
    QObject::connect(_backendProcess, SIGNAL(finished(int,QProcess::ExitStatus)),
                     this, SLOT(handleBackendStop(int,QProcess::ExitStatus)));


    int h = ui->labelProfilePicture->height();
    int w = ui->labelProfilePicture->width();
    ui->comboBoxEncryptDecrypt->addItem("Encrypt", 0);
    ui->comboBoxEncryptDecrypt->addItem("Decrypt", 1);

    QPixmap scaled = mainPic.scaled(w, h, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->labelProfilePicture->setPixmap(scaled);
}

MainWidget::~MainWidget()
{
    delete _backendProcess;
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
    // Getting password and storing it in temp file
    _passwordFilePath = QString("%1/passwordFile.tmp").arg(_lastFilePath);
    QFile file(_passwordFilePath);
    QString password = ui->lineEditPassPhrase->text();
    if (file.open(QIODevice::ReadWrite))
    {
        QTextStream stream(&file);
        stream << password << endl;
    }
    file.close();

    // Getting output file name and path
    _outputFilePath = ui->lineEditOutFile->text();

    if (_encryptEnabled)
    {
        encrypt();
    }
    else
    {
        decrypt();
    }
}

void MainWidget::encrypt()
{
    QStringList backendParams;
    backendParams << "-i" << _targetFilePath;
    backendParams << "-o" << _outputFilePath;
    backendParams << "-k" << _passwordFilePath;
    backendParams << "-e";

    _backendProcess->setProcessChannelMode(QProcess::MergedChannels);
    _backendProcess->start(_pathToBackendExec, backendParams, QIODevice::ReadWrite);
}

void MainWidget::decrypt()
{
    QStringList backendParams;
    backendParams << "-i" << _targetFilePath;
    backendParams << "-o" <<  _outputFilePath;
    backendParams << "-k" << _passwordFilePath;
    backendParams << "-d";

    _backendProcess->setProcessChannelMode(QProcess::MergedChannels);
    _backendProcess->start(_pathToBackendExec, backendParams, QIODevice::ReadWrite);
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
        _encryptEnabled = true;
        ui->pushButtonBrowseTargetFile->setText(targetEncryptText);
        ui->pushButtonEncrypt->setText(buttonEncryptText);
    }
    else {
        _encryptEnabled = false;
        ui->pushButtonBrowseTargetFile->setText(targetDecryptText);
        ui->pushButtonEncrypt->setText(buttonDecryptText);
    }
}

void MainWidget::notifyBackendStart()
{
    qDebug() << "[backendMonitor] process started";
}

void MainWidget::handleBackendError(QProcess::ProcessError error)
{
    qDebug() << QString("[backendMonitor] ERROR %1 occured!!!").arg(error);
}

void MainWidget::handleBackendStop(int exitCode, QProcess::ExitStatus exitStatus)
{
    qDebug() << QString("[backendMonitor] process exited with code %1 status %1").arg(exitCode).arg(exitStatus);
    QFile::remove(_passwordFilePath);
}

void MainWidget::on_comboBoxEncryptDecrypt_currentIndexChanged(int index)
{
    if (index == 0)
    {
        _encryptEnabled = true;
    }
    else if (index == 1)
    {
        _encryptEnabled = false;
    }
    emit checkBoxToggle(_encryptEnabled);
}
