#include"PWM_Motors.h"
#include<rclcpp/rclcpp.hpp>
#include<string>
#include<vector>

#define MOTOR_NUM 8 //TODO something more dynamic

using std::placeholders::_1;

PWM_Motor::PWM_Motor(std::string publisher_name, std::string subscriber_name):
    Node("PWM")
{
    publisher = this->create_publisher<publisher_msg_t>(publisher_name, 10);
    subscriber = this->create_subscription<subscriber_msg_t>(subscriber_name, 10, std::bind(&PWM_Motor::topic_callback, this, _1));
}

void PWM_Motor::topic_callback(const subscriber_msg_t::SharedPtr msg) const {
    double ret[MOTOR_NUM];

    for (size_t i = 0; i<MOTOR_NUM; i++){
        ret[i] = convert(msg->data[i]);
    }

    publisher_msg_t msg_;
    msg_.data = std::vector<double>(ret, ret + MOTOR_NUM);
    publisher->publish(msg_);
}

double PWM_Motor::convert(const double x) const {
    if (x < model.left_thr){
        return model.left_poly.get(x);
    } else if(x > model.right_thr){
        return model.right_poly.get(x);
    } else {
        return 0;
    }
}

int main(int argc, char** argv){
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<PWM_Motor>("/bluerov/controller/thruster_setpoints_sim", "PWM"));
    rclcpp::shutdown();
    return 0;
}
