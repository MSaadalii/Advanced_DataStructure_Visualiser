#ifndef STYLEMANAGER_H
#define STYLEMANAGER_H

#include <QString>
#include <QWidget>
#include <QPushButton>
#include <QListWidget>
#include <QGroupBox>
#include <QTabWidget>
#include <QLabel>
#include <QLineEdit>
#include <QFont>
#include <QFontDatabase>

class StyleManager
{
public:
    // Singleton pattern for global access
    static StyleManager& instance();
    
    // Common styling methods
    QString getTraversalGroupStyle() const;
    QString getTraversalButtonStyle(const QString &color) const;
    QString getTraversalResultListStyle() const;
    QString getOperationButtonStyle(const QString &color) const;
    QString getInputFieldStyle() const;
    QString getSplitterStyle() const;
    QString getStepTraceStyle() const;
    QString getTabWidgetStyle() const;
    
    // Apply styles to widgets
    void applyTraversalGroupStyle(QGroupBox *groupBox);
    void applyTraversalButtonStyle(QPushButton *button, const QString &color);
    void applyTraversalResultListStyle(QListWidget *listWidget);
    void applyOperationButtonStyle(QPushButton *button, const QString &color);
    void applyInputFieldStyle(QLineEdit *lineEdit);
    void applySplitterStyle(QWidget *splitter);
    void applyStepTraceStyle(QListWidget *listWidget);
    void applyTabWidgetStyle(QTabWidget *tabWidget);
    
    // Font management
    QFont getPreferredFont(int size = 12, bool bold = false) const;
    QFont getTitleFont() const;
    
private:
    StyleManager() = default;
    ~StyleManager() = default;
    StyleManager(const StyleManager&) = delete;
    StyleManager& operator=(const StyleManager&) = delete;
};

#endif // STYLEMANAGER_H
