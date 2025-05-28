#include"Compass.h"
#include<rclcpp/rclcpp.hpp>
#include<string>
#include<vector>

using std::placeholders::_1;

Compass::Compass(std::string publisher_name, std::string subscriber_name):
    Node("Compass_parser")
{
    publisher = this->create_publisher<publisher_msg_t>(publisher_name, 10);
    subscriber = this->create_subscription<subscriber_msg_t>(subscriber_name, 10, std::bind(&Compass::topic_callback, this, _1));
}

void Compass::topic_callback(const subscriber_msg_t::SharedPtr msg) const {
    auto res = msg->magnetic_field;

    std::vector<int> ret;
    ret = {(int)res.x, (int)res.y, (int)res.z};

    publisher_msg_t msg_;
    msg_.data = {ret};
    publisher->publish(msg_);
}

int main(int argc, char** argv){
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Compass>("Compass", "bluerov/sensors/Compass"));
    rclcpp::shutdown();
    return 0;
}
