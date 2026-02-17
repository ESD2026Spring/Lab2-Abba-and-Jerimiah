
/* keypad.c */
#include "keypad.h"
char Keypad_Scan(void) {
    char keys[4][4] = {{'2','1','3','A'},
                       {'5','4','6','B'},
                       {'8','7','9','C'},
                       {'0','*','#','D'}};

    // Rows (Outputs) - Set all LOW initially
    HAL_GPIO_WritePin(GPIOA, R1_Pin|R2_Pin|R3_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, R4_Pin, GPIO_PIN_RESET); // Corrected to GPIOB

    for (int i=0; i<4; i++) {
        // Set only the current row HIGH
        if(i==0) HAL_GPIO_WritePin(GPIOA, R1_Pin, GPIO_PIN_SET);
        else if(i==1) HAL_GPIO_WritePin(GPIOA, R2_Pin, GPIO_PIN_SET);
        else if(i==2) HAL_GPIO_WritePin(GPIOA, R3_Pin, GPIO_PIN_SET);
        else if(i==3) HAL_GPIO_WritePin(GPIOB, R4_Pin, GPIO_PIN_SET); // Corrected to GPIOB

        HAL_Delay(10); // Stabilize

        // Scan Columns
        if (HAL_GPIO_ReadPin(GPIOC, C1_Pin)) {
            while(HAL_GPIO_ReadPin(GPIOC, C1_Pin));
            return keys[i][0];
        }
        if (HAL_GPIO_ReadPin(GPIOC, C2_Pin)) {
            while(HAL_GPIO_ReadPin(GPIOC, C2_Pin));
            return keys[i][1];
        }
        if (HAL_GPIO_ReadPin(GPIOC, C3_Pin)) {
            while(HAL_GPIO_ReadPin(GPIOC, C3_Pin));
            return keys[i][2];
        }
        if (HAL_GPIO_ReadPin(GPIOC, C4_Pin)) {
            while(HAL_GPIO_ReadPin(GPIOC, C4_Pin));
            return keys[i][3];
        }

        // Set row back to LOW
        if(i==0) HAL_GPIO_WritePin(GPIOA, R1_Pin, GPIO_PIN_RESET);
        else if(i==1) HAL_GPIO_WritePin(GPIOA, R2_Pin, GPIO_PIN_RESET);
        else if(i==2) HAL_GPIO_WritePin(GPIOA, R3_Pin, GPIO_PIN_RESET);
        else if(i==3) HAL_GPIO_WritePin(GPIOB, R4_Pin, GPIO_PIN_RESET); // Corrected to GPIOB
    }
    return 0;
}
