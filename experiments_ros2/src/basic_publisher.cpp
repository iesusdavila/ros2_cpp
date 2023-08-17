#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

// El publicador siempre hereda del rclcpp::Node
class MinimalPublisher : public rclcpp::Node
{
  // Todo lo referente a this hace referencia al nodo
  public:
    MinimalPublisher() : Node("minimal_publisher"), count_(0){
      publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);
      // Se publicara cada 2 veces por segundo (500ms = 0.5s => f=1/T=1/0.5=2)
      timer_ = this->create_wall_timer(500ms, std::bind(&MinimalPublisher::timer_callback, this));
    }

  private:
    void timer_callback(){
      // El tipo de mensaje a enviar sera String
      auto message = std_msgs::msg::String();
      message.data = "Hola, soy un publicador " + std::to_string(count_++);
      RCLCPP_INFO(this->get_logger(), "Publicando...: '%s'", message.data.c_str());
      publisher_->publish(message);
    }

    // Declarar los campos de temporizador, editor y contador.
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    size_t count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}