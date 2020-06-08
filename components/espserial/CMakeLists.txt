idf_component_register(SRCS "esp_serial.cpp"
                       INCLUDE_DIRS "include"
                       REQUIRES esp_common esp_event ros_sra20  
								vfs xtensa rosserial_esp32 logger)
