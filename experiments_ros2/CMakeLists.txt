cmake_minimum_required(VERSION 3.8)
project(experiments_ros2)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(example_interfaces REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

add_executable(talker src/topics/basic_publisher.cpp)
ament_target_dependencies(talker rclcpp std_msgs)

add_executable(listener src/topics/basic_suscriber.cpp)
ament_target_dependencies(listener rclcpp std_msgs)

add_executable(numero src/topics/examples/pub_numero.cpp)
ament_target_dependencies(numero rclcpp std_msgs)

add_executable(contador_ps src/topics/examples/cont_num.cpp)
ament_target_dependencies(contador_ps rclcpp std_msgs example_interfaces)

add_executable(servidor_suma src/services/servidor_suma_dos_numeros.cpp)
ament_target_dependencies(servidor_suma rclcpp example_interfaces)

add_executable(cliente_suma src/services/cliente_sumador_dos_numeros.cpp)
ament_target_dependencies(cliente_suma rclcpp example_interfaces)

add_executable(cliente_reset_cont src/services/examples/cliente_reset_contador.cpp)
ament_target_dependencies(cliente_reset_cont rclcpp example_interfaces)

install(TARGETS
  talker
  listener
  numero
  contador_ps
  servidor_suma
  cliente_suma
  cliente_reset_cont
  DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
