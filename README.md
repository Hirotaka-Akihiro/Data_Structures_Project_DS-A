<h1 style="text-align:center;">City Traffic Network Simulation</h1>

## Table of Contents
- [Overview](#overview)
- [Real-Life Use Cases](#real-life-use-cases)
- [Main Logic and Features](#main-logic-and-features)
- [How to Run](#how-to-run)
- [Assumptions](#assumptions)
- [Code Structure](#code-structure)
- [Conclusion](#conclusion)
## Overview 
<div style="background-color: #f2f2f2; padding: 10px; margin: 10px 0;">
  This program simulates a city's traffic network using a graph data structure. It allows users to manage and analyze traffic flow, handle emergency vehicle routing, block roads due to accidents, and display various traffic-related information. The simulation is useful for urban planning, traffic management, and route optimization in real-life scenarios.
</div>
<h2>Real-Life Use Cases</h2> 

<div style="background-color: #e0e0e0; padding: 10px; margin: 10px 0;">
  
  
  1. **Urban Planning**: Helps city planners design and optimize road networks, signal timings, and traffic flow.
  2. **Traffic Management Systems**: Real-time traffic updates, road closures, and emergency vehicle routing.
  3. **Emergency Services**: Efficient routing for ambulances, fire trucks, and police vehicles to minimize response times.
  4. **Congestion Analysis**: Identifying traffic bottlenecks and optimizing vehicle distribution across the network.
</div>
<h2>Main Logic and Features</h2>
<div style="background-color: #d0d0d0; padding: 10px; margin: 10px 0;">
  
  
  ### Data Structures
  
  - **Graph**: Represents the city's road network with intersections as nodes and roads as edges.
  - **GraphNode**: Represents an intersection with an ID and green time for traffic signals.
  - **Edge**: Represents a road between two intersections with weight (distance/time), vehicle count, and block status.
  - **LinkedList**: Used for implementing stacks, queues, and adjacency lists for graph nodes.
  - **HashTable**: Efficiently stores and retrieves graph nodes and their data.
  - **MinHeap**: Priority queue for handling emergency vehicles based on priority levels.
  
  ### Key Functionalities
  
  1. **Loading Data from CSV Files**:
     - **Road Network**: Reads from "road_network.csv" to build the graph.
     - **Blocked Roads**: Reads from "road_closures.csv" to block specific roads.
     - **Vehicles**: Reads from "vehicles.csv" to add regular vehicles to the network.
     - **Emergency Vehicles**: Reads from "emergency_vehicles.csv" to add emergency vehicles with priorities.
     - **Traffic Signals**: Reads from "traffic_signals.csv" to set green times for intersections.
  
  2. **Graph Operations**:
     - **Add Node/Edge**: Dynamically add new intersections and roads.
     - **Block Road**: Block a road due to an accident or closure.
     - **Find All Paths**: Find and display all possible routes between two intersections.
     - **Dijkstra's Algorithm**: Find the shortest path between two intersections, considering road weights and blocks.
  
  3. **Vehicle Management**:
     - **Add Vehicle**: Add a regular vehicle to the network and increment the vehicle count on the chosen road.
     - **Emergency Vehicle Routing**: Use a priority queue to handle emergency vehicles based on their priority (High, Medium, Low).
  
  4. **Display Functions**:
     - **City Traffic Network**: Display the entire graph with intersections and connected roads.
     - **Traffic Signal Status**: Show the green time for each intersection.
     - **Congestion Status**: Display the number of vehicles on each road.
     - **Blocked Roads**: List all currently blocked roads.
     - **Vehicles and Emergency Vehicles**: Show the list of all regular and emergency vehicles in the network.
  
  5. **Simulation Dashboard**:
     - A menu-driven interface allowing users to interact with the simulation, perform operations, and visualize the network's state.
</div>

<div style="background-color: #c0c0c0; padding: 10px; margin: 10px 0;">
  <h2>How to Run</h2> 
  
  1. **Prepare Input Files**:
     - Ensure that the CSV files ("road_network.csv", "road_closures.csv", "vehicles.csv", "emergency_vehicles.csv", "traffic_signals.csv") are present in the working directory.
     - Format the CSV files according to the expected structure.
  
  2. **Compile and Run**:
     - Compile the C++ code using a CMake environment.
     - Run the executable on the IDE of your choice. (Project was done on CLion).
  
  3. **Interact with the Menu**:
     - Use the provided menu options to load data, perform operations, and display information about the city's traffic network.
</div>

<div style="background-color: #b0b0b0; padding: 10px; margin: 10px 0;">
  <h2>Assumptions</h2> 
  
  - The program assumes that the input CSV files are correctly formatted and placed in the working directory.
  - Node IDs are unique strings, and road weights are non-negative integers.
  - Emergency vehicle priorities are categorized as "High", "Medium", or "Low".
</div>

<div style="background-color: #a0a0a0; padding: 10px; margin: 10px 0;">
  <h2>Code Structure</h2>
  
  - **Classes**:
    - `Edge`: Represents a road with destination, weight, vehicle count, and block status.
    - `Vehicles`: Represents a vehicle with an ID, start, and end intersections.
    - `GraphNode`: Represents an intersection with an ID, green time, and a list of neighboring roads.
    - `LinkedList<T>`: A generic linked list for various data storage needs.
    - `HashTable<T>`: A hash table for efficient data retrieval using string keys.
    - `MinHeap<T>`: A priority queue for handling emergency vehicles based on priority.
    - `Graph`: The main class that manages the city's traffic network, including nodes, edges, vehicles, and operations.
  
  - **Functions**:
    - **Graph Operations**: `addNode`, `addEdge`, `blockEdge`, `getEdge`, `findNode`.
    - **Path Finding**: `findAllPaths`, `dijkstra`.
    - **Display Functions**: `printGraph`, `showTraffic`, `showCongestion`, `showBlocked`, `showVehicles`, `showEmergencyVehicles`.
    - **Data Loading**: `loadNetwork`, `loadBlocked`, `loadVehicles`, `loadEmergencyVehicles`, `loadSignals`.
    - **Menu System**: `displayMenu` for user interaction.
</div>

<div style="background-color: #909090; padding: 10px; margin: 10px 0;">
  <h2>Conclusion</h2> 
  
  This simulation provides a comprehensive model for managing and analyzing a city's traffic network. It can be extended and customized for various urban planning and traffic management applications.
</div>
