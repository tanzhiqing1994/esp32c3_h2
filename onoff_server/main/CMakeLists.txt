set(srcs "main.c"
    "board.c"
    "mesh_model.c"
    "bms.c"
    "uart_debug.c"
    "deep_sleep.c")

idf_component_register(SRCS "mesh_model.c" "uart_debug.c" "bms.c" "${srcs}"
                    INCLUDE_DIRS  ".")
