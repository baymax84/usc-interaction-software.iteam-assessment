#include <ros/ros.h>

#include <std_msgs/Float32.h>

typedef std_msgs::Float32 _TargetLevelMsg;
typedef std_msgs::Float32 _SensorMsg;
typedef std_msgs::Float32 _ControlMsg;

class ControllerNode
{
public:
    ros::NodeHandle nh_rel_;

    double output_min_;
    double output_max_;
    double gain_;

    boost::shared_ptr<ros::Rate> loop_rate_ptr_;
    ros::Subscriber sensor_sub_;
    ros::Subscriber target_level_sub_;
    ros::Publisher control_pub_;

    _TargetLevelMsg::ConstPtr target_level_ptr_;

    ControllerNode( ros::NodeHandle & nh )
    :
        nh_rel_( nh ),
        output_min_( -10 ),
        output_max_( 10 ),
        gain_( 0.5 )
    {
        double loop_rate;
        nh_rel_.param<double>( "loop_rate", loop_rate, 10 );
        loop_rate_ptr_ = boost::make_shared<ros::Rate>( loop_rate );

        nh_rel_.param<double>( "output_min", output_min_, output_min_ );
        nh_rel_.param<double>( "output_max", output_max_, output_max_ );
        nh_rel_.param<double>( "gain", gain_, gain_ );

        control_pub_ = nh_rel_.advertise<_ControlMsg>( "control", 1 );
        sensor_sub_ = nh_rel_.subscribe( "sensor", 1, &ControllerNode::sensorCB, this );
        target_level_sub_ = nh_rel_.subscribe( "target_level", 1, &ControllerNode::targetLevelCB, this );
    }

    void targetLevelCB( _TargetLevelMsg::ConstPtr const & msg )
    {
        target_level_ptr_ = msg;
    }

    void sensorCB( _SensorMsg::ConstPtr const & msg )
    {
        if( !target_level_ptr_ ) return;

        _ControlMsg control_msg;
        double control_value = gain_ * ( target_level_ptr_->data - msg->data );
        control_msg.data = control_value > output_max_ ? output_max_ : control_value < output_min_ ? output_min_ : control_value;
        control_pub_.publish( control_msg );
    }

    void spin()
    {
        while( ros::ok() )
        {
            ros::spinOnce();
            loop_rate_ptr_->sleep();
        }
    }
};

int main( int argc, char ** argv )
{
    ros::init( argc, argv, "controller_node" );
    ros::NodeHandle nh( "~" );

    ControllerNode controller_node( nh );
    controller_node.spin();
}
