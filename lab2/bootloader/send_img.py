# import os
import struct
import serial
import time

# === 1️⃣ 準備要傳送的映像檔 ===
IMG_PATH = 'kernel8.img'

with open(IMG_PATH, 'rb') as f:
    kernel_data = f.read()

checksum = sum(kernel_data) & 0xFFFFFFFF
size = len(kernel_data)

print(f"📦 Image: {IMG_PATH}")
print(f"  Size: {size} bytes")
print(f"  Checksum: {checksum:#010x}")

# === 2️⃣ 準備封包 header ===
header = struct.pack('<III',
    0x544F4F42,   # 'BOOT' in little-endian
    size,         # image size (bytes)
    checksum      # checksum
)

packet = header + kernel_data

# === 3️⃣ 指定 QEMU 的虛擬 UART 埠 ===
PORT = "/dev/pts/2"   # ← 改成 QEMU 顯示的那個
#PORT = "/dev/ttyUSB0" 
BAUD = 115200
TIMEOUT = 0.1

# === 4️⃣ 連線並傳送 ===
ser = serial.Serial(PORT, BAUD, timeout=TIMEOUT)
print(f"🔌 Connected to {PORT}")

# 傳送映像
ser.write(packet)
print(f"✅ Sent {len(packet)} bytes.")

# === 5️⃣ 等待 bootloader/kernel 回傳訊息 ===
print("📡 Reading UART output... (Ctrl+C to stop)\n")
try:
    while True:
        data = ser.read(ser.in_waiting or 1)
        if data:
            print(data.decode(errors="ignore"), end="")
        time.sleep(0.05)
except KeyboardInterrupt:
    print("\n🛑 Stopped reading.")
finally:
    ser.close()