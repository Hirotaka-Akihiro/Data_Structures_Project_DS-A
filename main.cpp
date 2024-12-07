#include <iostream>
using namespace std;

template <typename T>
class Node {
public:
    T data;
    int weight; // Weight associated with the node
    Node* next;

    Node(T value, int weight = 0) : data(value), weight(weight), next(nullptr) {}
};

template <typename T>
class LinkedList {
public:
    Node<T>* head;
    Node<T>* tail;
    int size;

    LinkedList() : head(nullptr), tail(nullptr), size(0) {}

    void push(T value, int weight = 0) {
        Node<T>* NN = new Node<T>(value, weight);
        if (!head) {
            head = tail = NN;
        } else {
            NN->next = head;
            head = NN;
        }
        size++;
    }

    T pop() {
        if (!head) {
            return T();
        }

        Node<T>* temp = head;
        T value = temp->data;
        head = head->next;

        if (!head) {
            tail = nullptr;
        }

        delete temp;
        size--;
        return value;
    }

    void enqueue(T value, int weight = 0) {
        Node<T>* NN = new Node<T>(value, weight);
        if (!tail) {
            head = tail = NN;
        } else {
            tail->next = NN;
            tail = NN;
        }
        size++;
    }

    T dequeue() {
        if (!head) {
            return T();
        }

        Node<T>* temp = head;
        T value = temp->data;
        head = head->next;

        if (!head) {
            tail = nullptr;
        }

        delete temp;
        size--;
        return value;
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    void printList() const {
        Node<T>* current = head;
        while (current) {
            cout << "(" << current->data << ", " << current->weight << ") ";
            current = current->next;
        }
        cout << endl;
    }

    bool contains(T value) const {
        Node<T>* current = head;
        while (current) {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    ~LinkedList() {
        while (head) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

class GraphNode {
public:
    int id;
    LinkedList<int> neighbors;

    GraphNode(int id = 0) : id(id) {}

    void addNeighbor(int neighborId, int weight) {
        neighbors.enqueue(neighborId, weight);
    }
};

class Graph {
private:
    LinkedList<GraphNode*> vertices;

    GraphNode* findNode(int id) {
        Node<GraphNode*>* current = vertices.head;
        while (current) {
            if (current->data->id == id) {
                return current->data;
            }
            current = current->next;
        }
        return nullptr;
    }

public:
    Graph() : vertices() {}

    ~Graph() {
        Node<GraphNode*>* current = vertices.head;
        while (current) {
            delete current->data;
            current = current->next;
        }
    }

    void addNode(int id) {
        if (findNode(id)) {
            return;
        }
        GraphNode* newNode = new GraphNode(id);
        vertices.enqueue(newNode);
    }

    void addEdge(int from, int to, int weight) {
        GraphNode* fromNode = findNode(from);
        GraphNode* toNode = findNode(to);
        if (!fromNode || !toNode) {
            cout << "One or both nodes not found. Cannot add edge." << endl;
            return;
        }
        if (fromNode && toNode) {
            fromNode->addNeighbor(to, weight);
        }
    }

    void printGraph() {
        Node<GraphNode*>* current = vertices.head;
        while (current) {
            cout << "Node " << current->data->id << ": ";
            current->data->neighbors.printList();
            current = current->next;
        }
    }

    void bfs(int startId) {
        GraphNode* start = findNode(startId);
        if (!start) {
            cout << "Start node not found!" << endl;
            return;
        }

        LinkedList<int> queue;
        LinkedList<int> visited;
        queue.enqueue(startId);

        while (!queue.isEmpty()) {
            int currentId = queue.dequeue();
            if (!visited.contains(currentId)) {
                cout << currentId << " ";
                visited.enqueue(currentId);

                GraphNode* currentNode = findNode(currentId);
                if (currentNode) {
                    Node<int>* neighbor = currentNode->neighbors.head;
                    while (neighbor) {
                        if (!visited.contains(neighbor->data)) {
                            queue.enqueue(neighbor->data);
                        }
                        neighbor = neighbor->next;
                    }
                }
            }
        }
        cout << endl;
    }

    void dfsHelper(int nodeId, LinkedList<int>& visited) {
        if (visited.contains(nodeId)) {
            return;
        }

        cout << nodeId << " ";
        visited.enqueue(nodeId);

        GraphNode* node = findNode(nodeId);
        if (node) {
            Node<int>* neighbor = node->neighbors.head;
            while (neighbor) {
                if (!visited.contains(neighbor->data)) {
                    dfsHelper(neighbor->data, visited);
                }
                neighbor = neighbor->next;
            }
        }
    }

    void dfs(int startId) {
        LinkedList<int> visited;
        dfsHelper(startId, visited);
        cout << endl;
    }
};

int main() {
    Graph graph;
    graph.addNode(1);
    graph.addNode(2);
    graph.addNode(3);
    graph.addNode(4);
    graph.addNode(5);

    graph.addEdge(1, 2, 4);
    graph.addEdge(4, 3, 3);
    graph.addEdge(2, 5, 2);
    graph.addEdge(1, 3, 1);
    graph.addEdge(3, 4, 5);
    graph.addEdge(3, 2, 6);
    graph.addEdge(4, 1, 7);
    graph.addEdge(4, 5, 8);
    graph.addEdge(5, 2, 9);

    cout << "Graph Adjacency List:" << endl;
    graph.printGraph();

    cout << "\nBFS Traversal:" << endl;
    graph.bfs(1);

    cout << "\nDFS Traversal:" << endl;
    graph.dfs(1);

    return 0;
}
