/*    快速排序模板函数       */


/*    使用方法:
 *    1. qsort(  迭代器begin或数组开头  ,  元素数量n    ,    比较函数);
 *    2. qsort(  迭代器begin或数组开头  ,  迭代器end或指向数组末尾的下一个元素的指针  ,  比较函数);
 *
 *    适用于:
 *    int x[100] , int x[a]  , int x[a][100]  ,  类数组
 *    vector deque list
 *    
 *    不适用于:
 *    int x[a][b]
 *
 *    其中a,b为变量
 *  */

/*
 *    比较函数:
 *    int compare(const type &a,const type &b)
 *    {
 *      ...
 *    }
 *    返回值<0:a在b左边
 *    返回值>0:a在b右边
 *    返回值=0:a与b位置关系不确定
 * */

/*    注意事项:
 *    swap函数与std::swap重名，请不要使用using namespace std; 
 *    或者将修改源码将swap换个名字
 * */


#include <stdlib.h>
template<typename T>
char swap(T &a,T &b)
{
    char *temp1=(char *)&a,*temp2=(char *)&b;
    for(long unsigned i=0;i<sizeof(T);i++)
    {
        *temp1^=*temp2;
        *temp2^=*temp1;
        *temp1^=*temp2;
        temp1++;
        temp2++;
    }
    return 1;
}
template<typename T,typename T2>
char qsort(const T begin,const int n,int (*comp)(const T2& a,const T2& b));
template<typename T,typename T2>
char qsort(const T begin,const T fake_end,int (*comp)(const T2& a,const T2& b));
template<typename T,typename T2>
char qsort(const T begin,const T end,int n,int (*comp)(const T2& a,const T2& b));
template<typename T,typename T2>
char qsort(const T begin,const int n,int (*comp)(const T2& a,const T2& b))
{
    if(n>2)
    {
        T end=begin;
        for(int i=0,max=n/2;i<max;i++)
        {
            end++;
        }
        T2 *jizhun=(T2 *)malloc(sizeof(T2));
        memcpy(jizhun,&(*end),sizeof(T2));
        for(int i=0,max=n-n/2-1;i<max;i++)
        {
            end++;
        }
        T i=begin,j=end;
        int i_c=n,j_c=n;
        int temp1,temp2;
        do
        {
            while((temp1=comp(*i,*jizhun))<0)
            {
                i++;
                i_c--;
            }
            while((temp2=comp(*j,*jizhun))>0)
            {
                j--;
                j_c--;
            }
            if(i>j)
            {
                break;
            }
            else if(i==j)
            {
                i++;
                i_c--;
                j--;
                j_c--;
                break;
            }
            else if(temp1==temp2)
            {
                i++;
                i_c--;
                j--;
                j_c--;
            }
            else
            {
                swap(*i,*j);
                i++;
                i_c--;
                j--;
                j_c--;
            }
        }
        while(i<=j);
        free(jizhun);
        qsort(begin,j,j_c,comp);
        qsort(i,end,i_c,comp);
    }
    else if(2==n)
    {
        T end=begin;
        end++;
        if(comp(*begin,*end)>0)
        {
            swap(*begin,*end);
        }
    }
    return 1;
}
template<typename T,typename T2>
char qsort(const T begin,T end,int (*comp)(const T2& a,const T2& b))
{
    end--;                   //fake_end to true end
    int n=1;
    T2 *jizhun;
    {
        T i=begin,j=end;
        do
        {
            i++;
            n++;
            if(i==j)
            {
                break;
            }
            j--;
            n++;
        }
        while(i!=j);
        if(n>2)
        {
            jizhun=(T2 *)malloc(sizeof(T2));
            memcpy(jizhun,&(*i),sizeof(T2));
            goto label1;
        }
        else if(n==2)
        {
            goto label2;
        }
        else
        {
            return 1;
        }
    }
    {
label1:
        T i=begin,j=end;
        int i_c=n,j_c=n;
        int temp1,temp2;
        do
        {
            while((temp1=comp(*i,*jizhun))<0)
            {
                i++;
                i_c--;
            }
            while((temp2=comp(*j,*jizhun))>0)
            {
                j--;
                j_c--;
            }
            if(i>j)
            {
                break;
            }
            else if(i==j)
            {
                i++;
                i_c--;
                j--;
                j_c--;
                break;
            }
            else if(temp1==temp2)
            {
                i++;
                i_c--;
                j--;
                j_c--;
            }
            else
            {
                swap(*i,*j);
                i++;
                i_c--;
                j--;
                j_c--;
            }
        }
        while(i<=j);
        free(jizhun);
        //printf("j_c=%d i_c=%d i-begin=%ld j-begin=%ld\n",j_c,i_c,i-begin,j-begin);
        qsort(begin,j,j_c,comp);
        qsort(i,end,i_c,comp);
        return 1;
    }
    {
label2:
        if(comp(*begin,*end)>0)
        {
            swap(*begin,*end);
        }
        return 1;
    }
}
template<typename T,typename T2>
char qsort(const T begin,const T end,const int n,int (*comp)(const T2& a,const T2& b))
{
    if(n>2)
    {
        T2 *jizhun=(T2 *)malloc(sizeof(T2));
        {
            T j=end;
            for(int i=0,max=n-n/2-1;i<max;i++)
            {
                j--;
            }
            memcpy(jizhun,&(*j),sizeof(T2));
        }
        T i=begin,j=end;
        int i_c=n,j_c=n;
        int temp1,temp2;
        do
        {
            while((temp1=comp(*i,*jizhun))<0)
            {
                i++;
                i_c--;
            }
            while((temp2=comp(*j,*jizhun))>0)
            {
                j--;
                j_c--;
            }
            if(i>j)
            {
                break;
            }
            else if(i==j)
            {
                i++;
                i_c--;
                j--;
                j_c--;
                break;
            }
            else if(temp1==temp2)
            {
                i++;
                i_c--;
                j--;
                j_c--;
            }
            else
            {
                swap(*i,*j);
                i++;
                i_c--;
                j--;
                j_c--;
            }
        }
        while(i<=j);
        free(jizhun);
        //printf("j_c=%d i_c=%d i-begin=%ld j-begin=%ld\n",j_c,i_c,i-begin,j-begin);
        qsort(begin,j,j_c,comp);
        qsort(i,end,i_c,comp);
    }
    else if(2==n)
    {
        if(comp(*begin,*end)>0)
        {
            swap(*begin,*end);
        }
    }
    return 1;
}