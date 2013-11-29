// JavaScript Document
/*window.addEventListener("load",windowLoaded,false);

function windowLoaded(){
	var button = document.getElementById("button");
	button.addEventListener("keydown",Send,false);
	button.addEventListener("click",Send,false);
		
	function Send(){
		var a = document.getElementById("a").value;
		var b = document.getElementById("b").value;
		console.log("volle nummber = " + isFullNumber(a));
		console.log("Natuurlijke nummer = " + isNaturalNumber(a));
		console.log("deelbaarheid nummer =" + isDelerVan(a,b));
		console.log("de delers zijn = " , a , ":", delers(a).toString());
		/*if(e.keyCode == 13){
			var a = document.getElementById("a").value;
			console.log("volle nummber = " + isFullNumber(a));
			console.log("Natuurlijke nummer = " + isNaturalNumber(a));	
			console.log("deelbaarheid nummer =" + isDelerVan(a,b));
		}
	}
}*/

function isNaturalNumber(a){	
	var answer = false;
	if(isFullNumber(a) && Math.abs(a) == a){
		answer = true;	
	}
	
	return answer;
	
}
function isFullNumber(a){	
	var answer = false;
	if(a%1 == 0){
		answer = true;	
	}
	
	return answer;
}
function isDelerVan(deeltal,deler){
	var answer = false
	if(isFullNumber(deler / deeltal)){
		answer = true;
	}
	return answer	
}
function delers(a){
	var answer = new Array();
	if(isFullNumber(a) && a > 1){
		for(var i = 1; i <= a ;i++){
			if(isDelerVan(i,a)){
				answer.push(i);
			}
		}
		
	}
	
	return answer;	
}
function primeNrArray(maxNum) {
	answ = new Array();

	for (var i=0; i < maxNum; i++) {
		if (delers(i).length == 2) {
			answ.push(i);
		}
	}

	return answ;
}
