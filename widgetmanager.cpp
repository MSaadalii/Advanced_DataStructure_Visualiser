#include "widgetmanager.h"

// Global widget manager instance
std::unique_ptr<WidgetManager> g_widgetManager = nullptr;

WidgetManager::WidgetManager(QObject *parent)
    : QObject(parent)
{
}

WidgetManager::~WidgetManager()
{
    cleanup();
}

QTimer* WidgetManager::createTimer(QObject *parent)
{
    QTimer *timer = new QTimer(parent);
    m_timers.append(QPointer<QTimer>(timer));
    
    // Connect to cleanup when timer is destroyed
    connect(timer, &QObject::destroyed, this, &WidgetManager::onWidgetDestroyed);
    
    return timer;
}

void WidgetManager::stopAllTimers()
{
    for (auto it = m_timers.begin(); it != m_timers.end();) {
        if (*it) {
            (*it)->stop();
            ++it;
        } else {
            it = m_timers.erase(it);
        }
    }
}

void WidgetManager::safeDeleteLater(QWidget *widget)
{
    if (!widget) return;
    
    m_pendingDeletion.append(QPointer<QWidget>(widget));
    widget->deleteLater();
}

void WidgetManager::cleanup()
{
    // Stop all timers first
    stopAllTimers();
    
    // Clean up orphan widgets
    cleanupOrphanWidgets();
    
    // Clear all tracking lists
    m_timers.clear();
    m_orphanWidgets.clear();
    m_pendingDeletion.clear();
}

void WidgetManager::cleanupOrphanWidgets()
{
    for (auto it = m_orphanWidgets.begin(); it != m_orphanWidgets.end();) {
        if (*it) {
            (*it)->deleteLater();
            ++it;
        } else {
            it = m_orphanWidgets.erase(it);
        }
    }
    m_orphanWidgets.clear();
}

void WidgetManager::onWidgetDestroyed()
{
    // Clean up null pointers from our tracking lists
    m_timers.removeAll(QPointer<QTimer>());
    m_orphanWidgets.removeAll(QPointer<QWidget>());
    m_pendingDeletion.removeAll(QPointer<QWidget>());
}

// Convenience functions
void cleanupAllWidgets()
{
    if (g_widgetManager) {
        g_widgetManager->cleanup();
    }
}
