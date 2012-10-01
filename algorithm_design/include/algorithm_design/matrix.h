#ifndef ALGORITHMDESIGN_MATRIX_H_
#define ALGORITHMDESIGN_MATRIX_H_

#include <vector>

class Matrix
{
protected:
    //! Storage for all elements
    std::vector<double> data_;
    //! Number of rows; same as height
    unsigned int rows_;
    //! Number of cols; same as width
    unsigned int cols_;

public:
    //! Empty constructor
    Matrix();

    //! Copy constructor
    Matrix( Matrix const & other );

    //! Construct given number of rows and cols; total required storage is rows * cols
    Matrix( unsigned int const & rows, unsigned int const & cols )
    :
        rows_( rows ),
        cols_( cols ),
        data_( rows * cols )
    {
        //
    }

    //! Get a read/write reference to the element at the given row+col
    double & at( unsigned int const & row, unsigned int const & col );
};

class SquareMatrix : public Matrix
{
public:

    //! Default constructor
    SquareMatrix();

    //! Copy constructor; forward to base since we have no members
    SquareMatrix( SquareMatrix const & other )
    :
        Matrix( other )
    {
        //
    }

    //! Size constructor; the purpose for this class; set rows and cols in base to size (definition of a square matrix)
    SquareMatrix( unsigned int const & size )
    :
        Matrix( size, size )
    {
        //
    }
};

class SymmetricMatrix : public SquareMatrix
{
public:

    //! Default constructor
    SymmetricMatrix();

    //! Copy constructor
    SymmetricMatrix( SymmetricMatrix const & other );

// =============================================================================================================================================
    //! Implement this function
    /*!
     * Construct a (size x size) SymmetricMatrix

     * Your implementation may be either an upper-symmetric or lower-symmetric matrix; for example, say your matrix is:

        3 7 4
        7 0 3
        4 3 9

       your final representation must not store any redundant information, ie:

        3 7 4
        . 0 3
        . . 9

       or:

        3 . .
        7 0 .
        4 3 9

     * This means that you cannot use the constructor Matrix::Matrix( row, col ) or SquareMatrix::SquareMatrix( size ), as both would allocate too many elements;
     *   in the above example, this would result in allocation of 9 elements rather than the ideal 6.
     */
    SymmetricMatrix( unsigned int const & size ) ...

// =============================================================================================================================================
    //! Implement this function
    /*!
     * Get a read/write reference to the element at the given row + col

     * Your implementation must transparently provide the usual row/column access (ie "at( 2, 1 )" and "at( 1, 2 )" must both return a reference to the same element)
     */
    double & at( unsigned int const & row, unsigned int const & col ) ...
};

#endif // ALGORITHMDESIGN_MATRIX_H_
