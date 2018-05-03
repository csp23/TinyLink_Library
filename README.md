# TinyLink
[TinyLink](http://tinylink.emnets.org)是一个物联网应用快速开发平台。开发者编写并提交硬件平台无关的应用代码，系统会自动生成硬件解决方案和对应硬件平台的可执行文件。采用top-down的开发流程，大大加快了物联网应用的开发速度。目前，TinyLink共支持五款硬件平台，包括Arduino UNO、LinkIT One、BeagleBone Black、Raspberry Pi和Tiny BLE，支持100多种传感器，包括DHT11、SDS018、Grove UART WiFi、Grove Light等。

**自顶向下**
- 开发者先编写物联网应用的代码，并上传至服务器。TinyLink系统在综合考虑各种硬件限制条件的基础上，自动给出硬件选型的建议，并将应用代码自动交叉编译成硬件匹配的目标代码。

**快速开发**
- 开发者只需用TinyLink API编写应用代码，然后根据系统生成的硬件连接图即可组装成硬件平台，并一键烧写系统生成的目标代码，即可完成物联网应用。这大大加速了物联网应用的开发。

**自动生成**
- 开发者上传代码后，系统对代码进行自动分析，自动给出最合适的硬件选型及相似的硬件选型建议。
- 系统会自动生成对应的硬件配置的目标代码，并提供一键自动烧写工具。

**硬件无关**
- 开发者无需学习底层硬件的相关知识，只需专注于物联网应用软件的开发。
- TinyLink系统会根据代码生成最合适的硬件配置，同时满足开发者的应用需求和硬件组件之间的兼容性要求。

# TinyLink Library
TinyLink软件库包括了目前支持的所有开发板和传感器，目录结构如下：

|TinyLink library root |平台名称|功能名称|模块名称|源文件|
|----------------------|:--------:|:--------:|:--------:|-------:|
|TinyLink library root |Arduino|TL_TEMPERATURE|DHT11|DHT11_Temperature_Arduino_UNO.h DHT11_Temperature_Arduino_UNO.cpp|
