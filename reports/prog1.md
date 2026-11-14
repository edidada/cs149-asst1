# CS149 Assignment 1 Program 1

基线05e602d3445123eab76ae1d0f81c370c34441e13；要求见原README Program 1。连续分块以height*id/n划分，包含不可整除余行；默认循环分行row=id+k*n，无线程间同步，各线程写不重叠行。MANDELBROT_POLICY=block可复现初始分块；MANDELBROT_TIMING=1在join后打印每线程计算耗时，计时区不包含打印。

CI在两个原视图、两种策略和1/2/3/4/5/6/7/8/16/32线程下使用原串行验证及PPM逐字节比较。尚未验收，待远端运行和独立小尺寸/余行检查。需后续汇总加速图与负载解释。GitHub共享runner不是规定的Stanford myth四核机器，不能将其加速作为7–8倍目标证明。Program2–6尚未实现，不能声称整个Assignment1完成。本地不编译运行，无新增Python源文件。
