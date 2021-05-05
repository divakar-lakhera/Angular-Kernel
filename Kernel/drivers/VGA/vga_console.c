/* 
    vga_console.c
    Basic 25x80 BIOS VGA Textmode Controller
    Written By: Divakar Lakhera
*/
#include "../../headers/angular-kernel.h"

#define BIOS_VGA_CONTROLLER_TEXT  (unsigned short *)0xB8000    
#define CRT_CONTROL_REG 0x3D4
#define CRT_DATA_REG 0x3D5
u8int STATE_READY=0; // 0: Not_Ready (Maybe in Higher Graphics mode or System Not Ready) 1: Ready
int index_x=0;
int index_y=0;
int foregroundColour=0;
int backgroundColour=0;
int attribute=0x0F;

u8int isReady(){
    // Will need these functions when MultiTasking is implimented
    return STATE_READY;
}

u8int trySetVGATextState(u8int state){
    STATE_READY=state;
    return 0;
}

void VGATextSetColor(u8int fg, u8int bg){
    foregroundColour=fg;
    backgroundColour=bg;
    attribute=(bg<<4)|(bg&0x0F);
    return;
}

void VGATextUpdateCursor(){
    unsigned linerAddress=(index_y*80)+index_x;
    outb(CRT_CONTROL_REG,14);
    outb(CRT_DATA_REG,linerAddress>>8);
    outb(CRT_CONTROL_REG,15);
    outb(CRT_DATA_REG,linerAddress);
    return;
}

void VGATextScroll(void)
{
    unsigned blank, temp;

    /* A blank is defined as a space... we need to give it
    *  backcolor too */
    blank = 0x20 | (attribute << 8);

    /* Row 25 is the end, this means we need to scroll up */
    if(index_y >= 25)
    {
        /* Move the current text chunk that makes up the screen
        *  back in the buffer by a line */
        temp = index_y- 25 + 1;
        memcpy (BIOS_VGA_CONTROLLER_TEXT, BIOS_VGA_CONTROLLER_TEXT + temp * 80, (25 - temp) * 80 * 2);

        /* Finally, we set the chunk of memory that occupies
        *  the last line of text to our 'blank' character */
        memsetw (BIOS_VGA_CONTROLLER_TEXT + (25 - temp) * 80, blank, 80);
        index_y = 25 - 1;
    }
}


void VGATextClearScreen(){
    if(!isReady()){
        if(trySetVGATextState(1)){
            VGATextClearScreen();
            return;
        }
        else{
            // TODO
            // panic(); // KERNEL PANIC: Unable To Start VGA Controller
        }
    }
    unsigned bufChar=0x20|(attribute<<8); // Higher 8 Bits Attribute, Lower 8 character
    for(int i=0;i<25;i++)
        memsetw(BIOS_VGA_CONTROLLER_TEXT+(i*80),bufChar,80);
    index_x=0;
    index_y=0;
    VGATextUpdateCursor();
    return;
}

void VGATextPutch(char ch){
    // TODO:
    // Sanitation Check
    u16int atrib=attribute<<8;
    u16int *linearindex;
    if(ch>=' '){
        linearindex=BIOS_VGA_CONTROLLER_TEXT+(index_y*80)+index_x;
        *linearindex=ch|atrib;  // Lower 8 char upper 8 attrib
        index_x++;
    }
    else if(ch==0x08){
        if(index_x!=0){
            index_x--;
            linearindex-BIOS_VGA_CONTROLLER_TEXT+(index_y*80)+index_x;
            *linearindex=' '|atrib;
        }
    }
    else if(ch==0x09){
        index_x = (index_x + 8) & ~(8 - 1);
    }
    else if(ch=='\n')
    {
        index_x=0;
        index_y++;
    }
    else if(ch=='\r'){
        index_x=0;
    }
    if(index_x>80){
        index_x=0;
        index_y++;
    }
    VGATextUpdateCursor();
    VGATextScroll();
}

void kprintf (const char *format, ...)
{
    char **arg = (char **) &format;
    char *p;
    int c;
    unsigned colour;
    char buf[20];
    
    arg++;

    while ((c = *format++) != 0)
    {
    if (c != '%')
        VGATextPutch(c);
    else
        {
        c = *format++;
        switch (c)
            {
            case 'd':
            case 'u':
            case 'x':
            itoa (buf, c, *((int *) arg++));
            p = buf;
            goto string;
            break;

            case 's':
            p = *arg++;
            if (! p)
                p = "(null)";

            string:
            while (*p)
                VGATextPutch(*p++);
            break;

            default:
            VGATextPutch(*((int *) arg++));
            break;
            }
        }
    }
    return;
}