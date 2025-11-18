#ifndef UIUTILS_H
#define UIUTILS_H

#include <QString>
#include <QPushButton>
#include <QLabel>
#include <QListWidget>
#include <QGroupBox>
#include <QFont>
#include <QFontDatabase>
#include "backbutton.h"

class UIUtils
{
public:
    // Common button styles
    static QString getButtonStyle(const QString &color = "#7b4fff");
    static QString getBackButtonStyle();
    static QString getScrollBarStyle();
    
    // Button creation helpers
    static QPushButton* createStyledButton(const QString &text, const QString &color = "#7b4fff");
    static BackButton* createBackButton(BackButton::ButtonType type = BackButton::BackToOperations);
    static BackButton* createBackButton(const QString &text);
    
    // Label creation helpers
    static QLabel* createTitleLabel(const QString &title);
    static QLabel* createStyledLabel(const QString &text, int fontSize = 12);
    
    // Font helpers
    static QFont getPreferredFont(int size = 12, bool bold = false);
    
private:
    UIUtils() = delete; // Static utility class
};

#endif // UIUTILS_H
