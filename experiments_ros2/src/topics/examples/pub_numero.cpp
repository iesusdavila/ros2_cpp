#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/int32.hpp>

class PublisherNode : public rclcpp::Node {
    public:
        PublisherNode() : Node("number_publisher") {
            publisher_ = this->create_publisher<std_msgs::msg::Int32>("number", 10);
            timer_ = this->create_wall_timer(std::chrono::seconds(1), std::bind(&PublisherNode::publishNumber, this));
        }

    private:
        void publishNumber() {
            auto msg = std::make_unique<std_msgs::msg::Int32>();
            msg->data = number_;
            RCLCPP_INFO(this->get_logger(), "Publishing: %d", msg->data);
            publisher_->publish(std::move(msg));
        }

        rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr publisher_;
        rclcpp::TimerBase::SharedPtr timer_;
        int number_ = 3;
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<PublisherNode>());
    rclcpp::shutdown();
    return 0;
}