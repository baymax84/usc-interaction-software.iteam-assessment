#include <ros/ros.h>

#include <std_msgs/Float32.h>

typedef std_msgs::Float32 _SensorMsg;
typedef std_msgs::Float32 _ControlMsg;

class DriverNode
{
public:
    ros::NodeHandle nh_rel_;
    boost::shared_ptr<ros::Rate> loop_rate_ptr_;
    ros::Publisher sensor_pub_;
    ros::Subscriber control_sub_;

    double internal_value_;
    double mass_;
    double velocity_;
    double damping_;

    _ControlMsg::ConstPtr control_value_ptr_;

    ros::Time last_update_time_;

    DriverNode( ros::NodeHandle & nh )
    :
        nh_rel_( nh ),
        internal_value_( 0 ),
        mass_( 5.0 ),
        velocity_( 0 ),
        damping_( 0.5 ),
        last_update_time_( 0 )
    {
        double loop_rate;
        nh_rel_.param<double>( "loop_rate", loop_rate, 10 );
        loop_rate_ptr_ = boost::make_shared<ros::Rate>( loop_rate );

        nh_rel_.param<double>( "initial_value", internal_value_, internal_value_ );
        nh_rel_.param<double>( "mass", mass_, mass_ );
        nh_rel_.param<double>( "velocity", velocity_, velocity_ );
        nh_rel_.param<double>( "damping", damping_, damping_ );

        std::cout << "set initial velocity to " << velocity_ << std::endl;

        sensor_pub_ = nh_rel_.advertise<_SensorMsg>( "sensor", 1 );
        control_sub_ = nh_rel_.subscribe( "control", 1, &DriverNode::controlCB, this );
    }

    void controlCB( _ControlMsg::ConstPtr const & msg )
    {
        control_value_ptr_ = msg;
    }

    double forceModel( _ControlMsg::ConstPtr const & control_value_ptr )
    {
        return 5 * ( 1 / ( 1 + powf( M_E, -control_value_ptr->data ) ) - 0.5 );
    }

    void spinOnce()
    {
        ros::Time now = ros::Time::now();

        if( !last_update_time_.isZero() )
        {
            double const dt = ( now - last_update_time_ ).toSec();
            double acceleration = 0;

            if( control_value_ptr_ )
            {
                acceleration = ( forceModel( control_value_ptr_ ) ) / mass_;
            }

            velocity_ += dt * ( acceleration - ( velocity_ * damping_ ) / mass_ );
            internal_value_ += velocity_ * dt + acceleration * pow( dt, 2 ) / 2.0;
        }

        last_update_time_ = now;

        _SensorMsg sensor_msg;
        sensor_msg.data = internal_value_;
        sensor_pub_.publish( sensor_msg );
    }

    void spin()
    {
        while( ros::ok() )
        {
            spinOnce();
            ros::spinOnce();
            loop_rate_ptr_->sleep();
        }
    }
};

int main( int argc, char ** argv )
{
    ros::init( argc, argv, "driver_node" );
    ros::NodeHandle nh( "~" );

    DriverNode driver_node( nh );
    driver_node.spin();
}
