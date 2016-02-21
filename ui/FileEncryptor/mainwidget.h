#pragma once

#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QString>

const QString targetEncryptText = "Select file to encrypt";
const QString targetDecryptText = "Select file to decrypt";
const QString buttonEncryptText = "Encrypt";
const QString buttonDecryptText = "Decrypt";

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

protected:
    QString _targetFileName;

    QString _targetFilePath;
    QString _passwordFilePath;
    QString _outputFilePath;
    QString _lastFilePath;

private slots:
    void on_pushButtonBrowseTargetFile_clicked();

    void on_pushButtonEncrypt_clicked();

    void on_lineEditOutFile_textChanged();

    void on_lineEditTargetFile_textChanged();

    void on_checkBoxToggleEncryptDecrypt_stateChanged();

    void toggleEncryptDecrypt(bool encrypt);

signals:
    void lastFilePathChanged();

    void targetFilePathChanged();

    void checkBoxToggle(bool encrypt);

private:
    Ui::MainWidget *ui;
};

#endif // MAINWIDGET_H
