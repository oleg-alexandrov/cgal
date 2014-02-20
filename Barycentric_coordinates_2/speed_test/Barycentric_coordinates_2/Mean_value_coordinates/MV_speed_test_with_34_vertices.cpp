// Author(s) : Dmitry Anisimov.
// We test speed of Mean Value coordinates on a set of automatically generated
// points inside a concave polygon with 34 vertices. We use inexact kernel.

#include <CGAL/Real_timer.h>

#include <CGAL/Polygon_2.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

#include <CGAL/Mean_value_coordinates_2.h>

typedef CGAL::Real_timer Timer;

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;

typedef Kernel::FT      Scalar;
typedef Kernel::Point_2 Point;

typedef CGAL::Polygon_2<Kernel> Polygon;

typedef std::vector<Scalar> Coordinate_vector;
typedef Coordinate_vector::iterator Overwrite_iterator;

typedef CGAL::Barycentric_coordinates::Mean_value_coordinates_2<Polygon, Overwrite_iterator> Mean_value_coordinates;

using std::cout; using std::endl; using std::string;

int main()
{
    const int number_of_x_coordinates = 100000;
    const int number_of_y_coordinates = 1000;
    const int number_of_runs          = 1;

    const Scalar zero = Scalar(0);
    const Scalar one  = Scalar(1);
    const Scalar x_step = one / Scalar(number_of_x_coordinates);
    const Scalar y_step = one / Scalar(number_of_y_coordinates);

    const Point vertices[34] = { Point(zero                  , zero - y_step         ),
                                 Point(one                   , zero - y_step         ),
                                 Point(Scalar(3)  / Scalar(2), Scalar(-1) / Scalar(2)),
                                 Point(2                     , Scalar(-1) / Scalar(2)),
                                 Point(Scalar(5)  / Scalar(2), 0                     ),
                                 Point(2                     , Scalar(1)  / Scalar(2)),
                                 Point(Scalar(5)  / Scalar(2), 1                     ),
                                 Point(3                     , Scalar(3)  / Scalar(4)),
                                 Point(3                     , Scalar(5)  / Scalar(4)),
                                 Point(Scalar(5)  / Scalar(2), Scalar(7)  / Scalar(4)),
                                 Point(3                     , Scalar(5)  / Scalar(2)),
                                 Point(Scalar(5)  / Scalar(2), Scalar(5)  / Scalar(2)),
                                 Point(Scalar(9)  / Scalar(4), 2                     ),
                                 Point(Scalar(7)  / Scalar(4), 2                     ),
                                 Point(2                     , Scalar(5)  / Scalar(2)),
                                 Point(Scalar(3)  / Scalar(2), Scalar(5)  / Scalar(2)),
                                 Point(Scalar(5)  / Scalar(4), 2                     ),
                                 Point(Scalar(3)  / Scalar(4), 2                     ),
                                 Point(1                     , Scalar(5)  / Scalar(2)),
                                 Point(Scalar(1)  / Scalar(2), Scalar(5)  / Scalar(2)),
                                 Point(Scalar(1)  / Scalar(4), 2                     ),
                                 Point(Scalar(-1) / Scalar(4), 2                     ),
                                 Point(zero                  , Scalar(5)  / Scalar(2)),
                                 Point(Scalar(-1) / Scalar(2), Scalar(5)  / Scalar(2)),
                                 Point(Scalar(-3) / Scalar(4), 2                     ),
                                 Point(Scalar(-1) / Scalar(2), Scalar(3)  / Scalar(2)),
                                 Point(Scalar(-5) / Scalar(4), Scalar(3)  / Scalar(2)),
                                 Point(Scalar(-1) / Scalar(2), Scalar(3)  / Scalar(4)),
                                 Point(-one                  , Scalar(1)  / Scalar(2)),
                                 Point(-one                  , zero                  ),
                                 Point(Scalar(-3) / Scalar(2), zero                  ),
                                 Point(Scalar(-3) / Scalar(2), Scalar(-1) / Scalar(2)),
                                 Point(Scalar(-1) / Scalar(2), Scalar(-1) / Scalar(2)),
                                 Point(Scalar(-1) / Scalar(2), zero - y_step         )
                              };
    const Polygon concave_polygon(vertices, vertices + 34);

    Mean_value_coordinates mean_value_coordinates(concave_polygon);

    Coordinate_vector coordinates;
    coordinates.resize(34);
    Overwrite_iterator it = coordinates.begin();

    Timer time_to_compute;

    double time = 0.0;
    for(int i = 0; i < number_of_runs; ++i) {

        time_to_compute.start();
        for(Scalar x = zero; x <= one; x += x_step) {
            for(Scalar y = zero; y <= one; y += y_step)
                mean_value_coordinates.compute(Point(x, y), it, CGAL::BC::ON_BOUNDED_SIDE);
        }
        time_to_compute.stop();

        time += time_to_compute.time();

        time_to_compute.reset();
    }
    const double mean_time = time / number_of_runs;

    cout.precision(10);
    cout << endl << "CPU time to compute Mean Value coordinates (34 vertices) = " << mean_time << " seconds." << endl << endl;
    
    return EXIT_SUCCESS;
}