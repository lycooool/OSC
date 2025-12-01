# lab 1
### linker script (.ld)
* 把輸入檔 (object file, .o) 的 section 重新分類與排列，產生輸出檔 ( Executable and Linkable Format .elf) 
* 用來決定
    * `.text` 程式碼 (code)
    * `.data` 有初始化的 global/static 變數
    * `.bss` 未初始化的 global/static 變數
    * `.rodata` 常數資料
    
    在實體記憶體的哪些位址上。 
* 樹莓派把 img load 到 0x80000 並開始執行，因此各 section 從 0x80000 開始擺放
* PHDRS (Program Header Table)，）用來定義 ELF 的Segment 。每個 segment 可以包含多個 section，並且可以為每個 segment 設定記憶體權限（R/W/X）。
* 此 lab linker scrip 可參考 [linder.ld](src/linker.ld)
### MMIO (Memory-Mapped I/O )
* 樹莓派透過 MMIO 存取設備
* CPU load/store 特定 physical address 的值時，其實是在 load 周邊設備的 register
* 相關腳位定義可參考 [BCM2837-ARM-Peripherals.pdf](https://github.com/ec-enggshivam/CPPWork/blob/master/Raspberry%20Pi/BCM2837-ARM-Peripherals.pdf)
### uart
* uart 是一種一次傳送 1 byte 的通訊協定，可用來當作樹莓派與主機溝通的橋樑
* 樹莓派的 GPIO 有提供 uart 等替代功能，可透過設定 GPIO 腳位來使用
* miniuart  設定可參考 [mini_uart.c](src/mini_uart.c)
### 簡單可互動的 shell
* 可參考 [shell.c](src/shell.c)
### mailbox
* 樹莓派中 CPU 和 GPU 的通訊機制，也可用來設定某些周邊設備
* 可參考 [Mailboxes](https://github.com/raspberrypi/firmware/wiki/Mailboxes), [Mailbox-property-interface](https://github.com/raspberrypi/firmware/wiki/Mailbox-property-interface) 
* 由 mailbox register, channel, message 三部分組成
    * mailbox register 可透過 MMIO 存取 (硬體介面)
    * 共有 16 channel 控制不同功能
    * message 放在 message buffer (16 byte aligned)
    * message buffer 可同時有多個 request
    * gpu 回覆會直接寫進 message buffer
    * buffer 結構參考 [Mailbox-property-interface](https://github.com/raspberrypi/firmware/wiki/Mailbox-property-interface) 
* mailbox call 流程
    1. 取 message buffer address 和 channel 組成 32 bit mailbox 信封 (最低四位放 channel)
    2. 等 mailbox not full 時寫入 mail box (將 mailbox 信封存到特定 register)
    3. 等待 GPU 回覆 (讀特定 register)，並確認回覆的是否為傳送的訊息 (讀特定 register)，是的話讀取 (讀 message buffer)
### 讀取硬體資訊
* 可參考[mailbox.c](src/mailbox.c)
    

