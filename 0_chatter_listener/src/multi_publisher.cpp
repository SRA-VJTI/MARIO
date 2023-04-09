#include "rclcpp/rclcpp.hpp"

// Including ROS messages used
// Every Ros message has a type which provides utility to use different combination of data types which helps a lot in understanding data from a topic : Eg. IMU publishes RPY values but in ros it will publish a single message which have all RPY in the form of quaternion
#include "std_msgs/msg/string.hpp"
#include "geometry_msgs/msg/point.hpp"

// Will help us monitor the published message
#include "chrono" 

// This basically initializes the MultiplePublisher with a name through the function in the node class
using namespace std::chrono_literals;

// The current class is derived from the rclcpp class "Node" which provides utility to subscribe or publish any topic
class MultiplePublisher : public rclcpp::Node
{

    private:
        void timer_callback()
        {
            auto message = std_msgs::msg::String();
            message.data = "Hello_world!!" + std::to_string(count_++);
            // Current Published data
            RCLCPP_INFO(this->get_logger(), "Publishing message: %s", message.data.c_str());
            publisher_->publish(message);
        }

        void timer2_callback()
        {
            auto message2 = geometry_msgs::msg::Point();
            message2.x = (float)(count_++);
            // Current published data
            RCLCPP_INFO(this->get_logger(), "Publishing coordinate: %f", message2.x);
            publisher2_->publish(message2);
        
        }
        
        // Shared pointer allows to make multiple instances of respective data types in the scope of the program
        rclcpp::TimerBase::SharedPtr timer_; 
        rclcpp::TimerBase::SharedPtr timer2_;
        
        rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
        rclcpp::Publisher<geometry_msgs::msg::Point>::SharedPtr publisher2_;
        
        size_t count_;

    public:

         // This basically initializes the MultiplePublisher with a name through the function in the node class
        MultiplePublisher() : Node("first_talker") 
        {  
             // Note that all the undefined variables below are private variables
            publisher_ = this->create_publisher<std_msgs::msg::String>("topic1", 1);  // This is basically the type of message that we want to publish and to what topic with what type
            timer_ = this->create_wall_timer(500ms, std::bind(&MultiplePublisher::timer_callback,this)); // Attaches the current node with a timer
            // Note that all the undefined variables below are private variables
            publisher2_= this->create_publisher<geometry_msgs::msg::Point>("topic2", 10);
            timer2_ = this->create_wall_timer(500ms, std::bind(&MultiplePublisher::timer2_callback,this)); // Attaches the current node with a timer
        
        }

};

int main(int argc, char* argv[]){
    
    rclcpp::init(argc,argv);
    
    rclcpp::spin(std::make_shared<MultiplePublisher>());
    rclcpp::shutdown();
    
    return 0;
}