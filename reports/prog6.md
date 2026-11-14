# CS149 Program6 基线剖析

基线05e602d3445123eab76ae1d0f81c370c34441e13。当前只在允许的kmeansThread.cpp增加三阶段计时，stoppingConditionMet/接口/算法不改，尚未优化。远端合成100000×100/10簇输入用于识别热点，明确不替代官方800MB data.dat或PCA图/2.1x要求。官方数据需要Stanford账号，未获取，不伪造校内验证。先取得实际阶段耗时再决定仅并行化一个函数；原dist欧氏距离和收敛语义必须保持。本地不编译执行，无新增Python源文件。
