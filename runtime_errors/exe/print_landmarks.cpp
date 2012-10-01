#include <runtime_errors/landmark.h>
#include <vector>
#include <iostream>

int main()
{
    std::vector<Landmark> landmarks;
    landmarks.reserve( 6 );

    Landmark buoy1( 11.0, 3.1, 0.0, "buoy", 0 );
    Landmark buoy2( 11.5, 3.0, 0.0, "buoy", 1 );
    Landmark buoy3( 10.5, 2.9, 0.0, "buoy", 2 );

    Landmark gate( 4.0, 2.5, 0.14, "gate" );

    Landmark pipe1( 6.0, 2.0, 0.2, "pipe", 0 );
    Landmark pipe2( 14.0, 3.0, 0.3, "pipe", 1 );

    // add all landmarks to "landmarks" in the order they were defined above
    landmarks.push_back( buoy1 );
    landmarks[1] = buoy2;
    *landmarks.begin() = buoy3;
    landmarks.back() = gate;
    landmarks.at( 3 ) = pipe1;
    landmarks.insert( landmarks.begin(), pipe2 );

    // for everything below this line, assume the landmarks have all been added to "landmarks" correctly

    // print all the landmarks
    {
        unsigned int i = 0;
        while( i <= landmarks.size() )
        {
            Landmark landmark = *( landmarks.begin() + i );
            std::cout << landmark.toString() << std::endl;
        }
    }

    // print all the landmarks
    {
        std::vector<Landmark>::iterator landmarks_it = landmarks.begin();
        while( landmarks_it != landmarks.end() )
        {
            std::cout << landmarks_it->toString() << std::endl;

            ++landmarks_it;
        }
    }

    // print all the landmarks
    {
        for( Landmark * landmark_ptr = &landmarks[0]; landmark_ptr != &landmarks[landmarks.size()]; ++landmark_ptr )
        {
            std::cout << landmark_ptr->toString() << std::endl;
        }
    }

    return 0;
}
