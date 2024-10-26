import time
import math
from collections import Counter

# Sample dataset for red, green, and blue
data = [
    [0, 255, 200, 'Red'],
    [2, 250, 195, 'Red'],
    [120, 255, 200, 'Green'],
    [122, 250, 195, 'Green'],
    [240, 255, 200, 'Blue'],
    [245, 250, 195, 'Blue']
]

def knn_predict(data, x, k=3):
    distances = []
    for entry in data:
        h, s, v, label = entry
        euclidean_distance = math.sqrt((x[0] - h) ** 2 + (x[1] - s) ** 2 + (x[2] - v) ** 2)
        distances.append((euclidean_distance, label))

    distances.sort(key=lambda x: x[0])
    k_nearest_neighbors = distances[:k]
    k_nearest_labels = [label for _, label in k_nearest_neighbors]
    majority_class = Counter(k_nearest_labels).most_common(1)[0][0]
    return majority_class

# Measure performance
query = [120, 250, 180]
k = 3
iterations = 10000  # Number of times to repeat the prediction for timing

start_time = time.time()
for _ in range(iterations):
    knn_predict(data, query, k)
end_time = time.time()

avg_time = (end_time - start_time) / iterations
print(f"Average time per prediction in Python: {avg_time * 1e6:.2f} microseconds")