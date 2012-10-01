#ifndef ALGORITHMDESIGN_GAUSSIANPDF_H_
#define ALGORITHMDESIGN_GAUSSIANPDF_H_

#include <algorithm_design/matrix.h>

class GaussianPDF
{
protected:
    //! Storage for new samples
    std::vector<double> samples_;
    //! The mean of the samples
    std::vector<double> mean_;
    //! The covariance of the samples
    SymmetrixMatrix covariance_;

public:
    //! Default constructor
    GaussianPDF();

    //! Copy constructor
    GaussianPDF( GaussianPDF const & other );

    //! Save a given sample for processing
    /*!
     * Here, you can assume that all samples will have the same, non-statically-known size
     */
    void addSample( std::vector<double> const & sample )
    {
        samples_.push_back( sample );
    }

// =============================================================================================================================================
    //! Implement this function
    /*!
     * Calculate the mean of any samples added so far; store the result in "mean_"; return a const ref to "mean_"
     */
    std::vector<double> const & calculateMean();

// =============================================================================================================================================
    //! Implement this function
    /*!
     * Calculate the covariance of any samples added so far; store the result in "covariance_"; return a const ref to "covariance_"
     */
    SymmetricMatrix const & calculateCovariance();
};

#endif // ALGORITHMDESIGN_GAUSSIANPDF_H_
