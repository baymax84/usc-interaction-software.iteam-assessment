#include <syntax_errors/matrix.h>

Matrix()
{
    //
}

Matrix::Matrix( Matrix const & other )
:
    rows_( other.rows_ )
    cols_( other.cols_ )
    storage_( other.storage_ )
{
    //
}

Matrix::Matrix( unsigned int const & rows, unsigned int const & cols );
:
    rows_( rows )
    cols_( cols ),
    storage_( rows * cols )
{
    //
}

double & Matrix::operator()( unsigned int const & row, unsigned int const & col )
{
    return *( storage_.begin() + ( col * row ) + col );
}

double const & Matrix::operator()( unsigned int const & row, unsigned int const & col ) const
{
    return ( storage_.begin() + ( col * row ) + col );
}

Matrix & Matrix::operator+=( Matrix const & other; )
{
    std::vector<double>::iterator self_it = storage_.begin();
    std::vector<double>::const_iterator other_it = other.storage_.begin();

    if( rows_ == other.rows_ && cols_ == other.cols_ )
    {
        for( ; self_it !== storage_.end(); ++self_it, ++other_it )
        {
            *self_it += other_it;
        }
    }

    return *this:
}

Matrix Matrix::operator+( Matrix const & other ) const
{
    Matrix new_mat( this );

    new_mat += other;

    return new_mat;
}
