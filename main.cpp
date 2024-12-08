#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <type_traits>
using namespace std;

const int size = 26; // Size of the hash table.

template <typename T>
class Node {
public:
    T data;
    Node* next;

    Node(T value = T()) : data(value), next(nullptr) {}
};

template <typename T>
class HashTableNode {
public:
    string key;
    T data;
    bool occupied;
    HashTableNode(string key = "") : key(key), data(T()), occupied(false) {}
};

template <typename T>
class MinHeapNode {
public:
    T id;
    int priority;

    MinHeapNode(T id = T(), int priority = INT_MAX)
        : id(id), priority(priority) {}

    bool operator<(MinHeapNode a) {
        return priority < a.priority;
    }

    bool operator>(MinHeapNode a) {
        return priority > a.priority;
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

class Vehicles {
public:
    string id;
    string start;
    string end;
    Vehicles(string id = "", string start = "", string end = "") : id(id), start(start), end(end) {}
    operator string() {
        if (id.empty())
            return "";
        return string(1, id[id.size() - 1]);  // Return the last character of `id` as a string
    }
};

template <typename T>
class LinkedList {

public:
    Node<T>* head;
    Node<T>* tail;
    int size;

    LinkedList() : head(nullptr), tail(nullptr), size(0) {}

    // Returns a true copy of the linked list.
    LinkedList<T> copyLinkedList(LinkedList<T>& original) {
        LinkedList<T> copy;
        Node<T>* current = original.head;
        while (current) {
            copy.enqueue(current->data);
            current = current->next;
        }
        return copy;
    }

    // Displays all neighbors of the graph.
    void printList() {
        Node<T>* current = head;
        while (current) {
            cout << "(" << current->data.destination << ", "
                 << current->data.weight  << ")";
            if (current->next) cout << " -> ";
            current = current->next;
        }
        cout << endl;
    }

    // Generic get function for heap operations
    T* getGeneric(string key) {
        Node<T>* current = head;
        while (current) {
            if (current->data.id == key) {
                return &current->data;
            }
            current = current->next;
        }
        return nullptr;
    }

    // Push function for linked list to serve as a stack.
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

    // Meant for returning a pointer to an Edge object if the destination i.e 'from' is present.
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

    // Pop function for linked list to serve as a stack.
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

    // Enqueue function for linked list to serve as a queue.
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

    // Dequeue function for linked list to serve as a queue.
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

    // Checks if linked list is empty.
    bool isEmpty() {
        return head == nullptr;
    }

    // Displays all elements of the linked list.
    void display() {
        Node<T>* current = head;
        while (current) {
            if (current->next)
                cout << current->data << " -> ";
            else
                cout << current->data;
            current = current->next;
        }
    }

    // Reverses the linked list.
    void reverse() {
        Node<T>* prev = nullptr;
        Node<T>* current = head;
        Node<T>* next = nullptr;

        while (current != nullptr) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }

        head = prev;
    }

    // Checks if an Edge's destination i.e 'from' is present.
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

    // Checks if linked list contains a string.
    bool containsString(string value) {
        Node<T>* current = head;
        while (current) {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }
};

template <typename T>
class HashTable {
public:
    HashTableNode<T> arr[size];

    HashTable() {
        for (int i = 0; i < size; ++i) {
            arr[i] = HashTableNode<T>();
        }
    }
    // Hashes the string key into an integer index.
    int hash(string key) {
        return (key[0] - 'A' + size) % size;
    }
    // Subscript operator overloading.
    T& operator[](const string& key) {
        int h = hash(key);
        for (int i = 0; i < size; ++i) {
            if (arr[h].occupied && arr[h].key == key) {
                return arr[h].data;  // Return a reference to the data
            }
            h = (h + 1) % size;
        }
        // If key is not found, insert it with a default value.
        insert(key, T());
        return arr[hash(key)].data;
    }

    // Insert a key-value pair into the hash table.
    void insert(string key, T val) {
        int h = hash(key);
        for (int i = 0; i < size; ++i) {
            if (arr[h].occupied && arr[h].key == key) {
                arr[h].data = val; // Update the value if key exists
                return;
            }
            if (!arr[h].occupied) {
                arr[h].key = key;
                arr[h].data = val;
                arr[h].occupied = true;
                return;
            }
            h = (h + 1) % size;
        }
    }

    // Returns a reference to the object.
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

    // Checks if it contains a key.
    bool contains(string key) {
        return search(key) != nullptr;
    }

    // Prints the list.
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

template <typename T>
class MinHeap {
public:
    LinkedList<MinHeapNode<T>> heap;  // Underlying structure for the heap
    HashTable<Node<MinHeapNode<T>>> hashMap;  // HashMap to store objects of MinHeapNode

    // Inserts a new node into the heap
    void insert(T id, int priority) {
        Node<MinHeapNode<T>>* existingNode = hashMap.search(id);
        if (existingNode) {
            if (existingNode->data.priority > priority) {
                existingNode->data.priority = priority;  // Update priority if it's better
            }
            return;
        }

        MinHeapNode<T> newNode(id, priority);
        heap.enqueue(newNode);
        hashMap.insert(id, *heap.tail);  // Store the object in the HashMap
    }

    // Helper function to swap data between two nodes
    void swap(Node<MinHeapNode<T>>* a, Node<MinHeapNode<T>>* b) {
        MinHeapNode<T> temp = a->data;
        a->data = b->data;
        b->data = temp;

        hashMap.insert(a->data.id, *a);
        hashMap.insert(b->data.id, *b);
    }

    // Finds the node with the minimum priority
    Node<MinHeapNode<T>>* findMinNode() {
        Node<MinHeapNode<T>>* minNode = heap.head;
        Node<MinHeapNode<T>>* current = heap.head;

        while (current) {
            if (current->data.priority < minNode->data.priority) {
                minNode = current;
            }
            current = current->next;
        }
        return minNode;
    }

    // Extracts the node with the minimum priority
    MinHeapNode<T> getMin() {
        if (heap.isEmpty()) {
            return MinHeapNode<T>();
        }

        Node<MinHeapNode<T>>* minNode = findMinNode();
        MinHeapNode<T> minValue = minNode->data;

        // Remove from the hashMap
        hashMap.insert(minNode->data.id, Node<MinHeapNode<T>>());  // Replace with an empty node

        // Remove from the list
        if (minNode == heap.head) {
            heap.dequeue();
        } else {
            Node<MinHeapNode<T>>* current = heap.head;
            while (current->next != minNode) {
                current = current->next;
            }
            current->next = minNode->next;
            if (minNode == heap.tail) {
                heap.tail = current;
            }
            delete minNode;
            heap.size--;
        }

        return minValue;
    }

    // Checks if the heap is empty
    bool isEmpty() {
        return heap.isEmpty();
    }

    // Prints the heap (for debugging)
    void printHeap() {
        Node<MinHeapNode<T>>* current = heap.head;
        while (current) {
            cout << "(" << current->data.id << ", " << current->data.priority << ")";
            if (current->next) {
                cout << " -> ";
            }
            current = current->next;
        }
        cout << endl;
    }
};

class GraphNode {
public:
    string id;
    int greenTime;
    LinkedList<Edge> neighbors;

    GraphNode(string id = "", int greenTime = 0) : id(id), greenTime(greenTime) {}
    // Appends a neighbor to the intersection.
    void addNeighbor(string& neighborId, int weight, int vehicles = 0) {
        if (!neighbors.contains(neighborId)) {
            neighbors.enqueue(Edge(neighborId, weight, vehicles));
        }
    }
    // Returns the edge that points to a neighbor
    Edge* getEdge(string& neighborId) {
        return neighbors.get(neighborId);
    }
};

class Graph {
public:
    HashTable<GraphNode> vertices;
    LinkedList<Vehicles> vehicles;
    MinHeap<Vehicles> emergencyVehicles;

    // Find a node by id (
    GraphNode* findNode(string& id) {
        GraphNode *node = vertices.search(id);
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

    // Function to find and print all possible routes from start node to end node
    void findAllPaths(string from, string to) {
        GraphNode* start = findNode(from);
        GraphNode* end = findNode(to);
        if (!start || !end) {
            cout << "Start or end node not found!" << endl;
            return;
        }

        HashTable<bool> visited;
        findAllPathsHelper(from, to, "", 0, visited);
    }

    // Helper function for DFS to find and print all paths
    void findAllPathsHelper(string from, string to, string path, int weight, HashTable<bool>& visited) {
        visited.insert(from, true);
        path += from + " ";

        if (from == to) {
            cout << "Path: " << path << " | Total Weight: " << weight << endl;
        } else {
            GraphNode* currentNode = findNode(from);
            if (currentNode) {
                Node<Edge>* neighbor = currentNode->neighbors.head;
                while (neighbor) {
                    if (!visited[neighbor->data.destination]) {
                        int edgeWeight = neighbor->data.weight;
                        findAllPathsHelper(neighbor->data.destination, to, path, weight + edgeWeight, visited);
                    }
                    neighbor = neighbor->next;
                }
            }
        }

        visited.insert(from, false);
    }

    // Print the entire graph
    void printGraph() {
        cout << "------ City Traffic Network ------" << endl;
        for (int i = 0; i < size; ++i) {
            if (vertices.arr[i].occupied) {
                cout << vertices.arr[i].data.id << " -> ";
                vertices.arr[i].data.neighbors.printList();
            }
        }
    }

    // Display all the vehicles and their destinations.
    void showVehicles() {
        Node<Vehicles>* head = vehicles.head;
        while (head) {
            cout << head->data.id << " moving from " << head->data.start << " to " << head->data.end << endl;
            head = head->next;
        }
    }

    // Display all the emergency vehicles and their destinations.
    void showEmergencyVehicles() {
        Node<MinHeapNode<Vehicles>> *head = emergencyVehicles.heap.head;
        while (head) {
            cout << head->data.id.id << " moving from " << head->data.id.start << " to " << head->data.id.end << " with priority " << head->data.priority << endl;
            head = head->next;
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

    // Show traffic signals.
    void showTraffic() {
        cout << "------ Traffic Signal Status ------" << endl;
        for (int i = 0; i < size; ++i) {
            if (vertices.arr[i].occupied) {
                GraphNode& node = vertices.arr[i].data;
                cout << "Intersection " << node.id << " Green Time: " << node.greenTime << "s" << endl;
            }
        }
    }
    // Breath first search
    void bfs(string startId) {
        GraphNode* start = findNode(startId);
        if (!start) {
            cout << "Start node not found!" << endl;
            return;
        }

        LinkedList<string> queue;
        LinkedList<string> visited;

        queue.enqueue(startId);

        while (!queue.isEmpty()) {
            string from = queue.dequeue();

            if (!visited.containsString(from)) {
                cout << from << " ";
                visited.enqueue(from);

                GraphNode* currentNode = findNode(from);
                if (currentNode) {
                    Node<Edge>* neighbor = currentNode->neighbors.head;
                    while (neighbor) {
                        if (!visited.containsString(neighbor->data.destination)) {
                            queue.enqueue(neighbor->data.destination);
                        }
                        neighbor = neighbor->next;
                    }
                }
            }
        }
        cout << endl;
    }

    // Helper function for depth first searches
    void dfsHelper(string nodeId, LinkedList<string>& visited) {
        if (visited.containsString(nodeId)) {
            return;
        }

        cout << nodeId << " ";
        visited.enqueue(nodeId);

        GraphNode* node = findNode(nodeId);
        if (node) {
            Node<Edge>* neighbor = node->neighbors.head;
            while (neighbor) {
                if (!visited.containsString(neighbor->data.destination)) {
                    dfsHelper(neighbor->data.destination, visited);
                }
                neighbor = neighbor->next;
            }
        }
    }

    // Depth first search function
    void dfs(string startId) {
        LinkedList<string> visited;
        dfsHelper(startId, visited);
        cout << endl;
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

    // Read vehicles data from csv.
    void loadVehicles(string filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "File doesn't exist.\n";
            return;
        }

        string line;
        getline(file, line);

        while (getline(file, line)) {
            stringstream ss(line);
            string id, from, to;
            if (getline(ss, id, ',') && getline(ss, from, ',') && getline(ss, to, ',')) {
                addVehicle(id, from, to);
            }
        }
        file.close();
    }

    // Read emergency vehicles data from csv.
    void loadEmergencyVehicles(string filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "File doesn't exist.\n";
            return;
        }

        string line;
        getline(file, line);

        while (getline(file, line)) {
            stringstream ss(line);
            string id, from, to, priority;
            if (getline(ss, id, ',') && getline(ss, from, ',') && getline(ss, to, ',') && getline(ss,  priority, ',')) {
                int priorityInt = (priority == "High")? 0 : (priority == "Medium")? 1 : (priority == "Low")? 2 : -1;
                cout << "Inserting Emergency Vehicle: "
     << id << " with priority " << priorityInt << endl;
                emergencyVehicles.insert({id, from, to}, priorityInt);
            }
        }
        file.close();
    }

    // Read signals data from csv.
    void loadSignals(string filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "File doesn't exist.\n";
            return;
        }

        string line;
        getline(file, line);

        while (getline(file, line)) {
            stringstream ss(line);
            string intersection, greenTime;
            if (getline(ss, intersection, ',') && getline(ss, greenTime, ',')) {
                GraphNode* node = findNode(intersection);
                if (node) {
                    node->greenTime = stoi(greenTime);
                }
            }
        }
        file.close();
    }

    void load() {
        loadNetwork("road_network.csv");
        loadBlocked("road_closures.csv");
        loadVehicles("vehicles.csv");
        loadEmergencyVehicles("emergency_vehicles.csv");
        loadSignals("traffic_signals.csv");
    }
    // Dijkstras algorithm for finding the shortest path.
    void dijkstra(string startId, string targetId) {
        if (!findNode(startId) || !findNode(targetId)) {
            cout << "One or both nodes do not exist!" << endl;
            return;
        }

        MinHeap<string> pq;
        HashTable<int> distances;
        HashTable<string> predecessors;

        for (int i = 0; i < size; ++i) {
            if (vertices.arr[i].occupied) {
                distances[vertices.arr[i].data.id] = INT_MAX;
            }
        }

        distances[startId] = 0;
        pq.insert(startId, 0);

        while (!pq.isEmpty()) {
            MinHeapNode<string> current = pq.getMin();  // Get the MinHeapNode directly

            if (current.id == targetId) break;

            GraphNode* node = findNode(current.id);
            if (!node) continue;

            Node<Edge>* neighbor = node->neighbors.head;
            while (neighbor) {
                Edge& edge = neighbor->data;
                if (!edge.blocked) {
                    int newDist = distances[current.id] + edge.weight;
                    if (newDist < distances[edge.destination]) {
                        distances[edge.destination] = newDist;
                        predecessors.insert(edge.destination, current.id);
                        pq.insert(edge.destination, newDist);
                    }
                }
                neighbor = neighbor->next;
            }
        }

        if (distances[targetId] == INT_MAX) {
            cout << "No path to " << targetId << endl;
        } else {
            LinkedList<string> path;
            string current = targetId;
            while (current != startId) {
                path.enqueue(current);
                current = *predecessors.search(current);  // Use the updated search method
            }
            path.enqueue(startId);
            path.reverse();

            cout << "Shortest path (Dijkstra): ";
            path.display();
            cout << "\nTotal weight: " << distances[targetId] << endl;
        }
    }

    // Displays vehicle counts.
    void showCongestion() {
        cout << "------ Congestion Status ------" << endl;

        for (int i = 0; i < size; ++i) {
            if (vertices.arr[i].occupied) {
                GraphNode& node = vertices.arr[i].data;
                Node<Edge>* current = node.neighbors.head;

                // Traverse all edges of the current vertex
                while (current) {
                    cout << node.id << " to " << current->data.destination << " -> Vehicles: " << current->data.vehicles << endl;
                    current = current->next;
                }
            }
        }
    }

    // Adds a new vehicle to the graph.
    void addVehicle(string id, string from, string to) {
        Edge* road = getEdge(from, to);
        if (road) {
            road->vehicles++;
            vehicles.enqueue({id, from, to});
            cout << "Added Vehicle: " << id << endl;
        }
    }
    void displayMenu() {
        bool quit = true;
        while (quit) {
            cout << "\n\n---- Simulation Dashboard -----\n";
            cout << "1. Display City Traffic Network\n";
            cout << "2. Display Traffic Signal Status\n";
            cout << "3. Display Congestion Status\n";
            cout << "4. Display Blocked Roads\n";
            cout << "5. Handle Emergency Vehicle Routing\n";
            cout << "6. Block Road due to Accident\n";
            cout << "7. Simulate Vehicle Routing\n";
            cout << "8. Add car to road.\n";
            cout << "9. Show all vehicles.\n";
            cout << "10. Show all emergency vehicles.\n";
            cout << "11. Add road between intersections.\n";
            cout << "80. Exit Simulation\n";
            cout << "Enter your choice: \n";
            int n;
            cin >> n;
            switch (n) {
                case 1: {
                    printGraph();
                    break;
                }
                case 2: {
                    showTraffic();
                    break;
                }
                case 3: {
                    showCongestion();
                    break;
                }
                case 4: {
                    showBlocked();
                    break;
                }
                case 5: {
                    cout << "Enter start and end intersections for emergency vehicle.\n";
                    string start, end;
                    cin >> start >> end;
                    dijkstra(start, end);
                    break;
                }
                case 6: {
                    cout << "Enter road to block (start, end): ";
                    string start, end;
                    cin >> start >> end;
                    blockEdge(start, end);
                    break;
                }
                case 7: {
                    cout << "Simulating vehicle routing...\n";
                    string start, end;
                    cout << "Enter starting intersection: ";
                    cin >> start;
                    cout << "Enter ending intersection: ";
                    cin >> end;
                    cout << "All possible paths from A to F are:\n";
                    findAllPaths(start, end);
                    break;
                }
                case 8: {
                    string start, end, name;
                    cout << "Enter car name:\n";
                    cin >> name;
                    cout << "Enter starting intersection: ";
                    cin >> start;
                    cout << "Enter ending intersection: ";
                    cin >> end;
                    Edge* road = getEdge(start, end);
                    if (road) {
                        addVehicle(name, start, end);
                    }
                    break;
                }
                case 9: {
                    showVehicles();
                    break;
                }
                case 10: {
                    showEmergencyVehicles();
                    break;
                }
                case 11: {
                    string start, end, weight;
                    cout << "Enter starting intersection: ";
                    cin >> start;
                    cout << "Enter ending intersection: ";
                    cin >> end;
                    cout << "Enter weight: ";
                    cin >> weight;
                    addEdge(start, end, stoi(weight));
                    break;
                }

                case 80: {
                    quit = false;
                    break;
                }
            }
        }
    }
};


int main() {
    Graph graph;
    graph.load();
    graph.displayMenu();
    return 0;
}
