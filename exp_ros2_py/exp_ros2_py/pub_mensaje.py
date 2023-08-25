import rclpy
from rclpy.node import Node

from std_msgs.msg import String

# Clase que hereda de la clase Node para poder crear un nodo
class MinimalPublisher(Node):

    # funcion constructora de la clase
    def __init__(self):
        # nombre del nodo que vamos a crear
        super().__init__('mi_primer_publicador')
        # creacion de un publicador llamado hola_soy_publicador
        self.publisher_ = self.create_publisher(String, 'hola_soy_topic', 10)
        # periodo de cada cuanto publicara el mensaje
        timer_period = 0.5  # seconds
        # creamos un timer con un periodo establecido y con un callback cada vez que se ejecute
        self.timer = self.create_timer(timer_period, self.timer_callback)
        self.i = 0

    # funcion callback que se ejecutara cada vez que se mande a ejecutar el timer
    def timer_callback(self):
        # el publicador puede dar mensajes de tipo String
        msg = String()
        # definir el mensaje a enviar
        msg.data = 'Hola, soy un publicador y estoy aprendiendo a contar: %d' % self.i
        # publicar el mensaje creado
        self.publisher_.publish(msg)
        # publicar una informacion cada vez que el paquete vaya a ejecutarse
        self.get_logger().info('Publicando: "%s"' % msg.data)
        self.i += 1


def main(args=None):
    rclpy.init(args=args)

    minimal_publisher = MinimalPublisher()

    rclpy.spin(minimal_publisher)

    # Destrozar el nodo creado
    minimal_publisher.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()