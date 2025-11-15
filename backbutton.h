#ifndef BACKBUTTON_H
#define BACKBUTTON_H

#include <QPushButton>
#include <QWidget>
#include <QShowEvent>
#include <QEnterEvent>
#include <QEvent>

class BackButton : public QPushButton
{
    Q_OBJECT

public:
    enum ButtonType {
        BackToOperations,
        BackToMenu
    };

    explicit BackButton(QWidget *parent = nullptr);
    explicit BackButton(ButtonType type, QWidget *parent = nullptr);
    explicit BackButton(const QString &text, QWidget *parent = nullptr);
    ~BackButton();
    
    // Hide base setEnabled to ensure button is always enabled
    void setEnabled(bool enabled);

signals:
    void backRequested();

protected:
    void showEvent(QShowEvent *event) override;
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;

private slots:
    void onClicked();
    void onButtonClicked();

private:
    void setupButton();
    void applyRoundedStyle();
    void ensureConnection();
    bool m_connectionEstablished;
};

#endif // BACKBUTTON_H
