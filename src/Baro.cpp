#include"Baro.h"
#include<rclcpp/rclcpp.hpp>
#include<string>
#include<vector>

using std::placeholders::_1;

Baro::Baro(std::string publisher_name, std::string subscriber_name):
    Node("Baro")
{
    publisher = this->create_publisher<publisher_msg_t>(publisher_name, 10);
    subscriber = this->create_subscription<subscriber_msg_t>(subscriber_name, 10, std::bind(&Baro::topic_callback, this, _1));
}

void Baro::topic_callback(const subscriber_msg_t::SharedPtr msg) const {
    float ret;

    ret = msg->fluid_pressure + 1e5; //ADD the air pressure

    publisher_msg_t msg_;
    msg_.data = {ret};
    publisher->publish(msg_);
}

int main(int argc, char** argv){
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Baro>("Baro", "/bluerov/sensors/Baro"));
    rclcpp::shutdown();
    return 0;
}
