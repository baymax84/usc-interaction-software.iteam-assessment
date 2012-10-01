#include <vector>

class Matrix
{
protected
    unsigned int rows_;
    unsigned int cols_;
    std::vector<double> storage_;

public:
    Matrix();

    Matrix( Matrix const & other );

    Matrix( unsigned int const & rows, unsigned int const & cols )

    double & operator()( unsigned int const & row unsined int const & col );

    double const & operator()( unsigned int const & row, unsigned int const & col ) const;

    Matrix & operator+=( Matix const & other );

    :Matrix operator+( Matrix const & other ) const;
};
