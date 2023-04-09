#include "rclcpp/rclcpp.hpp"

// Including ROS messages used
// Every Ros message has a type which provides utility to use different combination of data types which helps a lot in understanding data from a topic : Eg. IMU publishes RPY values but in ros it will publish a single message which have all RPY in the form of quaternion
#include "std_msgs/msg/string.hpp"
#include "geometry_msgs/msg/point.hpp"

// Will help us monitor the published message
#include "chrono" 

// This basically initializes the MultipleSubscriber with a name through the function in the node class
using namespace std::chrono_literals;

// Placeholder to bind subsciber and subscriber 
using std::placeholders::_1;

// The current class is derived from the rclcpp class "Node" which provides utility to subscribe or publish any topic
class MultipleSubscriber : public rclcpp::Node
{

    private:

        void topic_callback(const std_msgs::msg::String & msg) 
        {
            // Current published data 
            RCLCPP_INFO(this->get_logger(), "Subscribing message: %s", msg.data.c_str());

        }

        void topic2_callback(const geometry_msgs::msg::Point & msg)
        {
            // Current published data
            RCLCPP_INFO(this->get_logger(), "Publishing coordinate: %f",msg.x);

        }
        
        rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscriber_;
        rclcpp::Subscription<geometry_msgs::msg::Point>::SharedPtr subscriber2_;
        
    public:

         // This basically initializes the MultipleSubscriber with a name through the function in the node class
        MultipleSubscriber() : Node("first_listener") 
        {  
             // Note that all the undefined variables below are private variables
            subscriber_ = this->create_subscription<std_msgs::msg::String>(
            "topic1", 10, std::bind(&MultipleSubscriber::topic_callback, this, _1));  // This is basically the type of message that we want to publish and to what topic with what type
            
            // Note that all the undefined variables below are private variables
            subscriber2_ = this->create_subscription<geometry_msgs::msg::Point>(
            "topic2", 10, std::bind(&MultipleSubscriber::topic2_callback, this, _1));
        
        }

};

int main(int argc, char* argv[]){
    
    rclcpp::init(argc,argv);
    // Running the Node in the loop
    rclcpp::spin(std::make_shared<MultipleSubscriber>());   
    rclcpp::shutdown();
    
    return 0;
}