#ifndef THEORYPAGE_H
#define THEORYPAGE_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QScrollArea>
#include <QFrame>
#include <QPainter>
#include <QLinearGradient>
#include <QRadialGradient>
#include <QFont>
#include <QFontDatabase>
#include <QGraphicsDropShadowEffect>
#include <QPaintEvent>
#include "backbutton.h"

class TheoryPage : public QWidget
{
    Q_OBJECT

public:
    explicit TheoryPage(const QString &dataStructureName, QWidget *parent = nullptr);
    ~TheoryPage();

signals:
    void backToMenu();
    void tryItYourself();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void setupUI();
    void loadTheoryContent();
    QString getDefinition();
    QString getTimeComplexity();
    QString getApplications();
    QString getAdvantages();
    QString getDisadvantages();
    QString getRehashing();
    QString getWhyHashing();
    QWidget* createInfoCard(const QString &title, const QString &content, const QString &icon);

    QString dsName;
    BackButton *backButton;
    QPushButton *tryButton;
    QLabel *titleLabel;
    QScrollArea *scrollArea;
    QWidget *contentWidget;
};

#endif // THEORYPAGE_H
