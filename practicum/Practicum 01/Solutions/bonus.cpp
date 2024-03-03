#include <iostream>
#include <cstring>


const int MAX_VERTEX_LABEL_LENGTH = 10;

struct Vertex {
    char label[MAX_VERTEX_LABEL_LENGTH + 1];
};

struct Edge {
    Vertex from;
    Vertex to;
};

struct Graph {
    Edge* edges = nullptr;
    int edgesCnt = 0;
    int verticesCnt = 0;
};

bool equal(const Vertex &lhs, const Vertex &rhs) {
    return strcmp(lhs.label, rhs.label) == 0;
}

bool equal(const Edge &lhs, const Edge &rhs) {
    return equal(lhs.from, rhs.from) && equal(lhs.to, rhs.to);
}

void pushBack(Graph &graph, const Edge &edge) {
    Edge* edges = new Edge[graph.edgesCnt + 1];

    for (int i = 0; i < graph.edgesCnt; ++i) {
        edges[i] = graph.edges[i];
    }

    edges[graph.edgesCnt] = edge;
    ++graph.edgesCnt;

    delete[] graph.edges;
    graph.edges = edges;
}

void addEdge(Graph &graph, const Edge &edge) {
    bool uniqueFrom = true, uniqueTo = true;
    for (int i = 0; i < graph.edgesCnt && (uniqueFrom || uniqueTo); ++i) {
        if (equal(graph.edges[i], edge)) {
            std::cout << "Edge already in graph!\n";
            return;
        }

        uniqueFrom &= equal(graph.edges[i].from, edge.from) && equal(graph.edges[i].to, edge.from);
        uniqueTo &= equal(graph.edges[i].from, edge.to) && equal(graph.edges[i].to, edge.to);
    }

    pushBack(graph, edge);
    graph.verticesCnt += uniqueFrom + uniqueTo;
}

void initGraph(Graph &graph) {
    int edgesCnt;
    std::cin >> edgesCnt;

    for (int i = 0; i < edgesCnt; ++i) {
        Edge edge;
        std::cin >> edge.from.label >> edge.to.label;

        addEdge(graph, edge);
    }
}

void freeGraph(Graph &graph) {
    delete[] graph.edges;
    graph.edges = nullptr;
    graph.edgesCnt = 0;
    graph.verticesCnt = 0;
}

int getIndegree(const Graph &graph, const Vertex &vertex) {
    int degree = 0;
    for (int i = 0; i < graph.edgesCnt; ++i) {
        degree += (equal(graph.edges[i].to, vertex) == 0);
    }

    return degree;
}

bool isGraphComplete(const Graph &graph) {
    return graph.edgesCnt == (graph.verticesCnt * (graph.verticesCnt - 1));
}

void removeEdge(Graph &graph, const Edge &edge) {
    int removeIndex = -1;
    bool uniqueFrom = true, uniqueTo = true;
    for (int i = 0; i < graph.edgesCnt; ++i) {
        if (equal(graph.edges[i], edge)) {
            removeIndex = i;
        }

        uniqueFrom &= equal(graph.edges[i].from, edge.from) && equal(graph.edges[i].to, edge.from);
        uniqueTo &= equal(graph.edges[i].from, edge.to) && equal(graph.edges[i].to, edge.to);
    }

    if (removeIndex != -1) {
        graph.edges[removeIndex] = graph.edges[graph.edgesCnt - 1];
        --graph.edgesCnt;
        graph.verticesCnt -= uniqueFrom + uniqueTo;
    } else {
        std::cout << "Edge to be removed was not found in graph!\n";
    }
}