#pragma once

#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QString>

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

signals:
    void lastFilePathChanged();
    void targetFilePathChanged();

private:
    Ui::MainWidget *ui;
};

#endif // MAINWIDGET_H
