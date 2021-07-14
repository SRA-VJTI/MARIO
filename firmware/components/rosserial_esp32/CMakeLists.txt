idf_component_register(SRCS "duration.cpp"
                            "time.cpp"
                            "esp_ros_wifi.c"
                    INCLUDE_DIRS "include"
                    REQUIRES vfs nvs_flash sra-board-component)
    