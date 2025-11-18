#ifndef BASEVISUALIZATION_H
#define BASEVISUALIZATION_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimer>
#include <QSplitter>
#include <QGroupBox>
#include <QListWidget>
#include <QTabWidget>
#include <QFontDatabase>
#include <QGraphicsDropShadowEffect>
#include <QLinearGradient>
#include <QFont>

class BaseVisualization : public QWidget
{
    Q_OBJECT

public:
    explicit BaseVisualization(const QString &title, QWidget *parent = nullptr);
    virtual ~BaseVisualization();

signals:
    void backToOperations();

protected:
    // Common UI setup methods
    virtual void setupUI();
    virtual void setupVisualizationArea();
    virtual void setupRightPanel() = 0; // Pure virtual - each subclass implements its own
    virtual void setupStepTrace();
    
    // Common UI components
    QSplitter *mainSplitter;
    QWidget *leftPanel;
    QWidget *rightPanel;
    QVBoxLayout *leftLayout;
    
    // Header components
    QPushButton *backButton;
    QLabel *titleLabel;
    QString visualizationTitle;
    
    // Step trace components
    QTabWidget *rightTabWidget;
    QListWidget *stepsList;
    QListWidget *algorithmList;
    QLabel *statusLabel;
    
    // Common utility methods
    QPushButton* createStyledButton(const QString &text, const QString &color = "#7b4fff");
    QLabel* createStyledLabel(const QString &text, int fontSize = 12);
    void addStepToHistory(const QString &step);
    void addOperationSeparator();
    void setControlsEnabled(bool enabled);
    
    // Common styling
    QString getButtonStyle(const QString &color = "#7b4fff");
    QString getBackButtonStyle();
    QString getSplitterStyle();
    QString getScrollBarStyle();

private slots:
    void onBackClicked();

private:
    void setupHeader();
};

#endif // BASEVISUALIZATION_H
