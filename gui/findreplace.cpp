#include "findreplace.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QLabel>


FindReplace::FindReplace(QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    this->setLayout(layout);

    findLine = new QLineEdit(this);
    closeButton  = new QPushButton(this);

    closeButton->setIcon(QIcon(":fileclose.png"));
    closeButton->setStyleSheet("border:none;");
    connect(closeButton, SIGNAL(clicked()), this, SLOT(hide()));

    findLine->setMaximumWidth(300);

    nextButton = new QPushButton(tr("Next"));
    prevButton = new QPushButton(tr("Previous"));
    caseSensitive = new QCheckBox(tr("Match case"));


    QSpacerItem *spacer = new QSpacerItem(this->width()/3,findLine->height(), QSizePolicy::MinimumExpanding);

    replaceLine = new QLineEdit();

    replaceLine = new QLineEdit();
    replaceLine->setMaximumWidth(300);
    replaceButton = new QPushButton(tr("Replace"), this);
    replaceAllButton = new QPushButton(tr("Replace all"),this);

    QVBoxLayout *closeLayout = new QVBoxLayout(this);
    closeLayout->addWidget(closeButton);
    QLabel *closeSpacer = new QLabel(this);
    closeLayout->addWidget(closeSpacer);

    QVBoxLayout *lineLayout = new QVBoxLayout(this);
    lineLayout->addWidget(findLine);
    lineLayout->addWidget(replaceLine);

    QVBoxLayout *button1Layout = new QVBoxLayout(this);
    button1Layout->addWidget(nextButton);
    button1Layout->addWidget(replaceButton);

    QVBoxLayout *button2Layout = new QVBoxLayout(this);
    button2Layout->addWidget(prevButton);
    button2Layout->addWidget(replaceAllButton);

    QVBoxLayout *checkLayout = new QVBoxLayout(this);
    checkLayout->addWidget(caseSensitive);
    checkLayout->addSpacerItem(spacer);

    layout->addLayout(closeLayout);
    layout->addLayout(lineLayout);
    layout->addLayout(button1Layout);
    layout->addLayout(button2Layout);
    layout->addLayout(checkLayout);

    nextButton->setDisabled(true);
    prevButton->setDisabled(true);
    replaceButton->setDisabled(true);
    replaceAllButton->setDisabled(true);
    caseSensitive->setDisabled(true);

    connect(findLine, SIGNAL(textChanged(QString)), this, SLOT(textChanged()));
    connect(replaceLine, SIGNAL(textChanged(QString)), this, SLOT(textChanged()));

    this->hide();

}


void FindReplace::showFind() {
    replaceLine->hide();
    replaceButton->hide();
    replaceAllButton->hide();
    caseSensitive->hide();

    if (isHidden())
        show();


}


void FindReplace::showFindReplace() {
    replaceLine->show();
    replaceButton->show();
    replaceAllButton->show();
    caseSensitive->show();

    if (isHidden())
        show();
}


void FindReplace::textChanged() {
    nextButton->setDisabled(true);
    prevButton->setDisabled(true);
    replaceButton->setDisabled(true);
    replaceAllButton->setDisabled(true);
    caseSensitive->setDisabled(true);

    if (findLine->text().trimmed() != "") {
        nextButton->setDisabled(false);
        prevButton->setDisabled(false);
        replaceButton->setDisabled(false);
        replaceAllButton->setDisabled(false);
        caseSensitive->setDisabled(false);
    }
}



QWebPage::FindFlags FindReplace::getCaseSensitive() {
    QWebPage::FindFlags ff;
    ff = QWebPage::HighlightAllOccurrences;
    ff = 0;
    if (caseSensitive->isChecked())
        ff = ff | QWebPage::FindCaseSensitively;

    return ff;
}
