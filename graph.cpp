#include <iostream>
#include <boost/property_map/property_map.hpp>
#include <boost/iterator/iterator_facade.hpp>

#include <iostream>
#include <vector>
using namespace std;

typedef double FT;

template <typename T>
struct Point_2
{
    T x, y;
    Point_2(T x = std::numeric_limits<T>::max(), T y = std::numeric_limits<T>::max()) : x(x), y(y) {}

    Point_2 operator+(const Point_2 &other)
    {
        return Point_2(x + other.x, y + other.y);
    }
};

template <typename T>
ostream &operator<<(ostream &out, const Point_2<T> &p)
{
    out << "(" << p.x << ", " << p.y << ")" << endl;
    return out;
}
typedef Point_2<FT> Pnt2;

//---------------------------------------------Property----------------------------------------
template <class T>
class Property_array
{
public:
    Property_array(string name) : name(name) {}

private:
    string name;
    vector<T> array_;
};

template <class I, class T, class CRTP_derived_class>
class Property_base_map : public boost::put_get_helper<typename vector<T>::reference, CRTP_derived_class>
{
public:
    Property_map_base(Property_array<T> *p = nullptr) : parray_(p) {}

private:
    Property_array<T> *parray_;
};

template <class I, class T>
class Property_map : public Property_base_map<I, T, Property_map<I, T>>
{
    typedef Property_base_map<I, T, Property_map<I, T>> Base;

public:
    Property_map() : Base() {}
    Property_map(const Base &pm) : Base(pm) {}
};

template <class Ref_class, class Key>
class Property_container
{

public:
    Property_container() : size_(0) {}

    template <class T>
    add(string name, const T t)
    {
        Property_array<T> *parray = new Property_array<T>(name);
        // props_.push_back(parray);
    }

private:
    size_t size_;
    //vector<Property_array<T> *> props_;
};

template <class P>
class Surface_mesh
{
    typedef Surface_mesh<P> Self;
    class Vertex_index
    {
        int idx_;
    };

    class Halfedge_index
    {
        int idx_;
    };

    class Face_index
    {
        int idx_;
    };

    struct Vertex_connectivity
    {
        Halfedge_index halfedge_;
    };

    struct Halfedge_connectivity
    {
        Vertex_index vertex_; // the vertex h points to
        Face_index face_;
        Halfedge_index prev_halfedge_;
        Halfedge_index next_halfedge_;
    };

    template <class, bool = true>
    struct Property_selector
    {
    };

    template <bool Dummy>
    struct Property_selector<Vertex_index, Dummy> // partial specialization
    {
        Property_selector(Self *sm) : sm(sm) {}

        Property_container<Self, Vertex_index> operator()()
        {
            cout << "vprops_ is selected" << endl;
            return sm->vprops_;
        }

    private:
        Self *sm;
    };

    template <bool Dummy>
    struct Property_selector<Halfedge_index, Dummy> // partial specialization
    {
        Property_selector(Self *sm) : sm(sm) {}

        Property_container<Self, Halfedge_index> operator()()
        {
            cout << "hprops_ is selected" << endl;
            return sm->hprops_;
        }

    private:
        Self *sm;
    };

    template <class I, class T>
    Property_map<I, T> add_property_map(string name, const T t = T())
    {
        // how to select which property container the property will be added to
        return Property_selector<I>(this)().template add<T>(name, t);
    }

public:
    Surface_mesh()
    {
        vconn_ = add_property_map<Vertex_index, Vertex_connectivity>("v:connectivity");
        hconn_ = add_property_map<Halfedge_index, Halfedge_connectivity>("h:connectivity");

        vpoint_ = add_property_map<Vertex_index, P>("v:point");
    }

private:
    Property_container<Self, Vertex_index> vprops_;   // TVert
    Property_container<Self, Halfedge_index> hprops_; // TEdge
    Property_container<Self, Face_index> fprops_;     // TFace

    Property_map<Vertex_index, Vertex_connectivity> vconn_;
    Property_map<Halfedge_index, Halfedge_connectivity> hconn_;

    Property_map<Vertex_index, P> vpoint_;
};

int main()
{
    Surface_mesh<Pnt2> sm;
    return 0;
}