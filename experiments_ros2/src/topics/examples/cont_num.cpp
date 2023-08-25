#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/int32.hpp>
#include "example_interfaces/srv/set_bool.hpp"

using std::placeholders::_1;
using std::placeholders::_2;

class SubscriberNode : public rclcpp::Node {
    public:
        SubscriberNode() : Node("number_counter") {
            subscription_ = this->create_subscription<std_msgs::msg::Int32>("number", 10, std::bind(&SubscriberNode::callback, this, _1));
            publisher_ = this->create_publisher<std_msgs::msg::Int32>("number_count", 10);
            server_ = this->create_service<example_interfaces::srv::SetBool>(
                "reset_counter",
                std::bind(&SubscriberNode::callbackResetCounter, this, _1, _2));
        }

    private:
        void callback(const std_msgs::msg::Int32::SharedPtr msg) {
            auto sum_msg = std::make_unique<std_msgs::msg::Int32>();
            contador_ = contador_ + msg->data;
            sum_msg->data = contador_;
            RCLCPP_INFO(this->get_logger(), "Publicando contador... %d", sum_msg->data);
            publisher_->publish(std::move(sum_msg));
        }

        void callbackResetCounter(const example_interfaces::srv::SetBool::Request::SharedPtr request,
                              const example_interfaces::srv::SetBool::Response::SharedPtr response)
        {
            if (request->data)
            {
                contador_ = 0;
                response->success = true;
                response->message = "Contador reiniciado correctamente";
            }
            else
            {
                response->success = false;
                response->message = "Contador no pudo ser reiniciado";
            }
        }

        rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr subscription_;
        rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr publisher_;
        int contador_ = 0;
        rclcpp::Service<example_interfaces::srv::SetBool>::SharedPtr server_;
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<SubscriberNode>());
    rclcpp::shutdown();
    return 0;
}