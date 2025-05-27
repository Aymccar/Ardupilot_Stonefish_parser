#include<rclcpp/rclcpp.hpp>
#include<sensor_msgs/msg/fluid_pressure.hpp>
#include<std_msgs/msg/int32_multi_array.hpp>
#include<string>

#define publisher_msg_t std_msgs::msg::Int32MultiArray
#define subscriber_msg_t sensor_msgs::msg::FluidPressure

class Baro : public rclcpp::Node{
public:
    Baro(std::string publisher_name, std::string subscriber_name);

private:

    void topic_callback(const subscriber_msg_t::SharedPtr msg) const;

    rclcpp::Publisher<publisher_msg_t>::SharedPtr publisher;
    rclcpp::Subscription<subscriber_msg_t>::SharedPtr subscriber;
};
