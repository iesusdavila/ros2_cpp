#include <rclcpp/rclcpp.hpp>
#include "example_interfaces/srv/add_two_ints.hpp"

class ClienteSumaNode : public rclcpp::Node {
    public:
        ClienteSumaNode() : Node("cliente_suma") {
            thread1_ = std::thread(std::bind(&ClienteSumaNode::callSumadorDosNumeros, this, 105, 95));
        }

        void callSumadorDosNumeros(int a, int b){
            auto cliente = this->create_client<example_interfaces::srv::AddTwoInts>("sumador_dos_enteros");
            while(!cliente->wait_for_service(std::chrono::seconds(3))){
                RCLCPP_INFO(this->get_logger(), "Esperando respuesta del servidor");               
            }

            auto request = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
            request->a = a;
            request->b = b;

            auto future = cliente->async_send_request(request);

            try{
                auto response = future.get();
                RCLCPP_INFO(this->get_logger(), "%d + %d = %d", a, b, (int)response->sum);               
            }catch(const std::exception& e){
                RCLCPP_INFO(this->get_logger(), "Llamada al servidor fallida");               
            }            
        }

    private:
        std::thread thread1_;
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ClienteSumaNode>());
    rclcpp::shutdown();
    return 0;
}