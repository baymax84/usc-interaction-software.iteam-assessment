#include <runtime_errors/landmark.h>

Landmark::Landmark( Landmark const & other )
:
    x_( other.x_ ),
    y_( other.y_ ),
    theta_( other.theta_ ),
    type_( other.type_ ),
    id_( other.id_ )
{
    //
}

Landmark::Landmark( double const & x, double const & y, double const & theta, std::string const & type, unsigned int const & id  )
:
    x_( x ),
    y_( y ),
    theta_( theta ),
    type_( type ),
    id_( id )
{
    //
}

std::string Landmark::toString() const
{
    std::stringstream result;

    result << type_ << " [" << id_ << "] (" << x_ << ", " << y_ << " ), " << theta_;

    return result.str();
}
