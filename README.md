# 使用随机化算法迭代计算等效电阻
这是我在电磁学小论文中做的一个项目，实现了一种通过随机的方法与大量的迭代计算电路中两点间等效电阻的算法。

## 如果你想引用本项目
你可以将 `rsim.h` 下载下来并放置到你的项目文件夹中，你也可以用其他语言复现这一段代码，但是如果你要将包含这段代码或复现代码的项目发布，请你注明原作者以及来源。

算法的主体为 `rsim.h` 中的 `rsim::calculate_resistance`，参数如下：
+ `u`：起始点；
+ `v`：终止点；
+ `get_neigh`：给定一个点、获取这个点所有相邻的点的函数（不能使用 lambda 函数）；
+ `progress_bar`：是否输出进度条，默认为 `false`；
+ `simu_timeout`：算法时间限制，单位 s，默认为 10.0；
+ `steps_limit`：单次游走步数限制，默认为 100000；
+ `num_threads`：线程数，默认为 256。

在 `examples` 文件夹中有几个例子，可以帮助你理解这个函数的使用方法。
