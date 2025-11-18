#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QFrame>
#include <QPainter>
#include <QLinearGradient>
#include <QFont>
#include <QFontDatabase>
#include <QDebug>
#include <QTimer>
#include <QPixmap>
#include <QPaintEvent>
#include <QShowEvent>

class HomePage : public QWidget
{
    Q_OBJECT

public:
    explicit HomePage(QWidget *parent = nullptr);
    ~HomePage();

signals:
    void navigateToMenu();

protected:
    void paintEvent(QPaintEvent *event) override;
    void showEvent(QShowEvent *event) override;


private slots:
    void onGetStartedClicked();

private:
    void setupUI();
    void setupLeftPanel();
    void setupRightPanel();
    void setupAnimations();
    void styleButton();

    QWidget *leftPanel;
    QWidget *rightPanel;

    QLabel *titleLabel;
    QLabel *subtitleLabel;
    QLabel *descriptionLabel;
    QLabel *illustrationLabel;
    QPushButton *getStartedButton;

    QGraphicsOpacityEffect *leftPanelOpacity;
    QGraphicsOpacityEffect *rightPanelOpacity;

    QPropertyAnimation *leftPanelAnimation;
    QPropertyAnimation *rightPanelAnimation;

    bool animationsStarted;
};

#endif // HOMEPAGE_H
