#include "MPU.h"

/**
 * @brief Cấu hình một vùng nhớ thành Read-Only dùng thanh ghi trực tiếp
 */
void MPU_Init_ReadOnly_Example(uint32_t base_addr) {
    // 1. Kiểm tra xem chip có hỗ trợ MPU không (Đọc thanh ghi TYPE)
    if (MPU_TYPE == 0) return;

    // 2. Tạm dừng MPU trước khi cấu hình để tránh lỗi treo chip
    MPU_CTRL = 0;

    // 3. Chọn vùng nhớ số 0 (Cortex-M3 thường có 8 vùng từ 0-7)
    MPU_RNR = 0;

    // 4. Thiết lập địa chỉ gốc cho vùng 0
    // Bit 4 (VALID) = 1 để cập nhật địa chỉ ngay cho vùng đã chọn ở RNR
    MPU_RBAR = (base_addr & 0xFFFFFFE0) | (1 << 4) | 0;

    // 5. Thiết lập thuộc tính: 
    // - AP = Read Only (0x06)
    // - Size = 256 Bytes
    // - Enable = 1
    MPU_RASR = AP_READ_ONLY | MPU_SIZE_256B | MPU_REGION_ENABLE;

    // 6. Kích hoạt MemManage Fault để CPU nhảy vào handler khi có vi phạm
    SCB_SHCSR |= MEMFAULTENA_BIT;

    // 7. Bật MPU
    // PRIVDEFENA = 1 cực kỳ quan trọng: Nó giúp các vùng nhớ khác (như Flash chứa code)
    // vẫn hoạt động theo mặc định. Nếu không bật, chip sẽ lock ngay lập tức.
    MPU_CTRL = MPU_CTRL_PRIVDEFENA | MPU_CTRL_ENABLE;
}

/**
 * @brief Tắt MPU
 */
void MPU_Disable(void) {
    MPU_CTRL = 0;
}