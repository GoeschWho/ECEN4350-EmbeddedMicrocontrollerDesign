This is an example project that demonstrates how the uGFX library can be used on the PSoC 5 platform.
This demo assumes an ILI9341 display connected to the CY8CKIT-059 PSoC 5LP Prototyping Kit.

Wiring:

    PSoC   <--->   ILI9341
   ------------------------
    P2.0   <--->   Reset
    P2.3   <--->   D/C
    P2.4   <--->   MISO
    P2.5   <--->   MOSI
    P2.6   <--->   SCK
    P2.7   <--->   CS