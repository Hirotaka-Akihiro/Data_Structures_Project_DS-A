#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

template <typename T>
class Node {
public:
    T data;
    Node* next;

    Node(T value) : data(value), next(nullptr) {}
};

template <typename T>
class LinkedList {

public:
    Node<T>* head;
    Node<T>* tail;
    int size;
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}
    void printList() {
        Node<T>* current = head;
        while (current) {
            cout << "(" << current->data.destination << ", "
                 << current->data.weight << ", "
                 << current->data.vehicles << ")";
            if (current->next) cout << " -> ";
            current = current->next;
        }
        cout << endl;
    }
    void push(T value) {
        Node<T>* NN = new Node<T>(value);
        if (!head) {
            head = tail = NN;
        } else {
            NN->next = head;
            head = NN;
        }
        size++;
    }
    T* get(string& value) {
        Node<T>* current = head;
        while (current) {
            if (current->data.destination == value) {
                return &current->data;
            }
            current = current->next;
        }
        return nullptr;
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

    void enqueue(T value) {
        Node<T>* NN = new Node<T>(value);
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

    bool isEmpty() {
        return head == nullptr;
    }
    bool contains(string& value) {
        Node<T>* current = head;
        while (current) {
            if (current->data.destination == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

};
template <typename T>
class HashTableNode {
public:
    string key;
    T data;
    bool occupied;
    HashTableNode(string key = "") : key(key), data(T(key)), occupied(false) {}
};

const int size = 26;
template <typename T>
class HashTable {
public:
    HashTableNode<T> arr[size];

    HashTable() {
        for (int i = 0; i < size; ++i) {
            arr[i] = HashTableNode<T>();
        }
    }

    int hash(string key) {
        return (key[0] - 'A') % size;
    }

    void insert(string key, T val) {
        int h = hash(key);
        for (int i = 0; i < size; ++i) {
            if (!arr[h].occupied) {
                arr[h].key = key;
                arr[h].data = val;
                arr[h].occupied = true;
                return;
            }
            h = (h + 1) % size;
        }
    }

    T* search(string key) {
        int h = hash(key);
        for (int i = 0; i < size; ++i) {
            if (arr[h].occupied && arr[h].key == key) {
                return &arr[h].data;
            }
            h = (h + 1) % size;
        }
        return nullptr;
    }

    bool contains(string key) {
        return search(key) != nullptr;
    }

    void printList() {
        for (int i = 0; i < size; ++i) {
            if (arr[i].occupied) {
                cout << "(" << arr[i].data.destination << ", "
                     << arr[i].data.weight << ", "
                     << arr[i].data.vehicles << ")";
                if (i != size-1)
                    cout << " -> ";
            }
        }
    }
};

class Edge {
public:
    string destination;
    int weight;
    int vehicles;
    bool blocked;
    Edge(const string& destination = "", int weight = 0, int vehicles = 0)
        : destination(destination), weight(weight), vehicles(vehicles), blocked(false) {}

    void block() { blocked = true; }
    void unblock() { blocked = false; }
};

class GraphNode {
public:
    string id;
    LinkedList<Edge> neighbors;

    GraphNode(string id) : id(id) {}

    void addNeighbor(string& neighborId, int weight, int vehicles = 0) {
        if (!neighbors.contains(neighborId)) {
            neighbors.enqueue(Edge(neighborId, weight, vehicles));
        }
    }

    Edge* getEdge(string& neighborId) {
        return neighbors.get(neighborId);
    }
};

class Graph {
public:
    HashTable<GraphNode> vertices;

    // Find a node by id (
    GraphNode* findNode(string& id) {
        GraphNode* node = vertices.search(id);
        return node;
    }

    // Add a node to the graph
    void addNode(string& id) {
        if (findNode(id)) {
            return;  // Node already exists
        }
        GraphNode newNode(id);  // Create a new GraphNode
        vertices.insert(id, newNode);  // Insert the GraphNode object into the HashTable
    }

    // Get the edge between two nodes
    Edge* getEdge(string& from, string& to) {
        GraphNode* fromNode = findNode(from);
        if (!fromNode) {
            cout << "Invalid nodes.\n";
            return nullptr;
        }
        return fromNode->getEdge(to);
    }

    // Block an edge between two nodes
    void blockEdge(string from, string to) {
        GraphNode* fromNode = findNode(from);
        if (!fromNode) {
            cout << "Node '" << from << "' doesn't exist.\n";
            return;
        }
        Edge* edge = fromNode->getEdge(to);
        if (edge) {
            edge->block();
            cout << "Road blocked from " << from << " to " << to << endl;
        } else {
            cout << "Road doesn't exist.\n";
        }
    }


    // Add an edge between two nodes
    void addEdge(string& from, string& to, int weight, int vehicles = 0) {
        GraphNode* fromNode = findNode(from);
        GraphNode* toNode = findNode(to);

        if (!fromNode || !toNode) {
            cout << "Either one of the nodes is missing!\n";
            return;
        }

        // Add edge between fromNode and toNode
        if (!fromNode->neighbors.contains(to)) {
            fromNode->addNeighbor(to, weight, vehicles);
        }
    }

    // Print the entire graph
    void printGraph() {
        for (int i = 0; i < size; ++i) {
            if (vertices.arr[i].occupied) {
                cout << vertices.arr[i].data.id << " -> ";
                vertices.arr[i].data.neighbors.printList();
            }
        }
    }

    // Show blocked roads
    void showBlocked() {
        cout << "------ Blocked Roads ------" << endl;
        for (int i = 0; i < size; ++i) {
            if (vertices.arr[i].occupied) {
                GraphNode& node = vertices.arr[i].data;
                Node<Edge>* current = node.neighbors.head;
                while (current) {
                    if (current->data.blocked) {
                        cout << node.id << " to " << current->data.destination << " is blocked.\n";
                    }
                    current = current->next;
                }
            }
        }
    }

    // Load blocked roads from a file
    void loadBlocked(string filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "File doesn't exist.\n";
            return;
        }
        string line;
        getline(file, line);

        while (getline(file, line)) {
            stringstream ss(line);
            string from, to, status;
            if (getline(ss, from, ',') && getline(ss, to, ',') && getline(ss, status, ',')) {
                if (status == "Blocked") {
                    blockEdge(from, to);
                }
            }
        }
        file.close();
    }
    // Read road network inputs from csv
    void loadNetwork(string filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "File doesn't exist.\n";
            return;
        }

        string line;
        getline(file, line);

        while (getline(file, line)) {
            stringstream ss(line);
            string from, to, weightStr;
            int weight;
            if (getline(ss, from, ',') && getline(ss, to, ',') && getline(ss, weightStr, ',')) {
                weight = stoi(weightStr);
                addNode(from);
                addNode(to);
                addEdge(from, to, weight);
            }
        }
        file.close();
    }
};


int main() {
    Graph graph;

    graph.loadNetwork("road_network.csv");
    graph.loadBlocked("road_closures.csv");

    cout << "Graph Adjacency List:" << endl;
    graph.printGraph();
    graph.showBlocked();
    graph.blockEdge("Y", "Z");
    graph.showBlocked();
    return 0;
}
