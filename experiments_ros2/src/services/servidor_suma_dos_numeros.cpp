#include <rclcpp/rclcpp.hpp>
#include "example_interfaces/srv/add_two_ints.hpp"

class ServidorSumaNode : public rclcpp::Node {
    public:
        ServidorSumaNode() : Node("servidor_suma") {
            server_ = this->create_service<example_interfaces::srv::AddTwoInts>(
                "sumador_dos_enteros",
                std::bind(&ServidorSumaNode::callbackSumadorDosNumeros, this, std::placeholders::_1,std::placeholders::_2)
            );
            RCLCPP_INFO(this->get_logger(), "Nodo del servidor inicializado correctamente");
        }

    private:
        void callbackSumadorDosNumeros(const example_interfaces::srv::AddTwoInts::Request::SharedPtr request,
                                       const example_interfaces::srv::AddTwoInts::Response::SharedPtr response){
            response->sum=request->a + request->b;
            RCLCPP_INFO(this->get_logger(), request->a + " + " + request->b);   
            RCLCPP_INFO(this->get_logger(), "La suma es " + response->sum);   
        }

        rclcpp::Service<example_interfaces::srv::AddTwoInts>::SharedPtr server_;
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ServidorSumaNode>());
    rclcpp::shutdown();
    return 0;
}