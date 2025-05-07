import java.util.Scanner;
public class heap_16{
	static void heapify(int[] arr,int size ,int i){
		int largest=i;
		int left=2*i+1;
		int right=2*i+2;
		if(left<size && arr[left]>arr[largest]){
			largest=left;
		}
		if(right<size && arr[right]>arr[largest]){
			largest=right;
		}
		if(largest!=i){
			int temp=arr[i];
			arr[i]=arr[largest];
			arr[largest]=temp;
			heapify(arr,size,largest);
		}
	}
	static void make_heap(int[] arr,int size){
		for(int i=(size/2)-1;i>=0;i--){
			heapify(arr,size,i);
		}
	}
	static void heap_sort(int[] arr,int size){
		make_heap(arr,size);
		for(int i=size-1;i>=0;i--){
			int temp=arr[0];
			arr[0]=arr[i];
			arr[i]=temp;
			heapify(arr,i,0);
		}
	}
	public static void main(String args[]){
		Scanner s=new Scanner(System.in);
		System.out.print("Enter the size of array : ");
		int a=s.nextInt();
		int[] arr=new int[a];
		System.out.println("Enter the elements of array : ");
		for(int i=0;i<a;i++){
			arr[i]=s.nextInt();
		}
		heap_sort(arr,a);
		System.out.print("Sorted array is : ");
		for(int i=0;i<a;i++){
			System.out.print(arr[i]+" ");
		}
		s.close();
	}
}