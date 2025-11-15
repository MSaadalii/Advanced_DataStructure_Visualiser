#include "theorypage.h"
#include <QPainter>
#include <QLinearGradient>
#include <QRadialGradient>
#include <QFont>
#include <QFontDatabase>
#include <QGraphicsDropShadowEffect>

TheoryPage::TheoryPage(const QString &dataStructureName, QWidget *parent)
    : QWidget(parent)
    , dsName(dataStructureName)
{
    setupUI();
    loadTheoryContent();
    setMinimumSize(900, 750);
}

TheoryPage::~TheoryPage()
{
}

void TheoryPage::setupUI()
{
    // Main layout with better spacing
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(30, 25, 30, 25);
    mainLayout->setSpacing(15);

    // Header section
    QHBoxLayout *headerLayout = new QHBoxLayout();

    // Back button with improved styling
    backButton = new BackButton(BackButton::BackToMenu, this);
    backButton->setFixedSize(150, 42);

    headerLayout->addWidget(backButton, 0, Qt::AlignLeft);
    headerLayout->addStretch();

    mainLayout->addLayout(headerLayout);

    // Title with better typography
    titleLabel = new QLabel(dsName, this);
    QFont titleFont("Segoe UI", 32, QFont::Bold);
    titleLabel->setFont(titleFont);
    titleLabel->setStyleSheet(R"(
        QLabel {
            color: #1a202c;
            background: transparent;
            padding: 10px 0px;
        }
    )");
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);

    // Content area - NO SCROLL AREA, direct layout
    contentWidget = new QWidget();
    contentWidget->setStyleSheet("background: transparent;");
    
    // Create a grid layout for better organization
    QGridLayout *contentGrid = new QGridLayout(contentWidget);
    contentGrid->setSpacing(15);
    contentGrid->setContentsMargins(0, 0, 0, 0);

    mainLayout->addWidget(contentWidget, 1); // Give it stretch

    // Try it yourself button with modern styling
    tryButton = new QPushButton("Try It Yourself →", this);
    tryButton->setFixedSize(240, 50);
    tryButton->setCursor(Qt::PointingHandCursor);

    QFont tryFont("Segoe UI", 14, QFont::Bold);
    tryButton->setFont(tryFont);
    tryButton->setStyleSheet(R"(
        QPushButton {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                stop:0 #667eea, stop:0.5 #764ba2, stop:1 #f093fb);
            color: white;
            border: none;
            border-radius: 25px;
            padding: 12px 24px;
        }
        QPushButton:hover {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                stop:0 #5a6fd8, stop:0.5 #6a4190, stop:1 #de81e9);
            transform: translateY(-2px);
        }
        QPushButton:pressed {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                stop:0 #4e5bc6, stop:0.5 #5e377e, stop:1 #cc6fd7);
        }
    )");

    mainLayout->addWidget(tryButton, 0, Qt::AlignCenter);
    mainLayout->addSpacing(10);

    setLayout(mainLayout);

    // Connect signals
    connect(backButton, &BackButton::backRequested, this, &TheoryPage::backToMenu);
    connect(tryButton, &QPushButton::clicked, this, &TheoryPage::tryItYourself);
}

void TheoryPage::loadTheoryContent()
{
    QGridLayout *contentGrid = qobject_cast<QGridLayout*>(contentWidget->layout());
    if (!contentGrid) return;

    // Clear existing content
    QLayoutItem *item;
    while ((item = contentGrid->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    // Add theory cards in a 2x3 grid layout for better space utilization
    contentGrid->addWidget(createInfoCard("📖 Definition", getDefinition(), "📖"), 0, 0, 1, 2); // Span 2 columns
    contentGrid->addWidget(createInfoCard("⏱️ Time Complexity", getTimeComplexity(), "⏱️"), 1, 0);
    contentGrid->addWidget(createInfoCard("💡 Applications", getApplications(), "💡"), 1, 1);
    contentGrid->addWidget(createInfoCard("✅ Advantages", getAdvantages(), "✅"), 2, 0);
    contentGrid->addWidget(createInfoCard("⚠️ Disadvantages", getDisadvantages(), "⚠️"), 2, 1);

    // Set column stretch to make cards equal width
    contentGrid->setColumnStretch(0, 1);
    contentGrid->setColumnStretch(1, 1);
}

QWidget* TheoryPage::createInfoCard(const QString &title, const QString &content, const QString &icon)
{
    QFrame *card = new QFrame();
    card->setFrameStyle(QFrame::NoFrame);
    
    // Modern glassmorphism-inspired design
    card->setStyleSheet(R"(
        QFrame {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                stop:0 rgba(255, 255, 255, 0.9),
                stop:0.5 rgba(248, 250, 255, 0.95),
                stop:1 rgba(240, 245, 255, 0.9));
            border: 1px solid rgba(255, 255, 255, 0.3);
            border-radius: 16px;
            margin: 5px;
        }
    )");

    // Subtle shadow effect
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect();
    shadowEffect->setBlurRadius(20);
    shadowEffect->setColor(QColor(0, 0, 0, 15));
    shadowEffect->setOffset(0, 8);
    card->setGraphicsEffect(shadowEffect);

    QVBoxLayout *cardLayout = new QVBoxLayout(card);
    cardLayout->setContentsMargins(20, 18, 20, 18);
    cardLayout->setSpacing(12);

    // Title with modern typography
    QLabel *titleLabel = new QLabel(title);
    QFont titleFont("Segoe UI", 16, QFont::Bold);
    titleLabel->setFont(titleFont);
    titleLabel->setStyleSheet(R"(
        QLabel {
            color: #2d3748;
            background: transparent;
            padding: 0px;
            margin-bottom: 8px;
        }
    )");
    cardLayout->addWidget(titleLabel);

    // Content with better readability
    QLabel *contentLabel = new QLabel(content);
    QFont contentFont("Segoe UI", 12);
    contentLabel->setFont(contentFont);
    contentLabel->setStyleSheet(R"(
        QLabel {
            color: #4a5568;
            background: transparent;
            line-height: 1.6;
            padding: 0px;
        }
    )");
    contentLabel->setWordWrap(true);
    contentLabel->setTextFormat(Qt::RichText);
    contentLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    cardLayout->addWidget(contentLabel);

    // Add some stretch to push content to top
    cardLayout->addStretch();

    card->setLayout(cardLayout);
    return card;
}

QString TheoryPage::getDefinition()
{
    if (dsName == "Binary Search Tree") {
        return "A <b>Binary Search Tree</b> is a hierarchical data structure in which each node has at most two children, "
               "referred to as the <b>left child</b> and <b>right child</b>. It starts with a root node and "
               "branches out into a tree-like structure. Binary Search Trees are fundamental in computer science and "
               "form the basis for more complex data structures like AVL Trees, and Heaps.";
    } else if (dsName == "Red-Black Tree") {
        return "A <b>Red-Black Tree</b> is a self-balancing Binary Search Tree where each node has an extra bit "
               "for denoting the color (red or black). These color bits ensure that the tree remains approximately "
               "balanced during insertions and deletions, guaranteeing O(log n) time complexity for operations.";
    } else if (dsName == "Graph") {
        return "A <b>Graph</b> is a non-linear data structure consisting of vertices (nodes) and edges that connect "
               "pairs of vertices. Graphs can be directed or undirected, weighted or unweighted, and are used to "
               "represent networks, relationships, and connections between entities.";
    } else if (dsName == "Hash Table") {
        return "A <b>Hash Table</b> (Hash Map) is a data structure that implements an associative array, mapping "
               "keys to values. It uses a hash function to compute an index into an array of buckets, from which "
               "the desired value can be found, providing average-case O(1) time complexity for search operations.";
    }
    return "Information not available.";
}

QString TheoryPage::getTimeComplexity()
{
    if (dsName == "Binary Search Tree") {
        return "<b>Search:</b> O(n) in worst case (unbalanced), O(log n) for balanced trees<br>"
               "<b>Insertion:</b> O(n) in worst case, O(log n) for balanced trees<br>"
               "<b>Deletion:</b> O(n) in worst case, O(log n) for balanced trees<br>"
               "<b>Space Complexity:</b> O(n)";
    } else if (dsName == "Red-Black Tree") {
        return "<b>Search:</b> O(log n)<br>"
               "<b>Insertion:</b> O(log n)<br>"
               "<b>Deletion:</b> O(log n)<br>"
               "<b>Space Complexity:</b> O(n)";
    } else if (dsName == "Graph") {
        return "<b>Search (BFS/DFS):</b> O(V + E) where V=vertices, E=edges<br>"
               "<b>Insertion:</b> O(1) for adding vertex/edge<br>"
               "<b>Deletion:</b> O(V + E) in worst case<br>"
               "<b>Space Complexity:</b> O(V + E)";
    } else if (dsName == "Hash Table") {
        return "<b>Search:</b> O(1) average case, O(n) worst case<br>"
               "<b>Insertion:</b> O(1) average case, O(n) worst case<br>"
               "<b>Deletion:</b> O(1) average case, O(n) worst case<br>"
               "<b>Space Complexity:</b> O(n)";
    }
    return "Information not available.";
}

QString TheoryPage::getApplications()
{
    if (dsName == "Binary Search Tree") {
        return "• <b>Expression Trees:</b> Used in compilers for parsing expressions<br>"
               "• <b>Binary Search Trees:</b> Efficient searching and sorting<br>"
               "• <b>Huffman Coding Trees:</b> Data compression algorithms<br>"
               "• <b>File System:</b> Directory structure representation<br>"
               "• <b>Database Indexing:</b> B-trees for efficient data retrieval";
    } else if (dsName == "Red-Black Tree") {
        return "• <b>Associative Arrays:</b> Implementation of maps and sets in C++ STL<br>"
               "• <b>Java TreeMap:</b> Sorted map implementation<br>"
               "• <b>Linux Kernel:</b> Completely Fair Scheduler (CFS)<br>"
               "• <b>Memory Management:</b> Virtual memory management in operating systems";
    } else if (dsName == "Graph") {
        return "• <b>Social Networks:</b> Representing connections between users<br>"
               "• <b>Maps & Navigation:</b> GPS and route finding (Dijkstra's algorithm)<br>"
               "• <b>Computer Networks:</b> Network topology and routing protocols<br>"
               "• <b>Web Crawlers:</b> Link structure of websites<br>"
               "• <b>Recommendation Systems:</b> Product and content recommendations";
    } else if (dsName == "Hash Table") {
        return "• <b>Databases:</b> Fast data retrieval and indexing<br>"
               "• <b>Caching:</b> Quick access to frequently used data<br>"
               "• <b>Symbol Tables:</b> Compiler design and interpreters<br>"
               "• <b>Password Verification:</b> Storing hashed passwords securely<br>"
               "• <b>Dictionaries:</b> Implementing key-value storage systems";
    }
    return "Information not available.";
}

QString TheoryPage::getAdvantages()
{
    if (dsName == "Binary Search Tree") {
        return "• Simple and intuitive hierarchical structure<br>"
               "• Forms the basis for more advanced tree structures<br>"
               "• Efficient searching in balanced binary search trees<br>"
               "• Natural representation of hierarchical data<br>"
               "• Supports efficient in-order, pre-order, and post-order traversals";
    } else if (dsName == "Red-Black Tree") {
        return "• Guaranteed O(log n) time complexity for operations<br>"
               "• Self-balancing ensures consistent performance<br>"
               "• Better than AVL trees for insertion-heavy workloads<br>"
               "• Widely used in production systems<br>"
               "• Requires at most 2 rotations for insertion";
    } else if (dsName == "Graph") {
        return "• Can represent complex relationships and networks<br>"
               "• Flexible structure accommodates various real-world scenarios<br>"
               "• Rich algorithms available (shortest path, MST, etc.)<br>"
               "• Both directed and undirected relationships supported<br>"
               "• Can model cyclic and acyclic dependencies";
    } else if (dsName == "Hash Table") {
        return "• Extremely fast average-case O(1) lookup, insertion, and deletion<br>"
               "• Efficient memory usage with proper load factor<br>"
               "• Simple to implement and use<br>"
               "• Ideal for key-value pair storage<br>"
               "• Widely supported in programming languages";
    }
    return "Information not available.";
}

QString TheoryPage::getDisadvantages()
{
    if (dsName == "Binary Search Tree") {
        return "• Can become unbalanced, leading to O(n) operations<br>"
               "• No guaranteed performance without balancing<br>"
               "• Requires extra memory for pointers<br>"
               "• Complex deletion operation (especially with two children)<br>"
               "• Not efficient for unsorted data";
    } else if (dsName == "Red-Black Tree") {
        return "• More complex implementation than basic binary trees<br>"
               "• Requires extra storage for color information<br>"
               "• More rotations needed than some other balanced trees<br>"
               "• Harder to understand and debug<br>"
               "• Slightly slower than AVL trees for search-heavy workloads";
    } else if (dsName == "Graph") {
        return "• Can consume significant memory for dense graphs<br>"
               "• Complex algorithms may be difficult to implement<br>"
               "• No fixed time complexity for many operations<br>"
               "• Cycle detection can be computationally expensive<br>"
               "• Requires careful handling of disconnected components";
    } else if (dsName == "Hash Table") {
        return "• Worst-case O(n) time complexity due to collisions<br>"
               "• No ordering of elements maintained<br>"
               "• Requires good hash function to avoid clustering<br>"
               "• Resizing can be expensive<br>"
               "• Vulnerable to hash collision attacks (DoS)";
    }
    return "Information not available.";
}

void TheoryPage::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Beautiful modern gradient background
    QLinearGradient gradient(0, 0, width(), height());
    gradient.setColorAt(0.0, QColor(255, 255, 255));      // Pure white at top
    gradient.setColorAt(0.3, QColor(248, 250, 252));      // Very light blue-gray
    gradient.setColorAt(0.7, QColor(241, 245, 249));      // Light blue-gray
    gradient.setColorAt(1.0, QColor(237, 242, 247));      // Slightly darker blue-gray

    painter.fillRect(rect(), gradient);

    // Add subtle geometric patterns for visual interest
    painter.setOpacity(0.02);
    QPen patternPen(QColor(99, 102, 241), 1);
    painter.setPen(patternPen);
    
    // Draw subtle diagonal grid pattern
    int spacing = 60;
    for (int x = 0; x < width(); x += spacing) {
        painter.drawLine(x, 0, x, height());
    }
    for (int y = 0; y < height(); y += spacing) {
        painter.drawLine(0, y, width(), y);
    }
    
    painter.setOpacity(1.0);

    // Add floating accent elements
    painter.setOpacity(0.08);
    QBrush accentBrush(QColor(139, 92, 246));
    painter.setBrush(accentBrush);
    painter.setPen(Qt::NoPen);
    
    // Top-left accent circle
    painter.drawEllipse(width() * 0.1, height() * 0.1, 120, 120);
    
    // Bottom-right accent circle
    painter.drawEllipse(width() * 0.85, height() * 0.8, 100, 100);
    
    // Middle accent element
    painter.drawEllipse(width() * 0.7, height() * 0.2, 80, 80);
    
    painter.setOpacity(1.0);
}
