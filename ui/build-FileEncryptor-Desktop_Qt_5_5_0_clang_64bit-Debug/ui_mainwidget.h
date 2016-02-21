/********************************************************************************
** Form generated from reading UI file 'mainwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWIDGET_H
#define UI_MAINWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWidget
{
public:
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout_Picture;
    QLabel *labelProfilePicture;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButtonBrowseTargetFile;
    QPushButton *pushButtonBrowsePassFile;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEditOutFile;
    QPushButton *pushButtonEncrypt;

    void setupUi(QWidget *MainWidget)
    {
        if (MainWidget->objectName().isEmpty())
            MainWidget->setObjectName(QStringLiteral("MainWidget"));
        MainWidget->resize(817, 610);
        verticalLayoutWidget_3 = new QWidget(MainWidget);
        verticalLayoutWidget_3->setObjectName(QStringLiteral("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(30, 50, 611, 481));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_Picture = new QVBoxLayout();
        verticalLayout_Picture->setSpacing(6);
        verticalLayout_Picture->setObjectName(QStringLiteral("verticalLayout_Picture"));
        labelProfilePicture = new QLabel(verticalLayoutWidget_3);
        labelProfilePicture->setObjectName(QStringLiteral("labelProfilePicture"));
        labelProfilePicture->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(labelProfilePicture->sizePolicy().hasHeightForWidth());
        labelProfilePicture->setSizePolicy(sizePolicy);
        labelProfilePicture->setMinimumSize(QSize(300, 300));
        labelProfilePicture->setMaximumSize(QSize(500, 200));
        labelProfilePicture->setFrameShape(QFrame::Box);
        labelProfilePicture->setFrameShadow(QFrame::Sunken);
        labelProfilePicture->setPixmap(QPixmap(QString::fromUtf8(":/new/main/Pictures/mainPic.jpg")));
        labelProfilePicture->setScaledContents(false);
        labelProfilePicture->setAlignment(Qt::AlignCenter);
        labelProfilePicture->setWordWrap(false);

        verticalLayout_Picture->addWidget(labelProfilePicture);


        verticalLayout_2->addLayout(verticalLayout_Picture);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        pushButtonBrowseTargetFile = new QPushButton(verticalLayoutWidget_3);
        pushButtonBrowseTargetFile->setObjectName(QStringLiteral("pushButtonBrowseTargetFile"));

        verticalLayout->addWidget(pushButtonBrowseTargetFile);

        pushButtonBrowsePassFile = new QPushButton(verticalLayoutWidget_3);
        pushButtonBrowsePassFile->setObjectName(QStringLiteral("pushButtonBrowsePassFile"));

        verticalLayout->addWidget(pushButtonBrowsePassFile);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        lineEditOutFile = new QLineEdit(verticalLayoutWidget_3);
        lineEditOutFile->setObjectName(QStringLiteral("lineEditOutFile"));

        horizontalLayout->addWidget(lineEditOutFile);

        pushButtonEncrypt = new QPushButton(verticalLayoutWidget_3);
        pushButtonEncrypt->setObjectName(QStringLiteral("pushButtonEncrypt"));

        horizontalLayout->addWidget(pushButtonEncrypt);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(MainWidget);

        QMetaObject::connectSlotsByName(MainWidget);
    } // setupUi

    void retranslateUi(QWidget *MainWidget)
    {
        MainWidget->setWindowTitle(QApplication::translate("MainWidget", "File Encryptor", 0));
        labelProfilePicture->setText(QString());
        pushButtonBrowseTargetFile->setText(QApplication::translate("MainWidget", "Browse target file", 0));
        pushButtonBrowsePassFile->setText(QApplication::translate("MainWidget", "Browse password file", 0));
        pushButtonEncrypt->setText(QApplication::translate("MainWidget", "Encrypt", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWidget: public Ui_MainWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWIDGET_H
