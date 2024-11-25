#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX 10     // 最大部门数量
#define INF INT_MAX // 表示无穷大

// 部门结构
typedef struct {
    char name[20];     // 部门名称
    char description[100]; // 部门描述
} Department;

// 图结构
typedef struct {
    int matrix[MAX][MAX]; // 邻接矩阵，存储距离
    Department departments[MAX]; // 部门信息
    int size;              // 部门数量
} Graph;

// 初始化图
void initGraph(Graph *g) {
    g->size = 0;
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            g->matrix[i][j] = (i == j) ? 0 : INF; // 自己到自己为0，其它为INF
        }
    }
}

// 添加部门
void addDepartment(Graph *g, const char *name, const char *description) {
    strcpy(g->departments[g->size].name, name);
    strcpy(g->departments[g->size].description, description);
    g->size++;
}

// 添加路径（带权边）
void addEdge(Graph *g, int from, int to, int weight) {
    g->matrix[from][to] = weight;
    g->matrix[to][from] = weight; // 无向图
}

// 根据部门名称查找信息
void queryDepartment(Graph *g, const char *name) {
    for (int i = 0; i < g->size; i++) {
        if (strcmp(g->departments[i].name, name) == 0) {
            printf("部门名称: %s\n", g->departments[i].name);
            printf("部门描述: %s\n", g->departments[i].description);
            return;
        }
    }
    printf("未找到部门: %s\n", name);
}

// Dijkstra算法计算最短路径
void dijkstra(Graph *g, int start, int end) {
    int dist[MAX], visited[MAX], prev[MAX];
    for (int i = 0; i < g->size; i++) {
        dist[i] = INF;
        visited[i] = 0;
        prev[i] = -1;
    }

    dist[start] = 0;

    for (int i = 0; i < g->size; i++) {
        int minDist = INF, u = -1;

        // 找到未访问的最近的节点
        for (int j = 0; j < g->size; j++) {
            if (!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
                u = j;
            }
        }

        if (u == -1) break;
        visited[u] = 1;

        // 更新邻居节点的距离
        for (int v = 0; v < g->size; v++) {
            if (!visited[v] && g->matrix[u][v] != INF && dist[u] + g->matrix[u][v] < dist[v]) {
                dist[v] = dist[u] + g->matrix[u][v];
                prev[v] = u;
            }
        }
    }

    // 输出结果
    if (dist[end] == INF) {
        printf("从起点到终点不可达。\n");
    } else {
        printf("从起点到终点的最短距离为: %d\n", dist[end]);
        printf("路径为: ");
        int path[MAX], pathSize = 0, current = end;
        while (current != -1) {
            path[pathSize++] = current;
            current = prev[current];
        }
        for (int i = pathSize - 1; i >= 0; i--) {
            printf("%s", g->departments[path[i]].name);
            if (i > 0) printf(" -> ");
        }
        printf("\n");
    }
}

// 主函数
int main() {
    Graph g;
    initGraph(&g);

    // 添加部门
    addDepartment(&g, "门诊部", "负责常规病人就诊的部门");//0
    addDepartment(&g, "住院部", "提供住院服务的部门");//1
    addDepartment(&g, "急诊部", "处理紧急情况的部门");//2
    addDepartment(&g, "药房", "负责提供药品的部门");//3
    addDepartment(&g, "收费室", "负责费用结算的部门");//4
    addDepartment(&g, "化验室", "进行各类化验的部门");//5
    addDepartment(&g, "放射科", "负责影像检查的部门");//6
    addDepartment(&g, "手术室", "进行手术治疗的部门");//7
    addDepartment(&g, "B超室", "提供超声检查的部门");//8
    addDepartment(&g, "行政楼", "医院管理部门");//9

    // 添加路径
    addEdge(&g, 3, 2, 120);
    addEdge(&g, 3, 4, 50);
    addEdge(&g, 4, 5, 150);
    addEdge(&g, 4, 0, 190);
    addEdge(&g, 2, 0, 100);
    addEdge(&g, 2, 9, 80);
    addEdge(&g, 0, 5, 150);
    addEdge(&g, 0, 9, 90);
    addEdge(&g, 5, 1, 60);
    addEdge(&g, 5, 7, 100);
    addEdge(&g, 9, 6, 160);
    addEdge(&g, 1, 7, 50);
    addEdge(&g, 1, 6, 130);
    addEdge(&g, 1, 8, 100);
    addEdge(&g, 8, 6, 30);
    addEdge(&g, 7, 6, 100);


    // 查询部门信息
    printf("查询部门信息:\n");
    queryDepartment(&g, "急诊部");

    // 查询最短路径
    printf("\n查询最短路径:\n");
    dijkstra(&g, 0, 7); // 从门诊部到手术室

    return 0;
}
