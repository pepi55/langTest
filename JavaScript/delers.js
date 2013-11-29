// JavaScript Document
window.addEventListener("load",windowLoaded,false);

function windowLoaded(){
	var feedback = document.getElementById("feedback");
	//feedback.innerHTML = "";
		for(var i = 1;i<=1000; i++){
			mijnDelers = delers(i);
			//feedback.innerHTML += i + "," + mijnDelers.length + ":" + MijnDelers + "<br>";
				var row=feedback.insertRow(0); 
			   var cell1=row.insertCell(0);
			   var cell2=row.insertCell(1);
			   var cell3=row.insertCell(2);
			   cell1.innerHTML= i;
			   cell2.innerHTML = mijnDelers.length;
			   cell3.innerHTML= mijnDelers;
			//cell1.innerHTML +=  MijnDelers ;
	}
}