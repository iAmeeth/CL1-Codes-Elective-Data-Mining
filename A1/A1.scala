import scala.annotation.tailrec
import scala.io
object Binary
{

	def main(string:Array[String])=
	{

	println("Enter Number of elements to be sorted");
	val num=readInt();
	var arr1=new Array[Int](num);

	println("Enter Numbers");
	for(i <-0 until num)
	{
	arr1(i)= readInt();
	}

	val l = arr1.sorted;

	println("Enter Key to be searched");
	val key=readInt();


	println("Output\n");
	println(binarySearch(key,l));
	}

	def binarySearch(key:Int,l:Array[Int]) =
	{

	@tailrec
	def recursive(low:Int,high:Int):Integer =(low+high)/2 match
		{
		case _ if(low>high) => return(-1); 
		case mid if(key<l(mid)) => recursive(low,mid-1);
		case mid if(key>l(mid)) => recursive(mid+1,high);
		case mid if(key==l(mid)) => return mid+1;	
		}

		recursive(0,l.size);
	}

}



