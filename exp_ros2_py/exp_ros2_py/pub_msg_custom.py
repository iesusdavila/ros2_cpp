import rclpy
from rclpy.node import Node

from custom_interfaces.msg import MsgNuevo                     


class MinimalPublisher(Node):

    def __init__(self):
        super().__init__('publicador_msg_personalizado')
        self.publisher_ = self.create_publisher(MsgNuevo, 'topic_msg_pers', 10) 
        timer_period = 0.5
        self.timer = self.create_timer(timer_period, self.timer_callback)
        self.i = 0

    def timer_callback(self):
        msg = MsgNuevo()                                                
        msg.num = self.i                                           
        self.publisher_.publish(msg)
        self.get_logger().info('Publicando: "%d"' % msg.num)       
        self.i += 1


def main(args=None):
    rclpy.init(args=args)

    minimal_publisher = MinimalPublisher()

    rclpy.spin(minimal_publisher)

    minimal_publisher.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()