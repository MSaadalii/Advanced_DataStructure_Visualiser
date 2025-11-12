#include <QApplication>
#include <QScreen>
#include <QRect>
#include <QStackedWidget>
#include <QTimer>
#include "homepage.h"
#include "menupage.h"
#include "operationpage.h"
#include "treeinsertion.h"
#include "graphvisualization.h"

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
    OperationPage *currentOperationPage = nullptr;
    TreeInsertion *currentTreeInsertion = nullptr;
    GraphVisualization *currentGraphVisualization = nullptr;
    int operationPageIndex = -1;
    int visualizationPageIndex = -1;
    QString currentDataStructure = "";

    // Connect HomePage to MenuPage navigation
    QObject::connect(homePage, &HomePage::navigateToMenu, [mainWindow, menuPageIndex]() {
        mainWindow->setCurrentIndex(menuPageIndex);
    });

    // Connect MenuPage navigation
    QObject::connect(menuPage, &MenuPage::dataStructureSelected,
                     [mainWindow, &currentOperationPage, &operationPageIndex, &currentDataStructure,
                      &currentTreeInsertion, &currentGraphVisualization, &visualizationPageIndex, menuPageIndex](const QString &dsName) {
                         // Store current data structure
                         currentDataStructure = dsName;

                         // For Graph, skip operation page and go directly to visualization
                         if (dsName == "Graph") {
                             // Remove old visualization if exists
                             if (currentGraphVisualization) {
                                 mainWindow->removeWidget(currentGraphVisualization);
                                 currentGraphVisualization->deleteLater();
                                 currentGraphVisualization = nullptr;
                             }
                             
                             // Create graph visualization directly
                             currentGraphVisualization = new GraphVisualization();
                             visualizationPageIndex = mainWindow->addWidget(currentGraphVisualization);

                             // Connect back button to menu
                             QObject::connect(currentGraphVisualization, &GraphVisualization::backToMenu,
                                              [mainWindow, menuPageIndex]() {
                                                  mainWindow->setCurrentIndex(menuPageIndex);
                                              });

                             mainWindow->setCurrentIndex(visualizationPageIndex);
                             return;
                         }

                         // For other data structures, show operation page
                         // Remove old operation page if exists
                         if (currentOperationPage) {
                             mainWindow->removeWidget(currentOperationPage);
                             currentOperationPage->deleteLater();
                         }

                         // Create new operation page
                         currentOperationPage = new OperationPage(dsName);
                         operationPageIndex = mainWindow->addWidget(currentOperationPage);

                         // Connect back button to menu
                         QObject::connect(currentOperationPage, &OperationPage::backToMenu,
                                          [mainWindow, menuPageIndex]() {
                                              mainWindow->setCurrentIndex(menuPageIndex);
                                          });

                         // Connect operation selection
                         QObject::connect(currentOperationPage, &OperationPage::operationSelected,
                                         [mainWindow, &currentTreeInsertion, &currentDataStructure, &visualizationPageIndex,
                                          &operationPageIndex](const QString &operation) {
                                              // Remove old visualization page if exists
                                              if (currentTreeInsertion) {
                                                  mainWindow->removeWidget(currentTreeInsertion);
                                                  currentTreeInsertion->deleteLater();
                                                  currentTreeInsertion = nullptr;
                                              }

                                              // Create appropriate visualization based on data structure and operation
                                              if (currentDataStructure == "Binary Tree" && operation == "Insertion") {
                                                  currentTreeInsertion = new TreeInsertion();
                                                  visualizationPageIndex = mainWindow->addWidget(currentTreeInsertion);

                                                  // Connect back button to return to operations
                                                  QObject::connect(currentTreeInsertion, &TreeInsertion::backToOperations,
                                                                   [mainWindow, operationPageIndex]() {
                                                                       mainWindow->setCurrentIndex(operationPageIndex);
                                                                   });

                                                  mainWindow->setCurrentIndex(visualizationPageIndex);
                                              }
                                              // TODO: Add other data structures and operations here
                                          });

                         // Show operation page
                         mainWindow->setCurrentIndex(operationPageIndex);
                     });

    // Center window on screen
    QScreen *screen = QApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int x = (screenGeometry.width() - mainWindow->width()) / 2;
    int y = (screenGeometry.height() - mainWindow->height()) / 2;
    mainWindow->move(x, y);
    mainWindow->show();

    return app.exec();
}
