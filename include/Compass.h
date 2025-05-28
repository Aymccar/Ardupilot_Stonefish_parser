#include<rclcpp/rclcpp.hpp>
#include<sensor_msgs/msg/magnetic_field.hpp>
#include<std_msgs/msg/int32_multi_array.hpp>
#include<string>

#define publisher_msg_t std_msgs::msg::Int32MultiArray
#define subscriber_msg_t sensor_msgs::msg::MagneticField

class Compass : public rclcpp::Node{
public:
    Compass(std::string publisher_name, std::string subscriber_name);

private:

    void topic_callback(const subscriber_msg_t::SharedPtr msg) const;

    rclcpp::Publisher<publisher_msg_t>::SharedPtr publisher;
    rclcpp::Subscription<subscriber_msg_t>::SharedPtr subscriber;
};
