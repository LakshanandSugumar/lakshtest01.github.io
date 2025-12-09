// outputs.c
// Flex Sensor Subsystem – ADC monitoring, band checking, and LED indication.

#define _XTAL_FREQ 16000000u

#include <xc.h>
#include <stdint.h>
#include <stdio.h>

#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/system/pins.h"   // IO_RF0_*, IO_RC0_*, IO_RB4_*
#include "mcc_generated_files/uart/uart1.h"
#include "mcc_generated_files/adc/adc.h"

/* ---------- helpers ---------- */

static inline void acq_us(uint16_t us)
{
    while (us--)
    {
        __delay_us(1);
    }
}

static inline adc_result_t adc_read_once(adc_channel_t ch)
{
    ADC_ChannelSelect(ch);
    acq_us(20); // raise if source impedance is high (50–200 us)
    ADC_ConversionStart();
    while (!ADC_IsConversionDone())
        ;
    return ADC_ConversionResultGet();
}

static inline adc_result_t median3(adc_result_t a, adc_result_t b, adc_result_t c)
{
    if (a > b)
    {
        adc_result_t t = a;
        a = b;
        b = t;
    }
    if (b > c)
    {
        adc_result_t t = b;
        b = c;
        c = t;
    }
    if (a > b)
    {
        adc_result_t t = a;
        a = b;
        b = t;
    }
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

/* ---------- button (RB4 active-low) ---------- */

static uint8_t btn_is_pressed(void)
{
    return (IO_RB4_GetValue() == 0);
}

// returns 1 on PRESS edge
static uint8_t btn_press_edge(uint8_t *last)
{
    uint8_t cur = btn_is_pressed();
    __delay_ms(20); // debounce
    cur = btn_is_pressed();

    uint8_t edge = (cur == 1u && *last == 0u) ? 1u : 0u;
    *last = cur;
    return edge;
}

/* ---------- configuration ---------- */

#define VREF_VOLTS   5.0f  // ADC reference (VDD). For printing only.
#define LED_BLINK_MS 40    // rapid blink period when out-of-band
#define HYST         0.01f // small hysteresis to reduce chatter
#define MIN_GAP      0.02f // keep upper >= lower + MIN_GAP

/* clamp helper */
static inline float clampf(float v, float lo, float hi)
{
    return (v < lo) ? lo : (v > hi) ? hi : v;
}

void main(void)
{
    SYSTEM_Initialize();

    const uint8_t  res     = ADC_ResolutionGet();        // e.g., 12
    const uint32_t adc_max = ((uint32_t)1u << res) - 1u; // 4095 @ 12-bit

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
        float volts = nor
