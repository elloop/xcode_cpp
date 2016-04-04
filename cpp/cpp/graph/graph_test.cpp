#include "inc.h"
#include <vector>
#include <string>
#include "rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/reader.h"
#include "util/FileReader.h"

NS_BEGIN(elloop);
NS_BEGIN(matrix_graph);

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
    kUnknownGraph
};

typedef int         VRType;             // vetext relationship type.
typedef char        InfoType;           // arc info type.
typedef string      VertexType;

typedef vector<VertexType>                              VexCollection;
typedef vector<tuple<VertexType, VertexType, VRType>>   ArcCollection;

struct ArcCell
{
    VRType      adj;
    InfoType    *info;
};

typedef ArcCell AdjMatrix[Max_Vertext_Num][Max_Vertext_Num];

struct MGraph
{
    MGraph() : vex_num(0), arc_num(0), kind(GraphKind::kUnknownGraph) {}
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
int     create_matrix_graph(MGraph &g, const VexCollection &vexs, const ArcCollection &arcs);
int     create_matrix_graph_DG(MGraph &g, const VexCollection &vexs, const ArcCollection &arcs);
int     create_matrix_graph_DN(MGraph &g, const VexCollection &vexs, const ArcCollection &arcs);
int     create_matrix_graph_UDG(MGraph &g, const VexCollection &vexs, const ArcCollection &arcs);
int     create_matrix_graph_UDN(MGraph &g, const VexCollection &vexs, const ArcCollection &arcs);
size_t  locate_matrix_vertex(const MGraph& g, const VertexType& v);
void    print_matrix_graph(const MGraph& g);

// traverse graph.
typedef std::function<void(const VertexType& v)> visit_func_t;
void    deep_first_search(const MGraph& g, size_t begin_index, vector<bool> &visited, const visit_func_t& visit_func);
void    breadth_first_search(const MGraph& g, size_t begin_index, vector<bool> &visited, const visit_func_t& visit_func);
size_t  first_adj(const MGraph &g, size_t vex_index);
size_t  next_adj(const MGraph &g, size_t vex_index, size_t current_adj);

MGraph* alloc_graph_using_json(const string& file_name);


int create_matrix_graph_DG(MGraph &g, const VexCollection &vexs, const ArcCollection &arcs) { return 0; }
int create_matrix_graph_UDG(MGraph &g, const VexCollection &vexs, const ArcCollection &arcs) { return 0;}
int create_matrix_graph_DN(MGraph &g, const VexCollection &vexs, const ArcCollection &arcs) { return 0;}

int create_matrix_graph(MGraph &g, const VexCollection &vexs, const ArcCollection &arcs)
{
    switch (g.kind) {
        case GraphKind::kUndirectedGraph:
            return create_matrix_graph_UDG(g, vexs, arcs);
        case GraphKind::kUndirectedNet:
            return create_matrix_graph_UDN(g, vexs, arcs);
        case GraphKind::kDirectedGraph:
            return create_matrix_graph_DG(g, vexs, arcs);
        case GraphKind::kDirectedNet:
            return create_matrix_graph_DN(g, vexs, arcs);
        default:
            break;
    }
    return -1;
}

int create_matrix_graph_UDN(MGraph &g, const VexCollection &vexs, const ArcCollection &arcs) {
    g.vex_num = vexs.size();
    g.arc_num = arcs.size();

    // read vex.
    for (size_t i=0; i<g.vex_num; ++i) {
        g.vexs[i] = vexs[i];
    }

    // init arcs.
    for (size_t i=0; i<Max_Vertext_Num; ++i) {
        for (size_t j=0; j<Max_Vertext_Num; ++j) {
            g.arcs[i][j] = {INF, nullptr};
        }
    }

    // create arcs.
    for (size_t i=0; i<g.arc_num; ++i) {
        VertexType from = std::get<0>(arcs[i]);
        VertexType to   = std::get<1>(arcs[i]);
        VRType w        = std::get<2>(arcs[i]);
        
        size_t b = locate_matrix_vertex(g, from);
        size_t e = locate_matrix_vertex(g, to);
        assert(b < g.vex_num && e < g.vex_num);
        g.arcs[e][b] = g.arcs[b][e] = {w, nullptr};
    }

    return 0;
}

size_t locate_matrix_vertex(const MGraph& g, const VertexType& v) {
    for (size_t i=0; i<g.vex_num; ++i) 
    {
        if (g.vexs[i] == v) 
        {
            return i;
        }
    }
    return g.vex_num;  // index out of range.
}

void print_matrix_graph(const MGraph& g) {
    p("/\t");
    for (size_t i=0; i<g.vex_num; ++i) {
        p(g.vexs[i]); p("\t");
    }
    cr;

    for (size_t i=0; i<g.vex_num; ++i) {
        p(g.vexs[i]); p("\t");
        for (size_t j=0; j<g.vex_num; ++j) {
            if (g.arcs[i][j].adj == INF) {
                p("n\t");
            }
            else {
                p(g.arcs[i][j].adj); p("\t");
            }
        }
        cr;
    }
}

template <typename T>
T smart_convert(const rapidjson::GenericValue<rapidjson::UTF8<>>& v) {
    return T();
    /*
    size_t type_code = typeid(T).hash_code();
    if (type_code == typeid(int).hash_code()) {
        return v.GetInt();
    }
    else if (type_code == typeid(float).hash_code() ||
             type_code == typeid(double).hash_code()) {
        return v.GetDouble();
    }
    else if (type_code == typeid(string).hash_code()) {
        return v.GetString();
    }
    else if (type_code == typeid(bool).hash_code()) {
        return v.GetBool();
    }
    else {
        return T();
    }
     */
}

template <>
int smart_convert<int>(const rapidjson::GenericValue<rapidjson::UTF8<>> &v) {
    return v.GetInt();
}

template <>
string smart_convert<string>(const rapidjson::GenericValue<rapidjson::UTF8<>> &v) {
    return v.GetString();
}

template <>
double smart_convert<double>(const rapidjson::GenericValue<rapidjson::UTF8<>> &v) {
    return v.GetDouble();
}


template <>
bool smart_convert<bool>(const rapidjson::GenericValue<rapidjson::UTF8<>> &v) {
    return v.GetBool();
}


MGraph* alloc_graph_using_json(const string& file_name) {
    
    using namespace rapidjson;
    unsigned long size(0);
    unsigned char * graph_data = FileReader::getInstance()->getFileData(file_name.c_str(), "rb", &size);
    string str((const char*)graph_data, size);
    Document doc;
    if (doc.ParseInsitu((char*)str.c_str()).HasParseError()) {
        return nullptr;
    }

    auto g = new MGraph;
    if (doc.HasMember("type")) {
        string type_name = doc["type"].GetString();
        if (type_name == "UDG") {
            g->kind = GraphKind::kUndirectedGraph;
        }
        else if (type_name == "UDN") {
            g->kind = GraphKind::kUndirectedNet;
        }
        else if (type_name == "DG") {
            g->kind = GraphKind::kDirectedGraph;
        }
        else if (type_name == "DN") {
            g->kind = GraphKind::kDirectedNet;
        }
        else {
            g->kind = GraphKind::kUnknownGraph;
        }
    }
    
    VexCollection vexs;
    if (doc.HasMember("vexs") && doc["vexs"].IsArray()) {
        for (SizeType i=0; i<doc["vexs"].Size(); ++i) {
            vexs.push_back(smart_convert<VertexType>(doc["vexs"][i]));
        }
    }
    
    ArcCollection arcs;
    if (doc.HasMember("arcs") && doc["arcs"].IsArray()) {
        for (SizeType i=0; i<doc["arcs"].Size(); ++i) {
            auto t = make_tuple(smart_convert<VertexType>(doc["arcs"][i]["from"]),
                                smart_convert<VertexType>(doc["arcs"][i]["to"]),
                                smart_convert<VRType>(doc["arcs"][i]["weight"]));
            arcs.push_back(t);
        }
    }
    
    if (vexs.size() > 0 && g->kind != GraphKind::kUnknownGraph) {
        create_matrix_graph(*g, vexs, arcs);
        return g;
    }
    else {
        delete g;
        return nullptr;
    }
    

    return nullptr;
}

size_t first_adj(const MGraph &g, size_t vex_index) {
    assert(vex_index >= 0 && vex_index < g.vex_num);
    for (size_t i=0; i<g.vex_num; ++i) {
        if (g.arcs[vex_index][i].adj != INF) {
            return i;
        }
    }
    return g.vex_num;
}

size_t next_adj(const MGraph &g, size_t vex_index, size_t current_adj) {
    assert(vex_index >= 0 && current_adj >= 0);
    assert(vex_index < g.vex_num);
    
    for (size_t i=current_adj+1; i<g.vex_num; ++i) {
        if (g.arcs[vex_index][i].adj != INF) {
            return i;
        }
    }
    return g.vex_num;
}

void deep_first_search(const MGraph& g, size_t begin_index, vector<bool> &visited, const visit_func_t& visit_func) {
    if (!visited[begin_index]) {
        visit_func(g.vexs[begin_index]);
        visited[begin_index] = true;
        for (size_t i=first_adj(g, begin_index); i<g.vex_num; i=next_adj(g, begin_index, i)) {
            deep_first_search(g, i, visited, visit_func);
        }
    }
    
}

void    breadth_first_search(const MGraph& g, size_t begin_index, vector<bool> &visited, const visit_func_t& visit_func) {

}

// ============================================================================
//
// Test.
//
// ============================================================================

RUN_GTEST(GraphTest, CreateDN, @@);

auto mg = alloc_graph_using_json("matrix_graph.json");
if (mg) {
    print_matrix_graph(*mg);
    
    // deep first iterate.
    vector<bool> visited(mg->vex_num);
    cout << boolalpha;
    printContainer(visited, "visited: ");
    auto visit_func = [](const VertexType &v) { p(v); p(" "); };
    // iterate for every single vex, otherwise will not reach all vexs if the graph is not a connected graph.
    for (size_t i=0; i<mg->vex_num; ++i) {
        deep_first_search(*mg, i, visited, visit_func);
    }
    cr;
    printContainer(visited, "visited: ");

    delete mg;
}

END_TEST;




NS_END(matrix_graph);
NS_END(elloop);
