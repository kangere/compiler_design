var x: int = 56;
var id: float = 5.6;

fun foo(x : int, y : int) -> int {
	
	if(x > y){
		return x;
	} else {
	 y = 25;
	}
	
	return x + y;
}