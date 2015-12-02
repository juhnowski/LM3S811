#include "sc.h"
#include "qpc.h"
#include "bsp.h"
#include "crc.h"
/**
http://www.ti.com/tool/sw-drl

*/
#define PART_LM3S811
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"

Q_DEFINE_THIS_FILE

static scd_uint8_t sc_buf[1024];
static char in_buf[1024];

void sc_send()
{
  //message for send
  scd_uint8_t *msg = "Hello world!";
  scd_int8_t msg_len = 12;
  
  //create SCA header
  SCAHeader sca_hdr;
    sca_hdr.source_address = 252U;  
    sca_hdr.dest_address = 251U;
    sca_hdr.total_length = 0U;
    sca_hdr.identification = 1U;
    sca_hdr.df = 0U;
    sca_hdr.mf = 0U;
    sca_hdr.res = 0U;
    sca_hdr.fragment_offset = 0U;
    sca_hdr.ttl = 2U;
    sca_hdr.protocol = 1U;
    sca_hdr.checksum = 0U;
    
  //create SCTP header
  SCTPHeader sctp_hdr;
    sctp_hdr.sca_header = sca_hdr;
    sctp_hdr.protocol = 1U;
    
  //create SCTPA header
  SCTPAHeader sctpa_hdr;
    sctpa_hdr.sctp_header = sctp_hdr;
    sctpa_hdr.ack = 0U;
    sctpa_hdr.psh = 0U;
    sctpa_hdr.rst = 0U;
    sctpa_hdr.syn = 0U;
    sctpa_hdr.fin = 0U;
    sctpa_hdr.res = 0x000U;
    sctpa_hdr.window = 1U;
    sctpa_hdr.source_port = 1U;
    sctpa_hdr.destination_port = 1U;
    sctpa_hdr.sequence_number = 1U;
    sctpa_hdr.acknowledgment_number = 1U;
    
    //create packet to send
    scd_int8_t cnt = 0;
    scd_uint8_t *ptr_sctpa_hdr = (scd_uint8_t *)&sctpa_hdr;
    while(cnt < sizeof(sctpa_hdr) ){
      sc_buf[cnt] = *(ptr_sctpa_hdr++);
      cnt++;
    }
    
    scd_int8_t end = cnt + msg_len;
    scd_int8_t i = 0;
    
    while(cnt < end ){
      sc_buf[cnt] = msg[i++];
      cnt++;
    }
    
    //fullfill chek variables: total_length and check_summ
    SCAHeader *sca = (SCAHeader *)&sc_buf;
    sca->total_length = cnt-1;
    scd_crc_t crc = gen_crc16(sc_buf, sizeof(sc_buf));
    sca->checksum = crc;
    
    /*from Stellaris Peripheral Driver Library User's Guide (spmu063.pdf) p.267*/

/** UART->USB->VCOM    
    long cThisChar;
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);//0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
  //  GPIOPinConfigure(GPIO_PA0_U0RX);
  //  GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200, //
                        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                         UART_CONFIG_PAR_NONE));
    
    for (int ii=0; ii<cnt; ii++){
      UARTCharPut(UART0_BASE, sc_buf[ii]);
    }

// echo 
    do
    {
        cThisChar = UARTCharGet(UART0_BASE); //
        UARTCharPut(UART0_BASE, cThisChar); //
    } while((cThisChar != '\n') && (cThisChar != '\r'));
*/
/*    
    long cThisChar;
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);//0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
  //  GPIOPinConfigure(GPIO_PA0_U0RX);
  //  GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTConfigSetExpClk(UART1_BASE, SysCtlClockGet(), 115200, //
                        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                         UART_CONFIG_PAR_NONE));
    
    for (int ii=0; ii<cnt; ii++){
      UARTCharPut(UART1_BASE, sc_buf[ii]);
    }
*/
    
    char cThisChar;

    //
    // Set the clocking to run directly from the external crystal/oscillator.
    // TODO: The SYSCTL_XTAL_ value must be changed to match the value of the
    // crystal on your board.
    //
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
                   SYSCTL_XTAL_16MHZ);

    //
    // Enable the peripherals used by this example.
    // The UART itself needs to be enabled, as well as the GPIO port
    // containing the pins that will be used.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1); //82:sysctl.h 
    SysCtlPeripheralEnable(U1RX_PERIPH);

    //
    // Configure the GPIO pin muxing for the UART function.
    // This is only necessary if your part supports GPIO pin function muxing.
    // Study the data sheet to see which functions are allocated per pin.
    // TODO: change this to select the port/pin you are using
    //
    //GPIOPinConfigure(GPIO_PA0_U0RX);
    //GPIOPinConfigure(GPIO_PA1_U0TX);

    //
    // Since GPIO A0 and A1 are used for the UART function, they must be
    // configured for use as a peripheral function (instead of GPIO).
    // TODO: change this to match the port/pin you are using
    //
    GPIOPinTypeUART(U1RX_PORT, U1RX_PIN | U1TX_PIN);

    //
    // Configure the UART for 115,200, 8-N-1 operation.
    // This function uses SysCtlClockGet() to get the system clock
    // frequency.  This could be also be a variable or hard coded value
    // instead of a function call.
    //
    UARTConfigSetExpClk(UART1_BASE, SysCtlClockGet(), 115200,
                        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                         UART_CONFIG_PAR_NONE));

    //
    // Put a character to show start of example.  This will display on the
    // terminal.
    //
    UARTCharPut(UART1_BASE, '!');

    //
    // Enter a loop to read characters from the UART, and write them back
    // (echo).  When a line end is received, the loop terminates.
    //
    do
    {
        //
        // Read a character using the blocking read function.  This function
        // will not return until a character is available.
        //
        cThisChar = UARTCharGet(UART1_BASE);

        //
        // Write the same character using the blocking write function.  This
        // function will not return until there was space in the FIFO and
        // the character is written.
        //
        UARTCharPut(UART1_BASE, cThisChar);

    //
    // Stay in the loop until either a CR or LF is received.
    //
    } while((cThisChar != '\n') && (cThisChar != '\r'));

    //
    // Put a character to show the end of the example.  This will display on
    // the terminal.
    //
    UARTCharPut(UART1_BASE, '@');

    
    return;
}

scd_err_t sc_recv(){
   SCTPAHeader *sctpa = (SCTPAHeader *)&sc_buf;
   scd_port_t port = sctpa->destination_port;
   scd_crc_t crc = sctpa->sctp_header.sca_header.checksum;
   sctpa->sctp_header.sca_header.checksum = 0U;
   return (crc == gen_crc16(sc_buf, sizeof(sc_buf)));
}