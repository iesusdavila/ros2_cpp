import sys

from example_interfaces.srv import AddTwoInts
import rclpy
from rclpy.node import Node

# Clase que hereda de la clase Node para poder crear un nodo
class MinimalClientAsync(Node):

    # funcion constructora de la clase
    def __init__(self):
        # nombre del nodo que vamos a crear
        super().__init__('mi_primer_srv_cliente')
        # creacion de un servicio-cliente que llama al servicio mi_primer_servicio
        self.cli = self.create_client(AddTwoInts, 'mi_primer_servicio')
        # ejecutar un mensaje en caso que la espera sea mayor a 1 segundo
        while not self.cli.wait_for_service(timeout_sec=1.0):
            self.get_logger().info('Servicio no disponible, siga esperando por favor...')
        # enviar peticion al servidor del servicio   
        self.req = AddTwoInts.Request()

    # funcion que envia la peticion al servidor del servicio
    def send_request(self, a, b):
        # enviar como parametros al servicio tanto a como b
        self.req.a = a
        self.req.b = b
        self.future = self.cli.call_async(self.req)
        rclpy.spin_until_future_complete(self, self.future)
        # obtener el valor que lo trae el servidor del servicio
        return self.future.result()


def main():
    rclpy.init()

    minimal_client = MinimalClientAsync()
    # obtener los numeros que se pasan como parametros
    response = minimal_client.send_request(int(sys.argv[1]), int(sys.argv[2]))
    minimal_client.get_logger().info(
        'Resultado de la suma de %d + %d = %d' %
        (int(sys.argv[1]), int(sys.argv[2]), response.sum))

    # destruir nodo
    minimal_client.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()