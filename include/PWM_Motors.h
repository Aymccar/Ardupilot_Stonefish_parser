#include<rclcpp/rclcpp.hpp>
#include<std_msgs/msg/float64_multi_array.hpp>
#include<std_msgs/msg/int32_multi_array.hpp>
#include<string>

#define publisher_msg_t std_msgs::msg::Float64MultiArray
#define subscriber_msg_t std_msgs::msg::Int32MultiArray

class PWM_Motor : public rclcpp::Node{
public:
    PWM_Motor(std::string publisher_name, std::string subscriber_name);

private:

    void topic_callback(const subscriber_msg_t::SharedPtr msg) const;

    rclcpp::Publisher<publisher_msg_t>::SharedPtr publisher;
    rclcpp::Subscription<subscriber_msg_t>::SharedPtr subscriber;
};
