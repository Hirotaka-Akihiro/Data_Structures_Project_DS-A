#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

template <typename T>
class Node {
public:
    T data;
    int weight;
    int vehicles;
    Node* next;
    Node(T value, int weight = 0, int vehicles = 0) : data(value), weight(weight), vehicles(vehicles), next(nullptr) {}
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

    void printList() const {
        Node<T>* current = head;
        while (current) {
            if (current->next != nullptr)
                cout << "(" << current->data  << ", "<< current->weight << "), ";
            else
                cout << "(" << current->data << ", "<< current->weight << ")";
            current = current->next;
        }
        cout << endl;
    }

    bool contains(const T& value) const {
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
    string id;

    LinkedList<string> neighbors;

    GraphNode(const string& id) : id(id) {}

    void addNeighbor(const string& neighborId, int weight) {
        neighbors.enqueue(neighborId, weight);
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
            return;
        }
        GraphNode* newNode = new GraphNode(id);
        vertices.enqueue(newNode);
    }

    void addEdge(const string& from, const string& to, int weight) {
        GraphNode* fromNode = findNode(from);
        GraphNode* toNode = findNode(to);

        if (!fromNode || !toNode) {
            cout << "Error! Either of the nodes is missing.\n";
            return;
        }

        if (!fromNode->neighbors.contains(to)) {
            fromNode->addNeighbor(to, weight);
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
            cout << "File doesn't exist.\n ";
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
