#pragma once

#include "BluetoothA2DPSink.h"

#if A2DP_I2S_SUPPORT

#define RINGBUF_HIGHEST_WATER_LEVEL    (32 * 1024)
#define RINGBUF_PREFETCH_PERCENT        70

enum A2DPRingBufferMode : char {
    RINGBUFFER_MODE_PROCESSING,    /* ringbuffer is buffering incoming audio data, I2S is working */
    RINGBUFFER_MODE_PREFETCHING,   /* ringbuffer is buffering incoming audio data, I2S is waiting */
    RINGBUFFER_MODE_DROPPING       /* ringbuffer is not buffering (dropping) incoming audio data, I2S is working */
};

extern "C" void ccall_i2s_task_handler(void *arg);

/**
 * @brief The BluetoothA2DPSinkQueued is using a separate Task with an additinal Queue to write the I2S data.
 * application. 
 * @ingroup a2dp
 * @author Phil Schatzmann
 * @copyright Apache License Version 2
 */
class BluetoothA2DPSinkQueued : public BluetoothA2DPSink {
    /// task hander for i2s 
    friend void ccall_i2s_task_handler(void *arg);

    public:
        BluetoothA2DPSinkQueued() = default;

        /// Defines the stack size of the i2s task (in bytes)
        void set_i2s_stack_size(int size){
            i2s_stack_size = size;
        }

        /// Defines the ringbuffer size used by the i2s task (in bytes)
        void set_i2s_ringbuffer_size(int size){
            i2s_ringbuffer_size = size;
        }

        /// Audio starts to play when limit exeeded
        void set_i2s_ringbuffer_prefetch_percent(int percent){
            if (percent<0) return;
            if (percent>100) return;
            ringbuffer_prefetch_percent = percent; 
        }

        /// Defines the priority of the I2S task
        void set_i2s_task_priority(UBaseType_t prio){
            i2s_task_priority = prio;
        }

        void set_i2s_write_size_upto(size_t size){
            i2s_write_size_upto = size;
        }

        void set_i2s_ticks(int ticks){
            i2s_ticks = ticks;
        }

        virtual void i2s_task_handler(void *arg) override ;

    protected:
        xTaskHandle s_bt_i2s_task_handle = nullptr;  /* handle of I2S task */
        RingbufHandle_t s_ringbuf_i2s = nullptr;     /* handle of ringbuffer for I2S */
        SemaphoreHandle_t s_i2s_write_semaphore = nullptr;
        // I2S task
        int i2s_stack_size = 2048;
        int i2s_ringbuffer_size = RINGBUF_HIGHEST_WATER_LEVEL;
        UBaseType_t i2s_task_priority = task_priority;
        volatile A2DPRingBufferMode ringbuffer_mode = RINGBUFFER_MODE_PROCESSING;
        volatile bool is_starting = true;
        size_t i2s_write_size_upto = 240 * 6;
        int i2s_ticks = 20;
        int ringbuffer_prefetch_percent = RINGBUF_PREFETCH_PERCENT;


        void bt_i2s_task_start_up(void) override;
        void bt_i2s_task_shut_down(void) override;
        size_t write_audio(const uint8_t *data, size_t size) override;

        void set_i2s_active(bool active) override {
            BluetoothA2DPSink::set_i2s_active(active);
            if (active) {
                ringbuffer_mode = RINGBUFFER_MODE_PREFETCHING;
                is_starting = true;
            }
        }

        int i2s_ringbuffer_prefetch_size() {
            int bytes = i2s_ringbuffer_size * ringbuffer_prefetch_percent / 100;
            return (bytes / 4 * 4);
        }

};



#endif
