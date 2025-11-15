#ifndef TRAVERSALVISUALIZATION_H
#define TRAVERSALVISUALIZATION_H

#include "basevisualization.h"
#include <QQueue>
#include <QStack>

enum class TraversalType {
    None,
    BFS,
    DFS
};

template<typename NodeType>
class TraversalVisualization : public BaseVisualization
{
public:
    explicit TraversalVisualization(const QString &title, QWidget *parent = nullptr)
        : BaseVisualization(title, parent)
        , traversalType(TraversalType::None)
        , traversalIndex(0)
        , traversalAnimTimer(new QTimer(this))
    {
        connect(traversalAnimTimer, &QTimer::timeout, this, &TraversalVisualization::onTraversalAnimationStep);
    }

    virtual ~TraversalVisualization()
    {
        if (traversalAnimTimer) {
            traversalAnimTimer->stop();
        }
    }

protected:
    // Traversal components
    QGroupBox *traversalGroup;
    QPushButton *bfsButton;
    QPushButton *dfsButton;
    QListWidget *traversalResultList;
    
    // Traversal state
    TraversalType traversalType;
    QList<NodeType*> traversalOrder;
    int traversalIndex;
    QTimer *traversalAnimTimer;

    // Pure virtual methods that subclasses must implement
    virtual void performBFS() = 0;
    virtual void performDFS() = 0;
    virtual void resetTraversalHighlights(NodeType* node) = 0;
    virtual NodeType* getRootNode() = 0;

    // Common traversal setup
    void setupTraversalControls()
    {
        // Traversal controls group
        traversalGroup = new QGroupBox("Tree Traversal");
        traversalGroup->setStyleSheet(R"(
            QGroupBox {
                font-weight: bold;
                font-size: 14px;
                color: #495057;
                border: 2px solid #e9ecef;
                border-radius: 8px;
                margin-top: 10px;
                padding-top: 10px;
                background: white;
            }
            QGroupBox::title {
                subcontrol-origin: margin;
                left: 10px;
                padding: 0 8px 0 8px;
                background: white;
            }
        )");

        QVBoxLayout *traversalLayout = new QVBoxLayout(traversalGroup);
        traversalLayout->setSpacing(12);

        // Traversal buttons
        QHBoxLayout *traversalButtonsLayout = new QHBoxLayout();
        
        bfsButton = createStyledButton("Start BFS", "#28a745");
        dfsButton = createStyledButton("Start DFS", "#dc3545");
        
        connect(bfsButton, &QPushButton::clicked, this, &TraversalVisualization::onStartBFS);
        connect(dfsButton, &QPushButton::clicked, this, &TraversalVisualization::onStartDFS);

        traversalButtonsLayout->addWidget(bfsButton);
        traversalButtonsLayout->addWidget(dfsButton);
        traversalButtonsLayout->addStretch();

        traversalLayout->addLayout(traversalButtonsLayout);

        // Traversal result list
        QLabel *resultLabel = createStyledLabel("Traversal Order:", 12);
        resultLabel->setStyleSheet("font-weight: bold; color: #495057;");
        traversalLayout->addWidget(resultLabel);

        traversalResultList = new QListWidget();
        traversalResultList->setMaximumHeight(120);
        traversalResultList->setStyleSheet(getScrollBarStyle());
        traversalLayout->addWidget(traversalResultList);

        leftLayout->addWidget(traversalGroup);
    }

    void onStartBFS()
    {
        if (!getRootNode()) {
            statusLabel->setText("Tree is empty!");
            return;
        }

        traversalType = TraversalType::BFS;
        traversalOrder.clear();
        traversalIndex = 0;
        
        performBFS();
        
        // Display results
        traversalResultList->clear();
        QString result = "BFS: ";
        for (int i = 0; i < traversalOrder.size(); ++i) {
            if (i > 0) result += " → ";
            result += QString::number(traversalOrder[i]->value);
        }
        
        if (traversalOrder.isEmpty()) {
            traversalResultList->addItem("No nodes to traverse");
        } else {
            traversalResultList->addItem(result);
        }
        
        setControlsEnabled(false);
        traversalAnimTimer->start(800);
        statusLabel->setText("Running BFS...");
        addStepToHistory("✅ BFS traversal order computed, starting animation");
        addOperationSeparator();
    }

    void onStartDFS()
    {
        if (!getRootNode()) {
            statusLabel->setText("Tree is empty!");
            return;
        }

        traversalType = TraversalType::DFS;
        traversalOrder.clear();
        traversalIndex = 0;
        
        performDFS();
        
        // Display results
        traversalResultList->clear();
        QString result = "DFS: ";
        for (int i = 0; i < traversalOrder.size(); ++i) {
            if (i > 0) result += " → ";
            result += QString::number(traversalOrder[i]->value);
        }
        
        if (traversalOrder.isEmpty()) {
            traversalResultList->addItem("No nodes to traverse");
        } else {
            traversalResultList->addItem(result);
        }
        
        setControlsEnabled(false);
        traversalAnimTimer->start(800);
        statusLabel->setText("Running DFS...");
        addStepToHistory("✅ DFS traversal order computed, starting animation");
        addOperationSeparator();
    }

    void onTraversalAnimationStep()
    {
        if (traversalIndex >= traversalOrder.size()) {
            QString algo = (traversalType == TraversalType::BFS) ? "BFS" : "DFS";
            traversalAnimTimer->stop();
            traversalType = TraversalType::None;
            
            // Reset traversal highlights to restore original colors
            resetTraversalHighlights(getRootNode());
            
            setControlsEnabled(true);
            statusLabel->setText(QString("%1 completed!").arg(algo));
            addStepToHistory(QString("🎯 %1 traversal animation completed").arg(algo));
            update();
            return;
        }
        
        // Clear previous highlights
        if (traversalIndex > 0) {
            NodeType* prev = traversalOrder[traversalIndex - 1];
            prev->isTraversalHighlighted = false;
            prev->isVisited = true;
        }
        
        // Highlight current node
        NodeType* current = traversalOrder[traversalIndex];
        current->isTraversalHighlighted = true;
        
        QString algo = (traversalType == TraversalType::BFS) ? "BFS" : "DFS";
        addStepToHistory(QString("🔍 %1: Visiting node %2").arg(algo).arg(current->value));
        
        traversalIndex++;
        update();
    }

    void setControlsEnabled(bool enabled) override
    {
        BaseVisualization::setControlsEnabled(enabled);
        if (bfsButton) bfsButton->setEnabled(enabled);
        if (dfsButton) dfsButton->setEnabled(enabled);
    }
};

#endif // TRAVERSALVISUALIZATION_H
