import random
from math import sqrt
from typing import Tuple, List
from kruskal import *
import matplotlib.pyplot as plt
import os

def load_dataset(filepath: str) -> List[Tuple[float, float]]:
    points = []
    with open(filepath) as file:
        for line in file:
            line = line.split(" ")
            x = float(line[0]) / 1000
            y = float(line[1]) / 1000
            points.append((x, y))
    return points

def norm2(point: Tuple[float, float]):
    x, y = point
    return sqrt(pow(x, 2) + pow(y, 2))

def distance(p1: Tuple[float, float], p2: Tuple[float, float]) -> float:
    x1, y1 = p1
    x2, y2 = p2
    return round(abs(norm2((x1 - x2, y1 - y2))), 3)

def create_edges_from_points(points: List[Tuple[float, float]]) -> List[Tuple[float, float, float]]:
    edges = set()
    for i, p1 in enumerate(points):
        for j, p2 in enumerate(points):
            if p1 != p2:
                d = distance(p1, p2)
                edges.add((i, j, d))
    return edges

def plot_graph(points: List[Tuple[float, float]], edges: List[Tuple[int, int, float]], file_path: str, clusters = None):
    
    x, y = zip(*points)
    
    plt.figure(figsize=(10, 8))
    
    if clusters is not None:
        colors = plt.get_cmap("tab10", len(clusters))
        
        # assegno degli id ai cluster partendo da 0, 1, 2...
        cluster_mapping = {cluster_id: idx for idx, cluster_id in enumerate(clusters)}
        
        for cluster_id, node_indices in clusters.items():
            cluster_points = [points[i] for i in node_indices]
            x, y = zip(*cluster_points)
            
            plt.scatter(x, y, color=colors(cluster_mapping[cluster_id]), s=50, label=f'Cluster {cluster_mapping[cluster_id] + 1}')
    else:
        plt.scatter(x, y, color='blue', s=50, label='Nodes')
    
    # Ho la mappatura effetuata nella funzione `create_edges_from_points`, quindi dati i punti, io ho la lista 
    # delle tuple contenente gli indici dei valori x e y di ciascun punto.
    
    for edge in edges:
        i, j, _ = edge
        x_values = [points[i][0], points[j][0]]
        y_values = [points[i][1], points[j][1]]
        plt.plot(x_values, y_values, 'gray', linewidth=1)

    plt.xlabel('X-axis')
    plt.ylabel('Y-axis')
   
    plt.title('Visualizzazione Grafo')
    plt.legend()
    plt.grid(True)
    
    plt.savefig(file_path)
    
    # plt.show()

if __name__ == "__main__":
    
    data_dir = "dataset"
    files = os.listdir("dataset")

    datasets = []
    for file in files:
        file_path = os.path.join(data_dir, file)
        datasets.append(file_path)
    
    files = [file.split(".")[0] for file in files]
        
    k = 6
    
    i = 0
    for ds in datasets:
        
        out1 = f"mst/{files[i]}.png"
        out2 = f"cluster/{files[i]}.png"
        
        points = load_dataset(ds)
        
        print(f"[INFO]: Loading dataset {ds}...")
        
        edges = create_edges_from_points(points)
        
        g = Graph(edges)
        mst = kruskal(g)
        cgraph, clusters = k_cluster(mst, k)
        
        print(f"[INFO]: Computed MST and Clutering...")
        plot_graph(points, mst.edges, out1)
        plot_graph(points, cgraph.edges, out2, clusters)
        
        print(f"[INFO]: Generated {out1} and {out2}")
        
        i += 1
