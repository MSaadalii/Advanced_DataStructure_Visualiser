#include "stylemanager.h"

StyleManager& StyleManager::instance()
{
    static StyleManager instance;
    return instance;
}

QString StyleManager::getTraversalGroupStyle() const
{
    return R"(
        QGroupBox {
            border: 3px solid qlineargradient(x1:0, y1:0, x2:1, y2:0,
                stop:0 rgba(138, 43, 226, 0.6),
                stop:0.5 rgba(30, 144, 255, 0.6),
                stop:1 rgba(0, 191, 255, 0.6));
            border-radius: 20px;
            margin-top: 15px;
            padding-top: 15px;
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                stop:0 rgba(240, 248, 255, 0.98),
                stop:0.3 rgba(230, 245, 255, 0.98),
                stop:0.7 rgba(245, 240, 255, 0.98),
                stop:1 rgba(250, 245, 255, 0.98));
            box-shadow: 0px 8px 25px rgba(138, 43, 226, 0.15);
        }
    )";
}

QString StyleManager::getTraversalButtonStyle(const QString &color) const
{
    QString hoverColor = (color == "#4a90e2") ? "#357abd" : "#218838";
    QString gradientEnd = (color == "#4a90e2") ? "#6bb6ff" : "#34ce57";
    QString hoverEnd = (color == "#4a90e2") ? "#5ba0e6" : "#28a745";
    
    return QString(R"(
        QPushButton {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                stop:0 %1, stop:1 %2);
            color: white;
            border: none;
            border-radius: 15px;
            font-weight: bold;
            font-size: 9px;
        }
        QPushButton:hover {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                stop:0 %3, stop:1 %4);
        }
        QPushButton:disabled {
            background: #cccccc;
            color: #666666;
        }
    )").arg(color, gradientEnd, hoverColor, hoverEnd);
}

QString StyleManager::getTraversalResultListStyle() const
{
    return R"(
        QListWidget {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                stop:0 rgba(255, 255, 255, 0.95),
                stop:1 rgba(248, 250, 255, 0.95));
            border: 2px solid qlineargradient(x1:0, y1:0, x2:1, y2:0,
                stop:0 rgba(123, 79, 255, 0.4),
                stop:0.5 rgba(74, 144, 226, 0.4),
                stop:1 rgba(138, 43, 226, 0.4));
            border-radius: 12px;
            padding: 10px;
            font-family: 'Segoe UI';
            font-size: 13px;
            font-weight: 600;
        }
        QListWidget::item {
            padding: 8px 12px;
            border-radius: 8px;
            color: #2d1b69;
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                stop:0 rgba(123, 79, 255, 0.08),
                stop:1 rgba(74, 144, 226, 0.08));
            margin: 3px 0;
            border: 1px solid rgba(123, 79, 255, 0.15);
        }
        QListWidget::item:selected {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                stop:0 rgba(123, 79, 255, 0.2),
                stop:1 rgba(74, 144, 226, 0.2));
            color: #1a1a2e;
            border-color: rgba(123, 79, 255, 0.3);
        }
        QListWidget::item:hover {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                stop:0 rgba(123, 79, 255, 0.15),
                stop:1 rgba(74, 144, 226, 0.15));
            border-color: rgba(123, 79, 255, 0.25);
        }
    )";
}

QString StyleManager::getOperationButtonStyle(const QString &color) const
{
    return QString(R"(
        QPushButton {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                stop:0 %1, stop:1 %2);
            color: white;
            border: none;
            border-radius: 20px;
            font-weight: bold;
            font-size: 11px;
            padding: 8px 16px;
        }
        QPushButton:hover {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                stop:0 %3, stop:1 %4);
            transform: translateY(-1px);
        }
        QPushButton:pressed {
            transform: translateY(0px);
        }
        QPushButton:disabled { 
            background: #cccccc; 
            color: #666666;
        }
    )").arg(color)
       .arg(color == "#7b4fff" ? "#9b6fff" : color)
       .arg(color == "#7b4fff" ? "#6b3fff" : color)
       .arg(color == "#7b4fff" ? "#8b5fff" : color);
}

QString StyleManager::getSplitterStyle() const
{
    return R"(
        QSplitter::handle {
            background-color: #e0e0e0;
            width: 2px;
        }
        QSplitter::handle:hover {
            background-color: #7b4fff;
        }
    )";
}

QString StyleManager::getStepTraceStyle() const
{
    return R"(
        QListWidget {
            background: white;
            border: 1px solid #e0e0e0;
            border-radius: 6px;
            padding: 8px;
            font-family: 'Segoe UI';
            font-size: 12px;
            selection-background-color: rgba(123, 79, 255, 0.2);
        }
        QListWidget::item {
            padding: 6px;
            border-bottom: 1px solid #f0f0f0;
            color: #495057;
        }
        QListWidget::item:selected {
            background: rgba(123, 79, 255, 0.1);
            color: #7b4fff;
        }
        QScrollBar:vertical {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                stop:0 rgba(240, 242, 247, 0.8),
                stop:1 rgba(248, 250, 255, 0.8));
            width: 10px;
            border-radius: 5px;
            margin: 2px;
            border: 1px solid rgba(123, 79, 255, 0.1);
        }
        QScrollBar::handle:vertical {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                stop:0 rgba(123, 79, 255, 0.7),
                stop:0.5 rgba(138, 43, 226, 0.7),
                stop:1 rgba(74, 144, 226, 0.7));
            border-radius: 5px;
            min-height: 30px;
            margin: 1px;
            border: 1px solid rgba(123, 79, 255, 0.2);
        }
        QScrollBar::handle:vertical:hover {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                stop:0 rgba(123, 79, 255, 0.9),
                stop:0.5 rgba(138, 43, 226, 0.9),
                stop:1 rgba(74, 144, 226, 0.9));
            border: 1px solid rgba(123, 79, 255, 0.4);
            box-shadow: 0px 2px 8px rgba(123, 79, 255, 0.3);
        }
        QScrollBar::handle:vertical:pressed {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                stop:0 rgba(123, 79, 255, 1.0),
                stop:0.5 rgba(138, 43, 226, 1.0),
                stop:1 rgba(74, 144, 226, 1.0));
            border: 1px solid rgba(123, 79, 255, 0.6);
            box-shadow: 0px 1px 4px rgba(123, 79, 255, 0.4);
        }
        QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
            height: 0px;
            width: 0px;
        }
        QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {
            background: transparent;
        }
    )";
}

void StyleManager::applyTraversalGroupStyle(QGroupBox *groupBox)
{
    if (groupBox) {
        groupBox->setStyleSheet(getTraversalGroupStyle());
    }
}

void StyleManager::applyTraversalButtonStyle(QPushButton *button, const QString &color)
{
    if (button) {
        button->setStyleSheet(getTraversalButtonStyle(color));
    }
}

void StyleManager::applyTraversalResultListStyle(QListWidget *listWidget)
{
    if (listWidget) {
        listWidget->setStyleSheet(getTraversalResultListStyle());
    }
}

void StyleManager::applyOperationButtonStyle(QPushButton *button, const QString &color)
{
    if (button) {
        button->setStyleSheet(getOperationButtonStyle(color));
    }
}

void StyleManager::applySplitterStyle(QWidget *splitter)
{
    if (splitter) {
        splitter->setStyleSheet(getSplitterStyle());
    }
}

void StyleManager::applyStepTraceStyle(QListWidget *listWidget)
{
    if (listWidget) {
        listWidget->setStyleSheet(getStepTraceStyle());
    }
}

QFont StyleManager::getPreferredFont(int size, bool bold) const
{
    QFont font;
    QStringList preferredFonts = {"Segoe UI", "Poppins", "SF Pro Display", "Arial"};
    for (const QString &fontName : preferredFonts) {
        if (QFontDatabase::families().contains(fontName)) {
            font.setFamily(fontName);
            break;
        }
    }
    font.setPointSize(size);
    font.setBold(bold);
    return font;
}

