from setuptools import find_packages, setup

package_name = 'exp_ros2_py'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='irda',
    maintainer_email='iesusdavila@gmail.com',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'nodo_prueba = exp_ros2_py.nodo_prueba:main',
            'publicador = exp_ros2_py.pub_mensaje:main',
            'suscriptor = exp_ros2_py.sub_mensaje:main',
            'servidor = exp_ros2_py.srv_servidor:main',
            'cliente = exp_ros2_py.srv_cliente:main',
            'publicador_msg_custom = exp_ros2_py.pub_msg_custom:main',
        ],
    },
)
