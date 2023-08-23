#include <rclcpp/rclcpp.hpp>
#include "example_interfaces/srv/set_bool.hpp"

class ServidorResetContNode : public rclcpp::Node {
    public:
        ServidorResetContNode() : Node("servidor_reset") {
            server_ = this->create_service<example_interfaces::srv::SetBool>(
                "set_reset",
                std::bind(&ServidorResetContNode::callbackSumadorDosNumeros, this, std::placeholders::_1,std::placeholders::_2)
            );
            RCLCPP_INFO(this->get_logger(), "Nodo del servidor inicializado correctamente");
        }

    private:
        void callbackSumadorDosNumeros(const example_interfaces::srv::SetBool::Request::SharedPtr request,
                                       const example_interfaces::srv::SetBool::Response::SharedPtr response){
            response->success=request->data;
            RCLCPP_INFO(this->get_logger(), "Resetear contador: %d", (int)response->success);   
        }

        rclcpp::Service<example_interfaces::srv::SetBool>::SharedPtr server_;
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ServidorResetContNode>());
    rclcpp::shutdown();
    return 0;
}