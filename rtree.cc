#include <iostream>
#include <boost/geometry.hpp>
#include <boost/geometry/index/rtree.hpp>

using namespace std;
namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;

typedef bg::model::point<double, 2, bg::cs::cartesian> point;
typedef bg::model::box<point> box;

int main()
{
    bgi::rtree<box, bgi::quadratic<16>> rtree;

    // add some boxes
    rtree.insert(box(point(0, 0), point(1, 1)));
    rtree.insert(box(point(1, 1), point(2, 2)));
    rtree.insert(box(point(-1, -1), point(0, 0)));

    // search for boxes intersecting with a point
    point query_point(0.5, 0.5);
    vector<box> result;
    rtree.query(bgi::intersects(query_point), back_inserter(result));

    // print out the result
    for (const auto& box : result)
    {
        cout << bg::dsv(box) << endl;
    }

    return 0;
}
