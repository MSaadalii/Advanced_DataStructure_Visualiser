#ifndef WIDGETMANAGER_H
#define WIDGETMANAGER_H

#include <QWidget>
#include <QTimer>
#include <QList>
#include <QPointer>
#include <QObject>
#include <memory>

class WidgetManager : public QObject
{
    Q_OBJECT

public:
    explicit WidgetManager(QObject *parent = nullptr);
    ~WidgetManager();

    // Memory-safe widget management
    template<typename T>
    T* createWidget(QWidget *parent = nullptr) {
        T* widget = new T(parent);
        if (!parent) {
            // Track widgets without parents to prevent memory leaks
            m_orphanWidgets.append(QPointer<QWidget>(widget));
        }
        return widget;
    }

    // Timer management
    QTimer* createTimer(QObject *parent = nullptr);
    void stopAllTimers();
    
    // Safe widget deletion
    void safeDeleteLater(QWidget *widget);
    
    // Cleanup methods
    void cleanup();
    void cleanupOrphanWidgets();

private slots:
    void onWidgetDestroyed();

private:
    QList<QPointer<QTimer>> m_timers;
    QList<QPointer<QWidget>> m_orphanWidgets;
    QList<QPointer<QWidget>> m_pendingDeletion;
};

// Global widget manager instance
extern std::unique_ptr<WidgetManager> g_widgetManager;

// Convenience functions
template<typename T>
T* createManagedWidget(QWidget *parent = nullptr) {
    if (!g_widgetManager) {
        g_widgetManager = std::make_unique<WidgetManager>();
    }
    return g_widgetManager->createWidget<T>(parent);
}

void cleanupAllWidgets();

#endif // WIDGETMANAGER_H
