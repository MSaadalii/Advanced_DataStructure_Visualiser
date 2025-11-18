#ifndef GRAPHVISUALIZATION_H
#define GRAPHVISUALIZATION_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPainter>
#include <QTimer>
#include <QSet>
#include <QHash>
#include <QListWidget>
#include <QVector>
#include <QSplitter>
#include <QGroupBox>
#include <QTabWidget>
#include <QFontDatabase>
#include <QLinearGradient>
#include <QFont>
#include <QMessageBox>
#include <QResizeEvent>
#include <QRandomGenerator>
#include <QtMath>
#include <QGraphicsDropShadowEffect>
#include <QPaintEvent>
#include "backbutton.h"
#include "stylemanager.h"
#include "widgetmanager.h"
#include "uiutils.h"

struct GraphNode {
    int id;
    QPointF pos;
    bool highlighted;
    bool visited;
    GraphNode() : id(-1), pos(0, 0), highlighted(false), visited(false) {}
    GraphNode(int nid, const QPointF &p) : id(nid), pos(p), highlighted(false), visited(false) {}
};

class GraphVisualization : public QWidget
{
    Q_OBJECT

public:
    explicit GraphVisualization(QWidget *parent = nullptr);
    ~GraphVisualization();

signals:
    void backToOperations();

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void onBackClicked();
    void onAddVertexClicked();
    void onDeleteVertexClicked();
    void onAddEdgeClicked();
    void onDeleteEdgeClicked();
    void onRemoveEdgeClicked();
    void onClearClicked();
    void onRandomizeClicked();
    void onRandomizeEdgeClicked();
    void onStartBFS();
    void onStartDFS();
    void onAnimationStep();

private:
    // UI setup
    void setupUI();
    void setupVisualizationArea();
    void setupRightPanel();
    void setupStepTrace();
    void setupTraversalControls();
    void refreshCombos();
    void setControlsEnabled(bool enabled);

    // Graph logic
    void resetHighlights();
    bool addEdgeInternal(int u, int v);
    bool removeVertexInternal(int u);
    bool removeEdgeInternal(int u, int v);

    // History/Logging
    void addStepToHistory(const QString &step);
    void addOperationSeparator();
    void updateStepTrace();
    void showAlgorithm(const QString &operation);

    // Animation state
    enum class TraversalType { None, BFS, DFS };
    TraversalType traversalType;
    QList<int> traversalOrder;
    int traversalIndex;
    QSet<int> frontier;
    QTimer *animTimer;

    // Forward declaration for canvas
    class GraphCanvas;
    
    // Main UI components
    QSplitter *mainSplitter;
    QWidget *leftPanel;
    QWidget *rightPanel;
    QVBoxLayout *leftLayout;
    QVBoxLayout *rightLayout;
    GraphCanvas *canvas;
    
    BackButton *backButton;
    QLabel *titleLabel;
    QLabel *statusLabel;

    QPushButton *addVertexButton;
    QLineEdit *vertexInput;
    QPushButton *deleteVertexButton;
    QLineEdit *edgeFromInput;
    QLineEdit *edgeToInput;
    QPushButton *addEdgeButton;
    QPushButton *deleteEdgeButton;

    QPushButton *clearButton;
    QPushButton *randomizeButton;
    QPushButton *randomizeEdgeButton;

    // Right panel components - Chat box
    QGroupBox *traceGroup;
    QTabWidget *traceTabWidget;
    QListWidget *stepsList;
    QListWidget *algorithmList;
    
    // Right panel components - Traversal controls
    QGroupBox *traversalGroup;
    QPushButton *bfsButton;
    QPushButton *dfsButton;
    QListWidget *traversalResultList;

    // Data
    QVector<GraphNode> nodes;
    QHash<int, QSet<int>> adjacency; // undirected, unweighted
    int nextId;
    QVector<QString> stepHistory;
    QString currentOperation;

    // Drawing constants
    const int NODE_RADIUS = 24;
};

#endif // GRAPHVISUALIZATION_H




