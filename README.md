# TA_course_demo
本代码用于清华大学《核能物理与超算》课程的助教课堂演示，主要内容有：
- `MPI`演示
   * **src/mpi_round.c** 在`n`个进程之间，轮流传递数据，即进程`0`传`0`给进程`1`，
   并自进程`n-1`接收`n-1`，进程`1`传`1`给进程`2`，并自进程`0`接收`0`，以此类推
   * **src/mpi_sum.c** 使用多个进程计算`1~n`的和（不使用高斯公式），并统计计算时间
- `OpenMP`演示
   * **src/omp_with_lock** 使用多个线程对同一个值进行累加，在加锁的情况下，分析
   计算结果与预期结果是否相同
   * **src/omp_without_lock** 使用多个线程对同一个值进行累加，在不加锁的情况下，
   分析计算结果与预期结果是否相同
- `pthread`演示，与`OpenMP`演示类似，体现`OpenMP`相对`pthread`在大部分应用场景下
使用的方便性

# 使用方法
## 编译
1. 建议使用`Linux`系统，如`Ubuntu`、`Manjaro`、`deepin`等，或`Mac OS`，在`Windows`
上建议使用`WSL`子系统
2. 预先安装好`MPI`相关库，以`Ubuntu`为例：
```bash
sudo apt-get update
sudo apt-get install mpich
```
3. `git clone`或者直接下载本仓库代码
4. 进入到`scripts`，使用：
```bash
./compile.sh
```

## 运行
在自己的机器上的`scripts`文件夹中，运行命令分别如下：

使用`4`个进程并行运行`mpi_round`
```bash
mpirun -n 4 ./mpi_round
```

使用`6`个进程并行运行`mpi_sum`，累加`1`到`100000`
```bash
mpirun -n 6 ./mpi_sum 100000
```

使用`4`个线程并行运行`omp_with_lock`，每个线程累加`10000`次，共计`40000`次
```bash
./omp_with_lock 4 10000
```

使用`4`个线程并行运行`omp_without_lock`，每个线程累加`10000`次，共计`40000`次
```bash
./omp_without_lock 4 10000
```

使用`4`个线程并行运行`pthread_with_lock`，每个线程累加`10000`次，共计`40000`次
```bash
./pthread_with_lock 4 10000
```

使用`4`个线程并行运行`pthread_without_lock`，每个线程累加`10000`次，共计`40000`次
```bash
./pthread_without_lock 4 10000
```
