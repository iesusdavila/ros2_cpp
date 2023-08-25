#include <rclcpp/rclcpp.hpp>
#include "example_interfaces/srv/set_bool.hpp"

class ClienteResetContNode : public rclcpp::Node {
    public:
        ClienteResetContNode() : Node("cliente_reset") {
            thread1_ = std::thread(std::bind(&ClienteResetContNode::callResetContador, this, true));

            RCLCPP_INFO(this->get_logger(), "Nodo del cliente inicializado correctamente");
        }

        void callResetContador(bool to_reset){
            auto cliente = this->create_client<example_interfaces::srv::SetBool>("reset_counter");
            while(!cliente->wait_for_service(std::chrono::seconds(3))){
                RCLCPP_INFO(this->get_logger(), "Esperando respuesta del servidor");               
            }

            auto request = std::make_shared<example_interfaces::srv::SetBool::Request>();
            request->data = to_reset;

            auto future = cliente->async_send_request(request);

            try{
                auto response = future.get();
                RCLCPP_INFO(this->get_logger(), "%d - %s", (int)response->success, response->message.c_str());               
            }catch(const std::exception& e){
                RCLCPP_INFO(this->get_logger(), "Llamada al servidor fallida");               
            }            
        }

    private:
        std::thread thread1_;
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ClienteResetContNode>());
    rclcpp::shutdown();
    return 0;
}