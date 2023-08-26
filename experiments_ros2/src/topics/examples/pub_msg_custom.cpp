#include <chrono>
#include <memory>
#include <rclcpp/rclcpp.hpp>
#include "custom_interfaces/msg/msg_nuevo.hpp"

class PublisherNode : public rclcpp::Node
{
public:
  PublisherNode()
    : Node("custom_publisher")
  {
    publisher_ = this->create_publisher<custom_interfaces::msg::MsgNuevo>("custom_topic", 10);

    timer_ = this->create_wall_timer(
      std::chrono::milliseconds(1000),
      std::bind(&PublisherNode::publishMessage, this));
  }

private:
  void publishMessage()
  {
    auto message = custom_interfaces::msg::MsgNuevo();
    message.num = number_++;

    RCLCPP_INFO(this->get_logger(), "Publicando: campo num = '%d'",(int)message.num);

    publisher_->publish(message);
  }

  rclcpp::Publisher<custom_interfaces::msg::MsgNuevo>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
  int number_ = 0;
};

int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<PublisherNode>());
  rclcpp::shutdown();
  return 0;
}
