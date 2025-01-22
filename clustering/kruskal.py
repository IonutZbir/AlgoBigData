from typing import Dict, Tuple, List
from union_find import QuickFindUF
import matplotlib.pyplot as plt

class Graph:    
    def __init__(self, edges: Tuple[int | str] = None) -> None:
        if edges is not None:
            self.edges = set(edges)
        else:
            self.edges = set()
        
        self.__get_nodes_from_edges()
    
    def __get_nodes_from_edge(self, edge):
            x = edge[0]
            y = edge[1]
                    
            if x not in self.nodes:
                self.nodes.add(x)
            if y not in self.nodes:
                self.nodes.add(y)
    
    def __get_nodes_from_edges(self):
        self.nodes = set()

        for edge in self.edges:
            self.__get_nodes_from_edge(edge)    
            
    def add_edge(self, edge: Tuple[int | str]) -> None:
        self.__get_nodes_from_edge(edge)
        self.edges.add(edge)
    
    def __str__(self):
        out = "Graph(V, E) = \n"
        for edge in self.edges:
            out += f"{edge}\n"        
        return out

def kruskal(graph: Graph) -> Graph:
    uf = QuickFindUF(len(graph.nodes) + 1)
    mst = Graph()
    edges = sorted(graph.edges, key=lambda edge: edge[2])
    n = len(graph.nodes)
    for edge in edges:
        x, y, _ = edge
        if uf.find(x) != uf.find(y):
            uf.union(x, y)
            mst.add_edge(edge)
    return mst

def k_cluster(graph: Graph, k: int) -> Tuple[Graph, Dict[int, List[int]]]:
    mst = kruskal(graph)
    
    edges = sorted(mst.edges, key=lambda edge: edge[2])
    for _ in range(k - 1):
        edges.pop()
    
    final_graph = Graph(edges)
    
    n = len(graph.nodes)
    uf = QuickFindUF(n + 1)
    for u, v, _ in edges:
        uf.union(u, v)
    
    clusters = {}
    for node in range(n):
        root = uf.find(node)
        if root not in clusters:
            clusters[root] = []
        clusters[root].append(node)
    
    return final_graph, clusters

if __name__ == "__main__":
    edges = [
        ('A', 'B', 7),
        ('A', 'C', 14),
        ('A', 'D', 30),
        ('B', 'C', 21),
        ('C', 'D', 10),
        ('C', 'E', 1),
        ('E', 'F', 6),
        ('E', 'G', 9),
        ('F', 'G', 4)
    ]

    letter_to_number = {
        'A': 1,
        'B': 2,
        'C': 3,
        'D': 4,
        'E': 5,
        'F': 6,
        'G': 7
    }

    numeric_edges = [(letter_to_number[u], letter_to_number[v], w) for u, v, w in edges]

    g = Graph(numeric_edges)
    print(g)
    mst = kruskal(g)
    print(mst)       
