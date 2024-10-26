using Statistics
using StatsBase
using Printf

# Example dataset
data = [
    (0, 255, 200, "Red"),
    (2, 250, 195, "Red"),
    (120, 255, 200, "Green"),
    (122, 250, 195, "Green"),
    (240, 255, 200, "Blue"),
    (245, 250, 195, "Blue")
]

# Euclidean distance function
function euclidean_distance(x1, x2)
    sqrt(sum((x1[i] - x2[i])^2 for i in 1:3))
end

# KNN prediction function
function knn_predict(data, x, k=3)
    distances = [(euclidean_distance((h, s, v), x), label) for (h, s, v, label) in data]
    nearest_neighbors = sort(distances, by=x->x[1])[1:k]
    labels = [neighbor[2] for neighbor in nearest_neighbors]
    counts = countmap(labels)
    majority_class, _ = findmax(counts)
    return majority_class
end

# Measure performance
query = (120, 250, 180)
k = 3
iterations = 10000

# Start timing
start_time = time_ns()
for _ in 1:iterations
    knn_predict(data, query, k)
end
end_time = time_ns()

# Calculate average time in microseconds
total_time_ns = end_time - start_time
avg_time_microseconds = total_time_ns / (iterations * 1000)
@printf("Average time per prediction in Julia: %.2f microseconds\n", avg_time_microseconds)