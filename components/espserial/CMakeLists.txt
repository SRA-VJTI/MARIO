idf_component_register(SRCS "esp_serial.cpp" "esp_serial_moveit.cpp"
                       INCLUDE_DIRS "include"
                       REQUIRES esp_common esp_event ros_sra19  
								vfs xtensa rosserial_esp32)
