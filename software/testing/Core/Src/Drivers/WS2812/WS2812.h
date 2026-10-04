#ifndef SRC_DRIVERS_WS2812_WS2812_H_
#define SRC_DRIVERS_WS2812_WS2812_H_

#include "stm32f4xx_hal.h"

// --- Color Table (Format: 0xRRGGBB) ---
#define COLOR_BLACK     0x000000
#define COLOR_WHITE     0xFFFFFF
    
#define COLOR_RED       0xFF0000
#define COLOR_GREEN     0x00FF00
#define COLOR_BLUE      0x0000FF
    
#define COLOR_YELLOW    0xFFFF00
#define COLOR_CYAN      0x00FFFF
#define COLOR_MAGENTA   0xFF00FF
#define COLOR_ORANGE    0xFF8000
#define COLOR_PURPLE    0x800080
#define COLOR_INDIGO    0x4B0082
#define COLOR_PINK      0xFFC0CB

// If ARR = 104:
//   Logic 0 (~32%): 35
//   Logic 1 (~64%): 80
#define WS2812_DUTY_0   35
#define WS2812_DUTY_1   80

typedef struct
{
    TIM_HandleTypeDef *htim;     // Pointer to Timer handle (e.g., &htim1)
    uint32_t TIM_CHANNEL;        // Timer Channel (e.g., TIM_CHANNEL_3)
    
    // Buffer: (LEDs * 24 bits) + 250 reset "zeros"
    // We use uint16_t because DMA usually transfers half-words for timers
    uint16_t pwmData[24 + 250];
    uint8_t brightness;          // Optional: Global brightness (0-255)
} WS2812_Handle_t;

// Function Prototypes
HAL_StatusTypeDef WS2812_Init(WS2812_Handle_t *led);
void WS2812_SetColor(WS2812_Handle_t *led, uint32_t color);
void WS2812_Clear(WS2812_Handle_t *led);
HAL_StatusTypeDef WS2812_Send(WS2812_Handle_t *led);

#endif /* SRC_DRIVERS_WS2812_WS2812_H_ */
