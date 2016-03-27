#pragma once

#include <QWidget>
#include <QString>
#include <QProcess>
#include <QtDebug>

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

    bool _encryptEnabled;

    void clearFields();

    // === backend support ===
    QProcess *_backendProcess;
    QString _pathToBackendExec;

private slots:
    void on_pushButtonBrowseTargetFile_clicked();

    void on_pushButtonEncrypt_clicked();

    void on_lineEditTargetFile_editingFinished();

    void on_lineEditOutFile_editingFinished();

    void on_comboBoxEncryptDecrypt_currentIndexChanged(int index);

    void toggleEncryptDecrypt(bool encrypt);

    void encrypt();

    void decrypt();

    // === backend signal handling ===
    void notifyBackendStart();

    void handleBackendError(QProcess::ProcessError error);

    void handleBackendStop(int exitCode, QProcess::ExitStatus exitStatus);

signals:
    void lastFilePathChanged();

    void targetFilePathChanged();

    void checkBoxToggle(bool encrypt);

private:
    Ui::MainWidget *ui;
};
