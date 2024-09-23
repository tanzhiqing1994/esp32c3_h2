set(srcs "main.c"
        "board.c"
        "uart_debug.c"
        "mesh_model.c"
        "bms.c"
        "rtc_wake_stub_example.c"
      )

idf_component_register(SRCS "rtc_wake_stub_example.c" "bms.c" "uart_debug.c" "mesh_model.c" "${srcs}"
                    INCLUDE_DIRS  ".")
