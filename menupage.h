#ifndef MENUPAGE_H
#define MENUPAGE_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>
#include <QPauseAnimation>
#include <QVector>
#include <QFrame>
#include <QGraphicsDropShadowEffect>
#include <QPainter>
#include <QLinearGradient>
#include <QRadialGradient>
#include <QFont>
#include <QFontDatabase>
#include <QDebug>
#include <QTimer>
#include <QPaintEvent>
#include <QShowEvent>

class MenuPage : public QWidget
{
    Q_OBJECT

public:
    explicit MenuPage(QWidget *parent = nullptr);
    ~MenuPage();

protected:
    void paintEvent(QPaintEvent *event) override;
    void showEvent(QShowEvent *event) override;

signals:
    void dataStructureSelected(const QString &dsName);

private slots:
    void onTreeClicked();
    void onRedBlackTreeClicked();
    void onGraphClicked();
    void onHashTableClicked();

private:
    void setupUI();
    void setupAnimations();
    QWidget* createMenuCard(const QString &title, const QString &description,
                            const QString &icon, QPushButton* &button);
    void styleCard(QWidget *card);
    void styleButton(QPushButton *button);

    QLabel *titleLabel;
    QLabel *subtitleLabel;
    QPushButton *treeButton;
    QPushButton *rbTreeButton;
    QPushButton *graphButton;
    QPushButton *hashTableButton;

    QWidget *menuContainer;
    QVector<QWidget*> cards;
    QVector<QGraphicsOpacityEffect*> cardOpacities;
    QParallelAnimationGroup *animationGroup;

    bool animationsStarted;
};

#endif // MENUPAGE_H
