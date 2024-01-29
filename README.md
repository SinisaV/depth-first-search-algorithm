# Depth-First Search Algorithm in C++

This C++ program implements the Depth-First Search (DFS) algorithm to explore and analyze graphs. It provides functionality to read a graph from a file, perform DFS from a specified node, display information about nodes, and find paths between nodes.

## Usage

1. **Graph Data File (`graf.txt`):** Create a text file named `graf.txt` containing graph data in the format: `node1 node2 weight`.

    Example:
    ```
    1 2 1
    1 8 1
    3 4 1
    3 7 1
    3 8 1
    4 5 1
    4 7 1
    5 6 1
    5 7 1
    6 7 1
    ```

2. **Run the Program:** Open and run the `main.cpp` file in your IDE.

3. **Menu Options:**
   - **1:** Load graph data from `graf.txt`.
   - **2:** Run DFS from a specified node.
   - **3:** Display information about nodes.
   - **4:** Find a path between specified nodes.
   - **5:** Exit the program.

## Example

Suppose `graf.txt` contains the following data:

```
1 2 1
1 8 1
3 4 1
3 7 1
3 8 1
4 5 1
4 7 1
5 6 1
5 7 1
6 7 1
```

1. Select option **1** to load graph data.
2. Select option **2** and enter the starting node to run DFS.
3. Select option **3** to display information about nodes.
4. Select option **4** and enter start node and end node to find a path.
