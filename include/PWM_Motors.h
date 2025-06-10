#include<rclcpp/rclcpp.hpp>
#include<std_msgs/msg/float64_multi_array.hpp>
#include<std_msgs/msg/int32_multi_array.hpp>
#include<string>

#define publisher_msg_t std_msgs::msg::Float64MultiArray
#define subscriber_msg_t std_msgs::msg::Int32MultiArray

struct Polynom {
    Polynom(std::vector<double> coeffs){coeffs_ = coeffs;};
    double get(const double x) const {
        double sum = 0; 
        for (size_t i = 0; i<coeffs_.size(); i++){
            sum += coeffs_[i]*pow(x, i);
        } 
        return sum;
    };

    void set_coeff(std::vector<double> coeffs){coeffs_ = coeffs;};
    private :
    std::vector<double> coeffs_;
};


class PWM_Motor : public rclcpp::Node{
public:
    PWM_Motor(std::string publisher_name, std::string subscriber_name);

private:

    void topic_callback(const subscriber_msg_t::SharedPtr msg) const;

    rclcpp::Publisher<publisher_msg_t>::SharedPtr publisher;
    rclcpp::Subscription<subscriber_msg_t>::SharedPtr subscriber;

    double convert(const double x) const;

    struct Model {
        double left_thr = 1464;
        double right_thr = 1536;
        Polynom left_poly = Polynom({3.53471369e+02, -1.70338187e+00, 9.77097000e-04});
        Polynom right_poly = Polynom({-3.58875990e+03, 3.61986122e+00, -8.15865860e-04});
    } model;

};
