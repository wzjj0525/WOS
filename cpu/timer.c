#include <timer.h>
#include <util.h>
#include <ports.h>
#include <screen.h>
#include <string.h>
extern void int32();
u32int tick = 0;
void timer_callback(registers_t regs) {
    /*char ticks[20];
    tick++;
    kprint("tick:");
    int_to_ascii((u32int)tick, ticks);  //qemu crash
    //kprint("a\n");
    //return;
    print_at(ticks, -1, -1, 0x0f);     //bochs wrong
    //kprint("a");
    kprint("\n");*/

}
void init_timer(u32int f) {
    set_interrupt_handle(IRQ(0), timer_callback);
    u32int division = TIMER_FREQUENCY / f;
    outb(0x43, 0x36);
    //for (int i=0;i<1000000;i++);
    u8int l = division & 0xff;
    u8int h = (division & 0xff00) >> 8;
    outb(0x40, l);
    //for (int i=0;i<1000000;i++);
    outb(0x40, h);
}