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

    void printList() const {
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

    bool contains(const string& value) const {
        Node<T>* current = head;
        while (current) {
            if (current->data.destination == value) {
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

class Edge {
public:
    string destination;
    int weight;
    int vehicles;

    Edge(const string& destination, int weight, int vehicles = 0)
        : destination(destination), weight(weight), vehicles(vehicles) {}
};

class GraphNode {
public:
    string id;
    bool blocked;
    LinkedList<Edge> neighbors;

    GraphNode(const string& id) : id(id), blocked(false) {}

    void addNeighbor(const string& neighborId, int weight, int vehicles = 0) {
        Edge edge(neighborId, weight, vehicles);
        neighbors.enqueue(edge);
    }
};

class Graph {
public:
    LinkedList<GraphNode*> vertices;

    GraphNode* findNode(const string& id) {
        Node<GraphNode*>* current = vertices.head;
        while (current) {
            if (current->data->id == id) {
                return current->data;
            }
            current = current->next;
        }
        return nullptr;
    }

    ~Graph() {
        Node<GraphNode*>* current = vertices.head;
        while (current) {
            delete current->data;
            current = current->next;
        }
    }

    void addNode(const string& id) {
        if (findNode(id)) {
            return;  // Node already exists
        }
        GraphNode* newNode = new GraphNode(id);
        vertices.enqueue(newNode);
    }

    void addEdge(const string& from, const string& to, int weight, int vehicles = 0) {
        GraphNode* fromNode = findNode(from);
        GraphNode* toNode = findNode(to);

        if (!fromNode || !toNode) {
            cout << "Either one of the nodes is missing!\n";
            return;
        }

        if (!fromNode->neighbors.contains(to)) {
            fromNode->addNeighbor(to, weight, vehicles);
        }
    }

    void printGraph() const {
        Node<GraphNode*>* current = vertices.head;
        while (current) {
            cout << current->data->id << " -> ";
            current->data->neighbors.printList();
            current = current->next;
        }
    }

    void load(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Unable to open file " << filename << endl;
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

    graph.load("road_network.csv");

    cout << "Graph Adjacency List:" << endl;
    graph.printGraph();

    return 0;
}
