#include "../../helpers/getInput.hpp"
#include "../../helpers/timer.hpp"
#include <limits>
#include <unordered_map>
#include <algorithm>
#include <queue>
#include <sstream>
#include <iostream>

enum FileType { EXAMPLE_FILE, PUZZLE_FILE, CUSTOM_EXAMPLE_FILE };

void printTotal(long long total)
{
    static int calls = 1;
    printf("Part %i Answer: %lld\n", calls, total);
    calls++;
}

struct Point3D { int x, y, z; };

long long distanceSquared(const Point3D &a, const Point3D &b)
{
    long long dx = static_cast<long long>(a.x) - b.x;
    long long dy = static_cast<long long>(a.y) - b.y;
    long long dz = static_cast<long long>(a.z) - b.z;
    return dx*dx + dy*dy + dz*dz;
}

// Disjoint Set Union (DSU / Union-Find)
struct DSU
{
    std::vector<int> parent;
    std::vector<int> size;

    DSU(int n)
    {
        parent.resize(n);
        size.resize(n, 1);
        for (int i = 0; i < n; ++i) parent[i] = i;
    }

    int find(int x)
    {
        while (parent[x] != x) {
            parent[x] = parent[parent[x]]; // path compression
            x = parent[x];
        }
        return x;
    }

    bool unite(int a, int b)
    {
        a = find(a);
        b = find(b);
        if(a == b) return false;
        if(size[a] < size[b]) std::swap(a, b);
        parent[b] = a;
        size[a] += size[b];
        return true;
    }
};

struct Edge
{
    int u, v;
    long long dist;
};

// generate only the numConnections smallest edges using a max-heap
std::vector<Edge> generateClosestEdges(const std::vector<Point3D>& points, int numConnections)
{
    int n = points.size();
    auto cmp = [](const Edge& a, const Edge& b){ return a.dist < b.dist; };
    std::priority_queue<Edge, std::vector<Edge>, decltype(cmp)> maxHeap(cmp);

    for(int i = 0; i < n; ++i) {
        for(int j = i + 1; j < n; ++j) {
            long long dist = distanceSquared(points[i], points[j]);
            Edge e{i, j, dist};

            if((int)maxHeap.size() < numConnections) {
                maxHeap.push(e);
            } else if(dist < maxHeap.top().dist) {
                maxHeap.pop();
                maxHeap.push(e);
            }
        }
    }

    std::vector<Edge> edges;
    edges.reserve(maxHeap.size());
    while(!maxHeap.empty()) {
        edges.push_back(maxHeap.top());
        maxHeap.pop();
    }
    std::reverse(edges.begin(), edges.end()); // ascending order
    return edges;
}

long long connectClosestPairs(const std::vector<Point3D>& points, int numConnections = 1000)
{
    int n = points.size();
    auto edges = generateClosestEdges(points, numConnections);

    DSU dsu(n);
    for(const auto& e : edges) {
        dsu.unite(e.u, e.v);
    }

    // collect all circuit sizes
    std::unordered_map<int,int> rootCount;
    for(int i = 0; i < n; ++i) rootCount[dsu.find(i)]++;

    std::vector<int> sizes;
    for(auto &kv : rootCount) sizes.push_back(kv.second); 
    std::sort(sizes.rbegin(), sizes.rend()); // descending

    long long result = 1;
    for(int i = 0; i < 3 && i < (int)sizes.size(); ++i) result *= sizes[i];

    return result;
}

void part1(const std::vector<Point3D>& points, const FileType& fileType)
{
    ScopedTimer timer("Part 1");
    int connections = (fileType == EXAMPLE_FILE) ? 10 : 1000;
    long long total = connectClosestPairs(points, connections);
    printTotal(total);
}

long long lastConnectionProduct(const std::vector<Point3D>& points)
{
    int n = points.size();
    DSU dsu(n);
    int remainingCircuits = n;
    Edge lastEdge{0,1,0};

    // Min-heap for edges
    auto cmp = [](const Edge& a, const Edge& b){ return a.dist > b.dist; };
    std::priority_queue<Edge, std::vector<Edge>, decltype(cmp)> minHeap(cmp);

    // Only generate edges lazily as needed
    for(int i = 0; i < n; ++i)
        for(int j = i + 1; j < n; ++j)
            minHeap.push({i,j,distanceSquared(points[i], points[j])});

    while(remainingCircuits > 1 && !minHeap.empty()) {
        Edge e = minHeap.top(); minHeap.pop();
        if(dsu.unite(e.u, e.v)) {
            lastEdge = e;
            remainingCircuits--;
        }
    }

    return static_cast<long long>(points[lastEdge.u].x) * points[lastEdge.v].x;
}

void part2(const std::vector<Point3D>& points)
{
    ScopedTimer timer("Part 2");
    long long total = lastConnectionProduct(points);
    printTotal(total);
}

std::vector<Point3D> parsePoints(const std::vector<std::string>& lines)
{
    std::vector<Point3D> points;
    for(const auto& line : lines) {
        std::stringstream ss(line);
        Point3D p;
        char c1, c2;
        if(ss >> p.x >> c1 >> p.y >> c2 >> p.z && c1 == ',' && c2 == ',') {
            points.push_back(p);
        } else {
            std::cerr << "Skipping malformed line: " << line << "\n";
        }
    }
    return points;
}

int main(int argc, char **argv)
{
    FileType fileType = EXAMPLE_FILE; // default

    if(argc > 1) {
        try {
            fileType = static_cast<FileType>(std::stoi(argv[1]));
        } catch(...) {
            std::cerr << "Invalid file index, using EXAMPLE_FILE\n";
        }
    }

    InputData input = readFile(fileType);
    std::vector<Point3D> points = parsePoints(input.lines);
    header(input);

    part1(points, fileType);
    part2(points);

    return 0;
}
