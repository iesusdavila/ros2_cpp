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
            'nodo_prueba = ros2_experimentos.nodo_prueba:main',
            'publicador = ros2_experimentos.pub_mensaje:main',
            'suscriptor = ros2_experimentos.sub_mensaje:main',
            'servidor = ros2_experimentos.srv_servidor:main',
            'cliente = ros2_experimentos.srv_cliente:main',
        ],
    },
)
