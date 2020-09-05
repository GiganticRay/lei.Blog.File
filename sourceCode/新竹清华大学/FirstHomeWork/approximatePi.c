#include <stdio.h>
#include "mpi.h"
#include <math.h>

double f(double x);

//返回函数值，因为调用次数很多，这里写成inline提高效率
double f(double x) {
	return sqrt(1 - pow(x, 2));
}
 
int main(int argc, char *argv[]) {
	double pi, width, sum, x, startime, endtime;
	int size, myid;
	long long n;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	printf("size = %d \n", size);
 
	n = 0;
	// 以rank=0的 process 作为root
	if(0 == myid) {
		printf("Please enter n: \n");
		scanf("%lld", &n);
		startime = MPI_Wtime();
	}
	// broadcasts a message from the process with rank root to all other process of the group
	MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);  	//将n广播到所有进程中
	width = 1.0/(double)n;							//每个矩形块的宽
	sum = 0.0;        
	for(int i=myid+1; i<=n; i+=size) {
		// -0.5 是梯形积分公式的那个中点	
		x = width*((double)i - 0.5);                //假设是4个进程、则进程0:1,5,9,...  进程1:2,6,10,... 进程2:3,7,11,... 进程3:4,8,12,...
		sum = sum + 4 * width * f(x);				//每个进程计算的矩形面积之和
	}          
						   

	// reduces values on all processes within a group
	MPI_Reduce(&sum, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);  //利用归约操作(MPI_SUM)将所有进程的sum累加到root进程(0)的sum当中得到结果
	if(myid == 0) {
		endtime = MPI_Wtime();
		printf("用时:%f\n", endtime-startime);
		printf("%0.15f\n", pi);
	}
	MPI_Finalize();
}