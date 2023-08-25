from example_interfaces.srv import AddTwoInts

import rclpy
from rclpy.node import Node

# Clase que hereda de la clase Node para poder crear un nodo
class MinimalService(Node):

    # funcion constructora de la clase
    def __init__(self):
        # nombre del nodo que vamos a crear
        super().__init__('mi_primer_srv_servidor')
        # creacion de un servicio-servidor llamado mi_primer_servicio que ejecuta un callback cada vez que se hace una peticion
        self.srv = self.create_service(AddTwoInts, 'mi_primer_servicio', self.add_two_ints_callback)

    # funcion que se ejecuta cada vez que se realiza una peticion
    def add_two_ints_callback(self, request, response):
        response.sum = request.a + request.b
        self.get_logger().info('Recibiendo la peticion\na: %d b: %d' % (request.a, request.b))

        return response

def main():
    rclpy.init()

    minimal_service = MinimalService()

    rclpy.spin(minimal_service)

    rclpy.shutdown()

if __name__ == '__main__':
    main()