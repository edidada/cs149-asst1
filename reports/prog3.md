# CS149 Assignment1 Program3

基线05e602d3445123eab76ae1d0f81c370c34441e13。只修改mandelbrot_ispc_withtasks：由两任务改为每行一任务，rowsPerTask=1、launch[height]。原task函数不改，避免固定两任务的负载不均并覆盖奇数高度。原SIMD foreach与串行/main/任务运行时不改，保留disable-fma确保算术一致。

CI固定ISPC1.28.1与官方release SHA256，两个原视图逐像素及PPM字节比较，25组独立小宽度/奇高度/哨兵检查。待远端结果和性能分析；每行策略未声称全尺寸最优或完成任务数调优测量。GitHub runner非myth，32倍指定环境目标未验证。本地不编译运行，无新增Python源文件；Program4–6未实现，整作业未完成。
