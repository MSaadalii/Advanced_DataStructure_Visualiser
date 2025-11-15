#include <QApplication>
#include <QScreen>
#include <QRect>
#include <QStackedWidget>
#include "homepage.h"
#include "menupage.h"
#include "theorypage.h"
#include "treeinsertion.h"
#include "graphvisualization.h"
#include "hashmapvisualization.h"
#include "redblacktree.h"
#include "widgetmanager.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Create main window with stacked widget
    QStackedWidget *mainWindow = new QStackedWidget();
    mainWindow->setWindowTitle("Advanced Data Structure Visualizer");
    mainWindow->setMinimumSize(900, 750);

    // Create pages
    HomePage *homePage = new HomePage();
    MenuPage *menuPage = new MenuPage();

    // Add pages to stacked widget
    int homePageIndex = mainWindow->addWidget(homePage);
    int menuPageIndex = mainWindow->addWidget(menuPage);

    // Start with home page
    mainWindow->setCurrentIndex(homePageIndex);

    // Variables to track pages
    TheoryPage *currentTheoryPage = nullptr;
    TreeInsertion *currentTreeInsertion = nullptr;
    GraphVisualization *currentGraphVisualization = nullptr;
    HashMapVisualization *currentHashMapVisualization = nullptr;
    RedBlackTree *currentRedBlackTree = nullptr;
    int theoryPageIndex = -1;
    int visualizationPageIndex = -1;
    QString currentDataStructure = "";

    // Connect HomePage to MenuPage navigation
    QObject::connect(homePage, &HomePage::navigateToMenu, [mainWindow, menuPageIndex]() {
        mainWindow->setCurrentIndex(menuPageIndex);
    });

    // Connect MenuPage to TheoryPage navigation
    QObject::connect(menuPage, &MenuPage::dataStructureSelected,
                     [mainWindow, menuPageIndex, &currentTheoryPage, &theoryPageIndex,
                      &currentDataStructure, &currentTreeInsertion, &currentGraphVisualization,
                      &currentHashMapVisualization, &currentRedBlackTree, &visualizationPageIndex](const QString &dsName) {
                         // Store current data structure
                         currentDataStructure = dsName;

                         // For all data structures, show theory page first
                         // Remove old theory page if exists
                         if (currentTheoryPage) {
                             mainWindow->removeWidget(currentTheoryPage);
                             currentTheoryPage->deleteLater();
                         }

                         // Create new theory page
                         currentTheoryPage = new TheoryPage(dsName);
                         theoryPageIndex = mainWindow->addWidget(currentTheoryPage);

                         // Connect back button to menu
                         QObject::connect(currentTheoryPage, &TheoryPage::backToMenu,
                                          [mainWindow, menuPageIndex]() {
                                              mainWindow->setCurrentIndex(menuPageIndex);
                                          });

                        // Connect "Try It Yourself" button directly to data structure visualization
                        // Using QPointer for memory safety
                        QObject::connect(currentTheoryPage, &TheoryPage::tryItYourself,
                                         [mainWindow, theoryPageIndex, currentDataStructure, &currentTheoryPage,
                                          &currentTreeInsertion, &currentGraphVisualization, &currentHashMapVisualization, 
                                          &currentRedBlackTree, &visualizationPageIndex]() mutable {
                                              // Safe cleanup using widget manager
                                              if (currentTreeInsertion) {
                                                  mainWindow->removeWidget(currentTreeInsertion);
                                                  if (g_widgetManager) {
                                                      g_widgetManager->safeDeleteLater(currentTreeInsertion);
                                                  } else {
                                                      currentTreeInsertion->deleteLater();
                                                  }
                                                  currentTreeInsertion = nullptr;
                                              }
                                              if (currentHashMapVisualization) {
                                                  mainWindow->removeWidget(currentHashMapVisualization);
                                                  if (g_widgetManager) {
                                                      g_widgetManager->safeDeleteLater(currentHashMapVisualization);
                                                  } else {
                                                      currentHashMapVisualization->deleteLater();
                                                  }
                                                  currentHashMapVisualization = nullptr;
                                              }
                                              if (currentRedBlackTree) {
                                                  mainWindow->removeWidget(currentRedBlackTree);
                                                  if (g_widgetManager) {
                                                      g_widgetManager->safeDeleteLater(currentRedBlackTree);
                                                  } else {
                                                      currentRedBlackTree->deleteLater();
                                                  }
                                                  currentRedBlackTree = nullptr;
                                              }
                                              if (currentGraphVisualization) {
                                                  mainWindow->removeWidget(currentGraphVisualization);
                                                  if (g_widgetManager) {
                                                      g_widgetManager->safeDeleteLater(currentGraphVisualization);
                                                  } else {
                                                      currentGraphVisualization->deleteLater();
                                                  }
                                                  currentGraphVisualization = nullptr;
                                              }

                                              // Get current theory page index dynamically (may have changed)
                                              int currentTheoryIndex = mainWindow->indexOf(currentTheoryPage);
                                              
                                              // Create appropriate visualization based on data structure
                                              if (currentDataStructure == "Binary Search Tree") {
                                                  currentTreeInsertion = new TreeInsertion();
                                                  visualizationPageIndex = mainWindow->addWidget(currentTreeInsertion);

                                                  // Use dynamic theory page index lookup
                                                  QObject::connect(currentTreeInsertion, &TreeInsertion::backToOperations,
                                                                   [mainWindow, &currentTheoryPage]() {
                                                                       if (currentTheoryPage) {
                                                                           int idx = mainWindow->indexOf(currentTheoryPage);
                                                                           if (idx >= 0 && idx < mainWindow->count()) {
                                                                               mainWindow->setCurrentIndex(idx);
                                                                           }
                                                                       }
                                                                   });

                                                  mainWindow->setCurrentIndex(visualizationPageIndex);
                                              } else if (currentDataStructure == "Red-Black Tree") {
                                                  currentRedBlackTree = new RedBlackTree();
                                                  visualizationPageIndex = mainWindow->addWidget(currentRedBlackTree);

                                                  // Use dynamic theory page index lookup
                                                  QObject::connect(currentRedBlackTree, &RedBlackTree::backToOperations,
                                                                   [mainWindow, &currentTheoryPage]() {
                                                                       if (currentTheoryPage) {
                                                                           int idx = mainWindow->indexOf(currentTheoryPage);
                                                                           if (idx >= 0 && idx < mainWindow->count()) {
                                                                               mainWindow->setCurrentIndex(idx);
                                                                           }
                                                                       }
                                                                   });

                                                  mainWindow->setCurrentIndex(visualizationPageIndex);
                                              } else if (currentDataStructure == "Hash Table") {
                                                  currentHashMapVisualization = new HashMapVisualization();
                                                  visualizationPageIndex = mainWindow->addWidget(currentHashMapVisualization);

                                                  // Use dynamic theory page index lookup
                                                  QObject::connect(currentHashMapVisualization, &HashMapVisualization::backToOperations,
                                                                   [mainWindow, &currentTheoryPage]() {
                                                                       if (currentTheoryPage) {
                                                                           int idx = mainWindow->indexOf(currentTheoryPage);
                                                                           if (idx >= 0 && idx < mainWindow->count()) {
                                                                               mainWindow->setCurrentIndex(idx);
                                                                           }
                                                                       }
                                                                   });

                                                  mainWindow->setCurrentIndex(visualizationPageIndex);
                                              } else if (currentDataStructure == "Graph") {
                                                  currentGraphVisualization = new GraphVisualization();
                                                  visualizationPageIndex = mainWindow->addWidget(currentGraphVisualization);

                                                  // Use dynamic theory page index lookup
                                                  QObject::connect(currentGraphVisualization, &GraphVisualization::backToOperations,
                                                                   [mainWindow, &currentTheoryPage]() {
                                                                       if (currentTheoryPage) {
                                                                           int idx = mainWindow->indexOf(currentTheoryPage);
                                                                           if (idx >= 0 && idx < mainWindow->count()) {
                                                                               mainWindow->setCurrentIndex(idx);
                                                                           }
                                                                       }
                                                                   });

                                                  mainWindow->setCurrentIndex(visualizationPageIndex);
                                              }
                                          });

                         // Show theory page
                         mainWindow->setCurrentIndex(theoryPageIndex);
                     });

    // Center window on screen
    QScreen *screen = QApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int x = (screenGeometry.width() - mainWindow->width()) / 2;
    int y = (screenGeometry.height() - mainWindow->height()) / 2;
    mainWindow->move(x, y);
    mainWindow->show();

    int result = app.exec();
    
    // Proper cleanup to prevent memory leaks and back button issues
    cleanupAllWidgets();
    delete mainWindow;
    
    return result;
}
