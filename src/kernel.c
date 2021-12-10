/*
 * kernel.c
 * original: http://arjunsreedharan.org/post/82710718100/kernel-101-lets-write-a-kernel
*/


#include "kernel.h"
#include "screen.h"
#include "io.h"
#include "kb.h"
#include "simulation.h"

void wait_loop()
{
    for(int i = 0; i < sizeof(int); i++) {
        __asm__("PAUSE");
    }
}

void kmain(void) 
{
    kb_init();
    screen_init();
    simulation_init();

    screen_write_byte(0, 72, 0x00, Green, Black);
    screen_write_byte(0, 74, 0xFF, Green, Black);

    simulation_init_spaceship_glider();

    simulation_setup_viewport(1, 1, 78, 23);

    simulation_print();
    //simulation_debug();

    while(1) {
        // read KB status
        char status = port_byte_in(0x64);

        // KB has data to read
        while (status & (0x01)) {
            char data = port_byte_in(0x60);
            
            // N -> Next tick
            if (data == (0x31)) {
                simulation_tick();
                simulation_print();
                //simulation_debug();
            }

            // a -> Move viewport left
            if (data == (0x1E)) {
                simulation_move_viewport(-1, 0);
                simulation_print();
            }
            // d -> Move viewport right
            if (data == (0x20)) {
                simulation_move_viewport(1, 0);
                simulation_print();
            }
            // w -> Move viewport up
            if (data == (0x11)) {
                simulation_move_viewport(0, -1);
                simulation_print();
            }
            // s -> Move viewport down
            if (data == (0x1F)) {
                simulation_move_viewport(0, 1);
                simulation_print();
            }

            // r -> Reset simulation
            if (data == (0x13)) {
                simulation_setup_viewport(1, 1, 78, 23);
                simulation_init_spaceship_glider();
                simulation_print();
            }

            status = port_byte_in(0x64);
        }

        wait_loop();
    }

    return;
}