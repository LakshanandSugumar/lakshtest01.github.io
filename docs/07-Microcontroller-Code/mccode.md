**Microcontroller Code**

#define \_XTAL_FREQ 16000000u
#include <xc.h>
#include <stdint.h>
#include <stdio.h>

#include "mcc*generated_files/system/system.h"
#include "mcc_generated_files/system/pins.h" // IO_RF0*_, IO*RC0*_, IO*RB4*\*
#include "mcc_generated_files/uart/uart1.h"
#include "mcc_generated_files/adc/adc.h"

/_ ---------- helpers ---------- _/
static inline void acq_us(uint16_t us){ while(us--) \_\_delay_us(1); }

static inline adc_result_t adc_read_once(adc_channel_t ch)
{
ADC_ChannelSelect(ch);
acq_us(20); // raise if source impedance is high (50–200 us)
ADC_ConversionStart();
while(!ADC_IsConversionDone());
return ADC_ConversionResultGet();
}

static inline adc_result_t median3(adc_result_t a, adc_result_t b, adc_result_t c)
{
if (a > b){ adc_result_t t=a; a=b; b=t; }
if (b > c){ adc_result_t t=b; b=c; c=t; }
if (a > b){ adc_result_t t=a; a=b; b=t; }
return b;
}

static adc_result_t adc_read_stable_ra0(void)
{
(void)adc_read_once(ADC_CHANNEL_ANA0); // discard first (channel residue)
adc_result_t s1 = adc_read_once(ADC_CHANNEL_ANA0);
adc_result_t s2 = adc_read_once(ADC_CHANNEL_ANA0);
adc_result_t s3 = adc_read_once(ADC_CHANNEL_ANA0);
return median3(s1, s2, s3);
}

/_ ---------- button (RB4 active-low) ---------- _/
static uint8_t btn_is_pressed(void){ return (IO_RB4_GetValue() == 0); }

static uint8_t btn_press_edge(uint8_t \*last) // returns 1 on PRESS edge
{
uint8_t cur = btn_is_pressed();
\_\_delay_ms(20); // debounce
cur = btn_is_pressed();

    uint8_t edge = (cur == 1u && *last == 0u) ? 1u : 0u;
    *last = cur;
    return edge;

}

/_ ---------- configuration ---------- _/
#define VREF_VOLTS 5.0f // ADC reference (VDD). For printing only.
#define LED_BLINK_MS 40 // rapid blink period when out-of-band
#define HYST 0.01f // small hysteresis to reduce chatter
#define MIN_GAP 0.02f // keep upper >= lower + MIN_GAP

/_ clamp helper _/
static inline float clampf(float v, float lo, float hi){
return (v < lo) ? lo : (v > hi) ? hi : v;
}

void main(void)
{
SYSTEM_Initialize();

    const uint8_t  res     = ADC_ResolutionGet();               // e.g., 12
    const uint32_t adc_max = ((uint32_t)1u << res) - 1u;        // 4095 @ 12-bit

    // Band on normalized value (0.0–1.0)
    float lower = 0.30f;
    float upper = 0.70f;

    printf("\r\nADC monitor (res=%u-bit). Normalized range = [%.2f, %.2f]\r\n",
           res, lower, upper);

    uint8_t last_btn = btn_is_pressed();

    while (1)
    {
        /* --- sample --- */
        adc_result_t raw = adc_read_stable_ra0();

        // normalized 0..1 using native full-scale
        float norm = (float)raw / (float)adc_max;
        norm = clampf(norm, 0.0f, 1.0f);

        // voltage print (for human sanity)
        float volts = norm * VREF_VOLTS;

        printf("RAW=%u  V=%.2f  norm=%.3f  band=[%.2f, %.2f]\r\n",
               (unsigned)raw, (double)volts, (double)norm, (double)lower, (double)upper);

        /* --- out-of-band detection with a hint of hysteresis --- */
        uint8_t too_low  = (norm < (lower - HYST));
        uint8_t too_high = (norm > (upper + HYST));
        uint8_t fault    = (too_low || too_high);

        /* --- calibration via RB4 press (only when actually out-of-band) --- */
        if (btn_press_edge(&last_btn) && fault)
        {
            if (too_high) {
                // If > upper (e.g., 0.90), make this the new upper and pull lower to 0.50
                upper = clampf(norm, 0.0f, 1.0f);
                lower = 0.50f;
                if (upper < lower + MIN_GAP) upper = clampf(lower + MIN_GAP, 0.0f, 1.0f);
                printf("CAL: new upper=%.3f, lower pulled to 0.50\r\n", (double)upper);
            } else {
                // If < lower (e.g., 0.00), make this the new lower and pull upper to 0.50
                lower = clampf(norm, 0.0f, 1.0f);
                upper = 0.50f;
                if (lower > upper - MIN_GAP) lower = clampf(upper - MIN_GAP, 0.0f, 1.0f);
                printf("CAL: new lower=%.3f, upper pulled to 0.50\r\n", (double)lower);
            }
        }

        /* --- indicate state --- */
        if (fault) {
            // Rapid blink BOTH RF0 and RC0 while out-of-band
            IO_RF0_Toggle();
            IO_RC0_Toggle();
            __delay_ms(LED_BLINK_MS);
        } else {
            // In-band → both off
            IO_RF0_SetLow();
            IO_RC0_SetLow();
            __delay_ms(120);
        }
    }

}
