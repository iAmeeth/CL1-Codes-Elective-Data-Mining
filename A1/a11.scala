import scala.io.StdIn.{readInt}

object BinarySearch{	

	def main(args:Array[String]){
		println("Enter number of elements");
		val n=readInt();
		var arr1=new Array[Int](n);
		for(i <-0 until n)
		{
			arr1(i)=readInt();	
		}

		val arr = arr1.sorted
		println("Enter value to find...");
		var key=readInt();

		Search(arr,0,arr.length-1,key);
		
}


def Search(arr:Array[Int],l:Int,r:Int,key:Int){
	var bottom=l;
	var top=r;
	var mid=(bottom+top)/2;

	while((key!=arr(mid)) && (bottom<=top))
	{
		if(key>arr(mid))
		{
			bottom=mid+1;	
		}
		else
		{
			top=mid-1;
		}
		mid=(bottom+top)/2;
	}		

	if(arr(mid)==key)
	{
	println("Element found at position"+(mid+1));
	return;
	}

	else
	{
	println("Element not found");
	return;
	}
	}
}
