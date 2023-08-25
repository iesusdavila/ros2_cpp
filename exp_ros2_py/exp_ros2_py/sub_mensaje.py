import rclpy
from rclpy.node import Node

from std_msgs.msg import String

# Clase que hereda de la clase Node para poder crear un nodo
class MinimalSubscriber(Node):

    # funcion constructora de la clase
    def __init__(self):
        # nombre del nodo que vamos a crear
        super().__init__('mi_primer_suscriptor')
        # creacion de un suscriptor haciendo referencia al topic "hola_soy_topic" y usando funcion callback
        self.subscription = self.create_subscription(
            String,
            'hola_soy_topic',
            self.listener_callback,
            10)
        
        # especifica que es una suscripcion
        self.subscription  # prevent unused variable warning

    # Funcion callback que se ejecuta cada vez que se publica algo en el "topic hola_soy_topic"
    def listener_callback(self, msg):
        self.get_logger().info('Estoy escuchando... : "%s"' % msg.data)


def main(args=None):
    rclpy.init(args=args)

    minimal_subscriber = MinimalSubscriber()

    rclpy.spin(minimal_subscriber)

    # Destruir el nodo
    minimal_subscriber.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()