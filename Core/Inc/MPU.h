#ifndef MPU_M3_H
#define MPU_M3_H

#include <stdint.h>

// --- ĐỊA CHỈ CÁC THANH GHI MPU (Cấu trúc Cortex-M3) ---
#define MPU_BASE_ADDR       (0xE000ED90UL)

#define MPU_TYPE            (*(volatile uint32_t *)(MPU_BASE_ADDR + 0x00))
#define MPU_CTRL            (*(volatile uint32_t *)(MPU_BASE_ADDR + 0x04))
#define MPU_RNR             (*(volatile uint32_t *)(MPU_BASE_ADDR + 0x08))
#define MPU_RBAR            (*(volatile uint32_t *)(MPU_BASE_ADDR + 0x0C))
#define MPU_RASR            (*(volatile uint32_t *)(MPU_BASE_ADDR + 0x10))

// --- THANH GHI ĐIỀU KHIỂN NGẮT (SCB) ĐỂ BẬT MEMMANAGE FAULT ---
#define SCB_SHCSR           (*(volatile uint32_t *)(0xE000ED24UL))
#define MEMFAULTENA_BIT     (1 << 16)

// --- ĐỊNH NGHĨA CÁC THÔNG SỐ CƠ BẢN ---
#define MPU_REGION_ENABLE   (1UL << 0)
#define MPU_CTRL_ENABLE     (1UL << 0)
#define MPU_CTRL_PRIVDEFENA (1UL << 2) // Dùng bản đồ mặc định cho các vùng không cấu hình

// Access Permissions (AP)
// 0x03: Full Access (Read/Write)
// 0x06: Read Only (Chế độ Privileged và User đều chỉ được đọc)
#define AP_READ_ONLY        (0x06UL << 24)

// Kích thước vùng nhớ (Size = 2^(n+1))
// 0x07 = 2^(7+1) = 256 bytes
#define MPU_SIZE_256B       (0x07UL << 1)

// Hàm nguyên mẫu
void MPU_Init_ReadOnly_Example(uint32_t base_addr);
void MPU_Disable(void);

#endif