#include "inc.h"

NS_BEGIN(elloop);
NS_BEGIN(graph);

using namespace std;


// ============================================================================
//
// Matrix Graph Structure Definition
//
// ============================================================================

const int INF             = INT_MAX;
const int Max_Vertext_Num = 20;

enum class GraphKind
{
    kDirectedGraph,
    kDirectedNet,
    kUndirectedGraph,
    kUndirectedNet,
};

typedef int     VRType;             // vetext relationship type.
typedef char    InfoType;           // arc info type.
typedef char    VertexType;

struct ArcCell
{
    VRType      adj;
    InfoType    *info;
};

typedef ArcCell AdjMatrix[Max_Vertext_Num][Max_Vertext_Num];

struct MGraph
{
    VertexType  vexs[Max_Vertext_Num];
    AdjMatrix   arcs;
    size_t      vex_num;
    size_t      arc_num;
    GraphKind   kind;
};

// ============================================================================
//
// Matrix Graph Operations.
//
// ============================================================================

int     create_matrix_graph_DG(MGraph &g);
int     create_matrix_graph_DN(MGraph &g);
int     create_matrix_graph_UDG(MGraph &g);
int     create_matrix_graph_UDN(MGraph &g);
size_t  locate_matrix_vertex(const MGraph& g, const VertexType& v);
void    print_matrix_graph(const MGraph& g);



int create_matrix_graph(MGraph &g)
{
    switch (g.kind)
    {
        case GraphKind::kDirectedGraph:
            return create_matrix_graph_DG(g);
        case GraphKind::kDirectedNet:
            return create_matrix_graph_DN(g);
        case GraphKind::kUndirectedGraph:
            return create_matrix_graph_UDG(g);
        case GraphKind::kUndirectedNet:
            return create_matrix_graph_UDN(g);
        default:
            return -1;
    }
}

int create_matrix_graph_DG(MGraph &g) { return 0; }
int create_matrix_graph_UDG(MGraph &g) { return 0;}
int create_matrix_graph_UDN(MGraph &g) { return 0;}


int create_matrix_graph_DN(MGraph &g)
{
    pln("vex_num, arc_num: ");
    cin >> g.vex_num >> g.arc_num;
    psln(g.vex_num);
    psln(g.arc_num);


    // read vex.
    LOGD("input v1 to v%lu: ", g.vex_num);
    for (size_t i=0; i<g.vex_num; ++i)
    {
        cin >> g.vexs[i];
    }

    // init arcs.
    for (size_t i=0; i<Max_Vertext_Num; ++i) 
    {
        for (size_t j=0; j<Max_Vertext_Num; ++j) 
        {
            g.arcs[i][j] = {INF, nullptr};
        }
    }

    // create arcs.
    for (size_t i=0; i<g.arc_num; ++i) 
    {
        LOGD("arc-%lu (begin, end, weight): ", (i+1));
        VertexType vb, ve;
        VRType w;
        cin >> vb >> ve >> w;
        LOGD("arc created (%c %c %d)\n", vb, ve, w);
        size_t b = locate_matrix_vertex(g, vb);
        size_t e = locate_matrix_vertex(g, ve);
        assert(b < g.vex_num && e < g.vex_num);
        g.arcs[e][b] = g.arcs[b][e] = {w, nullptr};
    }

    return 0;
}

size_t locate_matrix_vertex(const MGraph& g, const VertexType& v)
{
    for (size_t i=0; i<g.vex_num; ++i) 
    {
        if (g.vexs[i] == v) 
        {
            return i;
        }
    }
    return g.vex_num;  // index out of range.
}

void print_matrix_graph(const MGraph& g)
{
    p("/\t");
    for (size_t i=0; i<g.vex_num; ++i) 
    {
        p(g.vexs[i]); p("\t");
    }
    cr;

    for (size_t i=0; i<g.vex_num; ++i) 
    {
        p(g.vexs[i]); p("\t");
        for (size_t j=0; j<g.vex_num; ++j) 
        {
            if (g.arcs[i][j].adj == INF)
            {
                p("n\t");
            }
            else
            {
                p(g.arcs[i][j].adj); p("\t");
            }
        }
        cr;
    }
}

// ============================================================================
//
// Test.
//
// ============================================================================

RUN_GTEST(GraphTest, CreateDN, @@);

MGraph mg;
mg.kind = GraphKind::kDirectedNet;
create_matrix_graph(mg);
print_matrix_graph(mg);


END_TEST;




NS_END(graph);
NS_END(elloop);
