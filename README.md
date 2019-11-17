# HTISIC_MK66F18 底层驱动库


## 1. 简介

HITSIC_MK66F18是哈工大智能车创新俱乐部NXP MK66单片机的底层。该项目主要用于维护底层文件的更新。

### 1.1. 目录说明

/HITSIC_MK66F18_IAR 是IAR底层主目录，包含一个IAR EWARM工程。当前工具链版本是IAR EWARM

 8.32.4。根目录下各文件夹作用如下：

| 目录                                | 说明           |
| ----------------------------------- | -------------- |
| /HITSIC_MK66F18_IAR/CMSIS_x.x.x     | CMSIS库目录    |
| /HITSIC_MK66F18_IAR/boards          | 项目目录       |
| /HITSIC_MK66F18_IAR/devices/MK66F18 | MK66官方库     |
| /HITSIC_MK66F18_IAR/components      | MK66官方组件   |
| /HITSIC_MK66F18_IAR/middleware      | MK66官方中间件 |
| /HITSIC_MK66F18_IAR/HITSIC          | HITSIC组件库   |

其中，在 /HITSIC_MK66F18_IAR/boards 目录下是子项目目录，其中的每个文件夹都是一个独立的IAR工程，它们共用外部的所有库。这些项目文件夹互相独立，可以自由地复制、删除、重命名，都不会影响工程的完整性。


## 2. 文档





## 3. 许可

采用Apache 2.0协议。细节请阅读项目中LICENCE文件内容。


