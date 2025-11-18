# 📚 Project Explanation: Advanced Data Structure Visualizer

## 🏗️ **PART 1: PROJECT ARCHITECTURE**

### **Overall Structure**

Your project is a **Qt-based desktop application** that visualizes data structures. Think of it like a **multi-page book** where each page shows different content.

```
┌─────────────────────────────────────────┐
│         QStackedWidget (Main Window)    │
│  ┌──────────┐  ┌──────────┐  ┌────────┐ │
│  │ HomePage │→ │ MenuPage │→ │ Theory │ │
│  └──────────┘  └──────────┘  └────────┘ │
│                      ↓                  │
│         ┌─────────────────────┐         │
│         │ Visualizations:       │       │
│         │ - TreeInsertion       │       │
│         │ - RedBlackTree        │       │
│         │ - HashMapVisualization│       │
│         │ - GraphVisualization  │        │
│         └─────────────────────┘         │
└─────────────────────────────────────────┘
```

### **Detailed Project Structure**

```
Second_Attempt/
├── CMakeLists.txt            # Qt build script (adds all widgets/visualizers)
├── main.cpp                  # Application entry; owns QStackedWidget
├── homepage.*, menupage.*    # Landing + structure selection
├── theorypage.*              # Theory cards per data structure
├── treeinsertion.*           # BST lab (insertion/search/delete + traversals)
├── redblacktree.*            # Self-balancing RB tree lab
├── graphvisualization.*      # Graph builder/traversal sandbox
├── hashmapvisualization.*    # Hash table playground
├── hashmap.*                 # Core hash map data model
├── stylemanager.*, backbutton.*, widgetmanager.*, uiutils.*
│                              # Shared helpers (styling, safe deletion, reusable UI)
└── build/                    # Generated binaries + Qt autogen files
```

Think of it in layers:

1. **Navigation Shell** (`main.cpp`, `HomePage`, `MenuPage`, `TheoryPage`)
2. **Visualization Workspaces** (`TreeInsertion`, `RedBlackTree`, `GraphVisualization`, `HashMapVisualization`)
3. **Data Logic** (`hashmap.cpp`, tree/graph structures inside each lab)
4. **Infrastructure** (style/util/managers + Qt resources)

### **Key Classes & Their Roles**

#### **1. Main Entry Point (`main.cpp`)**
- **Purpose**: Starts the application, manages navigation
- **Key Component**: `QStackedWidget` - like a deck of cards, shows one page at a time
- **Flow**: Home → Menu → Theory → Visualization

#### **2. UI Pages**

**`HomePage`** (homepage.h/cpp)
- Welcome screen with animations
- "Get Started" button → goes to MenuPage

**`MenuPage`** (menupage.h/cpp)
- Shows 4 cards: BST, Red-Black Tree, Hash Table, Graph
- User clicks a card → goes to TheoryPage

**`TheoryPage`** (theorypage.h/cpp)
- Shows educational content about the selected data structure
- "Try It Yourself" button → opens Visualization

#### **3. Visualization Classes (High-Level Summary)**

| Class | Data Structure | Key Interactions | Unique Touches |
|-------|----------------|------------------|----------------|
| `TreeInsertion` | Binary Search Tree | Insert, search, delete, clear, randomize, BFS, DFS | Animated node drops, traversal history, algorithm tabs |
| `RedBlackTree` | Self-balancing BST | Insert, delete, search, randomize, BFS, DFS | Rotation highlights, color flipping, algorithm view stack |
| `GraphVisualization` | Undirected graph | Add/remove vertex, add/remove edge, randomize, BFS, DFS | Canvas-based node dragging, frontier highlighting, history log |
| `HashMapVisualization` | Hash table | Insert, search, delete, clear, type switching | Bucket rectangles, load-factor HUD, step trace |

Each workspace:
- Owns left/right panels via `QSplitter`
- Exposes a `backToOperations` signal tied to TheoryPage
- Relies on `BackButton`, `StyleManager`, `WidgetManager`
- Records verbose step history for the right-side tabs

#### **4. Helper Classes**

**`StyleManager`** - Manages consistent styling across the app
**`WidgetManager`** - Handles safe widget deletion (prevents crashes)
**`BackButton`** - Reusable back button component
**`UIUtils`** - Utility functions for creating UI elements

---

## 🗺️ **PART 2: VISUALIZATION MODULES (ALL DATA STRUCTURES)**

### 🌳 Binary Search Tree Lab (`TreeInsertion`)
- **Purpose**: Teach BST basics—insert/search/delete—and visualize traversals.
- **UI Layout**: Left panel hosts controls (value input, action buttons, randomize, BFS/DFS). Right panel shows step history + pseudocode tabs.
- **Animations**:
  - Nodes fall into position with easing curves.
  - Search/delete highlight paths, showing success/failure status text.
  - Traversal playback uses timers to highlight nodes sequentially.
- **Logic Highlights**:
  - `TreeNode` struct keeps coordinates plus highlight flags.
  - Separate helpers calculate node positions per level to keep spacing even.
  - Traversals support both BFS (queue-based) and DFS (stack/recursive) with visual cues.

### 🔴⚫ Red-Black Tree Studio (`RedBlackTree`)
- **Purpose**: Demonstrate how balancing works via rotations and recoloring.
- **UI Layout**: Similar split view; additional tab shows insertion/deletion/search algorithm cards.
- **Key Features**:
  - Insert/delete/search trigger the full RB-tree fix-up routines (`fixInsert`, `fixDelete`).
  - Rotations are both functional (`rotateLeft`, `rotateRight`) and visual (`rotateLeftSync`, etc.).
  - Traversal module mirrors BST lab, ensuring consistent learning flow.
  - Status label narrates each violation and the fix applied.
- **Learning Hooks**: Step trace uses everyday language (“Parent is red, apply Case 2 rotation”) plus timestamps.

### 🕸️ Graph Sandbox (`GraphVisualization`)
- **Purpose**: Let users build undirected graphs and run traversals.
- **UI Flow**:
  - Controls for adding/removing vertices/edges, randomizing nodes, and generating random edges.
  - Combos auto-refresh so you can select vertices for edge operations without typing.
  - Canvas auto-resizes; nodes have drop shadows for depth.
- **Logic Details**:
  - `GraphNode` holds id, position, highlight/visited flags.
  - Adjacency stored in `QHash<int, QSet<int>>` for fast lookups.
  - Traversal animations maintain a “frontier” set to show which nodes are pending.
  - History captures natural-language descriptions with timestamps.

### 🗂️ Hash Table Playground (`HashMapVisualization`)
- **Purpose**: Convert the hash map implementation into an educational canvas (see Part 3 below for internals).
- **Extras**:
  - Type selectors (string/int/double/float/char) for both key and value.
  - Load-factor warning label that changes color when nearing the rehash threshold.
  - Zoom-to-fit logic keeps bucket grid readable as size grows.
  - Step trace matches every HashMap operation with a visual highlight.

---

## 🧠 **PART 3: DATA STRUCTURE IMPLEMENTATIONS (Deep Dive)**

Below are beginner-friendly breakdowns for every simulator. Each section mirrors the style used earlier for the hash table so you can compare their inner workings side by side.

---

### 🌳 **Binary Search Tree (BST) – `treeinsertion.*`**

#### **What It Teaches**
- Ordered binary trees, insert/search/delete
- Traversal strategies (BFS + DFS)
- How structural changes affect visual layout

#### **Core Data Structure**
```cpp
struct TreeNode {
    int value;
    TreeNode *left;
    TreeNode *right;
    int x, y;                  // Canvas coordinates
    bool isHighlighted;
    bool isNewNode;
    bool isSearchHighlighted;
    bool isDeleteHighlighted;
    bool isTraversalHighlighted;
    bool isVisited;
};
```

**Why so many flags?** Each animation (insert flash, search path, delete highlight, traversal trail) needs its own visual cues. Instead of re-computing styles, the painter reads these booleans and adjusts colors/glow on the fly.

#### **UI & Controls**
- Left panel: numeric input, `Insert`, `Search`, `Delete`, `Clear`, `Randomize`, `BFS`, `DFS`.
- Right panel: `Steps` tab (narrated actions) + `Algorithm` tab (pseudo-code).
- Status label summarizes the latest operation (“Inserted 42 as left child of 50”).

#### **Insert Flow**
```
1. maybeAnimateInsertion(value);
2. insertNode(value);              // standard BST insert
3. calculateNodePositions(root);   // recalc x/y per depth
4. addStepToHistory("Inserted ...");
5. update();                       // triggers paintEvent
```

Paint routine draws edges first (to keep nodes on top), then nodes with drop shadows, highlighting `isNewNode` in a accent color so learners can track fresh inserts.

#### **Delete Flow**
- Uses `deleteNode(TreeNode*, int)` + `findMin` helper for two-child cases.
- After structural change, `resetHighlights` ensures only affected path glows.
- Step trace narrates the case (“Found successor 37, swapped values, deleted leaf”).

#### **Traversals**
- `performBFS()` enqueues nodes, while `performDFS()` runs recursive order.
- A `QTimer` walks `traversalOrder`, toggling `isTraversalHighlighted` per node with short delays so learners can see visit order.

#### **Code Path (From `treeinsertion.cpp`)**
```312:340:treeinsertion.cpp
void TreeInsertion::onInsertClicked()
{
    if (isAnimating) {
        QMessageBox::warning(this, "Animation in Progress",
                             "Please wait for the current animation to complete.");
        return;
    }

    QString text = inputField->text().trimmed();
    if (text.isEmpty()) {
        QMessageBox::warning(this, "Invalid Input", "Please enter a value.");
        return;
    }

    bool ok;
    int value = text.toInt(&ok);

    if (!ok) {
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid integer.");
        return;
    }

    currentOperation = "Insert";
    addStepToHistory("➕ INSERT OPERATION");
    addStepToHistory(QString("🔢 Adding value: %1").arg(value));
    showAlgorithm("Insert");
    animateInsertion(value);
    inputField->clear();
    inputField->setFocus();
}
```

```556:616:treeinsertion.cpp
void TreeInsertion::animateInsertion(int value)
{
    isAnimating = true;
    insertButton->setEnabled(false);
    searchButton->setEnabled(false);
    deleteButton->setEnabled(false);
    clearButton->setEnabled(false);

    addStepToHistory(QString("➕ Starting insertion of value: %1").arg(value));

    // Build traversal path
    traversalPath.clear();

    if (!root) {
        insertNode(value);
        addOperationSeparator();
        isAnimating = false;
        insertButton->setEnabled(true);
        searchButton->setEnabled(true);
        deleteButton->setEnabled(true);
        clearButton->setEnabled(true);
        updateStepTrace();
        update();
        return;
    }

    TreeNode *current = root;
    while (current) {
        traversalPath.append(current);
        if (value < current->value) {
            if (!current->left) {
                break;
            }
            current = current->left;
        } else if (value > current->value) {
            if (!current->right) {
                break;
            }
            current = current->right;
        } else {
            // Duplicate value
            QMessageBox::warning(this, "Duplicate Value",
                                 QString("Value %1 already exists in tree!").arg(value));
            addStepToHistory(QString("❌ Value %1 already exists in tree!").arg(value));
            addOperationSeparator();
            isAnimating = false;
            insertButton->setEnabled(true);
            searchButton->setEnabled(true);
            deleteButton->setEnabled(true);
            clearButton->setEnabled(true);
            updateStepTrace();
            return;
        }
    }

    currentTraversalStep = 0;

    QTimer::singleShot(0, this, [this, value]() {
        animateTraversal(root, value, 0);
    });
}
```

---

### 🔴⚫ **Red-Black Tree – `redblacktree.*`**

#### **Why It’s Unique**
Adds self-balancing logic (rotations + recoloring) to keep tree height logarithmic, and visualizes each fix-up as it happens.

#### **Node Structure**
```cpp
struct RBNode {
    int value;
    Color color;               // RED or BLACK
    RBNode *left, *right, *parent;
    int x, y;
    bool isHighlighted;
    bool isRotating;
    bool isSearchHighlighted;
    bool isDeleteHighlighted;
    bool isNewNode;
    bool isTraversalHighlighted;
    bool isVisited;
};
```

`NIL` sentinel nodes are created to simplify leaf handling; they are colored black and reused instead of storing `nullptr` children.

#### **Insertion Algorithm (Visual Steps)**
```
1. Standard BST insert → new node colored RED.
2. Call fixInsert(newNode):
   a. If parent is BLACK → done.
   b. If parent is RED → inspect uncle.
      - Case 1: Uncle RED → recolor parent/uncle BLACK, grandparent RED.
      - Case 2/3: Uncle BLACK → rotate + recolor.
3. Root forced to BLACK.
```

Each case logs a friendly description (“Case 2: Left rotation on grandparent 30”). During rotation, `isRotating` flag triggers thicker edge strokes so students notice the subtree swap.

#### **Deletion Algorithm**
Deletion uses `deleteNodeHelper` (BST delete) followed by `fixDelete` to restore properties. Visual cues:
- Double-black cases flash the affected node.
- Rotations show arrow overlays.
- Status label summarizes (“Double black at node 10 – performing sibling-left case”).

#### **Traversal & Algorithm Cards**
A `QStackedWidget` inside the right panel switches between:
- Step trace list.
- BFS/DFS results.
- Algorithm cards (Insertion/Deletion/Search) showing bulletized pseudo-code for quick reference.

#### **Code Path (From `redblacktree.cpp`)**
```1071:1130:redblacktree.cpp
void RedBlackTree::insertNode(int value)
{
    // Check for duplicate
    if (findNode(root, value) != NIL) {
        statusLabel->setText(QString("Value %1 already exists!").arg(value));
        addStepToHistory(QString("❌ Insert failed: Value %1 already exists").arg(value));
        addOperationSeparator();
        return;
    }

    addStepToHistory(QString("🔍 Checking if value %1 already exists...").arg(value));
    addStepToHistory("✅ Value is unique, proceeding with insertion");

    if (root == NIL) {
        addStepToHistory(QString("🌱 Tree is empty, inserting %1 as root").arg(value));
    } else {
        addStepToHistory(QString("🌳 Tree has nodes, finding insertion position for %1").arg(value));
    }

    isAnimating = true;
    insertButton->setEnabled(false);
    deleteButton->setEnabled(false);
    searchButton->setEnabled(false);

    statusLabel->setText(QString("Inserting %1...").arg(value));

    RBNode *node = new RBNode(value);
    node->left = node->right = NIL;

    addStepToHistory(QString("🔴 Created new RED node with value %1").arg(value));
    
    root = BSTInsert(root, node);
    addStepToHistory("📍 Node inserted using BST insertion rules");

    QTimer::singleShot(500, this, [this, node, value]() {
        node->isHighlighted = true;
        statusLabel->setText("Fixing Red-Black properties...");
        addStepToHistory("🔄 Checking Red-Black tree properties...");
        update();

        QTimer::singleShot(800, this, [this, node, value]() {
            addStepToHistory("⚖️ Applying Red-Black tree balancing rules");
            fixInsert(node);
            node->isHighlighted = false;

            statusLabel->setText(QString("Successfully inserted %1").arg(value));
            addStepToHistory(QString("✅ Node %1 successfully inserted and tree balanced").arg(value));
            addStepToHistory("🎯 Red-Black tree properties maintained");
            addOperationSeparator();

            isAnimating = false;
            insertButton->setEnabled(true);
            deleteButton->setEnabled(true);
            searchButton->setEnabled(true);
            update();
        });
    });

    update();
}
```

```1154:1210:redblacktree.cpp
void RedBlackTree::fixInsert(RBNode* node)
{
    while (node->parent && node->parent->color == RED) {
        // Check if parent->parent exists (parent is not root)
        if (!node->parent->parent) {
            break;  // Parent is root, no grandparent
        }

        if (node->parent == node->parent->parent->left) {
            RBNode *uncle = node->parent->parent->right;

            // Check if uncle exists and is RED (uncle could be NIL which is BLACK)
            if (uncle && uncle != NIL && uncle->color == RED) {
                // Case 1: Uncle is red
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                // Uncle is BLACK or NIL
                if (node == node->parent->right) {
                    // Case 2: Triangle - convert to line
                    node = node->parent;
                    rotateLeftSync(node);
                }
                // Case 3: Line
                node->parent->color = BLACK;
                if (node->parent->parent) {
                    node->parent->parent->color = RED;
                    rotateRightSync(node->parent->parent);
                }
            }
        } else {
            RBNode *uncle = node->parent->parent->left;

            // Check if uncle exists and is RED
            if (uncle && uncle != NIL && uncle->color == RED) {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                // Uncle is BLACK or NIL
                if (node == node->parent->left) {
                    node = node->parent;
                    rotateRightSync(node);
                }
                node->parent->color = BLACK;
                if (node->parent->parent) {
                    node->parent->parent->color = RED;
                    rotateLeftSync(node->parent->parent);
                }
            }
        }
    }
    root->color = BLACK;
}
```

---

### 🕸 **Graph Module – `graphvisualization.*`**

#### **Learning Goals**
- Building undirected graphs
- Managing adjacency
- BFS vs DFS over arbitrary topology

#### **Core Structures**
```cpp
struct GraphNode {
    int id;
    QPointF pos;
    bool highlighted;
    bool visited;
};

QHash<int, QSet<int>> adjacency;   // adjacency list
```

`nextId` auto-increments as vertices are added. Random placement uses `QRandomGenerator` to scatter nodes within the canvas bounds; resize events trigger gentle repositioning to keep layout proportional.

#### **UI Highlights**
- Input box for vertex id, paired boxes for edge endpoints.
- Buttons: `Add Vertex`, `Delete Vertex`, `Add Edge`, `Delete Edge`, `Randomize Nodes`, `Random Edges`, `Clear`, `BFS`, `DFS`.
- Right panel mirrors others with steps + algorithm tabs.

#### **Edge Management**
```
addEdge(u, v):
  if u == v → reject (no self-loops)
  adjacency[u].insert(v);
  adjacency[v].insert(u);
  addHistory("Edge (u,v) added...");
  refreshCombos();    // keep dropdowns synced
  canvas->update();
```

Canvas draws:
- Nodes as circles with drop shadows.
- Edges as anti-aliased lines.
- Highlight colors differentiate frontier, visited, and default states.

#### **Traversal Animations**
- `TraversalType` enum toggles BFS vs DFS.
- `frontier` `QSet<int>` displayed as part of the status text (“Frontier: {3,7,9}”).
- `animTimer` steps through `traversalOrder`, marking nodes visited.
- Each step appended to `stepsList` so the textual explanation stays in sync with the visuals.

#### **Code Path (From `graphvisualization.cpp`)**
```923:969:graphvisualization.cpp
void GraphVisualization::onAddVertexClicked()
{
    showAlgorithm("Add Vertex");
    
    int id = -1;
    QString text = vertexInput->text().trimmed();
    if (!text.isEmpty()) {
        bool ok;
        id = text.toInt(&ok);
        if (!ok) {
            addStepToHistory("❌ Invalid input: Please enter a valid integer for vertex ID");
            QMessageBox::warning(this, "Invalid Input", "Please enter a valid integer for vertex ID.");
            return;
        }
        addStepToHistory(QString("🔍 Checking if vertex %1 already exists...").arg(id));
        // Check if ID already exists
        for (const auto &n : nodes) {
            if (n.id == id) {
                addStepToHistory(QString("❌ Vertex %1 already exists in the graph").arg(id));
                QMessageBox::warning(this, "Duplicate ID", QString("Vertex %1 already exists.").arg(id));
                return;
            }
        }
        addStepToHistory(QString("✅ Vertex %1 is unique, proceeding with addition").arg(id));
    } else {
        // Auto-generate ID
        id = nextId++;
        addStepToHistory(QString("🆕 Auto-generating vertex ID: %1").arg(id));
    }
    
    addStepToHistory(QString("➕ Creating new vertex %1 in adjacency list").arg(id));
    nodes.append(GraphNode(id, QPointF(0, 0)));
    adjacency.insert(id, QSet<int>());
    if (id >= nextId) nextId = id + 1;
    
    addStepToHistory("🔄 Recalculating graph layout...");
    refreshCombos();
    vertexInput->clear();
    statusLabel->setText(QString("Vertex %1 added.").arg(id));
    addStepToHistory(QString("✅ Vertex %1 successfully added to graph").arg(id));
    addOperationSeparator();
    
    // Update the canvas
    if (canvas) {
        canvas->update();
    }
}
```

```1020:1106:graphvisualization.cpp
void GraphVisualization::onAddEdgeClicked()
{
    showAlgorithm("Add Edge");
    
    QString fromText = edgeFromInput->text().trimmed();
    QString toText = edgeToInput->text().trimmed();
    
    if (fromText.isEmpty() || toText.isEmpty()) {
        addStepToHistory("❌ Invalid input: Please enter both vertex IDs");
        QMessageBox::warning(this, "Invalid Input", "Please enter both vertex IDs.");
        return;
    }
    
    bool ok1 = false, ok2 = false;
    int u = fromText.toInt(&ok1);
    int v = toText.toInt(&ok2);
    
    if (!ok1 || !ok2) {
        addStepToHistory("❌ Invalid input: Please enter valid integers for vertex IDs");
        QMessageBox::warning(this, "Invalid Input", "Please enter valid integers for vertex IDs.");
        return;
    }
    
    if (u == v) {
        addStepToHistory("❌ Self-loops are not allowed in this graph");
        QMessageBox::warning(this, "Invalid", "Self-loops are not allowed.");
        return;
    }
    
    addStepToHistory(QString("🔍 Attempting to add edge between vertex %1 and vertex %2").arg(u).arg(v));
    
    if (addEdgeInternal(u, v)) {
        edgeFromInput->clear();
        edgeToInput->clear();
        statusLabel->setText(QString("Edge %1-%2 added.").arg(u).arg(v));
        addStepToHistory(QString("✅ Edge %1-%2 successfully added to graph").arg(u).arg(v));
        addOperationSeparator();
        if (canvas) canvas->update();
    } else {
        statusLabel->setText("Edge already exists or vertices missing.");
        addStepToHistory(QString("❌ Failed: Edge %1-%2 already exists or vertices missing").arg(u).arg(v));
        addOperationSeparator();
    }
}
```

```1172:1307:graphvisualization.cpp
void GraphVisualization::onStartBFS()
{
    showAlgorithm("BFS");
    
    if (nodes.isEmpty()) {
        addStepToHistory("❌ Graph is empty: Please add vertices first");
        QMessageBox::warning(this, "Empty Graph", "Please add vertices to the graph first.");
        return;
    }
    
    // Use the first vertex as starting point
    int s = nodes.first().id;
    
    addStepToHistory(QString("🌊 Starting BFS traversal from vertex %1").arg(s));
    resetHighlights();
    traversalType = TraversalType::BFS;
    traversalOrder.clear();
    frontier.clear();
    traversalIndex = 0;

    // BFS precompute order
    addStepToHistory("🔄 Initializing BFS queue and visited set");
    QSet<int> visited;
    QList<int> queue;
    queue.append(s);
    visited.insert(s);
    addStepToHistory(QString("➕ Added vertex %1 to queue and marked as visited").arg(s));
    
    while (!queue.isEmpty()) {
        int u = queue.front();
        queue.pop_front();
        traversalOrder.append(u);
        addStepToHistory(QString("👀 Processing vertex %1 (dequeued from front)").arg(u));
        
        for (int v : adjacency.value(u)) {
            if (!visited.contains(v)) {
                visited.insert(v);
                queue.append(v);
                addStepToHistory(QString("🆕 Found unvisited neighbor %1, added to queue").arg(v));
            }
        }
    }

    // Display traversal result
    QString result = "🌊 BFS Order: ";
    for (int i = 0; i < traversalOrder.size(); ++i) {
        result += QString::number(traversalOrder[i]);
        if (i < traversalOrder.size() - 1) result += " → ";
    }
    
    traversalResultList->clear();
    if (traversalOrder.isEmpty()) {
        traversalResultList->addItem("❌ No traversal result");
    } else {
        traversalResultList->addItem(result);
        // Also add to step history for debugging
        addStepToHistory(QString("📋 %1").arg(result));
    }

    setControlsEnabled(false);
    animTimer->start(700);
    statusLabel->setText("Running BFS...");
    addStepToHistory("✅ BFS traversal order computed, starting animation");
    addOperationSeparator();
}

void GraphVisualization::onStartDFS()
{
    showAlgorithm("DFS");
    
    if (nodes.isEmpty()) {
        addStepToHistory("❌ Graph is empty: Please add vertices first");
        QMessageBox::warning(this, "Empty Graph", "Please add vertices to the graph first.");
        return;
    }
    
    // Use the first vertex as starting point
    int s = nodes.first().id;
    
    addStepToHistory(QString("🏔️ Starting DFS traversal from vertex %1").arg(s));
    resetHighlights();
    traversalType = TraversalType::DFS;
    traversalOrder.clear();
    frontier.clear();
    traversalIndex = 0;

    // DFS precompute order
    addStepToHistory("🔄 Initializing DFS stack and visited set");
    QSet<int> visited;
    QList<int> stack;
    stack.append(s);
    addStepToHistory(QString("➕ Added vertex %1 to stack").arg(s));
    
    while (!stack.isEmpty()) {
        int u = stack.takeLast();
        if (visited.contains(u)) {
            addStepToHistory(QString("⚠️ Vertex %1 already visited, skipping").arg(u));
            continue;
        }
        visited.insert(u);
        traversalOrder.append(u);
        addStepToHistory(QString("👀 Processing vertex %1 (popped from stack)").arg(u));
        
        // push neighbors in reverse for a stable ordering
        QList<int> neigh = adjacency.value(u).values();
        std::sort(neigh.begin(), neigh.end(), std::greater<int>());
        for (int v : neigh) {
            if (!visited.contains(v)) {
                stack.append(v);
                addStepToHistory(QString("🆕 Found unvisited neighbor %1, pushed to stack").arg(v));
            }
        }
    }

    // Display traversal result
    QString result = "🏔️ DFS Order: ";
    for (int i = 0; i < traversalOrder.size(); ++i) {
        result += QString::number(traversalOrder[i]);
        if (i < traversalOrder.size() - 1) result += " → ";
    }
    
    traversalResultList->clear();
    if (traversalOrder.isEmpty()) {
        traversalResultList->addItem("❌ No traversal result");
    } else {
        traversalResultList->addItem(result);
        // Also add to step history for debugging
        addStepToHistory(QString("📋 %1").arg(result));
    }

    setControlsEnabled(false);
    animTimer->start(700);
    statusLabel->setText("Running DFS...");
    addStepToHistory("✅ DFS traversal order computed, starting animation");
    addOperationSeparator();
}
```

---

### 🗂 **Hash Table – `hashmap.*` & `hashmapvisualization.*`**

> This section retains the original detailed explanation (renamed Part 4 below) so it lines up with the BST/RBT/Graph coverage above.

#### **Code Path (From `hashmap.cpp`)**
```42:128:hashmap.cpp
int HashMap::indexFor(const QVariant &key, int bucketCount) const {
    size_t hashValue = 0;

    // Use std::hash-like behavior to mirror unordered_map hashing
    switch (key.type()) {
    case QVariant::String: {
        const std::string s = key.toString().toStdString();
        hashValue = std::hash<std::string>{}(s);
        break;
    }
    case QVariant::Int: {
        const int v = key.toInt();
        hashValue = std::hash<int>{}(v);
        break;
    }
    case QVariant::Double: {
        // QVariant stores float as double by default; both map through std::hash<double>
        const double v = key.toDouble();
        hashValue = std::hash<double>{}(v);
        break;
    }
    case QVariant::Char: {
        const QChar qc = key.toChar();
        const char c = qc.toLatin1();
        hashValue = std::hash<char>{}(c);
        break;
    }
    default: {
        // Try float explicitly if convertible
        if (key.canConvert<float>()) {
            const float v = key.toFloat();
            hashValue = std::hash<float>{}(v);
        } else {
            // Fallback to string representation
            const std::string s = key.toString().toStdString();
            hashValue = std::hash<std::string>{}(s);
        }
        break;
    }
    }

    // bucket_index = hash(key) % bucketCount
    return static_cast<int>(hashValue % static_cast<size_t>(bucketCount));
}

size_t HashMap::getHashValue(const QVariant &key) const {
    size_t hashValue = 0;

    // Use std::hash-like behavior to mirror unordered_map hashing
    switch (key.type()) {
    case QVariant::String: {
        const std::string s = key.toString().toStdString();
        hashValue = std::hash<std::string>{}(s);
        break;
    }
    case QVariant::Int: {
        const int v = key.toInt();
        hashValue = std::hash<int>{}(v);
        break;
    }
    case QVariant::Double: {
        const double v = key.toDouble();
        hashValue = std::hash<double>{}(v);
        break;
    }
    case QVariant::Char: {
        const QChar qc = key.toChar();
        const char c = qc.toLatin1();
        hashValue = std::hash<char>{}(c);
        break;
    }
    default: {
        if (key.canConvert<float>()) {
            const float v = key.toFloat();
            hashValue = std::hash<float>{}(v);
        } else {
            const std::string s = key.toString().toStdString();
            hashValue = std::hash<std::string>{}(s);
        }
        break;
    }
    }

    return hashValue;
}
```

```196:247:hashmap.cpp
bool HashMap::emplaceOrAssign(const QVariant &key, const QVariant &value, bool assignIfExists) {
    // Validate types
    if (!validateType(key, keyType_) || !validateType(value, valueType_)) {
        addStep(QStringLiteral("Type validation failed"));
        return false;
    }

    const int bucketCountNow = bucketCount();

    QString keyStr = variantToDisplayString(key);
    QString valueStr = variantToDisplayString(value);

    // Use our custom indexFor method which shows the simple hash
    const int index = indexFor(key, bucketCountNow);
    const size_t computedHash = getHashValue(key);

    // Show hash calculation with computed hash value
    if (key.type() == QVariant::Int || key.type() == QVariant::Double) {
        addStep(QString("📊 Compute hash(%1) = %2").arg(keyStr).arg(computedHash));
        addStep(QString("📐 Calculate: %2 % %1 = %3").arg(bucketCountNow).arg(computedHash).arg(index));
    } else {
        addStep(QString("📊 Compute hash for: \"%1\" = %2").arg(keyStr).arg(computedHash));
        addStep(QString("📐 Index = %2 % %1 = %3").arg(bucketCountNow).arg(computedHash).arg(index));
    }
    addStep(QStringLiteral("Visit bucket %1").arg(index));

    auto &chain = buckets_[static_cast<size_t>(index)];
    for (auto &node : chain) {
        QString nodeKeyStr = variantToDisplayString(node.key);
        addStep(QStringLiteral("Compare keys: %1 == %2 ? %3")
                    .arg(nodeKeyStr, keyStr, node.key == key ? QStringLiteral("Yes") : QStringLiteral("No")));
        if (node.key == key) {
            if (assignIfExists) {
                QString oldValueStr = variantToDisplayString(node.value);
                addStep(QStringLiteral("Key exists → update value: %1 → %2").arg(oldValueStr, valueStr));
                node.value = value;
            } else {
                addStep(QStringLiteral("Key exists → no insert (duplicate)"));
            }
            return false; // not a new insertion
        }
        addStep(QStringLiteral("Traverse next in chain"));
    }

    addStep(QStringLiteral("Append new node to bucket %1").arg(index));
    chain.push_front(Node{key, value});
    ++numElements_;
    addStep(QStringLiteral("New size = %1, load factor = %2")
                .arg(numElements_)
                .arg(loadFactor(), 0, 'f', 2));
    return true;
}
```

---

## 🗃️ **PART 4: HASHMAP IMPLEMENTATION (Beginner-Friendly)**

### **What is a HashMap?**

A **HashMap** (also called Hash Table) is like a **smart filing cabinet**:

- **Traditional Array**: To find "John's phone", you'd search through all entries (slow!)
- **HashMap**: Converts "John" → number → goes directly to that drawer (fast!)

**Real-world analogy**: Like a library where books are organized by a code (hash), so you can find any book instantly!

### **How HashMap Works: 3 Simple Steps**

```
1. HASH: Convert key → number
   "apple" → hash function → 12345

2. MODULO: Get bucket index
   12345 % 8 buckets = 1 (go to bucket 1)

3. STORE: Put key-value in that bucket
   Bucket 1: [("apple", "red")]
```

---

## 🔍 **DETAILED HASHMAP CODE EXPLANATION**

### **Class Structure (`hashmap.h`)**

```cpp
class HashMap {
    // PUBLIC: What users can do
    - insert(key, value)    // Add new entry
    - put(key, value)       // Add or update
    - get(key)              // Find value
    - erase(key)            // Delete entry
    - contains(key)         // Check if exists
    
    // PRIVATE: Internal workings
    - buckets_              // Array of linked lists
    - numElements_          // How many items stored
    - maxLoadFactor_        // When to resize (0.75 = 75% full)
};
```

### **Key Data Structures**

#### **1. Buckets Array**
```cpp
std::vector<std::forward_list<Node>> buckets_;
```

**Explanation**:
- `vector` = Array that can grow
- `forward_list` = Linked list (for collision handling)
- `Node` = Stores one key-value pair

**Visual**:
```
Buckets:  [0]  [1]  [2]  [3]  [4]  [5]  [6]  [7]
           │    │    │    │    │    │    │    │
           ▼    ▼    ▼    ▼    ▼    ▼    ▼    ▼
          empty apple banana empty empty empty empty
                  │
                  ▼
                 red
```

#### **2. Node Structure**
```cpp
struct Node {
    QVariant key;    // Can be string, int, double, etc.
    QVariant value;  // Can be any type
};
```

**Why QVariant?** - Allows storing different data types (string, int, etc.) in one structure.

---

### **Core Functions Explained**

#### **1. Hash Function (`indexFor`)**

```cpp
int HashMap::indexFor(const QVariant &key, int bucketCount) const {
    // Step 1: Convert key to hash number
    size_t hashValue = std::hash<std::string>{}(key.toString());
    
    // Step 2: Get bucket index (0 to bucketCount-1)
    return hashValue % bucketCount;
}
```

**Example**:
```
Key: "apple"
Hash: 123456789
Buckets: 8
Index: 123456789 % 8 = 5

Result: Store "apple" in bucket 5
```

**Why Modulo?** - Ensures index is always between 0 and (bucketCount - 1)

#### **2. Insert Operation (`insert` / `put`)**

```cpp
bool HashMap::insert(const QVariant &key, const QVariant &value) {
    // Step 1: Check if we need to resize (rehash)
    maybeGrow();
    
    // Step 2: Find the bucket
    int index = indexFor(key, bucketCount());
    
    // Step 3: Check if key already exists in that bucket
    // Step 4: If not, add new node to the chain
    return emplaceOrAssign(key, value, false);
}
```

**Step-by-Step Example**:
```
Insert("apple", "red"):

1. Hash "apple" → index = 5
2. Go to bucket 5
3. Check chain: empty? → Yes
4. Add node: ("apple", "red")
5. Done!
```

**Collision Handling** (when two keys go to same bucket):
```
Insert("banana", "yellow"):
1. Hash "banana" → index = 5 (same as apple!)
2. Go to bucket 5
3. Check chain: ("apple", "red") exists
4. Add to chain: ("apple", "red") → ("banana", "yellow")
5. Now bucket 5 has a chain of 2 items
```

#### **3. Search Operation (`get`)**

```cpp
std::optional<QVariant> HashMap::get(const QVariant &key) {
    // Step 1: Calculate bucket index
    int index = indexFor(key, bucketCount());
    
    // Step 2: Search through the chain in that bucket
    for (const auto &node : buckets_[index]) {
        if (node.key == key) {
            return node.value;  // Found!
        }
    }
    return std::nullopt;  // Not found
}
```

**Example**:
```
Get("apple"):

1. Hash "apple" → index = 5
2. Go to bucket 5
3. Check first node: key = "apple"? → Yes!
4. Return value: "red"
```

#### **4. Delete Operation (`erase`)**

```cpp
bool HashMap::erase(const QVariant &key) {
    int index = indexFor(key, bucketCount());
    
    // Traverse chain and remove matching node
    auto &chain = buckets_[index];
    // ... find and remove node from linked list
}
```

#### **5. Rehashing (`rehash`)**

**Why Rehash?** - When too many items in buckets, chains get long → slow!

```cpp
void HashMap::rehash(int newBucketCount) {
    // Step 1: Create new, larger bucket array
    std::vector<std::forward_list<Node>> newBuckets(newBucketCount);
    
    // Step 2: Move all existing items to new buckets
    for (each old bucket) {
        for (each node in bucket) {
            int newIndex = indexFor(node.key, newBucketCount);
            newBuckets[newIndex].push_front(node);
        }
    }
    
    // Step 3: Replace old buckets with new ones
    buckets_.swap(newBuckets);
}
```

**Example**:
```
Before: 8 buckets, 6 items (load factor = 0.75)
After:  16 buckets, 6 items (load factor = 0.375)

Why? More buckets = shorter chains = faster!
```

#### **6. Load Factor & Auto-Resize (`maybeGrow`)**

```cpp
void HashMap::maybeGrow() {
    float currentLoad = (numElements_ + 1) / bucketCount();
    
    if (currentLoad > maxLoadFactor_) {  // Usually 0.75 (75%)
        rehash(bucketCount() * 2);  // Double the buckets
    }
}
```

**Load Factor Formula**:
```
Load Factor = Number of Items / Number of Buckets

Example:
- 6 items, 8 buckets → 6/8 = 0.75 (75% full)
- If adding 1 more → 7/8 = 0.875 (87.5%) → TOO HIGH!
- Solution: Rehash to 16 buckets → 7/16 = 0.4375 (43.75%) ✓
```

---

## 🎨 **VISUALIZATION LAYER (`hashmapvisualization.h/cpp`)**

### **Purpose**
Takes the HashMap class and makes it **visual and interactive**.

### **Key Components**

1. **UI Elements**:
   - Input fields (key, value)
   - Buttons (Insert, Search, Delete, Clear)
   - Visualization area (draws buckets)

2. **Visualization**:
   - Draws each bucket as a rectangle
   - Shows key-value pairs inside buckets
   - Highlights buckets during operations
   - Shows load factor warnings

3. **Step Trace**:
   - Records every operation step
   - Shows in right panel for learning

### **How It Connects**

```
User clicks "Insert" button
    ↓
HashMapVisualization::onInsertClicked()
    ↓
hashMap->put(key, value)  // Calls HashMap class
    ↓
HashMap does the work, records steps
    ↓
updateVisualization()  // Redraws buckets
    ↓
User sees visual update!
```

---

## 📊 **COMPLETE EXAMPLE: Inserting "apple" → "red"**

### **Step-by-Step Flow**

```
1. USER ACTION:
   User types "apple" in key field, "red" in value field
   Clicks "Insert" button

2. UI LAYER (HashMapVisualization):
   onInsertClicked() called
   Gets text from input fields
   Converts to QVariant

3. HASHMAP LAYER:
   put("apple", "red") called
   
   a) maybeGrow() checks load factor
   b) indexFor("apple", 8) calculates:
      - Hash("apple") = 123456789
      - 123456789 % 8 = 5
      - Returns index = 5
   
   c) emplaceOrAssign():
      - Goes to buckets_[5]
      - Checks chain: empty
      - Adds node: ("apple", "red")
      - Increments numElements_
      - Records steps in stepHistory_

4. VISUALIZATION UPDATE:
   updateVisualization() called
   drawBuckets() redraws all buckets
   Bucket 5 now shows "apple→red"
   showStats() updates load factor display

5. USER SEES:
   - Bucket 5 highlighted
   - "apple→red" appears in bucket
   - Load factor updated
   - Steps shown in right panel
```

---

## 🎯 **KEY CONCEPTS SUMMARY**

### **1. Hashing**
- Converts key → number → bucket index
- Should distribute evenly (avoid clustering)

### **2. Collision Handling**
- When two keys hash to same bucket
- Solution: Linked list (chain) in each bucket

### **3. Load Factor**
- Ratio: items / buckets
- High load factor = long chains = slow
- Solution: Rehash (double buckets) when > 0.75

### **4. Time Complexity**
- **Best Case**: O(1) - Direct access, no collisions
- **Average Case**: O(1) - With good hash function
- **Worst Case**: O(n) - All items in one bucket (rare!)

---

## 💡 **LEARNING TIPS**

1. **Start Simple**: Understand hash function first
2. **Visualize**: Draw buckets on paper when learning
3. **Trace Code**: Follow one insert operation line by line
4. **Experiment**: Try different keys, see where they go
5. **Watch Load Factor**: See when rehashing happens

---

## 🔗 **RELATIONSHIP BETWEEN CLASSES**

```
main.cpp
  └─> Creates QStackedWidget
      └─> HomePage
          └─> MenuPage
              └─> TheoryPage
                  └─> HashMapVisualization
                      ├─> Uses HashMap class (hashmap.h/cpp)
                      ├─> Uses StyleManager (for UI styling)
                      └─> Uses WidgetManager (for safe deletion)
```

**Data Flow**:
```
User Input → HashMapVisualization → HashMap → stepHistory_ → Visualization Update
```

---

This is a well-structured project! The separation between:
- **Data Structure Logic** (HashMap class)
- **Visualization** (HashMapVisualization class)
- **UI Navigation** (main.cpp)

Makes it easy to understand and maintain! 🎉




