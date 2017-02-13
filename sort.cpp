
#include"stdio.h"

//插入排序
void InsertSort(int A[],int n);
void InsertSort_SplitHalf(int A[],int n);
void ShellSort(int A[],int n);

//交换排序
void BubbleSort(int A[],int n);
void QuickSort(int A[],int low,int high);

//选择排序
void SelectSort(int A[],int n);
void HeapSort(int A[],int len);

//归并排序
void MergSort(int A[],int low,int high);
int main()
{
    int test[11];
    test[0]=0;

    for(int i=1;i<11;++i)
        scanf("%d",&test[i]);

    //InsertSort(test,10);
    //InsertSort_SplitHalf(test,10);
    //ShellSort(test,10);
    //BubbleSort(test,11);
    //QuickSort(test,0,10);
    //SelectSort(test,11);
    //HeapSort(test,11);
    MergSort(test,0,10);
    for(int j=0;j<11;++j)
        printf("%d ",test[j]);

    printf("\n");

    return 0;
}

/**
哨兵作用说明：引入哨兵的目的是可以使得在for循环内不必去判断数组是否会越界，
可以避免不必要的判断语句。
**/
//直接插入排序
void InsertSort(int A[],int n){
   int i,j;
   for(i=2;i<=n;++i)               //依次将A[2]-A[n]插入到前面已排序序列
    {
      if(A[i]<A[i-1]){             //若A[i]小于A[i-1],则需要将A[i]插入到前面已排好序的有序表中
        A[0]=A[i];                //复制为哨兵，A[0]不存放元素
        for(j=i-1;A[0]<A[j];--j)  //从后往前查找带插入位置（哨兵例子）
        {
            A[j+1]=A[j];
        }
        A[j+1]=A[0];              //复制到插入位置
      }

    }
}
//折半插入排序
void InsertSort_SplitHalf(int A[],int n){

    int i,j,low,high,mid;

    for(i=2;i<=n;++i){

        A[0]=A[i];
        low=1;
        high=i-1;

        while(low<=high){
            mid=(low+high)/2;
            if(A[mid]>A[0])
              high=mid-1;
            else
              low=mid+1;
        }

        for(j=i-1;j>=high+1;--j)
           A[j+1]=A[j];
        A[high+1]=A[0];        //插入的位置为high+1

    }
}
//希尔排序
void ShellSort(int A[],int n){
  //对顺序表做希尔插入排序，本算法和直接插入排序相比，作了一下修改：
  //1、前后记录位置的增量是dk，不是1
  //2、A[0]只是暂存元素，不是哨兵，当j<0时，插入位置已到
  int i,j,dk;
  for(dk=n/2;dk>=1;dk=dk/2){   //dk从n/2一直减半至1
     for(i=dk+1;i<=n;++i){
        if(A[i]<A[i-dk]){
            A[0]=A[i];
            for(j=i-dk;j>0&&A[0]<A[j];j-=dk)  //注意A[0]并没有充当哨兵的作用
                A[j+dk]=A[j];
            A[j+dk]=A[0];
        }
     }

  }
}

//冒泡排序
void BubbleSort(int A[],int n){

    int i,j;
    bool flag;              //表示本趟冒泡是否发生交换的标志
   for(i=0;i<n-1;++i){
     flag=false;
     for(j=n-1;j>1;j--)
     if(A[j-1]>A[j]){
        int temp=A[j-1];
        A[j-1]=A[j];
        A[j]=temp;
        flag=true;
     }

     if(flag==false) return;
   }
}

//划分操作
int Partition(int A[],int low,int high){
  int pivot=A[low];   //将当前表中的第一个元素设为枢轴值，对表进行划分
  while(low<high){
     while(low<high&&A[high]>=pivot) --high;
     A[low]=A[high];      //将比枢轴值小的元素移到左端
     while(low<high&&A[low]<=pivot) ++low;
     A[high]=A[low];      //将比枢轴值大的元素移到右端
  }
  A[low]=pivot;
  return low;
}
//快速排序
void QuickSort(int A[],int low,int high){
    if(low<high){                             //递归跳出条件
        int pivotpos=Partition(A,low,high);   //划分
        QuickSort(A,low,pivotpos-1);          //分别对两个子表进行递归操作
        QuickSort(A,pivotpos+1,high);
    }
}

//简单选择排序
void SelectSort(int A[],int n){
   int i,j,Min;
   for(i=0;i<n-1;i++){
     Min=i;
     for(j=i+1;j<n;j++)
        if(A[j]<A[Min]) Min=j;   //更新最小元素位置
     if(Min!=i){
        int temp=A[i];
        A[i]=A[Min];
        A[Min]=temp;
     }
   }
}

//向下调整堆
void AdjustDown(int A[],int k,int len){
   int i;
   A[0]=A[k];
   for(i=2*k;i<=len;i*=2){          //沿较大的子结点向下筛选
       if(i<len&&A[i]<A[i+1]) ++i;  //取较大值子结点的下标
       if(A[0]>=A[i]) break;
        else{
            A[k]=A[i];              //将A[i]调整到双亲结点上
            k=i;                    //修改k值，以便继续向下筛选
        }
   }//for
   A[k]=A[0];                       //被筛选结点的值放入最终位置
}
//建立大根堆
void BuildMaxHeap(int A[],int len){
    for(int i=len/2;i>0;i--){
        AdjustDown(A,i,len);
    }

}
//堆排序（堆是由数组下标来建立完全二叉树的，下标从1开始故数组下标为0的元素不进行排序）
void HeapSort(int A[],int len){

     BuildMaxHeap(A,len);       //初始建堆
     for(int i=len;i>1;i--){        //n-1趟的交换和建堆过程
        int temp=A[i];
        A[i]=A[1];
        A[1]=temp;              //输出栈顶元素（和栈底元素交换）
        AdjustDown(A,1,i-1);   //整理，将剩余的i-1个元素整理成堆
     } //for
}


//对两个表进行归并
void Merge(int A[],int low,int mid,int high){

  int i,j,B[50],k;

  for( k=low;k<=high;++k)                   //将A中所有元素复制到B中
    B[k]=A[k];

  for(i=low,j=mid+1,k=i;i<=mid&&j<=high;++k){
     if(B[i]<=B[j])                           //比较B的左右两段中的元素
        A[k]=B[i++];                          //将较小值赋值到A中
     else
        A[k]=B[j++];
  }//for
  while(i<=mid) A[k++]=B[i++];                //若第一个表未检测完，复制
  while(j<=high) A[k++]=B[j++];               //若第二个表未检测完，复制

}
//归并排序
void MergSort(int A[],int low,int high){
    if(low<high){                            //从中间划分两个字序列
        int mid=(low+high)/2;
        MergSort(A,low,mid);                 //对左侧子序列进行递归排序
        MergSort(A,mid+1,high);              //队友侧子序列进行递归排序
        Merge(A,low,mid,high);               //归并
    }//if
}



















